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
    void insereStartYear(int startYear, int codeId) {
        startYearTree.insert(startYear, codeId);
    }

};


#endif //TBO_2024_01_TRIAGEM_H
