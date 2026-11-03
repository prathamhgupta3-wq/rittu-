// Finds a contact in a phone book using Linear search and Binary search
#include <iostream>
#include <string>
using namespace std;

struct phonebook
{
    char name[20];
    string phoneno;
} records[20], temp;

int main()
{
    int i, j, count = 0, ch;
    int flag = 0, low, high, mid, comparisons = 0;
    string target;

    do
    {
        cout << "\n\n----- MENU -----";
        cout << "\n1) Add Phonebook Records";
        cout << "\n2) Display Phonebook Records";
        cout << "\n3) Search Phonebook Records (Linear Search)";
        cout << "\n4) Search Phonebook Records (Binary Search)";
        cout << "\n5) Exit";

        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "\nEnter total number of records: ";
            cin >> count;

            for (i = 0; i < count; i++)
            {
                cout << "\nEnter Name: ";
                cin >> records[i].name;

                cout << "Enter Phone Number: ";
                cin >> records[i].phoneno;
            }

            // Bubble Sort by Name
            for (i = 0; i < count - 1; i++)
            {
                for (j = 0; j < count - i - 1; j++)
                {
                    if (string(records[j].name) > string(records[j + 1].name))
                    {
                        temp = records[j];
                        records[j] = records[j + 1];
                        records[j + 1] = temp;
                    }
                }
            }

            cout << "\nRecords Added and Sorted Successfully!";
            break;

        case 2:
            if (count == 0)
            {
                cout << "\nNo Records Found!";
            }
            else
            {
                cout << "\n\nName\t\tPhone Number";
                cout << "\n--------------------------------";

                for (i = 0; i < count; i++)
                {
                    cout << "\n"
                         << records[i].name << "\t\t" << records[i].phoneno;
                }
            }
            break;

        case 3:
            flag = 0;

            cout << "\nEnter Name or Phone Number to Search: ";
            cin >> target;

            for (i = 0; i < count; i++)
            {
                if (target == records[i].name || target == records[i].phoneno)
                {
                    cout << "\nRecord Found!";
                    cout << "\nName : " << records[i].name;
                    cout << "\nPhone Number : " << records[i].phoneno;
                    flag = 1;
                    break;
                }
            }

            if (flag == 0)
            {
                cout << "\nRecord Not Found!";
            }
            break;

        case 4:
            flag = 0;
            comparisons = 0;

            low = 0;
            high = count - 1;

            cout << "\nEnter Name to Search: ";
            cin >> target;

            while (low <= high)
            {
                mid = (low + high) / 2;
                comparisons++;

                if (records[mid].name == target)
                {
                    cout << "\nRecord Found!";
                    cout << "\nName : " << records[mid].name;
                    cout << "\nPhone Number : " << records[mid].phoneno;
                    cout << "\nComparisons : " << comparisons;
                    flag = 1;
                    break;
                }
                else if (target < records[mid].name)
                {
                    high = mid - 1;
                }
                else
                {
                    low = mid + 1;
                }
            }

            if (flag == 0)
            {
                cout << "\nRecord Not Found!";
            }

            break;

        case 5:
            cout << "\nExiting...";
            break;

        default:
            cout << "\nInvalid Choice!";
        }

    } while (ch != 5);

    return 0;
}