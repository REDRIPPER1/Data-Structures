#include "bst.h"
#include <iostream>

// Use 64 as size
bstree::bstree() {
    tr = new int[64];
    last = 63;
    for (int k = 1; k <= last; k++)
        tr[k] = 0;

    insertCost = 0;
    searchcost = 0;
}

// Preorder traversal (Recursive)
void bstree::pre(int r) {
    if (r > last || tr[r] == 0)
        return;
    printf("%2d ", tr[r]);
    pre(r * 2);
    pre(r * 2 + 1);
}

void bstree::pre() {
    pre(1);
    cout << endl;
}

// Inorder traversal (Recursive)
void bstree::in(int r) {
    if (r > last || tr[r] == 0)
        return;
    in(r * 2);
    printf("%2d ", tr[r]);
    in(r * 2 + 1);
}

void bstree::in() {
    in(1);
    cout << endl;
}

// Postorder traversal (Recursive)
void bstree::post(int r) {
    if (r > last || tr[r] == 0)
        return;
    post(r * 2);
    post(r * 2 + 1);
    printf("%2d ", tr[r]);
}

void bstree::post() {
    post(1);
    cout << endl;
}

void bstree::printBST(){
    in();
}

// Insert - Recursive
void bstree::insertR(int r, int val) {
    if (r > last || tr[r] == val)
        return;

    insertCost++;

    if (tr[r] == 0) {
        tr[r] = val;
        return;
    }

    if (val < tr[r])
        insertR(r * 2, val);
    else
        insertR(r * 2 + 1, val);
}

void bstree::insert(int val) {
    insertR(1, val);
}

// Search - Iterative
int bstree::searchI(int val) {
    int r = 1;
    while (r <= last && tr[r] != 0) {
        searchcost++;

        if (tr[r] == val)
            return 1; // Found
        if (val < tr[r])
            r = r * 2;
        else
            r = r * 2 + 1;
    }
    return 0; // Not found
}

int bstree::search(int val) {
    return searchI(val);
}

int bstree::minIndex(int r)
{
    while (r <= last && tr[r * 2] != 0) {
        r = r * 2;
    }
    return r;
}

void bstree::removeR(int r, int val) {
    if (r > last || tr[r] == 0)
        return;

    if (val < tr[r]) {
        removeR(r * 2, val);
    } else if (val > tr[r]) {
        removeR(r * 2 + 1, val);
    } else {
        // Node found
        if (tr[r * 2] == 0 && tr[r * 2 + 1] == 0) {
            // No children
            tr[r] = 0;
        } else if (tr[r * 2] == 0) {
            // One child (right)
            tr[r] = tr[r * 2 + 1];
            tr[r * 2 + 1] = 0;
        } else if (tr[r * 2 + 1] == 0) {
            // One child (left)
            tr[r] = tr[r * 2];
            tr[r * 2] = 0;
        } else {
            // Two children
            int minR = minIndex(r * 2 + 1);
            tr[r] = tr[minR];
            removeR(minR, tr[minR]);
        }
    }
}

void bstree::remove(int val) {
    removeR(1, val);
}

//Height - Recursive
int bstree::heightR(int r) {
    if(r > last || tr[r] == 0)
        return -1;
    return 1 + max(heightR(r * 2), heightR(r * 2 + 1));
}

int bstree::height(int val){
    int r = 1;
    while(r <= last && tr[r] != 0){
        if(tr[r] == val)
            return heightR(r);
        if(val < tr[r])
            r = r * 2;
        else
            r = r * 2 + 1;
    }
    return -1;
}

//balanced - Recursive
bool bstree::isBalancedR(int r) {
    if (r > last || tr[r] == 0)
        return true;

    int leftHeight = heightR(r * 2);
    int rightHeight = heightR(r * 2 + 1);

    if (abs(leftHeight - rightHeight) > 1)
        return false;

    return isBalancedR(r * 2) && isBalancedR(r * 2 + 1);
}

bool bstree::isBalanced() {
    return isBalancedR(1);
}

bool bstree::isWorstCase() {
    int nodeCount = countNodes();
    int height = heightR(1);
    return height == nodeCount - 1;
}

int bstree::countNodesR(int r) {
    if (r > last || tr[r] == 0)
        return 0;
    return 1 + countNodesR(r * 2) + countNodesR(r * 2 + 1);
}

int bstree::countNodes() {
    return countNodesR(1);
}

// Process commands from file
void bstree::processCommands(const char* filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return;
    }

    int command, value;
    while (file >> command) {
        switch (command) {
            case 0: // Quit
                cout << "Nodes: " << countNodes() << endl;
                cout << "Height: " << heightR(1) << endl;
                cout << "Insert Cost: " << insertCost << endl;
                cout << "Search Cost: " << searchcost << endl;
                cout << "Is Worst Case: " << (isWorstCase() ? "Yes" : "No") << endl;
                return;
            case 1: // Insert
                file >> value;
                cout << "Insert " << value << endl;
                insert(value);
                break;
            case 2: // Search
                file >> value;
                printf("Search %d: %s\n", value, search(value) ? "Found" : "Not Found");
                break;
            case 3: // Preorder
                pre();
                break;
            case 4: // Inorder
                in();
                break;
            case 5: // Postorder
                post();
                break;
            case 6: // Height
                file >> value;
                printf("Height %d: %d\n", value, height(value));
                break;
            case 7: // IsBalanced
                printf("IsBalanced: %s\n", isBalanced() ? "Yes" : "No");
                break;
            case 8: // Remove
                file >> value;
                remove(value);
                break;
            default:
                cerr << "Invalid command: " << command << endl;
        }
    }
    file.close();
}
