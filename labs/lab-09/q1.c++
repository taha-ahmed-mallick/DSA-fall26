#include <iostream>
#include <stack>
using namespace std;

class Node
{
public:
    int data;
    Node *left, *right;

    Node(int val)
    {
        data = val;
        left = right = NULL;
    }
};

class BinarySearchTree
{
    Node *root;

public:
    BinarySearchTree()
    {
        root = NULL;
    }
    void insert(int key)
    {
        root = insertRec(root, key);
    }

    void inorder()
    {
        inorderRec(root);
        cout << endl;
    }

    void deleteNode(int key)
    {
        root = deleteRec(root, key);
    }

    void preorder()
    {
        if (root == NULL)
            return;

        stack<Node *> s;
        s.push(root);

        while (!s.empty())
        {
            Node *current = s.top();
            s.pop();

            cout << current->data << " ";

            if (current->right != NULL)
            {
                s.push(current->right);
            }

            if (current->left != NULL)
            {
                s.push(current->left);
            }
        }

        cout << endl;
    }

    void postorder()
    {
        if (root == NULL)
            return;

        stack<Node *> s1, s2;

        s1.push(root);

        while (!s1.empty())
        {
            Node *current = s1.top();
            s1.pop();

            s2.push(current);

            if (current->left != NULL)
            {
                s1.push(current->left);
            }

            if (current->right != NULL)
            {
                s1.push(current->right);
            }
        }

        while (!s2.empty())
        {
            cout << s2.top()->data << " ";
            s2.pop();
        }

        cout << endl;
    }

private:
    Node *insertRec(Node *node, int key)
    {
        if (node == NULL)
        {
            return new Node(key);
        }

        if (key < node->data)
        {
            node->left = insertRec(node->left, key);
        }
        else if (key > node->data)
        {
            node->right = insertRec(node->right, key);
        }

        return node;
    }

    void inorderRec(Node *root)
    {
        if (root == NULL)
            return;

        inorderRec(root->left);
        cout << root->data << " ";
        inorderRec(root->right);
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;

        while (current && current->left != NULL)
        {
            current = current->left;
        }

        return current;
    }

    Node *deleteRec(Node *node, int key)
    {
        if (node == NULL)
        {
            return node;
        }

        if (key < node->data)
        {
            node->left = deleteRec(node->left, key);
        }
        else if (key > node->data)
        {
            node->right = deleteRec(node->right, key);
        }
        else
        {

            if (node->left == NULL)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }

            else if (node->right == NULL)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            Node *temp = minValueNode(node->right);

            node->data = temp->data;

            node->right = deleteRec(node->right, temp->data);
        }

        return node;
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

    cout << "PreOrder traversal of the tree: ";
    bst.preorder();

    cout << "PostOrder traversal of the tree: ";
    bst.postorder();

    return 0;
}