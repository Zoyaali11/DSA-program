#include <iostream>
#include <cstdlib>
#include <deque>

using namespace std;

struct Node {
    int data;
    int numNext;
    Node** next;
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
    Node** newNext = (Node**)malloc((source->numNext + 1) * sizeof(Node*));
    for (int i = 0; i < source->numNext; i++) {
        newNext[i] = source->next[i];
    }
    newNext[source->numNext] = destination;
    
    free(source->next);  // Free the old array
    source->next = newNext;
    source->numNext++;
    
    Node** newNextDest = (Node**)malloc((destination->numNext + 1) * sizeof(Node*));
    for (int i = 0; i < destination->numNext; i++) {
        newNextDest[i] = destination->next[i];
    }
    newNextDest[destination->numNext] = source;
    
    free(destination->next);  // Free the old array
    destination->next = newNextDest;
    destination->numNext++;
}

void breadthFirstSearch(Node* start) {
    deque<Node*> bfsQueue;
    bfsQueue.push_back(start);
    start->visited = true;

    cout << "Breadth-First Search starting from node " << start->data << ": ";
    while (!bfsQueue.empty()) {
        Node* current = bfsQueue.front();
        bfsQueue.pop_front();
        cout << current->data << " ";

        for (int i = 0; i < current->numNext; i++) {
            Node* neighbor = current->next[i];
            if (!neighbor->visited) {
                bfsQueue.push_back(neighbor);
                neighbor->visited = true;
            }
        }
    }
    cout << endl;
}

int main() {
    Node* node1 = createNode(1);
    Node* node2 = createNode(2);
    Node* node3 = createNode(3);
    Node* node4 = createNode(4);
    Node* node5 = createNode(5);

    addEdge(node1, node2);
    addEdge(node1, node3);
    addEdge(node2, node4);
    addEdge(node3, node4);
    addEdge(node3, node5);

    breadthFirstSearch(node1);

    
    free(node1->next);
    free(node1);
    free(node2->next);
    free(node2);
    free(node3->next);
    free(node3);
    free(node4->next);
    free(node4);
    free(node5->next);
    free(node5);

    return 0;
}
