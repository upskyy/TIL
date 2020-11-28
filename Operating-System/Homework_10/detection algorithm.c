#include <stdio.h>
#define TRUE 1
#define FALSE 0
int main()
{
	// P0, P1, P2, P3, P4 are the Process names 

	int n, m, i, j, k;
	n = 5; // Number of processes
	m = 3; // Number of resources
	int alloc[5][3] = { { 0, 1, 0 }, // P0    // Allocation Matrix
						{ 2, 0, 0 }, // P1
						{ 3, 0, 3 }, // P2
						{ 2, 1, 1 }, // P3
						{ 0, 0, 2 } }; // P4

	int req[5][3] = { { 0, 0, 0 }, // P0    // Request Matrix
					  { 2, 0, 2 }, // P1
					  { 0, 0, 0 }, // P2
					  { 1, 0, 0 }, // P3
					  { 0, 0, 2 } }; // P4

	int avail[3] = { 0, 0, 0 }; // Available Resources
	int original_avail[3] = { 0, 0, 0 };
	int f[n], ans[n], idx = 0;
	for (k = 0; k < n; k++) {
		f[k] = FALSE;
	}

	int y = 0;
	int flag2 = FALSE;
	for (k = 0; k < 5; k++) {
		for (i = 0; i < n; i++) {
			if (f[i] == FALSE) {
				int flag = FALSE;
				for (j = 0; j < m; j++) {
					if (req[i][j] > avail[j]) {
						flag = TRUE;
						break;
					}
				}
				if (flag == TRUE && i == n - 1) {
					flag2 = TRUE;
					break;
				}

				if (flag == FALSE) {
					ans[idx++] = i;
					for (y = 0; y < m; y++)
						avail[y] += alloc[i][y];
					f[i] = TRUE;
				}
			}
		}
		if (flag2 == TRUE) {
			break;
		}
	}

	for (i = 0; i < n; i++) {
		printf("P%d\n", i);
		printf("Allocation : %d %d %d\n", alloc[i][0], alloc[i][1], alloc[i][2]);
		printf("Request : %d %d %d\n", req[i][0], req[i][1], req[i][2]);
	}
	printf("\nAvailable : %d %d %d\n\n", original_avail[0], original_avail[1], original_avail[2]);

	if (flag2 == TRUE) {
		printf("It is deadlocked state.\n");
	}
	else {
		printf("SAFE Sequence\n");
		for (i = 0; i < n - 1; i++)
			printf("P%d -> ", ans[i]);
		printf("P%d\n", ans[n - 1]);
		printf("It is not deadlocked state.\n");
	}
	return (0);

}