//
// Created by João on 12/08/24.
//

#ifndef TBO_2024_01_BUSCA_H
#define TBO_2024_01_BUSCA_H
#include "Triagem.h"
#include <utility>
#include <algorithm>

class Busca : Triagem  {

public:
    Busca (){}
    vector<int> buscaCombinada(int startYear, int endYear, pair<int, int> runTimeMinutes, vector<string>& types,
                                vector<string>& genres, bool intervaloAno, bool intervaloTempo) {
        vector<int> results;

        if (intervaloAno && startYear > 0 && endYear > 0) {
            int ano = startYear;
            vector<int> filmesPorAno = buscaFilmesPorAno(ano);
            vector<int> temp;

            ++ano;
            while (ano <= endYear) {
                vector<int> buffer = buscaFilmesPorAno(ano);
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
            for (int tempo = runTimeMinutes.first; tempo <= runTimeMinutes.second; ++tempo) {
                vector<int> filmesPorRuntime = buscaFilmesPorTempo(tempo);
                results = buscaPorCodeIdsCommon(results, filmesPorRuntime);
            }
        }

        // Filtragem por tipo
        for (const auto& tipo : types) {
            vector<int> filmesPorType = buscaPorHashType(tipo);
            results = buscaPorCodeIdsCommon(results, filmesPorType);
        }

        // Filtragem por gênero
        for (const auto& genero : genres) {
            vector<int> filmesPorGenero = buscaPorHashGenres(genero);
            results = buscaPorCodeIdsCommon(results, filmesPorGenero);
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


#endif //TBO_2024_01_BUSCA_H
