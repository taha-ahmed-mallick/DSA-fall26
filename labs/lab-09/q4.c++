#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int val) : val(val), left(nullptr), right(nullptr) {}
};

class BST
{
    Node *root;

public:
    BST() : root(nullptr) {}
    void insert(int val)
    {
        root = insertRec(root, val);
    }

    int sum()
    {
        int summation = sumRec(root);
        cout << "The sum of all nodes is: " << summation << endl;
        return summation;
    }

private:
    Node *insertRec(Node *node, int val)
    {
        if (node == nullptr)
            return new Node(val);
        if (val < node->val)
            node->left = insertRec(node->left, val);
        else
            node->right = insertRec(node->right, val);
        return node;
    }
    int sumRec(Node *node)
    {
        if (node == nullptr)
            return 0;
        return node->val + sumRec(node->left) + sumRec(node->right);
    }
};

int main(int argc, char *argv[])
{
    vector<int> val = {7, 3, 11, 1, 5, 9, 13, 0, 2, 4, 6, 8, 10, 12, 14};
    BST bst;
    for (int x : val)
        bst.insert(x);
    bst.sum();
    return 0;
}