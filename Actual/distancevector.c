#include <stdio.h>

#define INF 999   // Represents infinity (no direct connection)
#define MAX 10    // Maximum number of nodes supported

// Each node maintains a routing table with distance and from (next hop)
struct Node {
    int dist[MAX];  // Distance to every node
    int from[MAX];  // Next hop to reach each destination
} rt[MAX];

int main() {
    int cost[MAX][MAX];  // Cost matrix between nodes
    int n;               // Number of nodes
    int i, j, k, count = 0;

    // ---------- Step 1: Input ----------
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the cost matrix (use %d for infinity):\n", INF);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);

            if (i == j)
                cost[i][j] = 0;  // Cost from node to itself is 0

            // Initialize routing table
            rt[i].dist[j] = cost[i][j]; // Initially, distance is direct cost
            rt[i].from[j] = j;          // Initially, assume direct path
        }
    }

    // ---------- Step 2: Bellman-Ford Update ----------
    do {
        count = 0;  // Tracks if any update occurred in this iteration

        // For each node i, check every destination j via every neighbor k
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                for (k = 0; k < n; k++) {
                    // If going from i to j via k is cheaper, update it
                    if (rt[i].dist[j] > cost[i][k] + rt[k].dist[j]) {
                        rt[i].dist[j] = cost[i][k] + rt[k].dist[j];
                        rt[i].from[j] = k;  // Update next hop
                        count++;  // Mark that an update happened
                    }
                }
            }
        }
    } while (count != 0);  // Repeat until no changes occur

    // ---------- Step 3: Display Routing Tables ----------
    for (i = 0; i < n; i++) {
        printf("\nRouting table for Node %c:\n", 'A' + i);
        printf("To\tCost\tNext Hop\n");

        for (j = 0; j < n; j++) {
            printf("%c\t%d\t", 'A' + j, rt[i].dist[j]);

            if (i == j)
                printf("-\n");  // No next hop to self
            else
                printf("%c\n", 'A' + rt[i].from[j]);  // Show next hop
        }
    }

    // ---------- Step 4: Query for Shortest Path ----------
    char srcChar, destChar;
    printf("\nEnter source node (A, B, ...): ");
    scanf(" %c", &srcChar);
    printf("Enter destination node (A, B, ...): ");
    scanf(" %c", &destChar);

    int src = srcChar - 'A';
    int dest = destChar - 'A';

    printf("Shortest path from %c to %c is: %d\n", srcChar, destChar, rt[src].dist[dest]);

    return 0;
}




// 🧪 Sample Input
// Copy
// Edit
// Enter the number of nodes: 3
// Enter the cost matrix (use 999 for infinity):
// 0 2 7
// 2 0 1
// 7 1 0
// Enter source node (A, B, ...): A
// Enter destination node (A, B, ...): C
// ✅ Sample Output
// less
// Copy
// Edit
// Routing table for Node A:
// To    Cost    Next Hop
// A     0       -
// B     2       B
// C     3       B

// Routing table for Node B:
// To    Cost    Next Hop
// A     2       A
// B     0       -
// C     1       C

// Routing table for Node C:
// To    Cost    Next Hop
// A     3       B
// B     1       B
// C     0       -

// Shortest path from A to C is: 3
// 🔁 Quick Revision Checklist
// Concept	Notes
// INF (999)	Represents no direct connection
// cost[i][j]	Direct link cost between nodes
// dist[i][j]	Best known distance from i to j
// from[i][j]	Next hop from i to reach j
// Bellman-Ford	Update if i→j via k is cheaper
// Convergence	Stops when no further updates happen
// Routing table	Shows cost and next hop for every node
// Path query	Prints cost from source to destination