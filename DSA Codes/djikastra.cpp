#include <iostream>
#include <cstdlib>

using namespace std;

const int INFINITY = 99999; 
struct Edge {
    int destination;
    int weight;
    Edge* next;
};


struct Vertex {
    int id;
    int distance;
    bool visited;
    Edge* edges;
};


void addEdge(Vertex* vertex, int dest, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->destination = dest;
    newEdge->weight = weight;
    newEdge->next = vertex->edges;
    vertex->edges = newEdge;
}


Vertex* MinDist(Vertex* vertices, int numVertices) {
    Vertex* minVertex = nullptr;
    int minDistance = INFINITY; 

    for (int i = 0; i < numVertices; ++i) {
        if (!vertices[i].visited && vertices[i].distance < minDistance) {
            minVertex = &vertices[i];
            minDistance = vertices[i].distance;
        }
    }

    return minVertex;
}


void dij(Vertex* vertices, int numVertices, int start) {
    for (int i = 0; i < numVertices; ++i) {
        vertices[i].distance = INFINITY; // Use the user-defined constant
        vertices[i].visited = false;
        vertices[i].edges = nullptr;
    }

    vertices[start].distance = 0;

    for (int count = 0; count < numVertices - 1; ++count) {
        Vertex* u = MinDist(vertices, numVertices);
        if (u == nullptr) {
            break;
        }
        u->visited = true;

        Edge* edge = u->edges;
        while (edge != nullptr) {
            Vertex* v = &vertices[edge->destination];
            if (!v->visited && u->distance != INFINITY && u->distance + edge->weight < v->distance) {
                v->distance = u->distance + edge->weight;
            }
            edge = edge->next;
        }
    }

    // Print the shortest distances from the starting vertex
    cout << "Shortest distances from vertex " << start << " to all other vertices:" << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << "Vertex " << i << ": " << vertices[i].distance << endl;
    }
}

int main() {
    int numVertices = 6; // Number of vertices
    Vertex* vertices = (Vertex*)malloc(numVertices * sizeof(Vertex));

    
    addEdge(&vertices[0], 1, 2);
    addEdge(&vertices[0], 2, 3);
    addEdge(&vertices[1], 2, 4);
    addEdge(&vertices[1], 3, 7);
    addEdge(&vertices[2], 4, 2);
    addEdge(&vertices[3], 5, 1);
    addEdge(&vertices[4], 5, 5);

    int startVertex = 0; 

    dij(vertices, numVertices, startVertex);

    free(vertices); // Free allocated memory

    return 0;
}
