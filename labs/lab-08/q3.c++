#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int value) : val(value), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
private:
    Node *root;
    int maxFactor;

public:
    BinaryTree(Node *root) : root(root), maxFactor(0) {}
    ~BinaryTree() { freeTree(root); }
    void isBalanced()
    {
        int maxFactor = 0;
        cout << "Height: " << checkHeight(root, maxFactor) << endl;
        cout << "Balanced: " << (maxFactor > 1 ? "false" : "true") << endl;
    }

private:
    int checkHeight(Node *node, int& maxFactor)
    {
        if (!node)
            return 0;
        int lh = checkHeight(node->left, maxFactor);
        int rh = checkHeight(node->right, maxFactor);
        int factor;
        if (lh < rh)
            factor = rh - lh;
        else
            factor = lh - rh;
        if (factor > maxFactor)
            maxFactor = factor;
        return 1 + max(lh, rh);
    }

    void freeTree(Node* node) {
        if (!node) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
};

int main(int argc, char *argv[])
{
    Node *root1 = new Node(0);
    root1->left = new Node(1);
    root1->right = new Node(2);
    root1->left->left = new Node(3);
    root1->right->right = new Node(4);
    root1->left->left->left = new Node(5);
    root1->right->right->right = new Node(6);
    cout << "Tree 1:\n";
    BinaryTree tree(root1);
    tree.isBalanced();

    Node* root2 = new Node(3);
    root2->left = new Node(9);
    root2->right = new Node(20);
    root2->right->left = new Node(15);
    root2->right->right = new Node(7);
    cout << "\nTree 2:\n";
    BinaryTree tree2(root2);
    tree2.isBalanced();

    Node* root3 = new Node(1);
    root3->left = new Node(2);
    root3->right = new Node(2);
    root3->left->left = new Node(3);
    root3->left->right = new Node(3);
    root3->left->left->left = new Node(4);
    root3->left->left->right = new Node(4);
    cout << "\nTree 3:\n";
    BinaryTree tree3(root3);
    tree3.isBalanced();
    return 0;
}