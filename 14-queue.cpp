// Bank queue where customers are served in the order they arrive (FIFO)
#include <iostream>
#include <string>
using namespace std;

struct Customer
{
    int id;
    string name;
};

const int SIZE = 50;
Customer customers[SIZE];
int front = 0, rear = -1;

bool isEmpty()
{
    return rear < front;
}

void addCustomer()
{
    if (rear == SIZE - 1)
    {
        cout << "Queue is full.\n";
        return;
    }
    Customer c;
    cout << "Enter customer ID: ";
    cin >> c.id;
    cout << "Enter customer name: ";
    cin.ignore(10000, '\n');
    getline(cin, c.name);

    customers[++rear] = c;
    cout << "Customer added to queue.\n";
}

void serveCustomer()
{
    if (isEmpty())
    {
        cout << "No customers waiting.\n";
        return;
    }
    Customer c = customers[front++];
    cout << "Serving customer " << c.id << " - " << c.name << endl;

    // reset when queue becomes empty so space can be reused
    if (isEmpty())
    {
        front = 0;
        rear = -1;
    }
}

void displayQueue()
{
    if (isEmpty())
    {
        cout << "No customers waiting.\n";
        return;
    }
    cout << "Customer ID\tName\n";
    for (int i = front; i <= rear; i++)
        cout << customers[i].id << "\t\t" << customers[i].name << endl;
}

void showFront()
{
    if (isEmpty())
    {
        cout << "No customers waiting.\n";
        return;
    }
    cout << "Next customer: " << customers[front].id << " - " << customers[front].name << endl;
}

int main()
{
    int choice;
    do
    {
        cout << "\n------------ BANK QUEUE ------------\n";
        cout << "1. Add Customer\n2. Serve Next Customer\n";
        cout << "3. Display Waiting Customers\n4. Show Front Customer\n5. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
            break;
        switch (choice)
        {
        case 1:
            addCustomer();
            break;
        case 2:
            serveCustomer();
            break;
        case 3:
            displayQueue();
            break;
        case 4:
            showFront();
            break;
        case 5:
            cout << "Exited.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);
    return 0;
}
