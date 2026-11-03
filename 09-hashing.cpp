// Student information system that stores and finds records using hashing
#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

struct Student
{
    int id;
    string name;
    float marks;
    Student *next;
};

Student *table[SIZE] = {};

int hashValue(int id)
{
    return id % SIZE;
}

Student *search(int id)
{
    if (id <= 0)
        return NULL;
    Student *temp = table[hashValue(id)];
    while (temp != NULL)
    {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void addStudent()
{
    int id;
    string name;
    float marks;
    cout << "Enter student ID: ";
    if (!(cin >> id))
        return;
    if (id <= 0)
    {
        cout << "ID must be positive.\n";
        return;
    }
    if (search(id) != NULL)
    {
        cout << "Student ID already exists.\n";
        return;
    }
    cout << "Enter student name: ";
    cin.ignore(10000, '\n');
    getline(cin, name);
    cout << "Enter marks (0 to 100): ";
    if (!(cin >> marks))
        return;
    if (marks < 0 || marks > 100 || name.empty())
    {
        cout << "Invalid student details.\n";
        return;
    }
    int index = hashValue(id);
    table[index] = new Student{id, name, marks, table[index]};
    cout << "Student added at index " << index << ".\n";
}

void findStudent()
{
    int id;
    cout << "Enter student ID to search: ";
    if (!(cin >> id))
        return;
    Student *student = search(id);
    if (student == NULL)
        cout << "Student not found.\n";
    else
    {
        cout << "ID: " << student->id << "\nName: " << student->name;
        cout << "\nMarks: " << student->marks << endl;
    }
}

void updateStudent()
{
    int id;
    cout << "Enter student ID to update: ";
    if (!(cin >> id))
        return;
    Student *student = search(id);
    if (student == NULL)
    {
        cout << "Student not found.\n";
        return;
    }
    string name;
    float marks;
    cout << "Enter new name: ";
    cin.ignore(10000, '\n');
    getline(cin, name);
    cout << "Enter new marks: ";
    if (!(cin >> marks))
        return;
    if (marks < 0 || marks > 100 || name.empty())
    {
        cout << "Invalid student details.\n";
        return;
    }
    student->name = name;
    student->marks = marks;
    cout << "Student updated.\n";
}

void deleteStudent()
{
    int id;
    cout << "Enter student ID to delete: ";
    if (!(cin >> id))
        return;
    if (id <= 0)
    {
        cout << "Student not found.\n";
        return;
    }
    int index = hashValue(id);
    Student *temp = table[index], *prev = NULL;
    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        cout << "Student not found.\n";
        return;
    }
    if (prev == NULL)
        table[index] = temp->next;
    else
        prev->next = temp->next;
    delete temp;
    cout << "Student deleted.\n";
}

void display()
{
    for (int i = 0; i < SIZE; i++)
    {
        cout << "Index " << i << ": ";
        Student *temp = table[i];
        while (temp != NULL)
        {
            cout << '[' << temp->id << ", " << temp->name;
            cout << ", " << temp->marks << "] -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

int main()
{
    int choice;
    do
    {
        cout << "\n------------ STUDENT INFORMATION SYSTEM ------------\n";
        cout << "1. Add Student\n2. Search Student\n3. Update Student\n";
        cout << "4. Delete Student\n5. Display Hash Table\n6. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
            break;
        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            findStudent();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            display();
            break;
        case 6:
            cout << "Exited.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);
    for (int i = 0; i < SIZE; i++)
    {
        while (table[i] != NULL)
        {
            Student *temp = table[i];
            table[i] = temp->next;
            delete temp;
        }
    }
    return 0;
}