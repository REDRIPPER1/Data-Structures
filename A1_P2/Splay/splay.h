#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
using namespace std;

class SplayTree {
    protected:
        struct Node {
            int key;
            int weight;
            Node* left;
            Node* right;
            Node *parent;
            Node(int k,Node * p =nullptr) {
                key = k;
                weight=0;
                left = nullptr;
                right = nullptr; 
                parent=p;
            }
        };

        Node* root;

        Node* rotateRight(Node* x);
        Node* rotateLeft(Node* x);

        virtual Node* splay(Node* root,int key)=0;

        Node* insertNode(Node* root, int key);
        //void insertNode(int key);

        Node* deleteNode(Node* root, int key);


        void printTree(Node* root, int space);

    public:
        SplayTree();
        long long totalRotations = 0;
        long long totalSearchDepth = 0;
        int searchCount = 0;
        void insert(int key);
        void remove(int key);
        int getDepth(int key);
        bool search(int key);
        void display();
        void resetMetrics(){
        totalRotations = 0;
        totalSearchDepth = 0;
        searchCount = 0;
        }
        
};

class BottomUpSplayTree: public SplayTree{
protected:
        Node *splay(Node *x, int key) override;
};

class TopDownSplayTree : public SplayTree {
protected:
    Node* splay(Node* x,int key) override;
};

class SemiSplayTree : public SplayTree {
protected:
    Node* splay(Node* root, int key) override;
};

class WeightedSplay : public SplayTree {
protected:
    Node* splay(Node* root, int key) override;
};

#endif 
