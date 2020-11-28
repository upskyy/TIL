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
						{ 3, 0, 2 }, // P2
						{ 2, 1, 1 }, // P3
						{ 3, 3, 2 } }; // P4

	int max[5][3] = { { 7, 5, 3 }, // P0    // MAX Matrix
					  { 3, 2, 2 }, // P1
					  { 9, 0, 2 }, // P2
					  { 2, 2, 2 }, // P3
					  { 4, 3, 3 } }; // P4
	int original_avail[3] = { 0, 0, 2 };   // Available Resources
	int avail[3] = { 0, 0, 2 }; 
	int f[n], ans[n], idx = 0;
	for (k = 0; k < n; k++) {
		f[k] = FALSE;
	}
	int need[n][m];
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			need[i][j] = max[i][j] - alloc[i][j];
	}
	int y = 0;
	int flag2 = FALSE;
	for (k = 0; k < 5; k++) {
		for (i = 0; i < n; i++) {
			if (f[i] == FALSE) {
				int flag = FALSE;
				for (j = 0; j < m; j++) {
					if (need[i][j] > avail[j]) {
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
		printf("Max : %d %d %d\n", max[i][0], max[i][1], max[i][2]);
		printf("Need : %d %d %d\n", need[i][0], need[i][1], need[i][2]);
	}
	printf("\nAvailable : %d %d %d\n\n", original_avail[0], original_avail[1], original_avail[2]);

	if (flag2 == TRUE) {
		printf("It doesn't exist SAFE Sequence.\n");
	}
	else {
		printf("SAFE Sequence\n");
		for (i = 0; i < n - 1; i++)
			printf("P%d -> ", ans[i]);
		printf("P%d\n", ans[n - 1]);
	}
	return (0);
}