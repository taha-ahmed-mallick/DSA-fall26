#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node
{
    int val;
    Node *left;
    Node *right;
    explicit Node(int value) : val(value), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
private:
    Node *root;

    Node *buildFromPreIn(const vector<int> &preorder, int inLeft, int inRight,
                         int &preIdx, const unordered_map<int, int> &inIndex)
    {
        if (inLeft > inRight)
            return nullptr;

        int rootVal = preorder[preIdx++];
        Node *node = new Node(rootVal);

        int mid = inIndex.at(rootVal);
        node->left = buildFromPreIn(preorder, inLeft, mid - 1, preIdx, inIndex);
        node->right = buildFromPreIn(preorder, mid + 1, inRight, preIdx, inIndex);

        return node;
    }

    void freeTree(Node *node)
    {
        if (!node)
            return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { freeTree(root); }

    void build(const vector<int> &preorder, const vector<int> &inorder)
    {
        freeTree(root);
        root = nullptr;
        if (preorder.empty() || preorder.size() != inorder.size())
            return;

        unordered_map<int, int> inIndex;
        inIndex.reserve(inorder.size());
        for (int i = 0; i < static_cast<int>(inorder.size()); ++i)
            inIndex[inorder[i]] = i;

        int preIdx = 0;
        root = buildFromPreIn(preorder, 0, static_cast<int>(inorder.size()) - 1,
                              preIdx, inIndex);
    }

    void printLevelOrder() const
    {
        if (!root)
        {
            cout << "[]\n";
            return;
        }
        cout << "[";
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *curr = q.front();
            q.pop();
            cout << curr->val << ", ";
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
        cout << "\b\b]\n";
    }
};

int main(int argc, char *argv[])
{
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};

    BinaryTree tree;
    tree.build(preorder, inorder);
    cout << "Tree (level order): ";
    tree.printLevelOrder();
    return 0;
}