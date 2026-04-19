#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int solveChocolate(int m, int n, int **prices) {
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = prices[i][j]; 

            for (int k = 1; k <= i / 2; k++) {
                dp[i][j] = max(dp[i][j], dp[k][j] + dp[i - k][j]);
            }

            for (int k = 1; k <= j / 2; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[i][j - k]);
            }
        }
    }

    return dp[m][n];
}

int main() {
    int m = 4;
    int n = 4;
    
    int **prices = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        prices[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for(int i=1; i<=m; i++) {
        for(int j=1; j<=n; j++) {
            prices[i][j] = i * j; 
        }
    }
    prices[2][2] = 100;

    printf("Max Revenue: %d\n", solveChocolate(m, n, prices));

    for (int i = 0; i <= m; i++) free(prices[i]);
    free(prices);

    return 0;
}