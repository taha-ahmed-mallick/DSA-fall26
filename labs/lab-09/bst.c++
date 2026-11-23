#include <iostream>
using namespace std;

struct TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree
{
public:
    TreeNode *root;
    BinarySearchTree() : root(nullptr) {}
    void insert(int key)
    {
        root = insertRec(root, key);
    }
    void deleteNode(int key)
    {
        root = deleteRec(root, key);
    }
    void inorder()
    {
        cout << "[";
        inorderRec(root);
        cout << "\b\b]\n";
    }

private:
    // Recursive function to insert a node
    TreeNode *insertRec(TreeNode *node, int key)
    {
        // Base case: if the tree is empty, create a new node
        if (node == nullptr)
            return new TreeNode(key);
        // Otherwise, recur down the tree
        if (key < node->val)
            node->left = insertRec(node->left, key);
        else if (key > node->val)
            node->right = insertRec(node->right, key);
        return node;
    }
    // Recursive function to delete a node
    TreeNode *deleteRec(TreeNode *node, int key)
    {
        // Base case: if the tree is empty
        if (node == nullptr)
            return node;
        // Recur down the tree
        if (key < node->val)
            node->left = deleteRec(node->left, key);
        else if (key > node->val)
            node->right = deleteRec(node->right, key);
        else
        {
            // Node with only one child or no child
            if (node->left == nullptr)
            {
                TreeNode *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                TreeNode *temp = node->left;
                delete node;
                return temp;
            }
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            TreeNode *temp = minValueNode(node->right);
            // Copy the inorder successor's content to this node
            node->val = temp->val;
            // Delete the inorder successor
            node->right = deleteRec(node->right, temp->val);
        }
        return node;
    }
    // Find the node with the minimum value (used for deleting nodes)
    TreeNode *minValueNode(TreeNode *node)
    {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }
    // Inorder traversal function
    void inorderRec(TreeNode *node)
    {
        if (node == nullptr)
            return;
        inorderRec(node->left);
        cout << node->val << ", ";
        inorderRec(node->right);
    }
};
int main()
{
    BinarySearchTree bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);
    cout << "Inorder traversal of the tree: ";
    bst.inorder();
    cout << "Delete 20\n";
    bst.deleteNode(20);
    cout << "Inorder traversal of the tree after deleting 20: ";
    bst.inorder();
}