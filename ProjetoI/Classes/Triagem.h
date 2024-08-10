//
// Created by João on 31/07/24.
//

#ifndef TBO_2024_01_TRIAGEM_H
#define TBO_2024_01_TRIAGEM_H
#include "TabelaHash.h"

class Triagem {
private:
    vector<HashFilmes> typeList;
    vector<HashFilmes> genresList;

public:
    Triagem(){}
    int existeHashType(string chave){
        int i = 0;
        int j = static_cast<int>(typeList.size() - 1);
        while (typeList[i].getChave() != chave && i < j) i++;
        if (typeList[i].getChave() != chave) return -1;
        return i;
    }
    int existeHashGenres(string chave){
        int i = 0;
        int j = static_cast<int>(genresList.size() - 1);
        while (genresList[i].getChave() != chave && i < j) i++;
        if(genresList[i].getChave() != chave) return -1;
        return i;
    }
    void insereNaHashType(string type, int indexHash, int codeId){
        if (!existeHashType(type)) {
            HashFilmes anotherType(type, codeId);
            typeList.push_back(anotherType);
        }
        typeList[indexHash].insereNaHash(codeId);
    }
    void insereNaHashGenres(string genres, int indexHash, int codeId){
        if(!existeHashGenres(genres)){
            HashFilmes anotherGenre(genres,codeId);
            genresList.push_back(anotherGenre);
        }
        genresList[indexHash].insereNaHash(codeId);
    }
};


#endif //TBO_2024_01_TRIAGEM_H
