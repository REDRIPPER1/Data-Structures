#include "binomial.h"
#include <climits>
#include "CustomErrorClass.h"

binomialNode::binomialNode(int k)
{
    key = k;
    degree = 0;
    sibling = nullptr;
    child = nullptr;
    parent = nullptr;
}

// ---------------------- PRIVATE FUNCTIONS ------------------------------
binomialNode* BinomialHeap::unionHeap(binomialNode* heap1, binomialNode* heap2)
{
    binomialNode* newHead = nullptr;
    binomialNode** pos = &newHead;

    // Merge the two heaps
    while (heap1 != nullptr && heap2 != nullptr) {
        if (heap1->degree <= heap2->degree) {
            *pos = heap1;
            heap1 = heap1->sibling;
        } else {
            *pos = heap2;
            heap2 = heap2->sibling;
        }
        pos = &((*pos)->sibling);
    }
    *pos = (heap1 != nullptr) ? heap1 : heap2;

    // Consolidate
    if (newHead == nullptr) return nullptr;

    binomialNode* prev = nullptr;
    binomialNode* curr = newHead;
    binomialNode* next = curr->sibling;

    while (next != nullptr) {
        if (curr->degree != next->degree || (next->sibling != nullptr && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->key <= next->key) {
                curr->sibling = next->sibling;
                mergeTrees(curr, next);
            } else {
                if (prev == nullptr) {
                    newHead = next;
                } else {
                    prev->sibling = next;
                }
                mergeTrees(next, curr);
                curr = next;
            }
        }
        next = curr->sibling;
    }

    return newHead;
}


binomialNode* BinomialHeap::mergeTrees(binomialNode* tree1, binomialNode* tree2)
{
    if (tree1->key > tree2->key) {
        swap(tree1, tree2);
    }
    tree2->parent = tree1;
    tree2->sibling = tree1->child;
    tree1->child = tree2;
    tree1->degree++;
    return tree1;
}

void BinomialHeap::linkTrees(binomialNode*& prev, binomialNode*& cur, binomialNode*& next)
{
    binomialNode* temp = cur->sibling;
    cur->sibling = next;
    if (prev != nullptr) {
        prev->sibling = temp;
    } else {
        head = temp;
    }
    cur = mergeTrees(cur, next);
    next = cur->sibling;
}

binomialNode* BinomialHeap::findNode(int key)
{
    binomialNode* current = head;
    while (current != nullptr) {
        binomialNode* found = findInTree(current, key);
        if (found != nullptr) return found;
        current = current->sibling;
    }
    return nullptr;
}

binomialNode* BinomialHeap::findInTree(binomialNode* node, int key)
{
    if (node == nullptr) return nullptr;
    if (node->key == key) return node;

    // Check children
    binomialNode* child = node->child;
    while (child != nullptr) {
        binomialNode* found = findInTree(child, key);
        if (found != nullptr) return found;
        child = child->sibling;
    }
    return nullptr;
}

// ---------------- PUBLIC FUNCTIONS ------------------------------
BinomialHeap::BinomialHeap()
{
    head = nullptr;
}

void BinomialHeap::insert(int key)
{
    binomialNode* newNode = new binomialNode(key);
    head = unionHeap(head, newNode);
}

void BinomialHeap::merge(BinomialHeap& other)
{
    head = unionHeap(head, other.head);
    other.head = nullptr;
}

int BinomialHeap::findMin()
{
    if (head == nullptr) {
        throw MyException("Heap is empty");
    }
    binomialNode* minNode = head;
    binomialNode* current = head->sibling;
    while (current != nullptr) {
        if (current->key < minNode->key) {
            minNode = current;
        }
        current = current->sibling;
    }
    return minNode->key;
}

void BinomialHeap::deleteMin()
{
    if (head == nullptr) {
        throw MyException("Cannot deleteMin from an empty heap");
    }

    binomialNode* minNode = head;
    binomialNode* minPrev = nullptr;
    binomialNode* current = head;

    // Find the minimum root
    while (current->sibling != nullptr) {
        if (current->sibling->key < minNode->key) {
            minNode = current->sibling;
            minPrev = current;
        }
        current = current->sibling;
    }

    // Remove minNode from root list
    if (minPrev == nullptr) {
        head = minNode->sibling;
    } else {
        minPrev->sibling = minNode->sibling;
    }

    // Reverse the children list
    binomialNode* child = minNode->child;
    binomialNode* reversed = nullptr;
    while (child != nullptr) {
        binomialNode* next = child->sibling;
        child->sibling = reversed;
        child->parent = nullptr;
        reversed = child;
        child = next;
    }

    // Union the reversed children with the heap
    head = unionHeap(head, reversed);

    delete minNode;
}
void BinomialHeap::decreaseKey(int oldKey, int newKey)
{
    binomialNode* node = findNode(oldKey);
    if (node == nullptr) {
        throw MyException("decreaseKey: key not found");
    }

    if (newKey > node->key) {
        throw MyException("decreaseKey: new key is greater than current key");
    }

    node->key = newKey;

    // Bubble up
    binomialNode* current = node;
    while (current->parent != nullptr && current->key < current->parent->key) {
        swap(current->key, current->parent->key);
        current = current->parent;
    }
}

void BinomialHeap::deleteKey(int key)
{
    binomialNode* node = findNode(key);
    if (node == nullptr) {
        throw MyException("deleteKey: key not found");
    }

    decreaseKey(key, INT_MIN);
    deleteMin();
}

void BinomialHeap::printHeap() {
    cout << "Binomial Heap:\n";
    binomialNode* current = head;


    while (current != nullptr) {
        cout << endl << "Tree of degree " << current->degree << endl;
        printTree(current, 0);
        current = current->sibling;
    }

}

void BinomialHeap::printTree(binomialNode* node, int space) 
{
    if (node == nullptr) 
        return;

    cout << setw(space * 2) << node->key << endl;

    binomialNode* child = node->child;
    while (child) {
        printTree(child, space + 3);
        child = child->sibling;
    }
}