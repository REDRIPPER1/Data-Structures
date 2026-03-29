#include "llrb.h"

int main() {
    LLRBTREE rb;

    cout << "Inserting 10:" << endl;
    rb.insert(10);
    rb.printTree();

    cout << "Inserting 20:" << endl;
    rb.insert(20);
    rb.printTree();

    cout << "Inserting 30:" << endl;
    rb.insert(30);
    rb.printTree();

    cout << "Inserting 15:" << endl;
    rb.insert(15);
    rb.printTree();

    cout << "Inserting 25:" << endl;
    rb.insert(25);
    rb.printTree();
    
    cout << "Removing 20:" << endl;
    rb.remove(20);
    rb.printTree();

    // Extra test cases - uncomment these lines to try more insertions and removals
    // rb.insert(7);
    // rb.insert(11);
    // rb.insert(23);
    // rb.insert(33);
    // rb.insert(20);
    // rb.insert(22);
    // rb.insert(2);
    // rb.insert(5);
    // rb.insert(30);
    // rb.insert(27);
    // rb.insert(25);
    // rb.printTree();
    // rb.remove(2);
    // rb.remove(11);
    // rb.remove(23);
    // cout << "-------------------------------------" << endl;
    // rb.printTree();
    
    return 0;
}
