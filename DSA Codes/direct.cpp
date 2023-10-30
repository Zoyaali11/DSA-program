#include <iostream>
#include <cstdlib>

using namespace std;

struct Edge {
    int dest;
    Edge* next;
};

struct Vertex {
    int data;
    Edge* adjList;
};

Edge* createEdge(int dest) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->next = nullptr;
    return newEdge;
}

Vertex* createVertex(int data) {
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
    newVertex->data = data;
    newVertex->adjList = nullptr;
    return newVertex;
}

void addEdge(Vertex* vertex, int dest) {
    Edge* newEdge = createEdge(dest);
    newEdge->next = vertex->adjList;
    vertex->adjList = newEdge;
}

void insertEdge(Vertex* vertices, int source, int dest) {
    addEdge(&vertices[source], dest);
}

int outDegree(const Vertex& vertex) {
    int count = 0;
    Edge* edge = vertex.adjList;
    while (edge) {
        count++;
        edge = edge->next;
    }
    return count;
}

int inDegree(const Vertex* vertices, int numVertices, int vertexIndex) {
    int count = 0;
    for (int i = 0; i < numVertices; i++) {
        Edge* edge = vertices[i].adjList;
        while (edge) {
            if (edge->dest == vertexIndex) {
                count++;
            }
            edge = edge->next;
        }
    }
    return count;
}

int main() {
    int numVertices = 5;
    Vertex* vertices = (Vertex*)malloc(numVertices * sizeof(Vertex));

    for (int i = 0; i < numVertices; i++) {
        vertices[i] = *createVertex(i);
    }

    insertEdge(vertices, 0, 1);
    insertEdge(vertices, 2, 2);
    insertEdge(vertices, 1, 3);
    insertEdge(vertices, 2, 3);
    insertEdge(vertices, 3, 0);
    insertEdge(vertices, 4, 2);

    for (int i = 0; i < numVertices; i++) {
        cout << "Vertex " << i << ": In-Degree = " << inDegree(vertices, numVertices, i) << ", Out-Degree = " << outDegree(vertices[i]) << endl;
    }

    free(vertices);
    return 0;
}
