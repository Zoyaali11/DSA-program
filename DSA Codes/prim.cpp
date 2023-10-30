#include <iostream>
#include <cstdlib>

using namespace std;

const int LARGE_VALUE = 999999; // large value as infinity

struct Edge {
    int source;
    int destination;
    int weight;
};

struct Graph {
    int vertices;
    Edge* edges;

    int* parent;
    int* key;
    bool* mstSet;

    void initial(int V, int E) {
        vertices = V;
        edges = new Edge[E];
        parent = new int[V];
        key = new int[V];
        mstSet = new bool[V];
    }

    void addEdge(int index, int u, int v, int w) {
        edges[index].source = u;
        edges[index].destination = v;
        edges[index].weight = w;
    }

    int findMinKey() {
        int minKey = LARGE_VALUE;
        int minIndex;

        for (int v = 0; v < vertices; ++v) {
            if (!mstSet[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        return minIndex;
    }

    void primMST() {
        for (int i = 0; i < vertices; ++i) {
            key[i] = LARGE_VALUE; // Initialize with a large value
            mstSet[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int i = 0; i < vertices - 1; ++i) {
            int u = findMinKey();
            mstSet[u] = true;

            for (int j = 0; j < vertices; ++j) {
                if (edges[j].weight < key[j] && edges[j].destination == j) {
                    parent[j] = u;
                    key[j] = edges[j].weight;
                }
            }
        }

        cout << "Edges in Minimum Spanning Tree:" << endl;
        for (int i = 1; i < vertices; ++i) {
            cout << "Vertex " << parent[i] << " - Vertex " << i << " - Weight: " << key[i] << endl;
        }
    }
};

int main() {
    int V = 5;
    int E = 7;
    Graph g;

    g.initial(V, E);

    for (int i = 0; i < E; ++i) {
        int t, v, w;
        cin >> t >> v >> w;
        g.addEdge(i, t, v, w);
    }

    g.primMST();

    return 0;
}
