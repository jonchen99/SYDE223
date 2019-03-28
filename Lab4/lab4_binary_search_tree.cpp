// Jonathan Chen 20722167 && Aman Mathur 20710307
// April 1st, 2019
// SYDE 223 Lab #4
#include <iostream>
#include "lab4_binary_search_tree.h"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
    int size = 0;
    root = NULL;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
    return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
    if (size == 0)
        return BinarySearchTree::TaskItem(-1, "N/A");

    TaskItem *max = root;
    while (max->right != NULL) {
        max = max->right;
    }
    return *max;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
    if (size == 0)
        return BinarySearchTree::TaskItem(-1, "N/A");

    TaskItem *min = root;
    while (min->left != NULL) {
        min = min->left;
    }
    return *min;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
  return get_node_depth(root);
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {

}

// PURPOSE: Returns true if a node with the value val exists in the tree
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
    return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return NULL;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
    if (n == NULL) return -1;
    int left_depth = 1+get_node_depth(n->left);
    int right_depth = 1+get_node_depth(n->right);
//
    return left_depth > right_depth ? left_depth : right_depth;

//    return get_node_depth(n->left) >= get_node_depth(n->right) ? get_node_depth(n->left) : get_node_depth(n->right);
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
    if (root == NULL) {
        root = new TaskItem(val);
        return true;
    };

    TaskItem *cur = root;
    TaskItem *parent = NULL;

    while (cur != NULL){
        if (val.priority > cur->priority){
            parent = cur;
            cur = cur -> right;
        } else if ( val.priority == cur -> priority){
            return false;
        } else {
            parent = cur;
            cur = cur -> left;
        }
    }

    if (val.priority > parent -> priority){
        parent -> right = new TaskItem(val);
    } else {
        parent -> left = new TaskItem(val);
    }
    return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
    cout << "test remove";
    if (root == NULL) {
        cout << "root priority if";
        return false;
    } else {
        cout << "root priority else";

    }

    TaskItem *cur = root;
    TaskItem *parent = NULL;
    bool left = true;
    bool found = false;

    //Traverse tree until value is found
    while (!found) {
        //If value is larger than cur, move cur to right child
        if (val.priority > cur->priority) {
            parent = cur;
            cur = cur->right;
            left = false;
            //If value is smaller than cur, move cur to left child
        }
        else if (val.priority < cur->priority) {
            parent = cur;
            cur = cur->left;
            left = true;
            //If value is equal to given value, update flag
        }
        else if (val.priority == cur->priority) {
            found = true;

        }
        else {
            return false;
        }
    }


    // If two children;
    if (cur -> left != NULL && cur -> right != NULL) {

        TaskItem *maxOnLeft = cur->left;
        TaskItem *maxParent = cur;

        while (maxOnLeft ->right != NULL) {
            maxParent = maxOnLeft;
            maxOnLeft = maxParent -> right;
        }

        TaskItem *temp = cur;
        temp -> right = maxOnLeft -> right;
        temp -> left = maxOnLeft -> left;

        if (left){
            parent -> left = maxOnLeft;
        } else {
            parent -> right = maxOnLeft;
        }
        maxOnLeft -> left = cur -> left;
        maxOnLeft -> right = cur -> right;
        maxParent -> right = temp;
        cur = temp;
    }

    //If leaf node
    if (cur -> left == NULL && cur -> right == NULL){
        delete cur;
        if (left){
            parent-> left = NULL;
        } else {
            parent -> right = NULL;
        }

    //if one right child
    } else if (cur -> left == NULL && cur -> right != NULL){
        delete cur;
        parent -> left = cur -> right;

        //if one left child
    } else if (cur -> left != NULL && cur -> right == NULL){
       delete cur;
       parent -> left = cur -> left;

    }
}
