#include <iostream>
#include <cstdlib>

using namespace std;

struct Edge {
    int source, destination, weight;
};

struct Graph {
    int vertices, edgesCount;
    Edge* edges;
    int* parent;

    void initial(int V, int E) {
        vertices = V;
        edgesCount = E;
        edges = new Edge[E];
        parent = new int[V];
    }

    void addEdge(int index, int u, int v, int w) {
        edges[index].source = u;
        edges[index].destination = v;
        edges[index].weight = w;
    }

    int findParent(int vertex) {
        if (parent[vertex] == -1) return vertex;
        return findParent(parent[vertex]);
    }

    void Sets(int u, int v) {
        int uRoot = findParent(u);
        int vRoot = findParent(v);
        parent[uRoot] = vRoot;
    }

    void kruskalMST() {
        Edge result[vertices];
        int e = 0;
        int i = 0;

        for (i = 0; i < vertices; ++i) {
            result[i] = Edge();
        }

        sortEdges();

        for (i = 0; i < vertices; ++i) {
            parent[i] = -1;
        }

        i = 0;

        while (e < vertices - 1) {
            Edge nextEdge = edges[i++];
            int r = findParent(nextEdge.source);
            int m = findParent(nextEdge.destination);

            if (r != m) {
                result[e++] = nextEdge;
                Sets(r, m);
            }
        }

        cout << "Edges in Minimum Spanning Tree:" << endl;
        for (i = 0; i < e; ++i) {
            cout << "Vertex " << result[i].source << " - Vertex " << result[i].destination << " - Weight: " << result[i].weight << endl;
        }
    }

    void sortEdges() {
        for (int i = 1; i < edgesCount; ++i) {
            for (int j = 0; j < edgesCount - i; ++j) {
                if (edges[j].weight > edges[j + 1].weight) {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }
    }
};

int main() {
    int V = 5;
    int E = 7;
    Graph g;

    g.initial(V, E);

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(i, u, v, w);
    }

    g.kruskalMST();

    return 0;
}
