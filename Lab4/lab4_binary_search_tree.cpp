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
    recursiveDestructor(root);
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

    //Iterate down and right until maximum node is found
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

    //Iterate down and left until minimum node is found
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
    if (root == NULL) {
        cout << " " << endl;
    } else {
        stringstream ss;
        queue<TaskItem*> node_queue;
        node_queue.push(root);
        while (!node_queue.empty()) {
            TaskItem* cur_node = node_queue.front();
            node_queue.pop();
            ss << cur_node->priority << " ";
            if (cur_node->left) {
                node_queue.push(cur_node->left);
            }
            if (cur_node->right) {
                node_queue.push(cur_node->right);
            }
        }
        cout << ss.str();
    }
}

// PURPOSE: Returns true if a node with the value val exists in the tree
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {

    TaskItem *cur = root;
    while(cur != NULL)
    {
        //if node is found, return true
        if(cur ->priority == val.priority){
            return true;
        }

        //If node is greater or less than, move right or left respectively
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


// PURPOSE: Helper created to use destructor recursively
void BinarySearchTree::recursiveDestructor( BinarySearchTree::TaskItem* n) {
    if (n != NULL) {
        recursiveDestructor(n->left);
        recursiveDestructor(n->right);
        delete n;
    }
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {

    //Recursively check each path for longest to determine depth
    if (n == NULL) return -1;
    int left_depth = 1+get_node_depth(n->left);
    int right_depth = 1+get_node_depth(n->right);

    //return the longer of the left or right depths
    return left_depth > right_depth ? left_depth : right_depth;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {

    //If inserting first value, set as root
    if (root == NULL) {
        root = new TaskItem(val);
        size++;
        return true;
    }

    TaskItem *cur = root;
    TaskItem *parent = NULL;

    //Traverse until location where node should be added is found
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

    //Insert node on left or right of parent depending on priority
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
    bool twoChild = false;
    bool maxIsLeft = false;

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
        } else {
            return false;
        }
    }

    TaskItem *maxOnLeft = cur -> left;

    //Traverse down left side to find maximum
    if (cur->left != NULL && cur->right != NULL) {
        if (maxOnLeft->right != NULL) {
            while (maxOnLeft->right != NULL) {
                parent = maxOnLeft;
                maxOnLeft = maxOnLeft->right;
                left = false;
            }
        } else {
            parent = cur;
            left = true;
            maxIsLeft = true;
        }

        cur = maxOnLeft;
        twoChild = true;
    }

    //If leaf node
    if (cur -> left == NULL && cur -> right == NULL){

        delete cur;
        if (cur->priority == root->priority){
            root = NULL;
        }
        if (left){
            parent->left = NULL;
        } else {
            parent -> right = NULL;
        }
        size--;
        cur = NULL;
    }
    //if one right child
    else if (cur -> left == NULL && cur -> right != NULL){

        delete cur;
        if (left) {
            parent -> left = cur -> right;
        } else {
            parent -> right = cur -> right;
        }
        size--;
        cur = NULL;
    }

    //if one left child
    else if (cur -> left != NULL && cur -> right == NULL){

        delete cur;
        if (left) {
            parent -> left = cur -> left;
        } else {
            parent -> right = cur -> left;
        }
        size--;
        cur = NULL;
    }

    if (twoChild) {
        //Find maximum value (and parent) on left side of removal node
        if (val.priority == root->priority) {
            root->priority = maxOnLeft->priority;
            root->description = maxOnLeft->description;
        } else if (left) {
            if (maxIsLeft) {
                parent->priority = maxOnLeft->priority;
                parent->description = maxOnLeft->description;
            } else {
                parent->left->priority = maxOnLeft->priority;
                parent->left->description = maxOnLeft->description;
            }
        } else if (!left) {
            parent->right->priority = maxOnLeft->priority;
            parent->right->description = maxOnLeft->description;
        }

    }
    return true;
}

