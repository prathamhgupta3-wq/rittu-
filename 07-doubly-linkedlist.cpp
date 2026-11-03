// Train route stations using a doubly linked list (insert, delete, search, reverse)
#include <iostream>
using namespace std;

struct Node
{
    int code;
    string name;
    Node *prev;
    Node *next;
};

Node *head = NULL;
Node *tail = NULL;

void insertStation()
{
    Node *newNode = new Node;

    cout << "Enter station code: ";
    cin >> newNode->code;

    cout << "Enter station name: ";
    cin >> newNode->name;

    newNode->prev = NULL;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    cout << "Station inserted successfully.\n";
}

void deleteStation()
{
    int code;
    cout << "Enter station code to delete: ";
    cin >> code;

    Node *temp = head;

    while (temp != NULL && temp->code != code)
        temp = temp->next;

    if (temp == NULL)
    {
        cout << "Station not found.\n";
        return;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    else
        tail = temp->prev;

    delete temp;

    cout << "Station deleted successfully.\n";
}

void display()
{
    Node *temp = head;

    if (head == NULL)
    {
        cout << "No stations available.\n";
        return;
    }

    cout << "\nStation Code\tStation Name\n";

    while (temp != NULL)
    {
        cout << temp->code << "\t\t" << temp->name << endl;
        temp = temp->next;
    }
}

void searchStation()
{
    int code;
    cout << "Enter station code to search: ";
    cin >> code;

    Node *temp = head;

    while (temp != NULL)
    {
        if (temp->code == code)
        {
            cout << "Station Found!\n";
            cout << "Code: " << temp->code << endl;
            cout << "Name: " << temp->name << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Station not found.\n";
}

void reverseDisplay()
{
    Node *temp = tail;

    if (tail == NULL)
    {
        cout << "No stations available.\n";
        return;
    }

    cout << "\nStations in Reverse Order:\n";

    while (temp != NULL)
    {
        cout << temp->code << " - " << temp->name << endl;
        temp = temp->prev;
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n------------TRAIN ROUTE MANAGEMENT SYSTEM ------------\n";
        cout << "1. Insert Station\n";
        cout << "2. Delete Station\n";
        cout << "3. Display All Stations\n";
        cout << "4. Search Station\n";
        cout << "5. Display Stations in Reverse\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            insertStation();
            break;

        case 2:
            deleteStation();
            break;

        case 3:
            display();
            break;

        case 4:
            searchStation();
            break;

        case 5:
            reverseDisplay();
            break;

        case 6:
            cout << " exited...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}