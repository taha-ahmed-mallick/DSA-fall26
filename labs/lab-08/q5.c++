#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    explicit Node(int value) : val(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

    pair<int, int> robDfs(Node* node) const {
        if (!node) return {0, 0}; // {rob node, skip node}

        auto [leftRob, leftSkip] = robDfs(node->left);
        auto [rightRob, rightSkip] = robDfs(node->right);

        int robCurrent = node->val + leftSkip + rightSkip;
        int skipCurrent = max(leftRob, leftSkip) + max(rightRob, rightSkip);

        return {robCurrent, skipCurrent};
    }

    void freeTree(Node* node) {
        if (!node) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

public:
    BinaryTree(Node* r) : root(r) {}
    ~BinaryTree() { freeTree(root); }

    int maxRobbery() const {
        auto [robRoot, skipRoot] = robDfs(root);
        return max(robRoot, skipRoot);
    }
};

int main(int argc, char* argv[]) {
    // Example 1: [3, 2, 3, null, 3, null, 1] -> 7
    Node* r1 = new Node(3);
    r1->left = new Node(2);
    r1->right = new Node(3);
    r1->left->right = new Node(3);
    r1->right->right = new Node(1);

    BinaryTree t1(r1);
    cout << "Tree 1 max robbed: " << t1.maxRobbery() << "\n";

    // Example 2: [3, 4, 5, 1, 3, null, 1] -> 9
    Node* r2 = new Node(3);
    r2->left = new Node(4);
    r2->right = new Node(5);
    r2->left->left = new Node(1);
    r2->left->right = new Node(3);
    r2->right->right = new Node(1);

    BinaryTree t2(r2);
    cout << "Tree 2 max robbed: " << t2.maxRobbery() << "\n";

    return 0;
}