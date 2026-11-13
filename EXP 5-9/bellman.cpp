
#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
using namespace std;
using namespace chrono;

struct Edge
{
    int u, v, weight;
};

void bellmanFord(int V, vector<Edge>& edges, int src)
{
    vector<int> dist(V, INT_MAX);

    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++)
    {
        bool updated = false;

        for (auto edge : edges)
        {
            int u = edge.u;
            int v = edge.v;
            int w = edge.weight;

            if (dist[u] != INT_MAX &&
                dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }

        if (!updated)
            break;
    }

    // Check for negative-weight cycle
    for (auto edge : edges)
    {
        int u = edge.u;
        int v = edge.v;
        int w = edge.weight;

        if (dist[u] != INT_MAX &&
            dist[u] + w < dist[v])
        {
            cout << "\nNegative weight cycle detected!\n";
            return;
        }
    }

    cout << "\nShortest distances from source " << src << ":\n";

    for (int i = 0; i < V; i++)
    {
        cout << "Vertex " << i << " : ";

        if (dist[i] == INT_MAX)
            cout << "INF\n";
        else
            cout << dist[i] << "\n";
    }
}

int main()
{
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < E; i++)
    {
        cin >> edges[i].u
            >> edges[i].v
            >> edges[i].weight;
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    auto start = high_resolution_clock::now();

    bellmanFord(V, edges, src);

    auto stop = high_resolution_clock::now();

    auto duration =
        duration_cast<nanoseconds>(stop - start);

    cout << "\nExecution time: "
         << duration.count() << " nanoseconds\n";

    return 0;
}
