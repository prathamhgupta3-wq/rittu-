// Text editor that uses two stacks to undo and redo actions
#include <iostream>
#include <string>
using namespace std;

// type 'A' = add text at end, 'D' = delete text from end
struct Action
{
    char type;
    string text;
};

Action undoStack[100], redoStack[100];
int undoTop = -1, redoTop = -1;
string text = "";

void addText()
{
    string value;
    cout << "Enter text to add: ";
    cin.ignore(10000, '\n');
    getline(cin, value);
    if (value.empty())
    {
        cout << "No text entered.\n";
        return;
    }
    text += value;
    undoStack[++undoTop] = {'A', value};
    redoTop = -1; // new action clears redo history
    cout << "Text added.\n";
}

void deleteText()
{
    int count;
    cout << "Enter number of characters to delete from end: ";
    cin >> count;
    if (count <= 0 || count > (int)text.length())
    {
        cout << "Invalid count.\n";
        return;
    }
    string removed = text.substr(text.length() - count);
    text.erase(text.length() - count);
    undoStack[++undoTop] = {'D', removed};
    redoTop = -1;
    cout << "Text deleted.\n";
}

void undo()
{
    if (undoTop == -1)
    {
        cout << "Nothing to undo.\n";
        return;
    }
    Action a = undoStack[undoTop--];
    if (a.type == 'A')
        text.erase(text.length() - a.text.length());
    else
        text += a.text;
    redoStack[++redoTop] = a;
    cout << "Undo done.\n";
}

void redo()
{
    if (redoTop == -1)
    {
        cout << "Nothing to redo.\n";
        return;
    }
    Action a = redoStack[redoTop--];
    if (a.type == 'A')
        text += a.text;
    else
        text.erase(text.length() - a.text.length());
    undoStack[++undoTop] = a;
    cout << "Redo done.\n";
}

int main()
{
    int choice;
    do
    {
        cout << "\n------------ TEXT EDITOR (UNDO / REDO) ------------\n";
        cout << "1. Add Text\n2. Delete Text\n3. Undo\n4. Redo\n5. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
            break;
        switch (choice)
        {
        case 1:
            addText();
            break;
        case 2:
            deleteText();
            break;
        case 3:
            undo();
            break;
        case 4:
            redo();
            break;
        case 5:
            cout << "Exited.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
        if (choice >= 1 && choice <= 4)
            cout << "Current text: \"" << text << "\"\n";
    } while (choice != 5);
    return 0;
}
