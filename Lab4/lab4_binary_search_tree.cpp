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
    return 0;
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
    return 0;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
    return false;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
    return false;
}
