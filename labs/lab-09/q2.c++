#include <iostream>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

class EmployeeNode
{
public:
    int id;
    string name;
    string department;

    EmployeeNode *left;
    EmployeeNode *right;

    EmployeeNode(int i, string n, string d)
    {
        id = i;
        name = n;
        department = d;
        left = right = NULL;
    }
};

class EmployeeBST
{
    EmployeeNode *root;

public:
    EmployeeBST()
    {
        root = NULL;
    }

    void insert(int id, string name, string department)
    {
        root = insertRec(root, id, name, department);
    }

    void search(int id)
    {
        EmployeeNode *temp = searchRec(root, id);

        if (temp == NULL)
        {
            cout << "Employee not found!\n";
        }
        else
        {
            cout << "Employee Found!\n";
            cout << "ID: " << temp->id << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Department: " << temp->department << endl;
        }
    }

    void deleteNode(int id)
    {
        if (root == NULL)
        {
            cout << "Tree is empty! Nothing to delete.\n";
            return;
        }

        if (searchRec(root, id) == NULL)
        {
            cout << "Employee ID " << id << " does not exist!\n";
            return;
        }

        root = deleteRec(root, id);

        cout << "Employee deleted successfully!\n";
    }

    void inOrderTraversal()
    {
        if (root == NULL)
        {
            cout << "Employee tree is empty!\n";
            return;
        }

        inOrderRec(root);
    }

    EmployeeNode *findMin()
    {
        EmployeeNode *temp = minValueNode(root);

        if (temp == NULL)
        {
            cout << "Tree is empty!\n";
            return NULL;
        }

        cout << "Minimum Employee:\n";
        cout << "ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Department: " << temp->department << endl;

        return temp;
    }

    EmployeeNode *findMax()
    {
        if (root == NULL)
        {
            cout << "Tree is empty!\n";
            return NULL;
        }

        EmployeeNode *temp = root;

        while (temp->right != NULL)
        {
            temp = temp->right;
        }

        cout << "Maximum Employee:\n";
        cout << "ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Department: " << temp->department << endl;

        return temp;
    }

private:
    EmployeeNode *insertRec(EmployeeNode *node, int id, string name, string department)
    {
        if (node == NULL)
        {
            return new EmployeeNode(id, name, department);
        }

        if (id < node->id)
        {
            node->left = insertRec(node->left, id, name, department);
        }
        else if (id > node->id)
        {
            node->right = insertRec(node->right, id, name, department);
        }
        else
        {
            cout << "Duplicate Employee ID! Cannot insert.\n";
        }

        return node;
    }

    EmployeeNode *searchRec(EmployeeNode *node, int id)
    {
        if (node == NULL || node->id == id)
        {
            return node;
        }

        if (id < node->id)
        {
            return searchRec(node->left, id);
        }

        return searchRec(node->right, id);
    }

    EmployeeNode *minValueNode(EmployeeNode *node)
    {
        if (node == NULL)
            return NULL;

        while (node->left != NULL)
        {
            node = node->left;
        }

        return node;
    }

    EmployeeNode *deleteRec(EmployeeNode *node, int id)
    {
        if (node == NULL)
        {
            return NULL;
        }

        if (id < node->id)
        {
            node->left = deleteRec(node->left, id);
        }
        else if (id > node->id)
        {
            node->right = deleteRec(node->right, id);
        }
        else
        {
            if (node->left == NULL)
            {
                EmployeeNode *temp = node->right;
                delete node;
                return temp;
            }

            else if (node->right == NULL)
            {
                EmployeeNode *temp = node->left;
                delete node;
                return temp;
            }

            EmployeeNode *temp = minValueNode(node->right);

            node->id = temp->id;
            node->name = temp->name;
            node->department = temp->department;

            node->right = deleteRec(node->right, temp->id);
        }

        return node;
    }

    void inOrderRec(EmployeeNode *node)
    {
        if (node == NULL)
            return;

        inOrderRec(node->left);

        cout << "ID: " << node->id
             << " | Name: " << node->name
             << " | Department: " << node->department << endl;

        inOrderRec(node->right);
    }
};

int main()
{
    EmployeeBST bst;

    bst.insert(50, "Ali", "IT");
    bst.insert(30, "Ahmed", "HR");
    bst.insert(70, "Sara", "Finance");
    bst.insert(20, "Usman", "Marketing");
    bst.insert(40, "Ayesha", "IT");
    bst.insert(60, "Bilal", "HR");
    bst.insert(80, "Hina", "Finance");

    cout << "\n===== ALL EMPLOYEES =====\n";
    bst.inOrderTraversal();

    cout << "\n===== SEARCH EMPLOYEE =====\n";
    bst.search(40);

    cout << "\n===== MINIMUM EMPLOYEE =====\n";
    bst.findMin();

    cout << "\n===== MAXIMUM EMPLOYEE =====\n";
    bst.findMax();

    cout << "\n===== DELETE EMPLOYEE =====\n";
    bst.deleteNode(20);

    cout << "\n===== EMPLOYEES AFTER DELETION =====\n";
    bst.inOrderTraversal();

    return 0;
}