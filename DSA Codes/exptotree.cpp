#include <iostream>
#include <stack>

using namespace std;


struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;
};

//  character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to create a new node
TreeNode* createNode(char value) {
    TreeNode* newNode = new TreeNode;
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Function to insert a new node into the binary tree
void insert(TreeNode* &root, char value) {
    if (!root) {
        root = createNode(value);
    }
    else if (isOperator(value)) {
        if (isOperator(root->data) && (value == '+' || value == '-') &&
            (root->data == '*' || root->data == '/')) {
            insert(root->right, value);
        }
        else {
            TreeNode* newNode = createNode(value);
            newNode->left = root;
            root = newNode;
        }
    }
    else {
        insert(root->right, value);
    }
}


void displayInfix(TreeNode* root) {
    if (root) {
        if (isOperator(root->data)) {
            cout << "(";
        }
        displayInfix(root->left);
        cout << root->data;
        displayInfix(root->right);
        if (isOperator(root->data)) {
            cout << ")";
        }
    }
}

int main() {
    string infixExpression;
    cout << "Enter an expression: ";
    getline(cin, infixExpression);

    TreeNode* root = nullptr;
    for (char c : infixExpression) {
        insert(root, c);
    }

    cout << "Infix expression: ";
    displayInfix(root);
    cout << endl;

    return 0;
}
