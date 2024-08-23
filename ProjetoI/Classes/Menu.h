#ifndef MENU_H
#define MENU_H
#include "Busca.h"
#include "Arquivo.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


class Menu : Busca{
private:
    int escolha;
    vector<string> tipos, generos;
    //int duracoes[2] = {0, 0};
    //int anos[2] = {0, 0};

    // int distancia = 0;
    // float valor = 0;
    // vector<int> localizacaoUsuario;
    Arquivo arquivoParaBusca;


public:
    Menu(Arquivo& arquivo):arquivoParaBusca(arquivo){}
    void principal() {
        cout << "### MENU PRINCPAL ###" << endl << endl;
        cout << "1 - Filmes" << endl;
        cout << "2 - Cinemas" << endl << endl;
        cout << "Escolha: ";
        cin >> this->escolha;

        if(this->escolha == 1) filmes();
        else if(this->escolha == 2) cinemas();
        else principal();
    }

    void filmes() {
        // Vetores para armazenar múltiplos filtros aplicados
        vector<string> tipos;
        vector<string> generos;
        int duracaoMin = -1, duracaoMax = -1;
        int anoInicial = -1, anoFinal = -1;
        int escolhaFilme;
        pair <int,int> runTime;
        bool genres, types, intervaloAno;


        do {
            cout << "### FILMES ###" << endl << endl;
            cout << "1. Filtrar por Tipo" << endl;
            cout << "2. Filtrar por Gênero" << endl;
            cout << "3. Filtrar por Duração (min/max)" << endl;
            cout << "4. Filtrar por Intervalo de Anos" << endl;
            cout << "5. Voltar ao Menu Principal" << endl;
            cout << "6. Pesquisar com filtros aplicados" << endl;
            cout << "Escolha uma opção: ";
            cin >> escolhaFilme;

            switch (escolhaFilme) {
                case 1: {
                    string tipo;
                    cout << "Digite o(s) tipo(s) de filme (separados por vírgula): ";
                    cin >> tipo;
                    // Separe as strings por vírgula
                    stringstream ss(tipo);
                    string token;
                    while (getline(ss, token, ',')) {
                        tipos.push_back(token); // Adiciona cada tipo ao vetor de tipos
                    }
                }
                case 2: {
                    // mesma coisa com os generos, aqui
                    string genero;
                    cout << "Digite o(s) gênero(s) de filme (separados por vírgula): ";
                    cin >> genero;

                    stringstream ss(genero);
                    string token;
                    while (getline(ss, token, ','))
                        generos.push_back(token);
                }
                case 3: {
                    // entrada duração mínima e máxima (considero sempre q o usuario quer um
                    // filme com tempo máximo)
                    cout << "Digite o tempo minimo que voce deseja..." << endl;
                    cin >> runTime.first;
                    cout << "Agora, digite o tempo maximo que voce deseja..." << endl;
                    cin >> runTime.second;
                }
                case 4: {
                    int op;
                    cout << "Se deseja buscar filmes com um intervalo de tempo de lancamento especifico?" << endl;;
                    cout << "Se sim digite 1, caso contrario, digite 2: ";
                    cin >> op;

                    switch (op) {
                        case 1: {
                            intervaloAno =  true;
                            cout << "Digite o ano inicial: " ;
                            cin >> anoInicial;
                            cout << endl << "Digite o ano final do intervalo: ";
                            cin >> anoFinal;
                            break;
                        }
                        case 2: {
                            intervaloAno = false;
                            cout << "Defina o ano de filmes que deseja filtrar:" << endl;
                            cin >> anoInicial;
                            break;
                        }
                        default: cout << "Numero invalido, repita." << endl;
                    }
                }
                case 5:
                    // Chamar busca combinada com os filtros aplicados
                    vector<int> resultadoFinal;
                    resultadoFinal = arquivoParaBusca.triagemFilmes.buscaCombinada(anoInicial, anoFinal, runTime,
                                                    tipos, generos, intervaloAno, intervaloAno);

                    // Exibir resultados
                    if (resultadoFinal.empty()) {
                        cout << "Nenhum filme encontrado com os filtros aplicados." << endl;
                    } else {
                        cout << "Filmes encontrados: " << endl;
                        int limit = resultadoFinal.size();
                        int codeId;
                        for( int i = 0; i < limit; i++) {
                            codeId = resultadoFinal[i];
                            Filme atual = arquivoParaBusca.getFilmePorId(codeId);
                            cout << atual.getCodeId()<< " " << atual.getNamePrimary() << " " << atual.getNameOriginal();
                            cout << " " << atual.getStartYear() << " " << atual.getEndYear() << " ";
                            cout << atual.getRunTimeMinutes() << " " << atual.getType() << " " << atual.getGenres();
                            cout << endl;
                        }
                    }
                    break;

            }
        } while (escolhaFilme != 5);  // Voltar ao menu principal com opção 5
    }

    void cinemas() {
        int escolhaCinema;
        pair<int, int> distancia;
        int valor;
        cout << "### CINEMAS ###" << endl << endl;
        cout << "1 - Distancia ";
        cout << ": " << distancia.first;
        if(distancia.first != 0) {
            cin>> distancia.first;
            cin>> distancia.second;
        }
        cout << endl << "2 - Valor";
        if(valor != 0) cout << ": " << valor;

        cout << endl << endl << "3 - Voltar" << endl;
        cout << "0 - Pesquisar" << endl << endl;
        cout << "Escolha: ";
        cin >> escolhaCinema;

        if(escolhaCinema == 1) {
            int dMax;
            cout << "Digite uma distancia maxima: ";
            cin >> dMax;
            cout << distancia.first << " " << distancia.second;
        }
        else if(escolhaCinema == 2) {
            int v;
            cout << "Digite um valor maximo: ";
            cin >> v;
            if(v == 0) valor = 0;
            else valor = v;
        }
        else if(escolhaCinema == 3) principal();

        cinemas();
    }

};



#endif //MENU_H