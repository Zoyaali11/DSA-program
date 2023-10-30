#include <iostream>
#include <cstdlib>

using namespace std;

struct Node {
    int data;
    Node** next;
    int numNext;
    bool visited;
};

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->numNext = 0;
    newNode->next = nullptr;
    newNode->visited = false;
    return newNode;
}

void addEdge(Node* source, Node* destination) {
    source->numNext++;
    source->next = (Node**)malloc(source->numNext * sizeof(Node*));
    source->next[source->numNext - 1] = destination;

    destination->numNext++;
    destination->next = (Node**)malloc(destination->numNext * sizeof(Node*));
    destination->next[destination->numNext - 1] = source;
}

void Graph(Node* nodes, int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        free(nodes[i].next);
    }
    free(nodes);
}

void dfs(Node* currentNode, int target, Node** path, int& pathLength) {
    if (currentNode->data == target) {
       
        path[pathLength++] = currentNode;
        return;
    }

    currentNode->visited = true;
    for (int i = 0; i < currentNode->numNext; i++) {
        Node* nextNode = currentNode->next[i];
        if (!nextNode->visited) {
            dfs(nextNode, target, path, pathLength);
            if (pathLength > 0) {
                // If target is found in the subpath, add the current node to the path
                path[pathLength++] = currentNode;
                return;
            }
        }
    }
}

int main() {
    int numNodes = 5; // Number of nodes
    Node* nodes = (Node*)malloc(numNodes * sizeof(Node));

    for (int i = 0; i < numNodes; i++) {
        nodes[i] = *createNode(i + 1);
    }

    addEdge(&nodes[0], &nodes[1]);
    addEdge(&nodes[0], &nodes[2]);
    addEdge(&nodes[1], &nodes[3]);
    addEdge(&nodes[2], &nodes[3]);
    addEdge(&nodes[2], &nodes[4]);

    int targetNode = 4;
    Node** path = (Node**)malloc(numNodes * sizeof(Node*));
    int pathLength = 0;

    dfs(&nodes[0], targetNode, path, pathLength);

    if (pathLength > 0) {
        cout << "Path from node " << nodes[0].data << " to node " << targetNode << ": ";
        for (int i = pathLength - 1; i >= 0; i--) {
            cout << path[i]->data << " ";
        }
        cout << endl;
    } else {
        cout << "Path not found." << endl;
    }

    free(path);
    Graph(nodes, numNodes);

    return 0;
}
