// Stores student grades as a sparse matrix and finds averages and toppers
#include <iostream>
#include <iomanip>
using namespace std;

struct Grade
{
    int student, subject, marks;
};

Grade grades[400];
int students = 0, subjects = 0, total = 0;

void enterGrades()
{
    int r, c, marks;
    cout << "Enter number of students and subjects (1 to 20): ";
    if (!(cin >> r >> c))
        return;
    if (r < 1 || r > 20 || c < 1 || c > 20)
    {
        cout << "Invalid size.\n";
        return;
    }
    Grade temp[400];
    int count = 0;
    cout << "Enter grades row wise (0 means subject not taken):\n";
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            if (!(cin >> marks))
                return;
            if (marks < 0 || marks > 100)
            {
                cout << "Marks must be from 0 to 100.\n";
                return;
            }
            if (marks != 0)
                temp[count++] = {i, j, marks};
        }
    }
    students = r;
    subjects = c;
    total = count;
    for (int i = 0; i < total; i++)
        grades[i] = temp[i];
    cout << "Grades stored successfully.\n";
}

void display()
{
    cout << "Students: " << students << "  Subjects: " << subjects;
    cout << "  Non-zero grades: " << total << endl;
    cout << "Student\tSubject\tMarks\n";
    for (int i = 0; i < total; i++)
        cout << grades[i].student << '\t' << grades[i].subject
             << '\t' << grades[i].marks << endl;
}

double average(int subject, int &count)
{
    int sum = 0;
    count = 0;
    for (int i = 0; i < total; i++)
    {
        if (grades[i].subject == subject)
        {
            sum += grades[i].marks;
            count++;
        }
    }
    return count == 0 ? 0 : (double)sum / count;
}

void showAverages()
{
    for (int j = 1; j <= subjects; j++)
    {
        int count;
        double value = average(j, count);
        cout << "Subject " << j << ": ";
        if (count == 0)
            cout << "No grades available\n";
        else
            cout << fixed << setprecision(2) << value << endl;
    }
}

void highestGrades()
{
    for (int j = 1; j <= subjects; j++)
    {
        int highest = 0;
        for (int i = 0; i < total; i++)
            if (grades[i].subject == j && grades[i].marks > highest)
                highest = grades[i].marks;
        cout << "Subject " << j << ": ";
        if (highest == 0)
        {
            cout << "No grades available\n";
            continue;
        }
        cout << "Highest marks = " << highest << ", Students: ";
        for (int i = 0; i < total; i++)
            if (grades[i].subject == j && grades[i].marks == highest)
                cout << grades[i].student << ' ';
        cout << endl;
    }
}

void bestSubject()
{
    double best = -1;
    for (int j = 1; j <= subjects; j++)
    {
        int count;
        double value = average(j, count);
        if (count != 0 && value > best)
            best = value;
    }
    if (best < 0)
    {
        cout << "No grades available.\n";
        return;
    }
    cout << "Highest average: " << fixed << setprecision(2) << best;
    cout << "\nSubjects: ";
    for (int j = 1; j <= subjects; j++)
    {
        int count;
        if (average(j, count) == best && count != 0)
            cout << j << ' ';
    }
    cout << endl;
}

void updateGrade()
{
    int s, sub, marks;
    cout << "Enter student number, subject number and marks: ";
    if (!(cin >> s >> sub >> marks))
        return;
    if (s < 1 || s > students || sub < 1 || sub > subjects ||
        marks < 0 || marks > 100)
    {
        cout << "Invalid grade details.\n";
        return;
    }
    for (int i = 0; i < total; i++)
    {
        if (grades[i].student == s && grades[i].subject == sub)
        {
            if (marks == 0)
            {
                for (int k = i; k < total - 1; k++)
                    grades[k] = grades[k + 1];
                total--;
            }
            else
                grades[i].marks = marks;
            cout << "Grade updated.\n";
            return;
        }
    }
    if (marks != 0)
        grades[total++] = {s, sub, marks};
    cout << "Grade updated.\n";
}

int main()
{
    int choice;
    do
    {
        cout << "\n------------ STUDENT GRADES ------------\n";
        cout << "1. Enter Grades\n2. Display Sparse Matrix\n";
        cout << "3. Subject Averages\n4. Highest Grades\n";
        cout << "5. Subject with Highest Average\n6. Update Grade\n7. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
            break;
        if (choice != 1 && choice != 7 && students == 0)
        {
            cout << "Enter grades first.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            enterGrades();
            break;
        case 2:
            display();
            break;
        case 3:
            showAverages();
            break;
        case 4:
            highestGrades();
            break;
        case 5:
            bestSubject();
            break;
        case 6:
            updateGrade();
            break;
        case 7:
            cout << "Exited.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 7);
    return 0;
}