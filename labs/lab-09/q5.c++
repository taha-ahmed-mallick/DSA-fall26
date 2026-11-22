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
    int getMinDiff()
    {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr))
            return 0;

        int minDiff = __INT_MAX__;
        bool hasPrev = false;
        int prevVal = 0;

        minDiffInorder(root, prevVal, hasPrev, minDiff);
        return (minDiff == __INT_MAX__) ? 0 : minDiff;
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
    void minDiffInorder(Node *node, int &prevVal, bool &hasPrev, int &minDiff)
    {
        if (node == nullptr)
            return;
        minDiffInorder(node->left, prevVal, hasPrev, minDiff);
        if (hasPrev)
            minDiff = min(minDiff, node->val - prevVal);
        prevVal = node->val;
        hasPrev = true;
        minDiffInorder(node->right, prevVal, hasPrev, minDiff);
    }
};

int main(int argc, char *argv[])
{
    vector<int> val = {4, 2, 6, 1, 3};
    BST bst;
    for (int x : val)
        bst.insert(x);
    cout << "Minimum difference: " << bst.getMinDiff() << endl;
    return 0;
}