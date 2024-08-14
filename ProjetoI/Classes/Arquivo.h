//
// Created by João on 28/07/24.
//

#ifndef TBO_2024_01_ARQUIVO_H
#define TBO_2024_01_ARQUIVO_H
#include "Filme.h"
#include "Cinema.h"
#include "Triagem.h"
#include "sstream"
#include "fstream"
#include "chrono"
#include "math.h"
#define MAX 638834 // ultimo valor que a hashFilme() é capaz de gerar
using namespace std;

class Arquivo {
public:
    vector<Filme> filmes;
    vector<Cinema> cinemas;
    string arquivo;

    Arquivo(const string& nomeArquivo) : arquivo(nomeArquivo) {}

    int lerArquivo() {
        ifstream file(arquivo);

        if (!file.is_open())
            return 1;
        Triagem triagemFilmes;
        filmes.reserve(MAX);
        string linha;
        getline(file, linha); // Ignora a primeira linha (cabeçalho)
        string t_const, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres;
        int i = 0;
        while (getline(file, linha)) {
            try {
                stringstream ss(linha);
                getline(ss, t_const, '\t');
                getline(ss, titleType, '\t');
                if(titleType.empty())
                    getline(ss, titleType, '\t');

                getline(ss, primaryTitle, '\t');
                getline(ss, originalTitle, '\t');
                getline(ss, isAdult, '\t');
                getline(ss, startYear, '\t');
                getline(ss, endYear, '\t');
                getline(ss, runtimeMinutes, '\t');
                getline(ss, genres, '\n');

                int startY = (startYear != "\\N") ? stoi(startYear) : -1;
                int endY = (endYear != "\\N") ? stoi(endYear) : -1;
                int runTime = (runtimeMinutes != "\\N") ? stoi(runtimeMinutes) : -1;
                bool adult = (isAdult == "1");
                cout << t_const << titleType<< primaryTitle<< originalTitle<< adult<<startY<<endY<<runTime<<genres;

                vector<string> genresVec; // Clear genresVec for each iteration
                stringstream genresStream(genres); // Create genresStream after genres is populated
                string genre;
                Filme atual(t_const, titleType, primaryTitle, originalTitle,
                            adult, startY, endY, runTime, genres);


                if (!filmes.empty() && atual.getCodeId() != filmes.back().getCodeId() + 1 )
                    atual.setCodeId(filmes.back().getCodeId() + 1);

                i = atual.getCodeId();

                if (startY != -1)
                    triagemFilmes.insereNaStartYear(startY, i);

                if (endY != -1)
                    triagemFilmes.insereNaEndYear(endY,i);

                if (runTime != -1)
                    triagemFilmes.insereNaRunTimeMinutes(runTime, i);

                while (getline(genresStream, genre, ',')) {
                    genresVec.push_back(genre);
                    triagemFilmes.insereNaHashGenres(genre, atual.getCodeId());
                }
                triagemFilmes.insereNaHashType(titleType, atual.getCodeId());
                filmes.push_back(atual);

            } catch (const out_of_range& e) {
                cerr << "Erro: " << e.what() << std::endl;
                return 1;
            } catch (const invalid_argument& e) {
                cerr << "Erro de conversão inválida: " << e.what() << std::endl;
                return 2;
            } catch (const runtime_error& e) {
                cerr << "Erro: " << e.what() << std::endl;
                return 3;
            }
        }
        file.close();
        return 0;
    }
    Filme getFilmePorId(int codeId){ return filmes[codeId];}
    Cinema getCinemaPorId(int codeId){ return cinemas[codeId];}
};

#endif //TBO_2024_01_ARQUIVO_H


