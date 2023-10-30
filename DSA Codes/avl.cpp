#include <iostream>
#include <cstdlib>  // For malloc

using namespace std;

// AVL Tree Node
struct TreeNode {
    int key;
    int height;
    TreeNode* left;
    TreeNode* right;
};

// Function to create a new node
TreeNode* createNode(int key) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->height = 1;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Function to get the height of a node
int getHeight(TreeNode* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to upgrade the height of a node
void upgradeHeight(TreeNode* node) {
    int leftHeight = (node->left) ? node->left->height : 0;
    int rightHeight = (node->right) ? node->right->height : 0;
    node->height = 1 + max(leftHeight, rightHeight);
}

// Function to perform a right rotation (shift right)
TreeNode* shiftRight(TreeNode* tail) {
    if (tail == nullptr || tail->left == nullptr)
        return tail;

    TreeNode* head = tail->left;
    TreeNode* T2 = head->right;

    head->right = tail;
    tail->left = T2;

    upgradeHeight(tail);
    upgradeHeight(head);

    return head;
}

// Function to perform a left rotation (shift left)
TreeNode* shiftLeft(TreeNode* head) {
    if (head == nullptr || head->right == nullptr)
        return head;

    TreeNode* tail = head->right;
    TreeNode* T2 = tail->left;

    tail->left = head;
    head->right = T2;

    upgradeHeight(head);
    upgradeHeight(tail);

    return tail;
}

// Function to calculate the balance factor of a node
int balFact(TreeNode* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to balance the AVL Tree
TreeNode* balance(TreeNode* node) {
    if (node == nullptr)
        return node;

    int balanceFactor = balFact(node);

    // Left Heavy
    if (balanceFactor > 1) {
        // Left-Right Case (LR)
        if (node->left && balFact(node->left) < 0) {
            node->left = shiftLeft(node->left);
        }
        return shiftRight(node);
    }

    // Right Heavy
    if (balanceFactor < -1) {
        // Right-Left Case (RL)
        if (node->right && balFact(node->right) > 0) {
            node->right = shiftRight(node->right);
        }
        return shiftLeft(node);
    }

    return node;
}

// Function to insert a key into the AVL Tree
TreeNode* insert(TreeNode* head, int key) {
    if (head == nullptr)
        return createNode(key);

    if (key < head->key)
        head->left = insert(head->left, key);
    else if (key > head->key)
        head->right = insert(head->right, key);
    else
        return head; // Duplicate keys not allowed

    upgradeHeight(head);
    return balance(head);
}

// Function to perform an in-order traversal of the AVL Tree
void inOrderTraversal(TreeNode* head) {
    if (head) {
        inOrderTraversal(head->left);
        cout << head->key << " ";
        inOrderTraversal(head->right);
    }
}

int main() {
    TreeNode* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 26);
    root = insert(root, 50);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 58);

    cout << "In-order traversal of AVL Tree: ";
    inOrderTraversal(root);
    cout << endl;

    return 0;
}
