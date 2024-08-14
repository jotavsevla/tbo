//
// Created by João on 12/08/24.
//

#ifndef TBO_2024_01_BUSCA_H
#define TBO_2024_01_BUSCA_H
#include "Triagem.h"

class Busca : public Triagem  {

public:
    Busca (){}
    vector<int> buscaCombinada(int startYear, int endYear, int runTimeMinutes, vector<string> types, vector<string> genres, bool intervalo) {
        vector<int> results;

        if (startYear > 0) {
            vector<int> filmesPorAno = buscaFilmesPorAno(startYear);
            results = filmesPorAno;
        }

        // Filtragem por intervalo de anos
        if (intervalo && startYear > 0 && endYear > 0) {
            for (int ano = startYear; ano <= endYear; ++ano) {
                vector<int> filmesPorAno = buscaFilmesPorAno(ano);
                results = buscaPorCodeIdsCommon(results, filmesPorAno);
            }
        }

        // Filtragem por duração
        vector<int> filmesPorRuntime = buscaFilmesPorTempo(runTimeMinutes);
        results = buscaPorCodeIdsCommon(results, filmesPorRuntime);

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
        set_intersection(lista_um.begin(), lista_um.end(),lista_dois.begin(), lista_dois.end(),
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
