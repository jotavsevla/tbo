//
// Created by João on 31/07/24.
//

#ifndef TBO_2024_01_TABELAHASH_H
#define TBO_2024_01_TABELAHASH_H
#include "Filme.h"
#include "Cinema.h"
#define HASH_MAX 90000
class HashFilmes{
private:
    string chave;
    int qntAtualItens, lastViewed;
    vector<int> codeIdFilmes;
public:
    HashFilmes(string chave) {
        this->chave = chave;
        codeIdFilmes.reserve(HASH_MAX);
        qntAtualItens = 0;
        lastViewed = 0;
    }
    bool insereNaHash(int codeId){
        codeIdFilmes.push_back(codeId);
        qntAtualItens++;
        return true;
    }
    int procuraNaHash(int codeId){
        while(codeIdFilmes[lastViewed] < codeId && lastViewed < qntAtualItens) lastViewed++;
        return codeIdFilmes[lastViewed] == codeId ? codeId : -1;
    }
    void setLastViewed(){this->lastViewed = 0;}
    string getChave(){return this->chave;}

};


#endif //TBO_2024_01_TABELAHASH_H
