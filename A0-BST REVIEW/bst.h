#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

class bstree {
public:
    bstree();

    //Task 1
    void insert(int x);
    int search(int x);    
    void remove(int x);
    void printBST();

    //Task 2
    void in();
    void pre();
    void post();
    bool isBalanced();
    int height(int x);

    //Task 3
    bool isWorstCase();
    int countNodes();
    int insertCost;
    int searchcost;

    void processCommands(const char* filename);

private:
    void insertR(int t, int x);
    int searchI(int x);
    int searchR(int x, int r);
    int minIndex(int r);
    void removeR(int r, int x);

    void pre(int r);
    void in(int r);
    void post(int r);

    int heightR(int r);
    bool isBalancedR(int r);
    int countNodesR(int r);

    int* tr;  // array
    int last; // last valid location
};

#endif
