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
#define INICIAL 7917520
#define MAX_FILME 638834 // ultimo valor que a hashFilme() é capaz de gerar
#define MAX_CINEMA 450
using namespace std;

class Arquivo {
public:
    vector<Filme> filmes;
    vector<Cinema> cinemas;
    string arquivoFilme, arquivoCinema;
    Triagem triagemFilmes;

    Arquivo(const string& nomeArquivo1, const string& nomeArquivo2) :
            arquivoFilme(nomeArquivo1), arquivoCinema(nomeArquivo2) {}

    Arquivo* lerArquivo() {
        ifstream movieFile(arquivoFilme);

        filmes.reserve(MAX_FILME);
        string linha;
        getline(movieFile, linha); // Ignora a primeira linha (cabeçalho)
        string t_const, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres;

        int i = 0;
        while (getline(movieFile, linha)) {
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
                Filme atual(i, titleType, primaryTitle, originalTitle,
                            adult, startY, endY, runTime, genres);

                if (startY != -1)
                    triagemFilmes.insereNaStartYear(startY, i);

                if (endY != -1)
                    triagemFilmes.insereNaEndYear(endY,i);

                if (runTime != -1)
                    triagemFilmes.insereNaRunTimeMinutes(runTime, i);

                while (getline(genresStream, genre, ',')) {
                    genresVec.push_back(genre);
                    triagemFilmes.insereNaHashGenres(genre, i);
                }

                triagemFilmes.insereNaHashType(titleType, i);
                filmes.push_back(atual);

                ++i;

            } catch (const out_of_range& e) {
                cerr << "Erro: " << e.what() << std::endl;
                return nullptr;
            } catch (const invalid_argument& e) {
                cerr << "Erro de conversão inválida: " << e.what() << std::endl;
                return nullptr;
            } catch (const runtime_error& e) {
                cerr << "Erro: " << e.what() << std::endl;
                return nullptr;
            }
        }
        movieFile.close();

        ifstream cinemaFile(arquivoCinema);
        cinemas.reserve(MAX_CINEMA);
        getline(cinemaFile, linha); // ignora cabeçalho dos cinemas
        string bufferCinemaId, nomeCinema, bufferCordenadaX, bufferCoordenadaY, bufferTicketValue, bufferFilmesId;
        vector<int> filmesId;
        double ticketValue;
        pair<double,double> coordenada;

        int j =0;
        while (getline(cinemaFile,linha)){
            stringstream ss(linha);
            getline(ss, bufferCinemaId,',');
            getline(ss, nomeCinema, ',');
            getline(ss, bufferCordenadaX, ',');
            getline(ss, bufferCoordenadaY, ',');
            getline(ss, bufferTicketValue,',');

            filmesId.clear();
            while (getline(ss,bufferFilmesId,',')){
                int codeId = hashFilme(bufferFilmesId);
                filmesId.push_back(codeId);
            }

            coordenada.first = stod(bufferCordenadaX);
            coordenada.second = stod(bufferCoordenadaY);
            ticketValue = stod(bufferTicketValue);

            Cinema atual(j, nomeCinema, coordenada, ticketValue, filmesId);
            cinemas.push_back(atual);

            ++j;
        }
        cinemaFile.close();

        return this;
    }
    int hashFilme(string t_const){
        t_const = t_const.substr(3);
        int codeId = stoi(t_const);
        codeId = (codeId - INICIAL) / 2;
        return codeId;
    }
    bool clearAll(){
        size_t limit = triagemFilmes.genresList.size();
        for (size_t i = 0; i < limit; i++)
            clearIn(triagemFilmes.genresList[i].codeIdFilmes);
        triagemFilmes.genresList.clear();
        limit = triagemFilmes.typeList.size();
        for (size_t i = 0; i < limit; i++)
            clearIn(triagemFilmes.typeList[i].codeIdFilmes);
        triagemFilmes.typeList.clear();
    }
    void clearIn(vector<int> discardList){
        discardList.clear();
    }
    Filme getFilmePorId(int codeId){ return filmes[codeId];}
    Cinema getCinemaPorId(int codeId){ return cinemas[codeId];}
};

#endif //TBO_2024_01_ARQUIVO_H


