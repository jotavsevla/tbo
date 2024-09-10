#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex> // Para usar expressões regulares
#define MAX 10000000
#define DICIONARIO "/Users/jotavsevla/CLionProjects/tbo_2024_01/ProjetoII/arquivoTexto/Dicionário pt_BR.dic"
using namespace std;
// estruturas
struct TrieNode {
    TrieNode* children[256]; // Assumindo um alfabeto de 256 caracteres
    bool isAccepting;
    TrieNode() {
        for (int i = 0; i < 256; ++i)
            children[i] = nullptr;
        isAccepting = false;
    }
};

//  cabeçalhos
// Função para ler o arquivo
string* lerArquivo (const string& index);
void kmp(string texto, string padrao);
// Função para criar a tabela de falhas do KMP
vector<int> criarTabelaFalha(const string& padrao);
void kmp_wildcard(const string& text, const string& pattern, TrieNode* root);
TrieNode* criarTabelhaFalhaWildCard(const string& pattern);
// Função para remover caracteres especiais e sufixos após as barras
string limparPalavra(const string& palavra);
string getPattern();
string capturarPalavra(const string& texto, int inicio, int fim);
bool isDelimiter(char c);

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


vector<int> criarTabelaFalha(const string& padrao) {
    int m = padrao.size();
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
TrieNode* criarTabelhaFalhaWildCard(const string& pattern) {
    TrieNode* root = new TrieNode();
    TrieNode* currentNode = root;

    for (int i = 0; i < pattern.size(); ++i) {
        char c = pattern[i];
        if (c == '*') {
            currentNode->isAccepting = true;
        } else {
            if (currentNode->children[c] == nullptr) {
                currentNode->children[c] = new TrieNode();
            }
            currentNode = currentNode->children[c];
        }
        if (i == pattern.size() - 1) {
            currentNode->isAccepting = true;
        }
    }

    return root;
}

void kmp_wildcard(const string& text, const string& pattern, TrieNode* root) {
    int n = text.size();
    int m = pattern.size();
    TrieNode* currentNode = root;

    for (int i = 0; i < n; ++i) {
        char c = text[i];
        while (currentNode != root && currentNode->children[c] == nullptr) {
            currentNode = root;
        }

        if (currentNode->children[c] != nullptr) {
            currentNode = currentNode->children[c];
        } else if (currentNode->children['*'] != nullptr) {
            currentNode = currentNode->children['*'];
        }

        if (currentNode->isAccepting) {
            int pos = i - m + 1;
            string palavraCompleta = capturarPalavra(text, pos, pos + m);
            cout << "Padrão encontrado na posição: " << pos << " | Palavra completa: " << palavraCompleta << endl;
            currentNode = root;
        }
    }
}
void kmp(string texto, string padrao) {
// Função KMP para buscar o padrão no texto e imprimir todas as ocorrências
    int n = texto.size();
    int m = padrao.size();

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
            string palavraCompleta = capturarPalavra(texto, pos, pos + m);
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

void liberarTrie(TrieNode* root) {
    if (root == nullptr) {
        return;
    }

    for (int i = 0; i < 256; ++i) {
        if (root->children[i] != nullptr) {
            liberarTrie(root->children[i]);
        }
    }

    delete root;
}
// Função para capturar a palavra completa em torno do padrão encontrado
string capturarPalavra(const string& texto, int inicio, int fim) {
    // Encontrar início da palavra anterior ao padrão
    int start = inicio;
    while (start > 0 && !isDelimiter(texto[start - 1]))
        start--;


    // Encontrar fim da palavra após o padrão
    int end = fim;
    while (end < texto.size() && !isDelimiter(texto[end]))
        end++;

    // Retornar a palavra completa extraída
    return texto.substr(start, end - start);
}



// Função para capturar o padrão
string getPattern(){
    string padrao;
    cout << "Informe o padrão a ser buscado: ";
    cin >> padrao;
    return padrao;
}


int main() {
    // Ler o arquivo e realizar a busca pelo padrão
    string* texto = lerArquivo(DICIONARIO);

    while (true) {
        string padrao;
        cout << "Informe o padrão a ser buscado (ou 'sair' para encerrar): ";
        cin >> padrao;

        if (padrao == "sair")
            break;

        // Verifica se o padrão contém o caractere wildcard
        bool hasWildcard = padrao.find('*') != string::npos;

        if (hasWildcard) {
            TrieNode* root = criarTabelhaFalhaWildCard(padrao);
            kmp_wildcard(*texto, padrao, root);
            liberarTrie(root);
        } else
            kmp(*texto, padrao);

    }

    return 0;
}