#include <iostream>
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
    void inorder()
    {
        cout << "[";
        inorderTraversal(root);
        cout << "\b\b]\n";
    }
    void preorder()
    {
        cout << "[";
        preorderTraversal(root);
        cout << "\b\b]\n";
    }
    void postorder()
    {
        cout << "[";
        postorderTraversal(root);
        cout << "\b\b]\n";
    }

    bool levelorderSearch(int val) {
        queue<Node *> q;
        if (root == nullptr)
            return false;
        q.push(root);
        while(!q.empty()) {
            Node *current = q.front();
            q.pop();
            if (current->val == val)
                return true;
            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
        }
        return false;
    }

private:
    void inorderTraversal(Node *node)
    {
        if (node == nullptr)
            return;
        inorderTraversal(node->left);
        cout << node->val << ", ";
        inorderTraversal(node->right);
    }

    void preorderTraversal(Node *node) {
        if (node == nullptr)
            return;
        cout << node->val << ", ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    void postorderTraversal(Node *node) {
        if (node == nullptr)
            return;
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << node->val << ", ";
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
    BinaryTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    cout << "Inorder Traversal: ";
    tree.inorder();
    cout << "Preorder Traversal: ";
    tree.preorder();
    cout << "Postorder Traversal: ";
    tree.postorder();
    vector<int> values = {1, 2, 8, 9, 4, 3};
    cout << "\nSearching:\n";
    for (int x : values) {
        cout << x << ": " << (tree.levelorderSearch(x) ? "node of tree": "not a node of tree") << ".\n";
    }
    return 0;
}