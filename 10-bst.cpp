// Binary search tree with insert, delete, search, traversals, depth, copy and leaf nodes
#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
};

Node *root = NULL;
Node *copyRoot = NULL;

Node *insert(Node *node, int value)
{
    if (node == NULL)
        return new Node{value, NULL, NULL};
    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    else
        cout << "Duplicate value not inserted.\n";
    return node;
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
    return node;
}

void inorder(Node *node)
{
    if (node == NULL)
        return;
    inorder(node->left);
    cout << node->data << ' ';
    inorder(node->right);
}

void preorder(Node *node)
{
    if (node == NULL)
        return;
    cout << node->data << ' ';
    preorder(node->left);
    preorder(node->right);
}

void postorder(Node *node)
{
    if (node == NULL)
        return;
    postorder(node->left);
    postorder(node->right);
    cout << node->data << ' ';
}

int depth(Node *node)
{
    if (node == NULL)
        return 0;
    int l = depth(node->left), r = depth(node->right);
    return 1 + (l > r ? l : r);
}

Node *copyTree(Node *node)
{
    if (node == NULL)
        return NULL;
    return new Node{node->data, copyTree(node->left), copyTree(node->right)};
}

void mirror(Node *node)
{
    if (node == NULL)
        return;
    Node *temp = node->left;
    node->left = node->right;
    node->right = temp;
    mirror(node->left);
    mirror(node->right);
}

void clearTree(Node *node)
{
    if (node == NULL)
        return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

void parents(Node *node)
{
    if (node == NULL)
        return;
    if (node->left != NULL || node->right != NULL)
    {
        cout << "Parent " << node->data << ": Left = ";
        if (node->left != NULL)
            cout << node->left->data;
        else
            cout << "None";
        cout << ", Right = ";
        if (node->right != NULL)
            cout << node->right->data;
        else
            cout << "None";
        cout << endl;
    }
    parents(node->left);
    parents(node->right);
}

void leaves(Node *node)
{
    if (node == NULL)
        return;
    if (node->left == NULL && node->right == NULL)
        cout << node->data << ' ';
    leaves(node->left);
    leaves(node->right);
}

void levelWise(Node *node)
{
    if (node == NULL)
    {
        cout << "Tree is empty.\n";
        return;
    }
    queue<Node *> q;
    q.push(node);
    while (!q.empty())
    {
        int size = (int)q.size();
        for (int i = 0; i < size; i++)
        {
            Node *temp = q.front();
            q.pop();
            cout << temp->data << ' ';
            if (temp->left != NULL)
                q.push(temp->left);
            if (temp->right != NULL)
                q.push(temp->right);
        }
        cout << endl;
    }
}

int main()
{
    int choice, value;
    do
    {
        cout << "\n------------ BINARY SEARCH TREE ------------\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Traversals\n";
        cout << "5. Depth\n6. Display Mirror Image\n7. Create and Display Copy\n";
        cout << "8. Parent and Child Nodes\n9. Leaf Nodes\n10. Level Wise\n11. Exit\n";
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
            cout << "\nPreorder: ";
            preorder(root);
            cout << "\nPostorder: ";
            postorder(root);
            cout << endl;
            break;
        case 5:
            cout << "Depth in levels: " << depth(root) << endl;
            break;
        case 6:
        {
            Node *temp = copyTree(root);
            mirror(temp);
            cout << "Mirror image level wise:\n";
            levelWise(temp);
            clearTree(temp);
            break;
        }
        case 7:
            clearTree(copyRoot);
            copyRoot = copyTree(root);
            cout << "Copied tree level wise:\n";
            levelWise(copyRoot);
            break;
        case 8:
            parents(root);
            break;
        case 9:
            cout << "Leaf nodes: ";
            leaves(root);
            cout << endl;
            break;
        case 10:
            levelWise(root);
            break;
        case 11:
            cout << "Exited.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 11);
    clearTree(root);
    clearTree(copyRoot);
    return 0;
}