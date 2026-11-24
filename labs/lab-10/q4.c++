#include <iostream>
#include <algorithm>
using namespace std;
class BST
{
private:
    struct Node
    {
        int key;
        Node *left;
        Node *right;
        Node(int k) : key(k), left(nullptr),
                      right(nullptr) {}
    };
    Node *root;
    Node *insert(Node *node, int key)
    {
        if (node == nullptr)
            return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        return node;
    }
    int diameterHelper(Node *node, int &diameter)
    {
        if (node == nullptr)
            return 0;
        int leftHeight =
            diameterHelper(node->left, diameter);
        int rightHeight =
            diameterHelper(node->right, diameter);
        diameter = max(diameter,
                       leftHeight + rightHeight);
        return 1 + max(leftHeight, rightHeight);
    }

public:
    BST() : root(nullptr) {}
    void insert(int key)
    {
        root = insert(root, key);
    }
    int findDiameter()
    {
        int diameter = 0;
        diameterHelper(root, diameter);
        return diameter;
    }
};
int main()
{
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(18);
    cout << "Diameter of BST: "
         << tree.findDiameter() << endl;
    return 0;
}