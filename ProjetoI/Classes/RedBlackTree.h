//
// Created by João on 12/08/24.
//

#ifndef TBO_2024_01_REDBLACKTREE_H
#define TBO_2024_01_REDBLACKTREE_H


#include <vector>
#include <algorithm>

using namespace std;
enum Color { RED, BLACK };

class RedBlackNode {
public:
    int startYear;
    std::vector<int> codeIds;
    Color color;
    RedBlackNode *left, *right, *parent;

    RedBlackNode(int year) : startYear(year), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

    void insertCodeId(int codeId) {
        codeIds.push_back(codeId);
        sort(codeIds.begin(), codeIds.end());
    }
};

class RedBlackTree {
private:
    RedBlackNode* root;

    // Utility functions for Red-Black Tree operations (rotate, fix violations, etc.)
    void rotateLeft(RedBlackNode*& root, RedBlackNode*& pt) {
        RedBlackNode* pt_right = pt->right;
        pt->right = pt_right->left;

        if (pt->right != nullptr)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void rotateRight(RedBlackNode*& root, RedBlackNode*& pt) {
        RedBlackNode* pt_left = pt->left;
        pt->left = pt_left->right;

        if (pt->left != nullptr)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void fixViolation(RedBlackNode*& root, RedBlackNode*& pt) {
        RedBlackNode* parent_pt = nullptr;
        RedBlackNode* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) &&
               (pt->parent->color == RED)) {

            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            // Caso A: O pai de pt é o filho esquerdo do avô de pt
            if (parent_pt == grand_parent_pt->left) {

                RedBlackNode* uncle_pt = grand_parent_pt->right;

                /* Caso 1: O tio de pt também é vermelho */
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    /* Caso 2: pt é o filho direito do seu pai */
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    /* Caso 3: pt é o filho esquerdo do seu pai */
                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }

                /* Caso B: O pai de pt é o filho direito do avô de pt */
            else {
                RedBlackNode* uncle_pt = grand_parent_pt->left;

                /* Caso 1: O tio de pt também é vermelho */
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    /* Caso 2: pt é o filho esquerdo do seu pai */
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    /* Caso 3: pt é o filho direito do seu pai */
                    rotateLeft(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK;
    }

    RedBlackNode* insertBST(RedBlackNode* root, RedBlackNode* pt) {
        if (root == nullptr)
            return pt;

        if (pt->startYear < root->startYear) {
            root->left = insertBST(root->left, pt);
            root->left->parent = root;
        } else if (pt->startYear > root->startYear) {
            root->right = insertBST(root->right, pt);
            root->right->parent = root;
        } else {
            root->insertCodeId(pt->codeIds[0]);
            return root;
        }

        return root;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int startYear, int codeId) {
        RedBlackNode* pt = new RedBlackNode(startYear);
        pt->insertCodeId(codeId);
        root = insertBST(root, pt);
        fixViolation(root, pt);
    }

    RedBlackNode* search(int startYear) const {
        RedBlackNode* current = root;
        while (current != nullptr) {
            if (startYear < current->startYear) {
                current = current->left;
            } else if (startYear > current->startYear) {
                current = current->right;
            } else {
                return current;
            }
        }
        return nullptr;
    }
};



#endif //TBO_2024_01_REDBLACKTREE_H
