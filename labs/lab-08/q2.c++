#include <iostream>
#include <vector>
#include <queue>
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

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { freeTree(root); }
    void insert(int val)
    {
        Node *newNode = new Node(val);
        if (root == nullptr)
        {
            root = newNode;
            return;
        }
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();
            if (current->left == nullptr)
            {
                current->left = newNode;
                return;
            }
            else
                q.push(current->left);

            if (current->right == nullptr)
            {
                current->right = newNode;
                return;
            }
            else
                q.push(current->right);
        }
    }

    bool isSymmetric()
    {
        if (!root) return true;
        return isMirror(root->left, root->right);
    }
private:
    bool isMirror(Node* leftSub, Node* rightSub) {
        if (!leftSub && !rightSub) return true;
        if (!leftSub || !rightSub) return false;
        if (leftSub->val != rightSub->val) return false;
        return isMirror(leftSub->left, rightSub->right) && isMirror(leftSub->right, rightSub->left);
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
    vector<int> values = {1, 2, 2, 3, 4, 4, 3};
    BinaryTree tree;
    for (int x : values)
        tree.insert(x);
    cout << "Tree 1: " << (tree.isSymmetric() ? "symmetric" : "not symmetric") << ".\n";
    values[3] = 5;
    BinaryTree tree2;
    for (int x : values)
        tree2.insert(x);
    cout << "Tree 2: " << (tree2.isSymmetric() ? "symmetric" : "not symmetric") << ".\n";
    return 0;
}