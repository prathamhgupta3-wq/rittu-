// Hospital patient records using a singly linked list (add, delete, display, search)
#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    int patient_id;
    string name;
    string condition;
    int age;
    Node *next;

    Node()
    {
        next = NULL;
    }

    void getPatientInfo(int id)
    {
        patient_id = id;

        cout << "Enter patient name: ";
        cin >> name;

        cout << "Enter patient age: ";
        cin >> age;

        cout << "Enter patient condition: ";
        cin >> condition;
    }

    void displayPatientInfo()
    {
        cout << "Patient ID: " << patient_id << endl;
        cout << "Patient Name: " << name << endl;
        cout << "Patient Age: " << age << endl;
        cout << "Patient Condition: " << condition << endl;
    }
};

Node *head = NULL;
Node *tail = NULL;

int patient_count = 0;

// Add Patient
void addPatient()
{
    patient_count++;

    Node *newNode = new Node();

    newNode->getPatientInfo(patient_count);

    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }

    cout << "\nPatient added successfully!\n";
    cout << "Assigned Patient ID: " << patient_count << endl;
}

// Display Patients
void displayPatientsList()
{
    if (head == NULL)
    {
        cout << "\nNo patient records available.\n";
        return;
    }

    Node *curr = head;

    cout << "\n----- Patient Records -----\n";

    while (curr != NULL)
    {
        curr->displayPatientInfo();
        cout << "---------------------------\n";
        curr = curr->next;
    }
}

// Search Patient
void searchPatient()
{
    if (head == NULL)
    {
        cout << "\nNo patient records available.\n";
        return;
    }

    int id;

    cout << "Enter patient ID to search: ";
    cin >> id;

    Node *curr = head;

    while (curr != NULL)
    {
        if (curr->patient_id == id)
        {
            cout << "\nPatient found!\n";
            cout << "---------------------------\n";
            curr->displayPatientInfo();
            cout << "---------------------------\n";
            return;
        }

        curr = curr->next;
    }

    cout << "\nPatient not found!\n";
}

// Delete Patient
void deletePatient()
{
    if (head == NULL)
    {
        cout << "\nNo patient records available.\n";
        return;
    }

    int id;

    cout << "Enter patient ID to delete: ";
    cin >> id;

    Node *curr = head;
    Node *prev = NULL;

    while (curr != NULL)
    {

        if (curr->patient_id == id)
        {

            // Deleting first node
            if (prev == NULL)
            {
                head = curr->next;

                if (head == NULL)
                {
                    tail = NULL;
                }
            }

            // Deleting middle or last node
            else
            {
                prev->next = curr->next;

                if (curr == tail)
                {
                    tail = prev;
                }
            }

            delete curr;

            cout << "\nPatient deleted successfully!\n";
            return;
        }

        prev = curr;
        curr = curr->next;
    }

    cout << "\nPatient not found!\n";
}

int main()
{

    int choice;

    do
    {
        cout << "\n=================================\n";
        cout << "   HOSPITAL PATIENT RECORD SYSTEM\n";
        cout << "=================================\n";
        cout << "1. Add Patient\n";
        cout << "2. Delete Patient\n";
        cout << "3. Display Patients\n";
        cout << "4. Search Patient\n";
        cout << "5. Exit\n";
        cout << "=================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {

        case 1:
            addPatient();
            break;

        case 2:
            deletePatient();
            break;

        case 3:
            displayPatientsList();
            break;

        case 4:
            searchPatient();
            break;

        case 5:
            cout << "\nExiting the program...\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}