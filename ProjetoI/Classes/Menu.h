#ifndef MENU_H
#define MENU_H
#include "Busca.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


class Menu : public Busca{
private:
    int escolha;
    vector<string> tipos, generos;
    int duracoes[2] = {0, 0};
    int anos[2] = {0, 0};

    int distancia = 0;
    float valor = 0;
    int localizacaoUsuario[2] = {10000, 20000};



public:
    vector<int> menuPrincipal() {
        cout << "\033[2J";
        cout << "### MENU PRINCPAL ###" << endl << endl;
        cout << "1 - Filmes" << endl;
        cout << "2 - Cinemas" << endl << endl;
        cout << "Escolha: ";
        cin >> this->escolha;
        vector<int>filmes;
        if(this->escolha == 1) filmes = menuFilmes();
        else if(this->escolha == 2) menuCinemas();

        return filmes;
    }

    vector<int> menuFilmes() {
        // Vetores para armazenar múltiplos filtros aplicados
        vector<string> tipos;
        vector<string> generos;
        int duracaoMin = -1, duracaoMax = -1;
        int anoInicial = -1, anoFinal = -1;

        int escolhaFilme;

        bool genres, types, intervaloAno, intervaloTempo, runTime;

        do {
            // Limpar tela e exibir opções
            cout << "\033[2J\033[H";  // Comando para limpar a tela
            cout << "### FILMES ###" << endl << endl;
            cout << "1. Filtrar por Tipo" << endl;
            cout << "2. Filtrar por Gênero" << endl;
            cout << "3. Filtrar por Duração (min/max)" << endl;
            cout << "4. Filtrar por Intervalo de Anos" << endl;
            cout << "5. Voltar ao Menu Principal" << endl;
            cout << "6. Pesquisar com filtros aplicados" << endl;
            cout << "Escolha uma opção: ";
            cin >> escolhaFilme;
            pair<int,int> duracao;

            switch (escolhaFilme) {
                case 1: {
                    string tipo;
                    cout << "Digite o(s) tipo(s) de filme (separados por vírgula): ";
                    getline(cin, tipo); // Use getline para ler a linha inteira

                    // Separe as strings por vírgula
                    stringstream ss(tipo);
                    string token;
                    while (getline(ss, token, ',')) {
                        tipos.push_back(token); // Adicione cada token ao vetor
                    }
                }
                case 2: {
                    string genero;
                    cout << "Digite o(s) gênero(s) de filme (separados por vírgula): ";
                    getline(cin, genero);

                    stringstream ss(genero);
                    string token;
                    while (getline(ss, token, ',')) {
                        generos.push_back(token);
                    }
                }
                case 3: {
                    // Solicitar duração mínima e máxima
                    cout << "Digite a duração mínima (em minutos): ";
                    cin >> duracao.first;
                    cout << "Digite a duração máxima (em minutos): ";
                    cin >> duracao.second;
                }
                case 4: {
                    // Solicitar ano inicial e final
                    cout << "Digite o ano inicial do intervalo: ";
                    cin >> anoInicial;
                    cout << "Digite o ano final do intervalo: ";
                    cin >> anoFinal;
                    anoFinal != 0 ? intervaloAno =  true : intervaloAno =  false;
                }
                case 5:
                    // Chamar busca combinada com os filtros aplicados
                    vector<int> resultadoFinal;

                    resultadoFinal = buscaCombinada(anoInicial, anoFinal, duracao, tipos, generos, intervaloAno, intervaloTempo);

                    // Exibir resultados
                    if (resultadoFinal.empty()) {
                        cout << "Nenhum filme encontrado com os filtros aplicados." << endl;
                    } else {
                        cout << "Filmes encontrados: " << endl;
                        return resultadoFinal;
                    }
                    break;

            }
        } while (escolhaFilme != 5);  // Voltar ao menu principal com opção 5
    }

void menuCinemas() {
    int escolhaCinema;


    cout << "### CINEMAS ###" << endl << endl;
    cout << "1 - Distancia ";
    if(this->distancia != 0) cout << ": " << this->distancia;
    cout << endl << "2 - Valor";
    if(this->valor != 0) cout << ": " << this->valor;

    cout << endl << endl << "3 - Voltar" << endl;
    cout << "0 - Pesquisar" << endl << endl;
    cout << "Escolha: ";
    cin >> escolhaCinema;

    if(escolhaCinema == 1) {
        int d;
        cout << "Digite uma distancia maxima: ";
        cin >> d;
        if(d == 0) distancia = 0;
        else this->distancia = d;
        cout << this->distancia;
    }
    else if(escolhaCinema == 2) {
        int v;
        cout << "Digite um valor maximo: ";
        cin >> v;
        if(v == 0) this->valor = 0;
        else this->valor = v;
    }
    else if(escolhaCinema == 3) menuPrincipal();

    menuCinemas();
}

};



#endif //MENU_H