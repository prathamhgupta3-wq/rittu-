// Finds the cheapest way to connect cities using Prim's minimum spanning tree
#include <iostream>
#include <string>
using namespace std;

const int MAX = 20;
string cities[MAX];
long long cost[MAX][MAX];
int n = 0;

void enterNetwork()
{
    int size, roads;
    cout << "Enter number of cities (1 to 20): ";
    if (!(cin >> size))
        return;
    if (size < 1 || size > MAX)
    {
        cout << "Invalid number of cities.\n";
        return;
    }
    string names[MAX];
    long long temp[MAX][MAX];
    cin.ignore(10000, '\n');
    for (int i = 0; i < size; i++)
    {
        cout << "Enter name of city " << i + 1 << ": ";
        getline(cin, names[i]);
        if (names[i].empty())
        {
            cout << "City name cannot be empty.\n";
            return;
        }
        for (int j = 0; j < i; j++)
        {
            if (names[i] == names[j])
            {
                cout << "City names must be different.\n";
                return;
            }
        }
        for (int j = 0; j < size; j++)
            temp[i][j] = -1;
    }
    cout << "Enter number of roads: ";
    if (!(cin >> roads))
        return;
    if (roads < 0 || roads > size * (size - 1) / 2)
    {
        cout << "Invalid number of roads.\n";
        return;
    }
    cout << "Enter each road as city numbers (1 based) and cost:\n";
    for (int i = 0; i < roads; i++)
    {
        int u, v;
        long long value;
        if (!(cin >> u >> v >> value))
            return;
        if (u < 1 || u > size || v < 1 || v > size || u == v || value < 0)
        {
            cout << "Invalid road details.\n";
            return;
        }
        u--;
        v--;
        if (temp[u][v] != -1)
        {
            cout << "Road already entered.\n";
            return;
        }
        temp[u][v] = temp[v][u] = value;
    }
    n = size;
    for (int i = 0; i < n; i++)
    {
        cities[i] = names[i];
        for (int j = 0; j < n; j++)
            cost[i][j] = temp[i][j];
    }
    cout << "Network stored.\n";
}

void prim()
{
    if (n == 0)
    {
        cout << "Enter network first.\n";
        return;
    }
    bool selected[MAX] = {};
    int from[MAX], to[MAX], edges = 0;
    long long total = 0;
    selected[0] = true;
    while (edges < n - 1)
    {
        int u = -1, v = -1;
        for (int i = 0; i < n; i++)
        {
            if (!selected[i])
                continue;
            for (int j = 0; j < n; j++)
            {
                if (!selected[j] && cost[i][j] != -1 &&
                    (u == -1 || cost[i][j] < cost[u][v]))
                {
                    u = i;
                    v = j;
                }
            }
        }
        if (u == -1)
        {
            cout << "Network is disconnected. No spanning tree exists.\n";
            return;
        }
        from[edges] = u;
        to[edges] = v;
        selected[v] = true;
        total += cost[u][v];
        edges++;
    }
    cout << "Minimum Spanning Tree:\n";
    for (int i = 0; i < edges; i++)
        cout << cities[from[i]] << " - " << cities[to[i]]
             << " : " << cost[from[i]][to[i]] << endl;
    cout << "Total cost: " << total << endl;
}

int main()
{
    int choice;
    do
    {
        cout << "\n------------ CITY ROAD NETWORK ------------\n";
        cout << "1. Enter Network\n2. Find Minimum Spanning Tree\n3. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
            break;
        switch (choice)
        {
        case 1:
            enterNetwork();
            break;
        case 2:
            prim();
            break;
        case 3:
            cout << "Exited.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);
    return 0;
}