#include "dsw.h"

// ----------------- PRIVATE ----------------------------------

// when left-heavy tree
void BST::rotateRight(Node*& node) // passing the parent
{
    if(node == nullptr || node->left == nullptr)
        return;
    
    // get the node to rotate R
    Node* leftChild = node->left; 
    // 1) leftnode's right child is going to become parent's left child
    node->left = leftChild->right;
    // 2) parent is going to be right child of node that is rotated
    leftChild->right = node;
    
    node = leftChild;
}

// when right-heavy
void BST::rotateLeft(Node*& node)
{
    if(node == nullptr || node->right == nullptr)
        return;

    // get the node to rotate L
    Node* rightChild = node->right;
    // 1) rightnode's left child is going to become parent's right child
    node->right = rightChild->left;
    // 2) parent is going to be left child of node that is rotated
    rightChild->left = node;

    node = rightChild;
}

// utility: count nodes in a subtree (used by both phases)
int BST::countNodes(Node* node)
{
    if (node == nullptr)
        return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

// Phase 1 - create a **left‑skewed vine** from the current tree
// our variation: rotate left when a right child exists and its subtree
// has more than two nodes; otherwise advance without rotating.
void BST::createVine()
{
    // sentinel to simplify edge cases when the root itself is rotated
    Node* pseudo = new Node(0);
    pseudo->left = root;

    Node* vineTail = pseudo;
    Node* remainder = root;

    // traverse down the tree, performing left rotations as needed
    while (remainder != nullptr) {
        if (remainder->right != nullptr && countNodes(remainder->right) > 2) {
            // rotate left at remainder; after rotation the subtree root
            // changes, so update vineTail->left to point at new root
            rotateLeft(remainder);
            vineTail->left = remainder;
            // remainder still points to the node that replaced the old one
        } else {
            // no rotation, move vineTail down and continue along left branch
            vineTail = remainder;
            remainder = remainder->left;
        }
    }

    root = pseudo->left;
    delete pseudo;
}

void BST::rebuildTree(int size)
{

    int rotations = size / 2;
    while (rotations > 0) {
        performRotation(rotations);
        size = rotations;
        rotations = size / 2;
    }
}

// right rotate every second node along the left‑skewed vine
void BST::performRotation(int count)
{
    Node** curr = &root;
    for (int i = 0; i < count; ++i) {
        if (*curr == nullptr || (*curr)->left == nullptr)
            break;
        rotateRight(*curr);
        curr = &((*curr)->right);
    }
}

void BST::printTree(Node* root, int space) {
    const int COUNT = 10; 

    if (root == nullptr) {
        return;
    }

    // Increase the distance between levels
    space += COUNT;

    // Print the right child first (to appear on top)
    printTree(root->right, space);

    // Print the current node after right child

    for (int i = COUNT; i < space; i++) {
        cout << " "; // Indentation for tree depth
    }
    cout << root->data << endl;

    // Print the left child
    printTree(root->left, space);
}

// --------------------- PUBLIC ------------------
BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    deleteTree(root);
}

void BST::deleteTree(Node*& node)
{
    if(node == nullptr)
        return;
    
    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

void BST::insert(int val)
{
    Node* newNode = new Node(val);
    if(root == nullptr){
        root = newNode;
        return;
    }
    
    Node* curr = root;
    Node*parent = nullptr;

    while(curr != nullptr)
    {
        parent = curr;
        if(val < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if(val < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
}

void BST::dswBalance()
{
    // 1. create a vine (chain of left children) with the modified rules
    createVine();
    
    // 2. count nodes in the vine
    int n = countNodes(root);

    // 3. rebuild the tree performing a sequence of right rotations
    rebuildTree(n);
}

void BST::display()
{
    cout << endl;
    printTree(root, 0);
    cout << endl;
}