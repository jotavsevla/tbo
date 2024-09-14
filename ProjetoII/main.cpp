#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex> // Para usar expressões regulares
// valor maximo arbitrário
#define MAX 10000000
#define DICIONARIO "/Users/jotavsevla/CLionProjects/tbo_2024_01/ProjetoII/arquivoTexto/Dicionário pt_BR.dic"
using namespace std;

//  cabeçalhos das funções
string* lerArquivo (const string& index);
string limparPalavra(const string& palavra);
vector<int> criarTabelaFalha(const string& padrao);
bool correspondeComWildcard(const string& texto, const string& pattern, size_t pos_texto);
void kmp_wildcard(const string& text, const string& pattern);
void kmp(string texto, string padrao);
bool isDelimiter(char c);
string getPattern();
string capturaPalavra(const string& texto, size_t inicio, size_t tamanho_padrao);

// funções
string* lerArquivo (const string& index){
    ifstream arquivo(index);
    auto * texto = new string();
    texto->reserve(MAX);

    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            string palavraLimpa = limparPalavra(linha);
            *texto += palavraLimpa + "\n";
        }
        arquivo.close();
        return texto;
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
        return nullptr;
    }
}
string limparPalavra(const string& palavra) {
    size_t posBarra = palavra.find('/');
    string limpa = (posBarra != string::npos) ? palavra.substr(0, posBarra) : palavra;
    limpa = regex_replace(limpa, regex("�"), "");
    return limpa;
}

void kmp_wildcard(const string& texto, const string& pattern) {
    size_t n = texto.size();
    for (size_t i = 0; i < n; ++i) {
        if (correspondeComWildcard(texto, pattern, i)) {
            string palavraCompleta = capturaPalavra(texto, i, pattern.size());
            cout << "Padrão encontrado na posição: " << i << " | Palavra completa: " << palavraCompleta << endl;
        }
    }
}
bool correspondeComWildcard(const string& texto, const string& pattern, size_t pos_texto) {
    size_t n = texto.size();
    size_t m = pattern.size();

    size_t i = pos_texto;
    size_t j = 0;

    while (i < n && j < m) {
        if (pattern[j] == '*') {
            // Ignora caracteres consecutivos '*' no padrão
            while (j < m && pattern[j] == '*') {
                j++;
            }
            // Se '*' for o último caractere, qualquer sequência restante é válida
            if (j == m) {
                return true;
            }
            // Tenta avançar no texto até encontrar a próxima correspondência
            while (i < n && texto[i] != pattern[j]) {
                i++;
            }
        } else if (pattern[j] == texto[i]) {
            // Correspondência exata
            i++;
            j++;
        } else {
            // Se não houver correspondência, retorna falso
            return false;
        }
    }

    // Verifica se todo o padrão foi processado
    while (j < m && pattern[j] == '*') {
        j++; // Ignorar qualquer '*' restante no final do padrão
    }

    return j == m;
}
vector<int> criarTabelaFalha(const string& padrao) {
    size_t m = padrao.size();
    vector<int> falha(m, 0);
    int j = 0;

    for (int i = 1; i < m; i++) {
        if (padrao[i] == padrao[j]) {
            j++;
            falha[i] = j;
        } else {
            if (j != 0) {
                j = falha[j - 1];
                i--;
            }
        }
    }

    return falha;

}

void kmp(string texto, string padrao) {
// Função KMP para buscar o padrão no texto e imprimir todas as ocorrências
    size_t n = texto.size();
    size_t m = padrao.size();

    vector<int> falha = criarTabelaFalha(padrao);
    int i = 0; // Índice do texto
    int j = 0; // Índice do padrão
    bool found = false; // Variável para verificar se o padrão foi encontrado

    while (i < n) {
        if (padrao[j] == texto[i]) {
            i++;
            j++;
        }

        if (j == m) {
            // Encontrou o padrão
            found = true;
            int pos = i - j;
            string palavraCompleta = capturaPalavra(texto, pos, m);
            cout << "Padrão encontrado na posição: " << pos << " | Palavra completa: " << palavraCompleta << endl;
            j = falha[j - 1];
        } else if (i < n && padrao[j] != texto[i]) {
            if (j != 0)
                j = falha[j - 1];
            else
                i++;
        }
    }

    if (!found) {
        cout << "Padrão não encontrado no texto." << endl;
    }
}

// Função para determinar se o caractere é um delimitador (espaço, nova linha, etc.)
bool isDelimiter(char c) {
    // Adiciono mais delimitadores conforme necessário
    return c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '.' || c == ',';
}
// Função para capturar a palavra completa em torno do padrão encontrado
string capturaPalavra(const string& texto, size_t inicio, size_t tamanho_padrao) {
    // Encontrar início da palavra anterior ao padrão
    size_t start = inicio;
    while (start > 0 && !isDelimiter(texto[start - 1]))
        start--;

    // Encontrar fim da palavra após o padrão
    size_t end = inicio + tamanho_padrao;
    while (end < texto.size() && !isDelimiter(texto[end]))
        end++;

    // Retornar a palavra completa extraída
    return texto.substr(start, end - start);
}
string getPattern(){

    string padrao;
    cout << "Informe o padrão a ser buscado (ou 'sair' para encerrar): ";
    cin >> padrao;

    return padrao;

}

int main() {
    // Ler o arquivo e realizar a busca pelo padrão
    string* texto = lerArquivo(DICIONARIO);
    string pattern;

    while (true) {

        pattern = getPattern();

        if (pattern == "sair")
            break;

        // Verifica se o padrão contém o caractere wildcard
        if (pattern.find('*') != string::npos)
            kmp_wildcard(*texto, pattern);
        else
            kmp(*texto, pattern);
    }

    delete[] texto;

    return 0;

}




