#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of vertices
#define MAX_VERTICES 100

// Define the structure of an adjacency list node
//
struct AdjListNode {
    char* dest;
    struct AdjListNode* next;
};



// Define the structure of an adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Define the structure of a graph
struct Graph {
    int V; // number of vertices
    struct AdjList* array;
};

// Create a new adjacency list node
struct AdjListNode* newAdjListNode(char* dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = (char*)malloc(strlen(dest)+1);
    strcpy(newNode->dest, dest);
    newNode->next = NULL;
    return newNode;
}

// Create a graph with a given number of vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    int i;
    for (i = 0; i < V; i++)
        graph->array[i].head = NULL;
    return graph;
}

// Add an edge to the graph
void addEdge(struct Graph* graph, char* src, char* dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Depth First Search algorithm
void DFS(struct Graph* graph, int v, int visited[], char* alarmVertex) {
    visited[v] = 1;
    printf("%s ", graph->array[v].head->dest);
    struct AdjListNode* node = graph->array[v].head;
    while (node != NULL) {
        char* w = node->dest;
        if (!visited[w]) {
            if (strcmp(w, alarmVertex) == 0) {
                printf("\nAlarm! Location Reached!\n");
                exit(0);
            }
            DFS(graph, w, visited, alarmVertex);
        }
        node = node->next;
    }
}

// Driver function
int main() {
    // Create a graph with 6 vertices
    int V = 6;
    struct Graph* graph = createGraph(V);

    // Add edges to the graph
    addEdge(graph, "bus stand", "school");
    addEdge(graph, "bus stand", "airport");
    addEdge(graph, "school", "airport");
    addEdge(graph, "airport", "bus stand");
    addEdge(graph, "airport", "hospital");
    addEdge(graph, "hospital", "hospital");

    // Set the alarm vertex to "airport"
    char* alarmVertex = "airport";

    // Run DFS algorithm from "bus stand"
    int visited[V];
    int i;
    for (i = 0; i < V; i++)
        visited[i] = 0;
    printf("DFS Traversal starting from \"bus stand\": ");
    DFS(graph, 0, visited, alarmVertex);
    printf("\n");

    return 0;
}
