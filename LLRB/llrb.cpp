#include "llrb.h"

// Public interface methods - what the outside world sees

LLRBTREE::LLRBTREE() {
    root = nullptr;
}

LLRBTREE::~LLRBTREE() {
    deleteSubtree(root);
}

void LLRBTREE::insert(int key) {
    try {
        root = insertR(root, key);
        root->color = BLACK; // The root must always be strictly BLACK in an LLRB tree
    } 
    catch (MyException& e) {
        // Oops! Something went wrong during insertion. Let's catch that error and tell the user
        cout << "Insertion Error: " << e.what() << endl;
    }
}

void LLRBTREE::remove(int key) {
   
}

void LLRBTREE::printTree() {
    if(root == nullptr)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    print(root, 0);
}

// Private helper methods - the behind-the-scenes magic
bool LLRBTREE::isRed(Node* x) {
    if (x == nullptr) return false;
    return x->color == RED;
}

Node* LLRBTREE::leftRotate(Node* h) {
    Node* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

Node* LLRBTREE::rightRotate(Node* h) {
    Node* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

void LLRBTREE::flipColors(Node* h) {
    h->color = RED;
    h->left->color = BLACK;
    h->right->color = BLACK;
}

Node* LLRBTREE::insertR(Node* h, int key) {
    // First, do the basic BST insert like we learned in class
    if (h == nullptr) {
        return new Node(key);
    }

    if (key < h->data) {
        h->left = insertR(h->left, key);
    } else if (key > h->data) {
        h->right = insertR(h->right, key);
    } else {
        // Hey, we don't allow duplicate keys! That's not cool.
        throw MyException("Duplicate key insertion is not allowed.");
    }

    // Now, let's make sure our tree stays balanced and follows LLRB rules
    // If the right kid is red but left is black, time to rotate left!
    if (isRed(h->right) && !isRed(h->left)) {
        h = leftRotate(h);
    }
    
    // If left is red and left's left is also red, rotate right to fix it
    if (isRed(h->left) && isRed(h->left->left)) {
        h = rightRotate(h);
    }
    
    // When both kids are red, let's flip the colors to balance things out
    if (isRed(h->left) && isRed(h->right)) {
        flipColors(h);
    }

    return h;
}

void LLRBTREE::removeR(Node*& node, int key) {

}

void LLRBTREE::deleteSubtree(Node* node) {
   
}

void LLRBTREE::print(Node* root, int space) {
    if (root == nullptr)
        return;

    space += 10;
    print(root->right, space);

    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";

    string color_code = (root->color == RED) ? RED_COLOR : BLACK_COLOR;
    cout << color_code << root->data << RESET_COLOR;
    cout << endl;
    print(root->left, space);
}