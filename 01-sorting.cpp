// Sorts student records by marks using Bubble, Selection and Insertion sort
#include <iostream>
#include <string>
using namespace std;
struct student
{
    string name;
    float marks;
} record[20], temp, sorted[20];

int main()
{
    int choice;
    int num;
    int counter = 0;

    do
    {
        cout << "\n------ MENU ------";
        cout << "\n1) Add Student Marks Record";
        cout << "\n2) Display Student Record";
        cout << "\n3) Bubble Sort";
        cout << "\n4) Selection Sort";
        cout << "\n5) Insertion Sort";
        cout << "\n6) Exit";

        cout << "\nEnter Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "\nEnter Number Of Students : ";
            cin >> num;
            for (int i = 0; i < num; i++)
            {
                cout << "\nEnter Student Name : ";
                cin >> record[counter].name;
                cout << "Enter Marks : ";
                cin >> record[counter].marks;
                counter++;
            }
            cout << "\nRecords Added Successfully.\n";
            for (int i = 0; i < counter; i++)
            {
                sorted[i] = record[i];
            }

            break;
        }
        case 2:
        {
            cout << "\n---------------------------";
            cout << "\nName\t\tMarks";
            cout << "\n---------------------------";
            for (int i = 0; i < counter; i++)
            {
                cout << "\n"
                     << sorted[i].name
                     << "\t\t"
                     << sorted[i].marks;
            }
            break;
        }
        case 3:
        {
            if (counter == 0)
            {
                cout << "\n No records to sort! \n";
                break;
            }

            for (int i = 0; i < counter - 1; i++)
            {
                for (int j = 0; j < counter - i - 1; j++)
                {
                    if (record[j].marks > record[j + 1].marks)
                    {
                        temp = record[j];
                        record[j] = record[j + 1];
                        record[j + 1] = temp;
                    }
                }
            }

            cout << "\n----- DISPLAY RECORDS -----";
            cout << "\nName\t\tMarks";
            cout << "\n---------------------------";
            for (int i = 0; i < counter; i++)
            {
                cout << "\n"
                     << sorted[i].name << "\t\t" << sorted[i].marks;
            }
            cout << "\n-----------------------";

            cout << "\n----- BUBBLE SORTED RECORDS -----";
            cout << "\nName\t\tMarks";
            cout << "\n---------------------------";
            for (int i = 0; i < counter; i++)
            {
                cout << "\n"
                     << record[i].name << "\t\t" << record[i].marks;
            }
            cout << "\n\nBubble Sorted Records Displayed Successfully...\n";
            break;
        }

        case 4:
        {
            if (counter == 0)
            {
                cout << "\nNo records to sort!\n";
                break;
            }
            for (int i = 0; i < counter - 1; i++)
            {
                int min = i;
                for (int j = i + 1; j < counter; j++)
                {
                    if (record[j].marks < record[min].marks)
                    {
                        min = j;
                    }
                }

                if (min != i)
                {
                    temp = record[i];
                    record[i] = record[min];
                    record[min] = temp;
                }
            }

            cout << "\n----- DISPLAY RECORDS -----";
            cout << "\nName\t\tMarks";
            cout << "\n---------------------------";
            for (int i = 0; i < counter; i++)
            {
                cout << "\n"
                     << sorted[i].name << "\t\t" << sorted[i].marks;
            }
            cout << "\n-----------------------";

            cout << "\n----- SELECTION SORTED RECORDS -----";
            cout << "\nName\t\tMarks";
            cout << "\n---------------------------";

            for (int i = 0; i < counter; i++)
            {
                cout << "\n"
                     << record[i].name << "\t\t" << record[i].marks;
            }
            cout << "\n\nSelection Sorted Records Displayed Successfully...\n";
            break;
        }

        case 5:
        {
            if (counter == 0)
            {
                cout << "\nNo records to sort!\n";
                break;
            }
            for (int i = 1; i < counter; i++)
            {
                student key = record[i];
                int j = i - 1;
                while (j >= 0 && record[j].marks > key.marks)
                {
                    record[j + 1] = record[j];
                    j--;
                }
                record[j + 1] = key;
            }

            cout << "\n----- DISPLAY RECORDS -----";
            cout << "\nName\t\tMarks";
            cout << "\n---------------------------";
            for (int i = 0; i < counter; i++)
            {
                cout << "\n"
                     << sorted[i].name << "\t\t" << sorted[i].marks;
            }
            cout << "\n-----------------------";

            cout << "\n----- INSERTION SORTED RECORDS -----";
            cout << "\nName\t\tMarks";
            cout << "\n---------------------------";

            for (int i = 0; i < counter; i++)
            {
                cout << "\n"
                     << record[i].name << "\t\t" << record[i].marks;
            }
            cout << "\n\nInsertion Sorted Records Displayed Successfully...\n";
            break;
        }
        case 6:
            cout << "\nThank You!";
            break;
        default:
            cout << "\nInvalid Choice!";
        }
    } while (choice != 6);
    return 0;
}