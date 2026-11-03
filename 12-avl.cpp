// AVL tree that stays balanced on insert and delete, with search
#include <iostream>
using namespace std;

struct Node
{
    int data, height;
    Node *left, *right;
};

Node *root = NULL;

int height(Node *node)
{
    return node == NULL ? 0 : node->height;
}

void updateHeight(Node *node)
{
    int l = height(node->left), r = height(node->right);
    node->height = 1 + (l > r ? l : r);
}

int balance(Node *node)
{
    return node == NULL ? 0 : height(node->left) - height(node->right);
}

Node *rotateRight(Node *y)
{
    Node *x = y->left;
    Node *temp = x->right;
    x->right = y;
    y->left = temp;
    updateHeight(y);
    updateHeight(x);
    return x;
}

Node *rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *temp = y->left;
    y->left = x;
    x->right = temp;
    updateHeight(x);
    updateHeight(y);
    return y;
}

Node *rebalance(Node *node)
{
    if (node == NULL)
        return NULL;
    updateHeight(node);
    int b = balance(node);
    if (b > 1)
    {
        if (balance(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (b < -1)
    {
        if (balance(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

Node *insert(Node *node, int value)
{
    if (node == NULL)
        return new Node{value, 1, NULL, NULL};
    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    else
    {
        cout << "Duplicate value not inserted.\n";
        return node;
    }
    return rebalance(node);
}

Node *search(Node *node, int value)
{
    if (node == NULL || node->data == value)
        return node;
    if (value < node->data)
        return search(node->left, value);
    return search(node->right, value);
}

Node *removeNode(Node *node, int value)
{
    if (node == NULL)
        return NULL;
    if (value < node->data)
        node->left = removeNode(node->left, value);
    else if (value > node->data)
        node->right = removeNode(node->right, value);
    else
    {
        if (node->left == NULL || node->right == NULL)
        {
            Node *child = node->left != NULL ? node->left : node->right;
            delete node;
            return child;
        }
        Node *temp = node->right;
        while (temp->left != NULL)
            temp = temp->left;
        node->data = temp->data;
        node->right = removeNode(node->right, temp->data);
    }
    return rebalance(node);
}

void inorder(Node *node)
{
    if (node == NULL)
        return;
    inorder(node->left);
    cout << node->data << ' ';
    inorder(node->right);
}

void display(Node *node, int space = 0)
{
    if (node == NULL)
        return;
    display(node->right, space + 4);
    for (int i = 0; i < space; i++)
        cout << ' ';
    cout << node->data << " (BF=" << balance(node) << ")\n";
    display(node->left, space + 4);
}

void clearTree(Node *node)
{
    if (node == NULL)
        return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

int main()
{
    int choice, value;
    do
    {
        cout << "\n------------ AVL TREE ------------\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Inorder Traversal\n";
        cout << "5. Display Tree and Balance Factors\n6. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
            break;
        if (choice >= 1 && choice <= 3)
        {
            cout << "Enter value: ";
            if (!(cin >> value))
                break;
        }
        switch (choice)
        {
        case 1:
            root = insert(root, value);
            break;
        case 2:
            if (search(root, value) == NULL)
                cout << "Value not found.\n";
            else
            {
                root = removeNode(root, value);
                cout << "Value deleted.\n";
            }
            break;
        case 3:
            cout << (search(root, value) ? "Value found.\n" : "Value not found.\n");
            break;
        case 4:
            cout << "Inorder: ";
            inorder(root);
            cout << endl;
            break;
        case 5:
            if (root == NULL)
                cout << "Tree is empty.\n";
            else
                display(root);
            break;
        case 6:
            cout << "Exited.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);
    clearTree(root);
    return 0;
}