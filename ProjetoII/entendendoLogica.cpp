//
// Created by João on 06/09/24.
//
#include <iostream>
#include <vector>
using namespace std;

// Função para construir a tabela de falhas
vector<int> buildFailureTable(const string& pattern) {
    int m = pattern.length();
    vector<int> fail(m, 0);
    int j = 0; // comprimento do prefixo anterior correspondente
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j])
            j = fail[j - 1];

        if (pattern[i] == pattern[j])
            j++;

        fail[i] = j;
    }
    return fail;
}

// Função para realizar a busca KMP
void KMPSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> fail = buildFailureTable(pattern);
    int j = 0; // índice no padrão

    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j])
            j = fail[j - 1];

        if (text[i] == pattern[j])
            j++;

        if (j == m) {
            cout << "Padrão encontrado na posição " << i - m + 1 << endl;
            j = fail[j - 1];
        }
    }
}

int main() {
    string text = "aaabbcaabbcaaabba";
    string pattern = "aabbca";
    KMPSearch(text, pattern);
    return 0;
}
