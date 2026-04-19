#include <bits/stdc++.h>

using namespace std;

#define ll long long

void dfs(vector<vector<ll>> &grid, ll i, ll j, ll old_color, ll new_color, ll rows, ll cols)
{
    // First 4 cases: Checks if out of bounds
    // Last case = checks if grid[i][j] is not the original color
    if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] != old_color)
    {
        return;
    }

    // Recursion

    grid[i][j] = new_color;

    dfs(grid, i + 1, j, old_color, new_color, rows, cols); // bottom
    dfs(grid, i - 1, j, old_color, new_color, rows, cols); // top
    dfs(grid, i, j + 1, old_color, new_color, rows, cols); // right
    dfs(grid, i, j - 1, old_color, new_color, rows, cols); // left
}

void bfs_floodfill(vector<vector<ll>> &grid, ll sr, ll sc, ll new_color)
{
    ll rows = grid.size();
    ll cols = grid[0].size();
    ll old_color = grid[sr][sc];
    if (old_color == new_color)
        return;
    queue<pair<ll, ll>> q;
    // push initial cell coordinates
    q.push({sr, sc});
    grid[sr][sc] = new_color; // mark on push to avoid duplicate entries in queue
    while (!q.empty())
    {
        pair<ll, ll> p = q.front();
        q.pop();

        ll i = p.first;
        ll j = p.second;
        // Check before pushing neighbors instead of after popping
        auto tryPush = [&](ll ni, ll nj)
        {
            if (ni < 0 || ni >= rows || nj < 0 || nj >= cols || grid[ni][nj] != old_color)
                return;
            grid[ni][nj] = new_color; // mark on push
            q.push({ni, nj});
        };
        tryPush(i + 1, j); // bottom
        tryPush(i - 1, j); // top
        tryPush(i, j + 1); // right
        tryPush(i, j - 1); // left
    }
}

int main()
{

    ll rows, cols;
    cin >> rows >> cols;

    vector<vector<ll>> grid(rows, vector<ll>(cols));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> grid[i][j];
        }
    }

    ll starting_row, starting_col, new_color;
    cin >> starting_row >> starting_col >> new_color;

    ll old_color = grid[starting_row][starting_col];

    /*if(old_color == new_color) return 0;
    dfs(grid,starting_row,starting_col,old_color,new_color,rows,cols);*/

    bfs_floodfill(grid, starting_row, starting_col, new_color);
}