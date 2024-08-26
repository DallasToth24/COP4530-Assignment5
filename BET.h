#ifndef BET_H
#define BET_H

#include <string>
#include <stack>
#include <iostream>
#include <sstream>

template<typename T>
class BET {
public:
    BET();
    BET(const std::string &postfix); 
    BET(const BET &other); 
    ~BET(); 
    bool buildFromPostfix(const std::string &postfix);
    const BET &operator=(const BET &other);
    void printInfixExpression();
    void printPostfixExpression();
    size_t size();
    size_t leaf_nodes();
    bool empty();

private:
    struct BinaryNode {
        T element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode(const T &e) : element(e), left(nullptr), right(nullptr) {}
        BinaryNode(const T &e, BinaryNode *leftChild, BinaryNode *rightChild) : element(e), left(leftChild), right(rightChild) {}
    };

    BinaryNode *root;
    void printInfixExpression(BinaryNode *n);
    void makeEmpty(BinaryNode* &t);
    BinaryNode *clone(BinaryNode *t) const;
    void printPostfixExpression(BinaryNode *n);
    size_t size(BinaryNode *t);
    size_t leaf_nodes(BinaryNode *t);
};

#include "BET.hpp"

#endif
