#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string linha;
    ifstream arquivo("arquivo.txt");

    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            // Processar a linha lida
            cout << linha << endl; // Exemplo: Imprimir a linha na tela

            // Separar os dados da linha em variáveis (se necessário)
            // Exemplo: Se cada linha tiver dois números separados por espaço
            int numero1, numero2;
            istringstream iss(linha);
            iss >> numero1 >> numero2;
            cout << "Numero 1: " << numero1 << ", Numero 2: " << numero2 << endl;
        }
        arquivo.close();
    } else
        cout << "Erro ao abrir o arquivo." << endl;

    return 0;
}