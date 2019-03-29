// Jonathan Chen 20722167 && Aman Mathur 20710307
// April 1st, 2019
// SYDE 223 Lab #4
#include <iostream>
#include "lab4_binary_search_tree.h"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
    size = 0;
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

    TaskItem *cur = root;
    while(cur != NULL)
    {
        if(cur ->priority == val.priority){
            return true;
        }

        if (cur ->priority > val.priority){
            cur = cur -> left;
        } else {
            cur = cur -> right;
        }

    }

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
        size++;
        return true;
    }

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
    size++;
    return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
    if (root == NULL) {
        return false;
    }

    TaskItem *cur = root;
    TaskItem *parent = root;
    bool left = true;
    bool found = false;

    //Traverse tree until value is found
    while (!found) {
        if (val.priority == cur->priority) {
            found = true;
        } else if (val.priority > cur->priority) {
            parent = cur;
            if (cur -> right != NULL) {
                cur = cur->right;
            } else {
                return false;
            }
            left = false;
            //If value is smaller than cur, move cur to left child
        } else if (val.priority < cur->priority) {
            parent = cur;
            if (cur -> left != NULL) {
                cur = cur->left;
            } else {
                return false;
            }
            left = true;
            //If value is equal to given value, update flag
        } else {
            return false;
        }
    }


    // If two children;
    if (cur -> left != NULL && cur -> right != NULL) {

        //Find maximum value (and parent) on left side of removal node
        TaskItem *maxOnLeftParent = cur;
        TaskItem *maxOnLeft = cur -> left;

        //Traverse down left side to find maximum
        while (maxOnLeft ->right != NULL) {
            maxOnLeftParent = maxOnLeft;
            maxOnLeft = maxOnLeft -> right;
        }

        //Create temp copy of removal node
        TaskItem *temp = cur;
        TaskItem tempCur = *cur;

        temp -> left = maxOnLeft -> left;
        temp -> right = maxOnLeft -> right;

        //Point parent to temp (to be removed)
        if (maxOnLeft->left == NULL) {
            maxOnLeftParent->right = NULL;
        } else {
            maxOnLeftParent->right = maxOnLeft->left;
        }

        maxOnLeft->left = tempCur.left;
        maxOnLeft->right = tempCur.right;

        if (maxOnLeft -> left->priority == maxOnLeft->priority){
            maxOnLeft -> left = NULL;
        }


        //set current to temp (to be removed);
        cur = temp;

        //set parent of removal node to max on left;
        if (root->priority != val.priority && left){
            parent -> left = maxOnLeft;
        } else if (root->priority != val.priority && !left) {
            parent -> right = maxOnLeft;
        } else if (root -> priority == val.priority) {
            root = maxOnLeft;
        }

    }


    //If leaf node
    if (cur -> left == NULL && cur -> right == NULL){
        //delete cur;
        if (cur->priority == root->priority){
            root = NULL;
            return true;
        }

        if (left){
            parent-> left = NULL;
        } else {
            parent -> right = NULL;
        }
        size--;

        return true;
    }
    //if one right child
    else if (cur -> left == NULL && cur -> right != NULL){
//        delete cur;
        if (left) {
            parent -> left = cur -> right;
        } else {
            parent -> right = cur -> right;
        }
        size--;
        return true;
    }
    //if one left child
    else if (cur -> left != NULL && cur -> right == NULL){
        // delete cur;
        if (left) {
            parent -> left = cur -> left;
        } else {
            parent -> right = cur -> left;
        }
        size--;
        return true;
    }

    return false;
}

