#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
void kruskalMST(int **cost, int V) {
    int parent[V];
    int edges[V * (V - 1) / 2][3];
    int edgeCount = 0;
    int selectedEdges = 0;
    int totalCost = 0;

    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (cost[i][j] != 9999) {
                edges[edgeCount][0] = i;
                edges[edgeCount][1] = j;
                edges[edgeCount][2] = cost[i][j];
                edgeCount++;
            }
        }
    }

    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j][2] > edges[j + 1][2]) {
                int temp;

                temp = edges[j][0];
                edges[j][0] = edges[j + 1][0];
                edges[j + 1][0] = temp;

                temp = edges[j][1];
                edges[j][1] = edges[j + 1][1];
                edges[j + 1][1] = temp;

                temp = edges[j][2];
                edges[j][2] = edges[j + 1][2];
                edges[j + 1][2] = temp;
            }
        }
    }

    for (int i = 0; i < edgeCount && selectedEdges < V - 1; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int weight = edges[i][2];

        int rootU = u;
        int rootV = v;

        while (parent[rootU] != rootU) {
            rootU = parent[rootU];
        }

        while (parent[rootV] != rootV) {
            rootV = parent[rootV];
        }

        if (rootU != rootV) {
            parent[rootU] = rootV;

            printf("Edge %d:(%d, %d) cost:%d\n",
                   selectedEdges, u, v, weight);

            totalCost += weight;
            selectedEdges++;
        }
    }

    printf("Minimum cost= %d\n", totalCost);
}
int main() {
    int V;
    printf("No of vertices: ");
    scanf("%d", &V);

    int **cost = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
        cost[i] = (int *)malloc(V * sizeof(int));

    printf("Adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &cost[i][j]);

    kruskalMST(cost, V);

    for (int i = 0; i < V; i++)
        free(cost[i]);
    free(cost);

    return 0;
}
