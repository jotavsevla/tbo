//
// Created by João on 31/07/24.
//

#ifndef TBO_2024_01_TRIAGEM_H
#define TBO_2024_01_TRIAGEM_H
#include "TabelaHash.h"
#include "RedBlackTree.h"

class Triagem {
public:
    vector<HashFilmes> typeList;
    vector<HashFilmes> genresList;
    RedBlackTree startYearTree;
    RedBlackTree endYearTree;
    RedBlackTree runTimeTree;
    enum tipoEstado{nao_existe = -1};
    Triagem(){
        typeList.reserve(60);
        genresList.reserve(90);
    }

    int existeHashType(string chave){
        int i = 0;
        const int j = static_cast<int>(typeList.size()) ;
        while (i < j && typeList[i].getChave() != chave ) i++;
        if (typeList[i].getChave() != chave) return -1;
        return i;
    }
    int existeHashGenres(string chave){
        int i = 0;
        const int j = static_cast<int>(genresList.size());
        while (i < j && genresList[i].getChave() != chave) i++;
        if(genresList[i].getChave() != chave) return -1;
        return i;
    }
    void insereNaHashType(string type, int codeId){
        if (existeHashType(type) == nao_existe) {
            HashFilmes anotherType(type);
            typeList.push_back(anotherType);
        }
        int indexHash = existeHashType(type);
        typeList[indexHash].insereNaHash(codeId);
    }
    void insereNaHashGenres(string genres, int codeId){
        if(existeHashGenres(genres)==nao_existe){
            HashFilmes anotherGenre(genres);
            genresList.push_back(anotherGenre);
        }
        int indexHash = existeHashGenres(genres);
        genresList[indexHash].insereNaHash(codeId);
    }

    void insereNaEndYear(int endYear, int codeId){
        endYearTree.insert(endYear, codeId);
    }
    void insereNaRunTimeMinutes(int runTime, int codeId){
        runTimeTree.insert(runTime, codeId);
    }
    vector<int>buscaHashGenres(string chave){
        return genresList[existeHashGenres(chave)].getCodeIdFilmes();
    }
    vector<int>buscaHashTypes(string chave){
        return typeList[existeHashType(chave)].getCodeIdFilmes();
    }
    vector<int>buscaRubroSY(int chave){
        shared_ptr<RedBlackNode> node = startYearTree.search(chave);
        return node->codeIds;
    }
    vector<int>buscaRubroEY(int chave){
        shared_ptr<RedBlackNode> node = endYearTree.search(chave);
        return node->codeIds;
    }
    vector<int>buscaRubroRT(int chave){
        shared_ptr<RedBlackNode> node = runTimeTree.search(chave);
        return node->codeIds;
    }

    void insereNaStartYear(int startYear, int codeId) {
        startYearTree.insert(startYear, codeId);
    }
    vector<int> buscaCombinada(int startYear, int endYear, pair<int, int> runTimeMinutes, vector<string>& types,
                               vector<string>& genres, bool intervaloAno, bool intervaloTempo) {
        vector<int> results;
        vector<int> temp, buffer;

        if (intervaloAno && startYear > 0 && endYear > 0) {
            int ano = startYear;
            vector<int> filmesPorAno = buscaFilmesPorAno(ano);

            ++ano;
            while (ano <= endYear) {
                buffer = buscaFilmesPorAno(ano);
                temp.clear();
                merge(filmesPorAno.begin(), filmesPorAno.end(), buffer.begin(), buffer.end(),
                      back_inserter(temp));
                filmesPorAno = temp;
                ++ano;
            }

            results = filmesPorAno;
        }
        if (startYear > 0 && !intervaloAno) {
            vector<int> filmesPorAno = buscaFilmesPorAno(startYear);
            results = filmesPorAno;
        }

        // Filtragem por intervalo de anos

        if (intervaloTempo && runTimeMinutes.first > 0) {
            int tempo = runTimeMinutes.first;
            vector<int> filmesPorRunTime = buscaFilmesPorTempo(tempo);
            while (tempo <= runTimeMinutes.second) {
                buffer = buscaFilmesPorTempo(tempo);
                temp.clear();
                merge(filmesPorRunTime.begin(), filmesPorRunTime.end(), buffer.begin(),
                      buffer.end(), back_inserter(temp));
                filmesPorRunTime = temp;
                ++tempo;
            }
            results = buscaPorCodeIdsCommon(results, filmesPorRunTime);
        }

        // Filtragem por tipo
        if (!types.empty()) {
            vector<int> filmesPorType = buscaPorHashType(types[0]); // Inicializa com o primeiro tipo

            for (size_t i = 1; i < types.size(); ++i) {
                vector<int> buffer = buscaPorHashType(types[i]);
                temp.clear();
                merge(filmesPorType.begin(), filmesPorType.end(), buffer.begin(),
                      buffer.end(), back_inserter(temp));
                filmesPorType = temp; // Atualiza filmesPorType com o resultado da combinação
            }

            results = buscaPorCodeIdsCommon(results, filmesPorType); // Combina com os resultados existentes
        }

        // Filtragem por gênero
        if (!genres.empty()) {
            vector<int> filmesPorGenero = buscaPorHashGenres(genres[0]); // Inicializa com o primeiro gênero

            for (size_t i = 1; i < genres.size(); ++i) {
                vector<int> buffer = buscaPorHashGenres(genres[i]);
                temp.clear();
                merge(filmesPorGenero.begin(), filmesPorGenero.end(), buffer.begin(),
                      buffer.end(), back_inserter(temp));
                filmesPorGenero = temp; // Atualiza filmesPorGenero com o resultado da combinação
            }

            results = buscaPorCodeIdsCommon(results, filmesPorGenero); // Combina com os resultados existentes
        }

        return results;
    }
    vector<int> buscaPorHashType(string chave){
        int indexChave = existeHashType(chave);
        if (indexChave == nao_existe) vector<int>();
        return typeList[indexChave].getCodeIdFilmes();
    }
    vector<int> buscaPorHashGenres(string chave){
        int indexChave = existeHashGenres(chave);
        if (indexChave == nao_existe) vector<int>();
        return genresList[indexChave].getCodeIdFilmes();
    }
    // consideramos que os valores contidos em ambos os vetores estão em ordem crescente
    vector<int> buscaPorCodeIdsCommon(vector<int>& lista_um, vector<int>& lista_dois){
        vector<int>commonElements;
        set_intersection(lista_um.begin(), lista_um.end(),
                         lista_dois.begin(), lista_dois.end(),
                         back_inserter(commonElements));
        return commonElements;
    }
    vector<int> buscaFilmesPorAno(int startYear){
        shared_ptr<RedBlackNode> node = startYearTree.search(startYear);
        if (node != nullptr)
            return node->codeIds;
        else
            return vector<int>();
    }
    vector<int> buscaFilmesPorTempo(int runTimeMinutes){
        shared_ptr<RedBlackNode> node = runTimeTree.search(runTimeMinutes);
        if (node != nullptr)
            return node->codeIds;
        else
            return vector<int>();
    }
};
#endif //TBO_2024_01_TRIAGEM_H
