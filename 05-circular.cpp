// Manages drive-thru food orders using a circular queue with time slices
#include <iostream>
#include <string>
using namespace std;

struct Order
{
    int id;
    string item;
    int remaining;
};

const int SIZE = 5;
Order orders[SIZE];
int front = 0, rear = -1, orderCount = 0, nextId = 1;

void addOrder()
{
    if (orderCount == SIZE)
    {
        cout << "Order queue is full.\n";
        return;
    }
    string item;
    int time;
    cout << "Enter item name: ";
    cin.ignore(10000, '\n');
    getline(cin, item);
    cout << "Enter preparation time in minutes: ";
    if (!(cin >> time))
        return;
    if (time <= 0 || item.empty())
    {
        cout << "Invalid order details.\n";
        return;
    }
    rear = (rear + 1) % SIZE;
    orders[rear] = {nextId++, item, time};
    orderCount++;
    cout << "Order " << orders[rear].id << " added.\n";
}

void processOrder()
{
    if (orderCount == 0)
    {
        cout << "No orders to process.\n";
        return;
    }
    int quantum;
    cout << "Enter time slice in minutes: ";
    if (!(cin >> quantum))
        return;
    if (quantum <= 0)
    {
        cout << "Time slice must be positive.\n";
        return;
    }
    Order current = orders[front];
    front = (front + 1) % SIZE;
    orderCount--;
    current.remaining -= quantum;
    if (current.remaining <= 0)
        cout << "Order " << current.id << " completed.\n";
    else
    {
        rear = (rear + 1) % SIZE;
        orders[rear] = current;
        orderCount++;
        cout << "Order " << current.id << ": " << current.remaining;
        cout << " minute(s) remaining. Moved to rear.\n";
    }
}

void display()
{
    if (orderCount == 0)
    {
        cout << "No ongoing orders.\n";
        return;
    }
    cout << "Order ID\tItem\tRemaining minutes\n";
    for (int i = 0; i < orderCount; i++)
    {
        int pos = (front + i) % SIZE;
        cout << orders[pos].id << '\t' << orders[pos].item;
        cout << '\t' << orders[pos].remaining << endl;
    }
}

int main()
{
    int choice;
    do
    {
        cout << "\n------------ DRIVE THRU ORDERS ------------\n";
        cout << "1. Add Order\n2. Process Next Time Slice\n";
        cout << "3. Display Ongoing Orders\n4. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
            break;
        switch (choice)
        {
        case 1:
            addOrder();
            break;
        case 2:
            processOrder();
            break;
        case 3:
            display();
            break;
        case 4:
            cout << "Exited.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);
    return 0;
}
