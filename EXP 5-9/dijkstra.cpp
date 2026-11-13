
#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
using namespace std;
using namespace chrono;

void dijkstra(int V, vector<vector<pair<int, int>>>& adj, int src)
{
    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);

    dist[src] = 0;

    for (int i = 0; i < V; i++)
    {
        int u = -1;

        // Find the unvisited vertex with minimum distance
        for (int j = 0; j < V; j++)
        {
            if (!visited[j] &&
                (u == -1 || dist[j] < dist[u]))
            {
                u = j;
            }
        }

        if (u == -1 || dist[u] == INT_MAX)
            break;

        visited[u] = true;

        // Update adjacent vertices
        for (auto edge : adj[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (!visited[v] &&
                dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
            }
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

    vector<vector<pair<int, int>>> adj(V);

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        if (w < 0)
        {
            cout << "Dijkstra cannot handle negative weights.\n";
            return 0;
        }

        adj[u].push_back({v, w});
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    auto start = high_resolution_clock::now();

    dijkstra(V, adj, src);

    auto stop = high_resolution_clock::now();

    auto duration =
        duration_cast<nanoseconds>(stop - start);

    cout << "\nExecution time: "
         << duration.count() << " nanoseconds\n";

    return 0;
}
