#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <cmath>

#define MAX 10000000
#define DICIONARIO "/Users/jotavsevla/CLionProjects/tbo_2024_01/ProjetoII/arquivoTexto/Dicionário pt_BR.dic"

using namespace std;

// Protótipos das funções
string* lerArquivo(const string& index);
string limparPalavra(const string& palavra);
vector<int> criarTabelaFalha(const string& padrao);
bool correspondeComWildcard(const string& texto, const string& pattern, size_t pos_texto);
bool kmp_wildcard(const string& text, const string& pattern);
bool kmp(const string& texto, const string& padrao);
bool isDelimiter(char c);
string getPattern();
string capturaPalavra(const string& texto, size_t inicio, size_t tamanho_padrao);
void encontrarPalavrasSimilares(const string& palavra, const string& dicionario);
bool isVogal(char c);
bool comWildcard(const string& pattern);
bool isConsoante(char c);
string removeLetter(string word, int index);
string insertLetter(string word, int index, char letter);
void buscarComRSAdicional(const string& palavra, const string& dicionario);

int main() {
    string* texto = lerArquivo(DICIONARIO);
    if (texto == nullptr) {
        cerr << "Erro ao ler o arquivo do dicionário. Encerrando o programa." << endl;
        return 1;
    }

    string pattern;
    char modo;

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

        pattern = getPattern();
        if (pattern == "sair") break;

        if (modo == '1') {
            bool encontrouPadrao = comWildcard(pattern) ? kmp_wildcard(*texto, pattern) : kmp(*texto, pattern);
            if (!encontrouPadrao) {
                cout << "Palavra não encontrada no dicionário." << endl;
            }
        } else {
            cout << "Buscando sugestões para a palavra..." << endl;
            encontrarPalavrasSimilares(pattern, *texto);
            buscarComRSAdicional(pattern, *texto);
        }
    }

    delete texto;
    return 0;
}

string* lerArquivo(const string& index) {
    ifstream arquivo(index);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
        return nullptr;
    }
    auto* texto = new string();
    texto->reserve(MAX);
    string linha;
    while (getline(arquivo, linha)) {
        string palavraLimpa = limparPalavra(linha);
        *texto += palavraLimpa + "\n";
    }
    arquivo.close();
    return texto;
}

string limparPalavra(const string& palavra) {
    size_t posBarra = palavra.find('/');
    string limpa = (posBarra != string::npos) ? palavra.substr(0, posBarra) : palavra;
    limpa = regex_replace(limpa, regex("�"), "");
    return limpa;
}

bool kmp_wildcard(const string& texto, const string& pattern) {
    size_t n = texto.size();
    bool found = false;
    for (size_t i = 0; i < n; ++i) {
        if (correspondeComWildcard(texto, pattern, i)) {
            string palavraCompleta = capturaPalavra(texto, i, pattern.size());
            cout << "Padrão encontrado na posição: " << i << " | Palavra completa: " << palavraCompleta << endl;
            found = true;
        }
    }
    return found;
}

bool correspondeComWildcard(const string& texto, const string& pattern, size_t pos_texto) {
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

vector<int> criarTabelaFalha(const string& padrao) {
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

bool kmp(const string& texto, const string& padrao) {
    size_t n = texto.size();
    size_t m = padrao.size();
    vector<int> falha = criarTabelaFalha(padrao);
    size_t i = 0, j = 0;
    bool found = false;
    while (i < n) {
        if (padrao[j] == texto[i]) {
            i++;
            j++;
        }
        if (j == m) {
            size_t pos = i - j;
            string palavraCompleta = capturaPalavra(texto, pos, m);
            cout << "Padrão encontrado na posição: " << pos << " | Palavra completa: " << palavraCompleta << endl;
            found = true;
            j = falha[j - 1];
        } else if (i < n && padrao[j] != texto[i]) {
            if (j != 0) j = falha[j - 1];
            else i++;
        }
    }
    return found;
}

bool isDelimiter(char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '.' || c == ',';
}

string capturaPalavra(const string& texto, size_t inicio, size_t tamanho_padrao) {
    size_t start = inicio;
    while (start > 0 && !isDelimiter(texto[start - 1])) start--;
    size_t end = inicio + tamanho_padrao;
    while (end < texto.size() && !isDelimiter(texto[end])) end++;
    return texto.substr(start, end - start);
}

string getPattern() {
    string padrao;
    cout << "Informe o padrão a ser buscado (ou 'sair' para encerrar): ";
    cin >> padrao;
    return padrao;
}

bool isVogal(char c) {
    static const string vogais = "aeiouAEIOU";
    return vogais.find(c) != string::npos;
}

bool isConsoante(char c) {
    return isalpha(c) && !isVogal(c);
}

bool comWildcard(const string& pattern) {
    return pattern.find('*') != string::npos;
}

string removeLetter(string word, int index) {
    return word.erase(index, 1);
}

string insertLetter(string word, int index, char letter) {
    return word.insert(index, 1, letter);
}

void encontrarPalavrasSimilares(const string& palavra, const string& dicionario) {
    vector<string> sugestoes;
    istringstream iss(dicionario);
    string palavra_dic;

    while (iss >> palavra_dic) {
        if (abs((int)palavra.length() - (int)palavra_dic.length()) <= 1) {
            int distancia = 0;
            for (size_t i = 0; i < max(palavra.length(), palavra_dic.length()); ++i) {
                if (i >= palavra.length() || i >= palavra_dic.length() || palavra[i] != palavra_dic[i]) {
                    distancia++;
                }
                if (distancia > 1) break;
            }
            if (distancia <= 1) {
                sugestoes.push_back(palavra_dic);
            }
        }
    }

    if (!sugestoes.empty()) {
        cout << "Sugestões de palavras similares:" << endl;
        for (const auto& sugestao : sugestoes) {
            cout << "- " << sugestao << endl;
        }
    } else {
        cout << "Nenhuma sugestão encontrada." << endl;
    }
}

void buscarComRSAdicional(const string& palavra, const string& dicionario) {
    vector<string> sugestoes;
    istringstream iss(dicionario);
    string palavra_dic;

    vector<string> variantes_palavra;
    variantes_palavra.push_back(palavra);

    for (size_t i = 1; i < palavra.length() - 1; ++i) {
        if (palavra[i] == 'r' || palavra[i] == 'R' || palavra[i] == 's' || palavra[i] == 'S') {
            string nova = palavra;
            nova.insert(i + 1, 1, palavra[i]);
            variantes_palavra.push_back(nova);
        }
    }

    while (iss >> palavra_dic) {
        for (const auto& variante : variantes_palavra) {
            if (variante == palavra_dic) {
                sugestoes.push_back(palavra_dic);
                break;
            }
        }
    }

    if (!sugestoes.empty()) {
        cout << "Sugestões de palavras com R/S adicional:" << endl;
        for (const auto& sugestao : sugestoes) {
            cout << "- " << sugestao << endl;
        }
    } else {
        cout << "Nenhuma sugestão encontrada com R/S adicional." << endl;
    }
}