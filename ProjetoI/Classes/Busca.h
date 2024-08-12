//
// Created by João on 12/08/24.
//

#ifndef TBO_2024_01_BUSCA_H
#define TBO_2024_01_BUSCA_H
#include "Triagem.h"

class Busca : public Triagem  {

public:
    Busca (){}
    
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
    vector<int> findCommomCodeId(vector<int>& lista_um, vector<int>& lista_dois){
        vector<int>commonElements;
        set_intersection(lista_um.begin(), lista_um.end(),lista_dois.begin(), lista_dois.end(),
                         back_inserter(commonElements));
        return commonElements;
    }
    vector<int> buscaFilmesPorAno(RedBlackTree startYearTree, int startYear){
        RedBlackNode* node = startYearTree.search(startYear);
        if (node != nullptr)
            return node->codeIds;
        else
            return vector<int>();
    }



};


#endif //TBO_2024_01_BUSCA_H
