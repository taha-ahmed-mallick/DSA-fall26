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
    Node *findLCA(int val1, int val2)
    {
        if (!searchRec(root, val1) || !searchRec(root, val2))
            return nullptr;

        Node *curr = root;
        while (curr != nullptr)
        {
            if (val1 < curr->val && val2 < curr->val)
                curr = curr->left;
            else if (val1 > curr->val && val2 > curr->val)
                curr = curr->right;
            else
                return curr;
        }
        return nullptr; // though this should not run
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
    Node *searchRec(Node *node, int val)
    {
        if (node == nullptr || node->val == val)
            return node;
        if (val < node->val)
            return searchRec(node->left, val);
        return searchRec(node->right, val);
    }
};

int main(int argc, char *argv[])
{
    vector<int> val = {7, 3, 11, 1, 5, 9, 13, 0, 2, 4, 6, 8, 10, 12, 14};
    BST bst;
    for (int x : val)
        bst.insert(x);
    vector<pair<int, int>> tests = {{0, 14}, {1, 4}, {8, 11}, {2, 5}, {-1, 15}};
    Node *res = nullptr;
    for (auto p : tests)
    {
        res = bst.findLCA(p.first, p.second);
        cout << "LCA of " << p.first << " and " << p.second << " is: ";
        if (res)
            cout << res->val << endl;
        else
            cout << "Either or both of the nodes may not exist in the tree.\n";
    }
    return 0;
}