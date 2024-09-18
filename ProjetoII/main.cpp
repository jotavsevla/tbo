#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

#define MAX 10000000
#define DICIONARIO "/Users/jotavsevla/CLionProjects/tbo_2024_01/ProjetoII/arquivoTexto/Dicionário pt_BR.dic"

using namespace std;

// Estrutura para comparar distâncias entre palavras
struct ComparadorDistancia {
    bool operator()(const pair<string, int>& a, const pair<string, int>& b) {
        return a.second < b.second;
    }
};

// Protótipos das funções
string* ler_arquivo(const string& index);
string limpar_palavra(const string& palavra);
bool corresponde_com_wildcard(const string& texto, const string& pattern, size_t pos_texto);
bool kmp_wildcard(const string& text, const string& pattern);
bool kmp(const string& texto, const string& padrao);
vector<int> criar_tabela_falha(const string& padrao);
bool is_delimiter(char c);
string get_pattern();
string captura_palavra(const string& texto, size_t inicio, size_t tamanho_padrao);
bool is_vogal(char c);
bool com_wildcard(const string& pattern);
unordered_map<char, vector<string> > indexar_dicionario(const string& dicionario);
void encontrar_palavras_similares(const string& palavra, const unordered_map<char, vector<string> >& indice);
void encontrar_palavras_RS_adicional(const string& palavra, const unordered_map<char, vector<string> >& indice);

// Função principal
int main() {
    // Lê o arquivo do dicionário
    string* texto = ler_arquivo(DICIONARIO);
    if (texto == nullptr) {
        cerr << "Erro ao ler o arquivo do dicionário. Encerrando o programa." << endl;
        return 1;
    }
    // Indexa o dicionário para busca rápida
    unordered_map<char, vector<string> > indice = indexar_dicionario(*texto);

    string pattern;
    char modo;

    // Loop principal do programa
    while (true) {
        cout << "Escolha o modo de busca:" << endl;
        cout << "1 - Buscar palavra no dicionário" << endl;
        cout << "2 - Buscar sugestões para palavras erradas" << endl;
        cout << "S - Sair" << endl;
        cin >> modo;

        if (modo == 'S' || modo == 's') break;

        if (modo != '1' && modo != '2') {
            cout << "Opção inválida. Por favor, escolha 1, 2 ou S." << endl;
            continue;
        }

        pattern = get_pattern();
        if (pattern == "sair") break;

        if (modo == '1') {
            // Busca exata no dicionário
            bool encontrouPadrao = com_wildcard(pattern) ? kmp_wildcard(*texto, pattern) : kmp(*texto, pattern);
            if (!encontrouPadrao) {
                cout << "Palavra não encontrada no dicionário." << endl;
            }
        } else {
            // Busca sugestões para palavras erradas
            cout << "Buscando sugestões para a palavra..." << endl;
            encontrar_palavras_similares(pattern, indice);
            encontrar_palavras_RS_adicional(pattern, indice);
        }
    }

    delete texto;
    return 0;
}

// Lê o conteúdo do arquivo de dicionário
string* ler_arquivo(const string& index) {
    ifstream arquivo(index);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
        return nullptr;
    }
    auto* texto = new string();
    texto->reserve(MAX);
    string linha;
    while (getline(arquivo, linha)) {
        string palavraLimpa = limpar_palavra(linha);
        *texto += palavraLimpa + "\n";
    }
    arquivo.close();
    return texto;
}

// Remove caracteres indesejados e informações adicionais das palavras
string limpar_palavra(const string& palavra) {
    size_t posBarra = palavra.find('/');
    string limpa = (posBarra != string::npos) ? palavra.substr(0, posBarra) : palavra;
    limpa = regex_replace(limpa, regex("�"), "");
    return limpa;
}

// Implementa o algoritmo KMP com suporte a wildcards
bool kmp_wildcard(const string& texto, const string& pattern) {
    size_t n = texto.size();
    bool found = false;
    for (size_t i = 0; i < n; ++i) {
        if (corresponde_com_wildcard(texto, pattern, i)) {
            string palavraCompleta = captura_palavra(texto, i, pattern.size());
            cout << "Padrão encontrado na posição: " << i << " | Palavra completa: " << palavraCompleta << endl;
            found = true;
        }
    }
    return found;
}

// Verifica se um padrão com wildcard corresponde a uma posição no texto
bool corresponde_com_wildcard(const string& texto, const string& pattern, size_t pos_texto) {
    size_t n = texto.size();
    size_t m = pattern.size();
    size_t i = pos_texto;
    size_t j = 0;
    if (n - pos_texto < m) return false;
    while (i < n && j < m) {
        if (pattern[j] == '*' || pattern[j] == texto[i]) {
            i++;
            j++;
        } else {
            return false;
        }
    }
    return j == m;
}

// Cria a tabela de falha para o algoritmo KMP
vector<int> criar_tabela_falha(const string& padrao) {
    size_t m = padrao.size();
    vector<int> falha(m, 0);
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && padrao[i] != padrao[j]) {
            j = falha[j - 1];
        }
        if (padrao[i] == padrao[j]) {
            j++;
        }
        falha[i] = j;
    }
    return falha;
}

// Implementa o algoritmo KMP para busca de padrões
bool kmp(const string& texto, const string& padrao) {
    size_t n = texto.size();
    size_t m = padrao.size();
    vector<int> falha = criar_tabela_falha(padrao);
    size_t i = 0, j = 0;
    bool found = false;
    while (i < n) {
        if (padrao[j] == texto[i]) {
            i++;
            j++;
        }
        if (j == m) {
            size_t pos = i - j;
            string palavraCompleta = captura_palavra(texto, pos, m);
            cout << "Padrão encontrado na posição: " << pos << " | Palavra completa: " << palavraCompleta << endl;
            found = true;
            j = falha[j - 1];
        } else if (i < n && padrao[j] != texto[i]) {
            if (j != 0)
                j = falha[j - 1];
            else
                i++;
        }
    }
    return found;
}

// Verifica se um caractere é um delimitador
bool is_delimiter(char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '.' || c == ',';
}

// Captura uma palavra completa do texto dado um início e um tamanho de padrão
string captura_palavra(const string& texto, size_t inicio, size_t tamanho_padrao) {
    size_t start = inicio;
    while (start > 0 && !is_delimiter(texto[start - 1])) start--;
    size_t end = inicio + tamanho_padrao;
    while (end < texto.size() && !is_delimiter(texto[end])) end++;
    return texto.substr(start, end - start);
}

// Obtém o padrão de busca do usuário
string get_pattern() {
    string padrao;
    cout << "Informe o padrão a ser buscado (ou 'sair' para encerrar): ";
    cin >> padrao;
    return padrao;
}

// Verifica se um caractere é uma vogal
bool is_vogal(char c) {
    static const string vogais = "aeiouAEIOU";
    return vogais.find(c) != string::npos;
}

// Verifica se um caractere é uma consoante
bool isConsoante(char c) {
    return isalpha(c) && !is_vogal(c);
}

// Verifica se o padrão contém wildcards
bool com_wildcard(const string& pattern) {
    return pattern.find('*') != string::npos;
}

// Remove uma letra de uma palavra
string removeLetter(string word, int index) {
    return word.erase(index, 1);
}

// Insere uma letra em uma palavra
string insertLetter(string word, int index, char letter) {
    return word.insert(index, 1, letter);
}

// Calcula a distância de Levenshtein entre duas strings
int distanciaLevenshtein(const string& s1, const string& s2) {
    const size_t len1 = s1.size(), len2 = s2.size();
    vector<vector<int> > d(len1 + 1, vector<int>(len2 + 1));

    for (int i = 0; i <= len1; ++i)
        d[i][0] = i;
    for (int j = 0; j <= len2; ++j)
        d[0][j] = j;

    for (int i = 1; i <= len1; ++i)
        for (int j = 1; j <= len2; ++j) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + cost);
        }

    return d[len1][len2];
}

// Encontra palavras similares no dicionário usando a distância de Levenshtein
void encontrar_palavras_similares(const string& palavra, const unordered_map<char, vector<string> >& indice) {
    vector<pair<string, int> > sugestoes;
    char inicial = tolower(palavra[0]);

    auto it = indice.find(inicial);
    if (it != indice.end()) {
        for (const auto& palavra_dic : it->second) {
            int distancia = distanciaLevenshtein(palavra, palavra_dic);
            if (distancia <= 2) {
                sugestoes.push_back(make_pair(palavra_dic, distancia));
            }
        }
    }

    // Ordena as sugestões pela distância de Levenshtein
    sort(sugestoes.begin(), sugestoes.end(),
         ComparadorDistancia());

    if (!sugestoes.empty()) {
        cout << "Sugestões de palavras similares:" << endl;
        for (size_t i = 0; i < sugestoes.size(); ++i) {
            cout << "- " << sugestoes[i].first << " (distância: " << sugestoes[i].second << ")" << endl;
        }
    } else {
        cout << "Nenhuma sugestão encontrada." << endl;
    }
}

// Busca palavras com R/S adicional ou substituído
void encontrar_palavras_RS_adicional(const string& palavra, const unordered_map<char, vector<string> >& indice) {
    vector<string> sugestoes_adicionais;

    // Geração das variantes com R/S adicional ou substituído
    for (size_t i = 0; i <= palavra.length(); ++i) {
        // Adicionar 'r' ou 's'
        string nova_r = palavra;
        nova_r.insert(i, 1, 'r');
        sugestoes_adicionais.push_back(nova_r);

        string nova_s = palavra;
        nova_s.insert(i, 1, 's');
        sugestoes_adicionais.push_back(nova_s);

        // Substituir por 'r' ou 's'
        if (i < palavra.length()) {
            nova_r = palavra;
            nova_r[i] = 'r';
            sugestoes_adicionais.push_back(nova_r);

            nova_s = palavra;
            nova_s[i] = 's';
            sugestoes_adicionais.push_back(nova_s);
        }
    }

    bool encontrou_sugestao = false;
    for (const auto& sugestao : sugestoes_adicionais) {
        char inicial = tolower(sugestao[0]);
        auto it = indice.find(inicial);
        if (it != indice.end()) {
            for (const auto& palavra_dic : it->second) {
                if (palavra_dic == sugestao) {
                    cout << "Sugestão encontrada: " << palavra_dic << endl;
                    encontrou_sugestao = true;
                }
            }
        }
    }

    if (!encontrou_sugestao) {
        cout << "Nenhuma sugestão encontrada com R/S adicional ou substituído." << endl;
    }
}

// Indexa o dicionário para busca rápida
unordered_map<char, vector<string> > indexar_dicionario(const string& dicionario) {
    unordered_map<char, vector<string> > indice;
    istringstream iss(dicionario);
    string palavra;

    while (iss >> palavra) {
        char inicial = tolower(palavra[0]);
        indice[inicial].push_back(palavra);
    }

    return indice;
}