#ifndef LLRBTREE_H
#define LLRBTREE_H

#include <iostream>
#include "CustomErrorClass.h"

using namespace std;

// Magic codes to make our tree colorful in the terminal
#define RED_COLOR "\033[1;31m"
#define BLACK_COLOR "\033[1;30m"
#define RESET_COLOR "\033[0m"

// Some handy constants we use
enum Color {RED, BLACK};

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;

    Node(int key) {
        data = key;
        left = nullptr;
        right = nullptr;
        color = RED; 
    }
};

class LLRBTREE {
    private:
        Node* root;
 
        bool isRed(Node* x);
        Node* leftRotate(Node* h);
        Node* rightRotate(Node* h);
        void flipColors(Node* h);

        // The heart of our tree operations, using recursion
        Node* insertR(Node* h, int key);
        void removeR(Node*& node, int key);
        
        void deleteSubtree(Node* node);
        void print(Node* root, int space);

    public:
        LLRBTREE();
        ~LLRBTREE();

        void insert(int key);
        void remove(int key);

        void printTree();
};

#endif