// Finds shortest path from one computer to all others using Dijkstra's algorithm
#include <iostream>
using namespace std;

const int MAX = 20;
const int INF = 999999;

int cost[MAX][MAX];
int n = 0;

void enterNetwork()
{
    int links;
    cout << "Enter number of computers (1 to 20): ";
    cin >> n;
    if (n < 1 || n > MAX)
    {
        cout << "Invalid number of computers.\n";
        n = 0;
        return;
    }

    // 0 means no direct link
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = 0;

    cout << "Enter number of links: ";
    cin >> links;
    cout << "Enter each link as: computer1 computer2 cost (computers are 1 to " << n << ")\n";
    for (int i = 0; i < links; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        if (u < 1 || u > n || v < 1 || v > n || u == v || c <= 0)
        {
            cout << "Invalid link, skipped.\n";
            continue;
        }
        cost[u - 1][v - 1] = c;
        cost[v - 1][u - 1] = c;
    }
    cout << "Network stored.\n";
}

void printPath(int parent[], int node)
{
    if (parent[node] == -1)
    {
        cout << node + 1;
        return;
    }
    printPath(parent, parent[node]);
    cout << " -> " << node + 1;
}

void dijkstra()
{
    if (n == 0)
    {
        cout << "Enter network first.\n";
        return;
    }

    int source;
    cout << "Enter source computer (1 to " << n << "): ";
    cin >> source;
    if (source < 1 || source > n)
    {
        cout << "Invalid source.\n";
        return;
    }
    source--;

    int dist[MAX], parent[MAX];
    bool visited[MAX];
    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = false;
    }
    dist[source] = 0;

    for (int count = 0; count < n; count++)
    {
        // pick the unvisited computer with smallest distance
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        if (dist[u] == INF)
            break;
        visited[u] = true;

        // update distances of its neighbours
        for (int v = 0; v < n; v++)
        {
            if (cost[u][v] != 0 && !visited[v] && dist[u] + cost[u][v] < dist[v])
            {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "\nComputer\tDistance\tPath\n";
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << "\t\t";
        if (dist[i] == INF)
            cout << "No path\n";
        else
        {
            cout << dist[i] << "\t\t";
            printPath(parent, i);
            cout << endl;
        }
    }
}

int main()
{
    int choice;
    do
    {
        cout << "\n------------ COMPUTER NETWORK ------------\n";
        cout << "1. Enter Network\n2. Shortest Path (Dijkstra)\n3. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
            break;
        switch (choice)
        {
        case 1:
            enterNetwork();
            break;
        case 2:
            dijkstra();
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
