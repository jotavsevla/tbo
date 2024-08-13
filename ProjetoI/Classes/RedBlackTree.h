#ifndef TBO_2024_01_REDBLACKTREE_H
#define TBO_2024_01_REDBLACKTREE_H

#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

enum Color { RED, BLACK };

class RedBlackNode {
public:
    int startYear;
    vector<int> codeIds;
    Color color;
    shared_ptr<RedBlackNode> left, right, parent;

    RedBlackNode(int year) : startYear(year), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

    void insertCodeId(int codeId) {
        codeIds.push_back(codeId);
    }
};

class RedBlackTree {
private:
    shared_ptr<RedBlackNode> root;

    // Rotação à esquerda
    void rotateLeft(shared_ptr<RedBlackNode>& node) {
        shared_ptr<RedBlackNode> nodeRight = node->right;
        node->right = nodeRight->left;

        if (node->right != nullptr)
            node->right->parent = node;

        nodeRight->parent = node->parent;

        if (node->parent == nullptr)
            root = nodeRight;
        else if (node == node->parent->left)
            node->parent->left = nodeRight;
        else
            node->parent->right = nodeRight;

        nodeRight->left = node;
        node->parent = nodeRight;
    }

    // Rotação à direita
    void rotateRight(shared_ptr<RedBlackNode>& node) {
        shared_ptr<RedBlackNode> nodeLeft = node->left;
        node->left = nodeLeft->right;

        if (node->left != nullptr)
            node->left->parent = node;

        nodeLeft->parent = node->parent;

        if (node->parent == nullptr)
            root = nodeLeft;
        else if (node == node->parent->left)
            node->parent->left = nodeLeft;
        else
            node->parent->right = nodeLeft;

        nodeLeft->right = node;
        node->parent = nodeLeft;
    }

    // Corrige violações da árvore rubro-negra
    void fixViolation(shared_ptr<RedBlackNode> node) {
        while (node != root && node->color == RED && node->parent != nullptr && node->parent->color == RED) {
            shared_ptr<RedBlackNode> parentNode = node->parent;
            shared_ptr<RedBlackNode> grandParentNode = parentNode->parent;

            if (grandParentNode != nullptr) {
                // Caso A: O pai do nó é o filho esquerdo do avô do nó
                if (parentNode == grandParentNode->left) {
                    shared_ptr<RedBlackNode> uncleNode = grandParentNode->right;

                    // Caso 1: O tio do nó também é vermelho
                    if (uncleNode != nullptr && uncleNode->color == RED) {
                        grandParentNode->color = RED;
                        parentNode->color = BLACK;
                        uncleNode->color = BLACK;
                        node = grandParentNode;
                    } else {
                        // Caso 2: O nó é o filho direito do seu pai
                        if (node == parentNode->right) {
                            rotateLeft(parentNode);
                            node = parentNode;
                            parentNode = node->parent;
                            grandParentNode = parentNode->parent;
                        }

                        // Caso 3: O nó é o filho esquerdo do seu pai
                        if (grandParentNode != nullptr) {
                            rotateRight(grandParentNode);
                            swap(parentNode->color, grandParentNode->color);
                            node = parentNode;
                        }
                    }
                } else {
                    // Caso B: O pai do nó é o filho direito do avô do nó
                    shared_ptr<RedBlackNode> uncleNode = grandParentNode->left;

                    // Caso 1: O tio do nó também é vermelho
                    if (uncleNode != nullptr && uncleNode->color == RED) {
                        grandParentNode->color = RED;
                        parentNode->color = BLACK;
                        uncleNode->color = BLACK;
                        node = grandParentNode;
                    } else {
                        // Caso 2: O nó é o filho esquerdo do seu pai
                        if (node == parentNode->left) {
                            rotateRight(parentNode);
                            node = parentNode;
                            parentNode = node->parent;
                            grandParentNode = parentNode->parent;
                        }

                        // Caso 3: O nó é o filho direito do seu pai
                        if (grandParentNode != nullptr) {
                            rotateLeft(grandParentNode);
                            swap(parentNode->color, grandParentNode->color);
                            node = parentNode;
                        }
                    }
                }
            } else {
                // Se o avô do nó atual é nullptr, apenas pintar o pai de preto e sair do loop
                parentNode->color = BLACK;
                node = parentNode;
                break;
            }
        }

        if (root != nullptr) root->color = BLACK;

    }

    // Função auxiliar para inserção BST

shared_ptr<RedBlackNode> insertBST(shared_ptr<RedBlackNode> root, shared_ptr<RedBlackNode> newNode) {
    if (root == nullptr)
        return newNode;

    if (newNode->startYear < root->startYear) {
        root->left = insertBST(root->left, newNode);
        root->left->parent = root;
    } else if (newNode->startYear > root->startYear) {
        root->right = insertBST(root->right, newNode);
        root->right->parent = root;
    } else {
        root->insertCodeId(newNode->codeIds[0]);
        return root;
    }

    return root;
}

public:
    RedBlackTree() : root(nullptr) {}

    ~RedBlackTree() {
        // A limpeza da árvore é automática com shared_ptr
    }

    // Insere um novo código ID para um ano específico na árvore
    void insert(int chave, int codeId) {

        if (root == nullptr) {
            auto newNode = make_shared<RedBlackNode>(chave);
            root = newNode;
            newNode->insertCodeId(codeId);
        } else {
            auto existingNode = search(chave);
            if (existingNode != nullptr)
                existingNode->insertCodeId(codeId);
            else {
                auto newNode = make_shared<RedBlackNode>(chave);
                newNode->insertCodeId(codeId);
                root = insertBST(root, newNode);
                fixViolation(newNode);
            }
        }

    }

    // Busca um nó pelo ano de início
    shared_ptr<RedBlackNode> search(int startYear) const {
        auto currentNode = root;
        while (currentNode != nullptr) {
            if (startYear < currentNode->startYear) {
                currentNode = currentNode->left;
            } else if (startYear > currentNode->startYear) {
                currentNode = currentNode->right;
            } else {
                return currentNode;
            }
        }
        return nullptr;
    }
};

#endif //TBO_2024_01_REDBLACKTREE_H
