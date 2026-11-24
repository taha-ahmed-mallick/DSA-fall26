#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
class BST
{
private:
    struct Node
    {
        int key;
        Node *left;
        Node *right;
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };
    Node *root;
    Node *sortedArrayToBST(vector<int> &nums,
                           int left, int right)
    {
        if (left > right)
            return nullptr;
        int mid = left + (right - left + 1) / 2;
        Node *node = new Node(nums[mid]);
        node->left = sortedArrayToBST(nums, left, mid - 1);
        node->right = sortedArrayToBST(nums, mid + 1, right);
        return node;
    }
    void levelOrder(Node *node)
    {
        if (!node)
            return;
        queue<Node *> q;
        vector<string> result;
        q.push(node);
        while (!q.empty())
        {
            Node *current = q.front();
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
    void createBST(vector<int> &nums)
    {
        root = sortedArrayToBST(nums, 0, nums.size() - 1);
    }
    void display()
    {
        levelOrder(root);
    }
};
int main()
{
    BST tree;
    vector<int> nums = {-10, -3, 0, 5, 9};
    tree.createBST(nums);
    cout << "Output: ";
    tree.display();
    return 0;
}