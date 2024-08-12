//
// Created by João on 12/08/24.
//

#ifndef TBO_2024_01_BUSCA_H
#define TBO_2024_01_BUSCA_H
#include "Triagem.h"

class Busca {
public:
    vector<int> buscaPorAno(const RedBlackTree& startYearTree, int startYear) const {
        RedBlackNode* node = startYearTree.search(startYear);
        if (node != nullptr)
            return node->codeIds;
        else
            return vector<int>();
    }

};


#endif //TBO_2024_01_BUSCA_H
