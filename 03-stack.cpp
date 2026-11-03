// Text editor that uses a stack to undo insert and delete actions
#include <iostream>
#include <string>
using namespace std;

struct Action
{
    char type;
    int position;
    string text;
};

Action actions[100];
int top = -1;
string text = "";

void insertText()
{
    if (top == 99)
    {
        cout << "Undo stack is full.\n";
        return;
    }
    int position;
    string value;
    cout << "Enter position (0 to " << text.length() << "): ";
    if (!(cin >> position))
        return;
    if (position < 0 || position > (int)text.length())
    {
        cout << "Invalid position.\n";
        return;
    }
    cout << "Enter text to insert: ";
    cin.ignore(10000, '\n');
    getline(cin, value);
    if (value.empty())
    {
        cout << "No text entered.\n";
        return;
    }
    actions[++top] = {'I', position, value};
    text.insert(position, value);
    cout << "Text inserted.\n";
}

void deleteText()
{
    if (top == 99)
    {
        cout << "Undo stack is full.\n";
        return;
    }
    int position, count;
    cout << "Enter starting position and number of characters: ";
    if (!(cin >> position >> count))
        return;
    if (position < 0 || position >= (int)text.length() ||
        count <= 0 || count > (int)text.length() - position)
    {
        cout << "Invalid range.\n";
        return;
    }
    actions[++top] = {'D', position, text.substr(position, count)};
    text.erase(position, count);
    cout << "Text deleted.\n";
}

void undo()
{
    if (top == -1)
    {
        cout << "No action to undo.\n";
        return;
    }
    Action action = actions[top--];
    if (action.type == 'I')
        text.erase(action.position, action.text.length());
    else
        text.insert(action.position, action.text);
    cout << "Last action undone.\n";
}

int main()
{
    int choice;
    do
    {
        cout << "\n------------ TEXT EDITOR ------------\n";
        cout << "1. Insert Text\n2. Delete Text\n3. Undo\n4. Display Text\n5. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
            break;
        switch (choice)
        {
        case 1:
            insertText();
            break;
        case 2:
            deleteText();
            break;
        case 3:
            undo();
            break;
        case 4:
            cout << "Text: " << text << endl;
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
