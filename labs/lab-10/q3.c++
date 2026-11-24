#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;
class BST
{
private:
    // Linked List Node
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };
    // Binary Search Tree Node
    struct TreeNode
    {
        int key;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : key(x), left(nullptr),
                          right(nullptr) {}
    };
    TreeNode *root;
    // Count linked list nodes
    int countNodes(ListNode *head)
    {
        int count = 0;
        while (head != nullptr)
        {
            count++;
            head = head->next;
        }
        return count;
    }
    // Convert sorted linked list into BST
    TreeNode *sortedListToBST(ListNode *&head, int n)
    {
        if (n <= 0)
            return nullptr;
        // Create left subtree
        TreeNode *leftSubtree =
            sortedListToBST(head, n / 2);
        // Create root node
        TreeNode *node = new TreeNode(head->val);
        node->left = leftSubtree;
        // Move to next linked list node
        head = head->next;
        // Create right subtree
        node->right =
            sortedListToBST(head, n - n / 2 - 1);
        return node;
    }
    // Level Order Traversal
    void levelOrder(TreeNode *node)
    {
        if (!node)
            return;
        queue<TreeNode *> q;
        vector<string> result;
        q.push(node);
        while (!q.empty())
        {
            TreeNode *current = q.front();
            q.pop();
            if (current == nullptr)
            {
                result.push_back("null");
            }
            else
            {
                result.push_back(to_string(current->key));
                q.push(current->left);
                q.push(current->right);
            }
        }
        // Remove extra null values at the end
        while (!result.empty() && result.back() == "null")
            result.pop_back();
        cout << "[";
        for (int i = 0; i < result.size(); i++)
        {
            cout << result[i];
            if (i != result.size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
    }

public:
    BST() : root(nullptr) {}
    // Create BST from sorted linked list
    void createBST(int arr[], int n)
    {
        ListNode *head = nullptr;
        ListNode *current = nullptr;
        // Create linked list
        for (int i = 0; i < n; i++)
        {
            ListNode *newNode = new ListNode(arr[i]);
            if (head == nullptr)
            {
                head = newNode;
                current = head;
            }
            else
            {
                current->next = newNode;
                current = current->next;
            }
        }
        int count = countNodes(head);
        root = sortedListToBST(head, count);
    }
    // Display BST
    void display()
    {
        levelOrder(root);
    }
};
int main()
{
    BST tree;
    int arr[] = {-10, -3, 0, 5, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    tree.createBST(arr, n);
    cout << "Output: ";
    tree.display();
    return 0;
}