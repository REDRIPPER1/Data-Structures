#include "splay.h"
#include "CustomErrorClass.h"
using namespace std;

SplayTree::SplayTree() 
{
    root = nullptr; 
}

// aka Zig
SplayTree::Node* SplayTree::rotateRight(Node* x) {
    totalRotations++;
    Node* y = x->left;
    x->left = y->right;

    if (y->right != nullptr) {
        y->right->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y; 
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent=y;
    return y;
}

// aka Zag
SplayTree::Node* SplayTree::rotateLeft(Node* x) {
    totalRotations++;
    Node* y = x->right;
    x->right = y->left; 
    
    if (y->left != nullptr) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y; 
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return y;
}

// Splaying :)
//bottom up approach going to the end and splaying up

// ...existing code...
SplayTree::Node* BottomUpSplayTree::splay(SplayTree::Node* rootNode, int key) {
    if (!rootNode)
        return nullptr;

    // 1. Find the target node to splay
    SplayTree::Node* curr = rootNode;
    SplayTree::Node* target = nullptr;

    while (curr != nullptr) {
        target = curr; 
        if (key == curr->key) 
            break;
        if (key < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }

    // 2. Splay the target up to the root
    while (target != nullptr && target->parent != nullptr) {
        SplayTree::Node* p = target->parent;
        SplayTree::Node* g = p->parent;

        if (g == nullptr) { // Zig or Zag 
            if (p->left == target) rotateRight(p);
            else rotateLeft(p);
        } else if (g->left == p && p->left == target) { // Zig-Zig (Case 2)
            rotateRight(g);
            rotateRight(p);
        } else if (g->right == p && p->right == target) { // Zag-Zag (Case 2)
            rotateLeft(g);
            rotateLeft(p);
        } else if (g->left == p && p->right == target) { // Zig-Zag (Case 3)
            rotateLeft(p);
            rotateRight(g);
        } else { // Zag-Zig (Case 3)
            rotateRight(p);
            rotateLeft(g);
        }
    }

    root = target; 
    return root;
}
// ...existing code...

//anothe version of splay // one pass no going all the way down and coming up
/*SplayTree:: Node * TopDownSplayTree::splay(Node* root, int key){ 

        if(root==nullptr || root->key ==key){
                return root;
        }
                
        //key is in left subtree
        if(key<root->key){
    
            if(root->left==nullptr)
                  return root;

            //zig zig
            if(key<root->left->key){ 
                root->left->left = splay(root->left->left,key); //fix this
                root=rotateRight(root);
            }

            else if(key > root->left->key){ //zig zag
                    root->left->right=splay(root->left->right,key);
                    if(root->left->right!= nullptr)
                          root->left   =rotateLeft(root->left);
                    
            }

            if(root->left==nullptr)
                return root;
            else
                return rotateRight(root->left);

        }
        //key is in right subtree
        if(key>root->key){

            if(root->right==nullptr)
                return root;

            //zag zag
            if(key<root->right->key){

                root->right->right= splay(root->right->right,key); //fix this
                root=rotateLeft(root);
            }//zag zig
            else if(key< root->right->key){


                root->right->left=splay(root->right->left,key);
                if(root->right->left!= nullptr)
                    root->right =rotateRight(root->right);
            }

            if(root->right==nullptr)
                return root;
            else
                return rotateLeft(root);

        }
    return root;
}
*/
// ...existing code...
SplayTree::Node* TopDownSplayTree::splay(Node* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }

    if (key < root->key) {
        if (root->left == nullptr) {
            return root;
        }

        if (key < root->left->key) {            // zig-zig
            root->left->left = splay(root->left->left, key);
            root = rotateRight(root);
        } else if (key > root->left->key) {     // zig-zag
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr) {
                root->left = rotateLeft(root->left);
            }
        }

        if (root->left != nullptr && root->left->key == key) {
            return rotateRight(root);
        } else {
            return root;
        }
    } else { // key > root->key
        if (root->right == nullptr) {
            return root;
        }

        if (key > root->right->key) {           // zag-zag
            root->right->right = splay(root->right->right, key);
            root = rotateLeft(root);
        } else if (key < root->right->key) {    // zag-zig
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr) {
                root->right = rotateRight(root->right);
            }
        }

        if (root->right != nullptr && root->right->key == key) {
            return rotateLeft(root);
        } else {
            return root;
        }
    }
}
// ...existing code...

SplayTree::Node* WeightedSplay::splay(Node* root, int key) {
    if (root == nullptr || root->key == key) {
        if (root) root->weight++;  // increment weight on successful search
        return root;
    }

    // key is in left subtree
    if (key < root->key) {
        if (root->left == nullptr)
            return root;

        // zig zig
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            
            // Rotate only if child weight >= parent weight
            if (root->left->left && root->left->left->weight >= root->left->weight) {
                root = rotateRight(root);
            }
        }
        // zig zag
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            
            if (root->left->right && root->left->right->weight >= root->left->weight)
                root->left = rotateLeft(root->left);
        }

        // Final rotation only if weight condition met
        if (root->left == nullptr)
            return root;
        else if (root->left->weight >= root->weight)
            return rotateRight(root);
        else
            return root;
    }

    // key is in right subtree
    if (key > root->key) {
        if (root->right == nullptr)
            return root;

        // zag zag
        if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            
            if (root->right->right && root->right->right->weight >= root->right->weight) {
                root = rotateLeft(root);
            }
        }
        // zag zig
        else if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            
            if (root->right->left && root->right->left->weight >= root->right->weight)
                root->right = rotateRight(root->right);
        }

        // Final rotation only if weight condition met
        if (root->right == nullptr)
            return root;
        else if (root->right->weight >= root->weight)
            return rotateLeft(root);
        else
            return root;
    }

    return root;
}
// Semi-splay with  (k rotations max)
SplayTree::Node* SemiSplayTree::splay(SplayTree::Node* rootNode, int key) {
    if (rootNode == nullptr) return nullptr;

    Node* x = rootNode;
    Node* target = nullptr;
    
    while (x != nullptr) {
        target = x;
        if (key == x->key) break;
        x = (key < x->key) ? x->left : x->right;
    }
    
    // Use the found node  for splaying
    x = target;
    int rotationCount = 0;
    int maxRotations = 50000; // i chose of the halfway point

    //splaying
    while (x && x->parent && rotationCount < maxRotations) {
        Node* parent = x->parent;
        Node* grandparent = parent->parent;
        
        // Zig step
        if (!grandparent) {
            if (x == parent->left) rotateRight(parent);
            else rotateLeft(parent);
            rotationCount++;
        }
        // Zig-zig step
        else if ((x == parent->left && parent == grandparent->left)) {
            rotateRight(grandparent);
            rotateRight(parent);
            rotationCount += 2;
        }
        else if ((x == parent->right && parent == grandparent->right)) {
            rotateLeft(grandparent);
            rotateLeft(parent);
            rotationCount += 2;
        }
        // Zig-zag step
        else {
            if (x == parent->left) {
                rotateRight(parent);
                rotateLeft(grandparent);
            } else {
                rotateLeft(parent);
                rotateRight(grandparent);
            }
            rotationCount += 2;
        }
    }
    

    return root;
}


SplayTree::Node * SplayTree:: insertNode(Node * root, int key) {

    
        if(!root){
            root= new Node(key);
            return root;
        }

        root= splay(root,key); 

        if(root->key==key)
            return root;

        Node * newNode = new Node(key);

        if (key<root->key){
            newNode->right= root;
            newNode->left = root->left;

            root->parent = newNode;
            if (newNode->left != nullptr) {
            newNode->left->parent = newNode;
        }
            root->left= nullptr;
        }else{
            newNode->left= root;
            newNode->right= root->right;
            root->parent = newNode;
            if (newNode->right != nullptr) {
            newNode->right->parent = newNode;
            }
            root->right=nullptr;
        }
        root=newNode;
        return newNode; 
    
}

void SplayTree::insert(int key) {
    root = insertNode(root, key);
}


SplayTree::Node* SplayTree::deleteNode(Node* root, int key) {
    if(!root)
        return nullptr;
    Node * curr=root;
    Node * lastVisited = nullptr;
    while(curr!= nullptr && curr->key!= key){
            lastVisited= curr;
            if (key< curr->key)
                curr= curr->left;
            else
                curr= curr->right;
    }
    if (!curr) {
         if (lastVisited) {
            root = splay(root, lastVisited->key);
    }
    return root; 
    }
    Node* splayTarget = curr->parent;
    Node* replacement = nullptr;
    
    if (!curr->left) {
        replacement = curr->right;
    } else if (!curr->right) {
        replacement = curr->left;
    } 
    else {
        Node* successor = curr->right;
        while (successor->left) successor = successor->left;
        
        if (successor->parent != curr) {
            splayTarget = successor->parent; 
            successor->parent->left = successor->right;
            if (successor->right) successor->right->parent = successor->parent;
            
            successor->right = curr->right;
            successor->right->parent = successor;
        } else {
            splayTarget = successor; 
        }
        
        replacement = successor;
        replacement->left = curr->left;
        replacement->left->parent = replacement;
    }

    if (!curr->parent) {
        root = replacement;
    } else if (curr == curr->parent->left) {
        curr->parent->left = replacement;
    } else {
        curr->parent->right = replacement;
    }

    if (replacement) replacement->parent = curr->parent;

    delete curr;

    if (splayTarget) {
        root = splay(root, splayTarget->key);
    }

    return root;
}


void SplayTree::remove(int key) {
    root = deleteNode(root, key);
}


bool SplayTree:: search(int key){
    try{
        if(root==nullptr)
            throw MyException("Empty Tree");
        
        //calculate depth
        int depth = 0;
        Node* curr = root;
        while (curr != nullptr && curr->key != key) {
            depth++;
            if (key < curr->key) curr = curr->left;
            else curr = curr->right;
        }
        
        
        totalSearchDepth += depth;
        searchCount++;
        root= splay(root,key);

        return(root != nullptr && root->key == key);

    }
    catch(MyException& c){
        cerr<< c.what()<<endl;
        return false;
    }


}
void SplayTree::printTree(Node* root, int space) {
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
    cout << root->key << endl;

    // Print the left child
    printTree(root->left, space);
}

void SplayTree::display() {
    printTree(root, 0);
    cout << endl;
}

