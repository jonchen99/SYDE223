#include <iostream>
#include <cstring>
using namespace std;

struct BinaryTreeNode {
    int value;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
    BinaryTreeNode(int new_value) : value(new_value), left(NULL), right (NULL) {}
};


void find_and_print_sum_of_nodes(BinaryTreeNode *T, int desired_sum, int cur_sum, string buffer) {
    if (!T)
        return;

    int new_sum = cur_sum + T->value;
    string new_buffer = buffer + "     " + to_string(T->value);

    if (new_sum == desired_sum)
        cout << new_buffer << endl;

    find_and_print_sum_of_nodes(T->left, desired_sum, new_sum, new_buffer);
    find_and_print_sum_of_nodes(T->right, desired_sum, new_sum, new_buffer);
    if (buffer == "") {
        find_and_print_sum_of_nodes(T->left, desired_sum, cur_sum, buffer);
    }
    if (buffer == "") {
        find_and_print_sum_of_nodes(T->right, desired_sum, cur_sum, buffer);
    }
}

int find_max_sum_of_nodes(BinaryTreeNode *T, int &temp_max_sum) {
    if (!T) return 0;
    int max1, max2;

    int left_sum = find_max_sum_of_nodes(T->left, temp_max_sum);

    int right_sum = find_max_sum_of_nodes(T->right, temp_max_sum);

    //TODO: compare t->value, left_sum + T->value, and right_sum + T->value; store as max1
    max1 = max({T->value, left_sum + T->value, right_sum + T->value});

    //TODO: compare max1, left_sum + right_sum + T->value, store as max2
    max2 = max(max1, left_sum + right_sum + T->value);

    temp_max_sum = max(temp_max_sum,max2);
    return max1;
}

int find_max_sum_of_nodes(BinaryTreeNode *T) {
    int temp_max_sum = INT_MIN;
    find_max_sum_of_nodes(T, temp_max_sum);
    return temp_max_sum;
}

void exercise1test1() {
    BinaryTreeNode *root = new BinaryTreeNode(5);
    root->left = new BinaryTreeNode(3);
    root->left->left = new BinaryTreeNode(-1);
    root->left->left->left = new BinaryTreeNode(18);
    root->left->right = new BinaryTreeNode(8);
    root->left->right->left = new BinaryTreeNode(6);
    root->right = new BinaryTreeNode(1);
    root->right->right = new BinaryTreeNode(11);
    find_and_print_sum_of_nodes(root, 17, 0, "");
}

void exercise1test2() {
    BinaryTreeNode *root = new BinaryTreeNode(5);
    root->left = new BinaryTreeNode(6);
    root->left->left = new BinaryTreeNode(15);
    root->left->right = new BinaryTreeNode(10);
    root->left->right->right = new BinaryTreeNode(-5);
    root->right = new BinaryTreeNode(-15);
    root->right->left = new BinaryTreeNode(-12);
    root->right->right = new BinaryTreeNode(9);
    find_and_print_sum_of_nodes(root, 5, 0, "");
}

void exercise1test3() {
    BinaryTreeNode *root = new BinaryTreeNode(6);
    root->left = new BinaryTreeNode(10);
    root->left->right = new BinaryTreeNode(-5);
    root->left->right->right = new BinaryTreeNode(4);
    root->right = new BinaryTreeNode(4);
    root->right->right = new BinaryTreeNode(-6);
    root->right->right->right = new BinaryTreeNode(7);
    find_and_print_sum_of_nodes(root, 10, 0, "");
}

void exercise2test1() {
    int max;
    BinaryTreeNode *root = new BinaryTreeNode(5);
    root->left = new BinaryTreeNode(6);
    root->left->left = new BinaryTreeNode(15);
    root->left->right = new BinaryTreeNode(10);
    root->left->right->right = new BinaryTreeNode(-5);
    root->right = new BinaryTreeNode(-15);
    root->right->left = new BinaryTreeNode(-12);
    root->right->right = new BinaryTreeNode(9);
    max = find_max_sum_of_nodes(root);
    cout << max << endl;
}

void exercise2test2() {
    int max;
    BinaryTreeNode *root = new BinaryTreeNode(6);
    root->left = new BinaryTreeNode(10);
    root->left->right = new BinaryTreeNode(-5);
    root->left->right->right = new BinaryTreeNode(4);
    root->right = new BinaryTreeNode(4);
    root->right->right = new BinaryTreeNode(-6);
    root->right->right->right = new BinaryTreeNode(7);
    max = find_max_sum_of_nodes(root);
    cout << max << endl;
}

void exercise2test3() {
    int max;
    BinaryTreeNode *root = new BinaryTreeNode(5);
    root->left = new BinaryTreeNode(3);
    root->left->left = new BinaryTreeNode(-1);
    root->left->left->left = new BinaryTreeNode(18);
    root->left->right = new BinaryTreeNode(8);
    root->left->right->left = new BinaryTreeNode(6);
    root->right = new BinaryTreeNode(1);
    root->right->right = new BinaryTreeNode(11);
    max = find_max_sum_of_nodes(root);
    cout << max << endl;
}

int main() {
    cout << endl <<  "Exercise 1, Test 1: " << endl;
    exercise1test1();

    cout << endl <<  "Exercise 1, Test 2: " << endl;
    exercise1test2();

    cout << endl <<  "Exercise 1, Test 3: " << endl;
    exercise1test3();

    cout << endl <<  "Exercise 2, Test 1: " << endl;
    exercise2test1();

    cout << endl <<  "Exercise 2, Test 2: " << endl;
    exercise2test2();

    cout << endl <<  "Exercise 2, Test 3: " << endl;
    exercise2test3();
    return 0;
}
