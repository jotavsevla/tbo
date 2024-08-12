//
// Created by João on 31/07/24.
//

#ifndef TBO_2024_01_TRIAGEM_H
#define TBO_2024_01_TRIAGEM_H
#include "TabelaHash.h"
#define MAXTYPE
class Triagem {
private:
    vector<HashFilmes> typeList;
    vector<HashFilmes> genresList;
    struct Node {
        int startYear;
        vector<int> codeIds;
        Node* left;
        Node* right;
    };

    Node* root;

public:
    Triagem(){
        typeList.reserve(60);
        genresList.reserve(90);
        root = nullptr;
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
        if (existeHashType(type) == -1) {
            HashFilmes anotherType(type);
            typeList.push_back(anotherType);
        }
        int indexHash = existeHashType(type);
        typeList[indexHash].insereNaHash(codeId);
    }
    void insereNaHashGenres(string genres, int codeId){
        if(existeHashGenres(genres)==-1){
            HashFilmes anotherGenre(genres);
            genresList.push_back(anotherGenre);
        }
        int indexHash = existeHashGenres(genres);
        genresList[indexHash].insereNaHash(codeId);
    }
    void insereStartYear(int startYear, int codeId) {
        Node* newNode = new Node();
        newNode->startYear = startYear;
        newNode->codeIds.push_back(codeId);

        if (root == nullptr) {
            root = newNode;
        } else {
            Node *current = root;
            while (true) {
                if (startYear < current->startYear) {
                    if (current->left == nullptr) {
                        current->left = newNode;
                        break;
                    }
                    current = current->left;
                } else {
                    if (current->right == nullptr) {
                        current->right = newNode;
                        break;
                    }
                    current = current->right;
                }
            }
        }
    }
};


#endif //TBO_2024_01_TRIAGEM_H
