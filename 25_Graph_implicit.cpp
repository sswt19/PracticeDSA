#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <list>
#include <sstream>
using namespace std;

/*
Pattern0: Flood fill: do something on nodes reachable from current node
1.Flood Fill
2.Keys and Rooms(Not Implicit graph Problem): https://leetcode.com/problems/keys-and-rooms/

Pattern1: Start DFS/BFS from nodes at boundary
1. Surrounded Regions:https://leetcode.com/problems/surrounded-regions/ 
2. Number of Enclaves:https://leetcode.com/problems/number-of-enclaves/

Pattern2: DFS/BFS from each unvisited node/Island problems
1. Number of Islands: https://leetcode.com/problems/number-of-islands/
2. Max Area of Island: https://leetcode.com/problems/max-area-of-island/

Pattern3: Might Require Combination of above 2 patterns
1. Number of Closed Islands: https://leetcode.com/problems/number-of-closed-islands/

Pattern4: BFS to get time/distance/other operations related to nbrs first
1.Rotting Oranges:https://leetcode.com/problems/rotting-oranges/
*/

//P0.1
class P0Solution1
{
public:
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor)
    {
        int modColor = image[sr][sc];
        if (modColor == newColor)
            return image;
        dfs_helper(sr, sc, image, modColor, newColor);
        return image;
    }
    void dfs_helper(int i, int j, vector<vector<int>> &image, int modColor, int newColor)
    {
        if (i < 0 || j < 0 || i >= image.size() || j >= image[0].size())
            return;
        if (image[i][j] != modColor) //only if it is allowed to be modified we change it
            return;
        image[i][j] = newColor;
        int lx[] = {1, 0, -1, 0};
        int ly[] = {0, 1, 0, -1};
        for (int k = 0; k < 4; k++)
            dfs_helper(i + lx[k], j + ly[k], image, modColor, newColor);
    }
};
//P0.2
class P0Solution2
{
public:
    bool canVisitAllRooms(vector<vector<int>> &rooms)
    {
        unordered_map<int, vector<int>> adjList;
        unordered_map<int, bool> visited;

        for (int i = 0; i < rooms.size(); i++)
            for (auto nbr : rooms[i])
                adjList[i].push_back(nbr);

        dfs_helper(0, visited, adjList);
        if (visited.size() == rooms.size())
            return true;
        return false;
    }
    void dfs_helper(int src, unordered_map<int, bool> &visited, unordered_map<int, vector<int>> adjList)
    {
        visited[src] = true;
        for (auto nbr : adjList[src])
            if (visited.find(nbr) == visited.end())
                dfs_helper(nbr, visited, adjList);
    }
};
//P1.1
class P1Solution1
{
public:
    void solve(vector<vector<char>> &board)
    {
        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[0].size(); j++)
                if (i == 0 || i == board.size() - 1 || j == 0 || j == board[0].size() - 1)
                    dfs_helper(i, j, board); // call dfs on each boundary row=0 col=0 and last row and col
        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[0].size(); j++)
            {
                if (board[i][j] == '1')
                    board[i][j] = 'O';
                else if (board[i][j] == 'O')
                    board[i][j] = 'X';
            }
    }
    void dfs_helper(int i, int j, vector<vector<char>> &board)
    {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
            return;
        if (board[i][j] == 'X' || board[i][j] == '1')
            return;
        board[i][j] = '1'; //make all connected O from boundary to 1
        int lx[] = {0, 1, 0, -1};
        int ly[] = {1, 0, -1, 0};

        for (int k = 0; k < 4; k++)
            dfs_helper(i + lx[k], j + ly[k], board);
    }
};
// P2.1
class P2Solution1
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int components = 0;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == '1')
                {
                    components++;
                    dfs_helper(i, j, grid);
                }
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == 'X')
                    grid[i][j] = '1'; //changing X back to 1
        return components;
    }
    void dfs_helper(int i, int j, vector<vector<char>> &grid)
    {
        if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size())
            return;
        if (grid[i][j] == '0' || grid[i][j] == 'X')
            return;
        grid[i][j] = 'X'; //make 1 to X so we know it has been visited
        int lx[] = {0, 1, 0, -1};
        int ly[] = {1, 0, -1, 0};
        for (int k = 0; k < 4; k++)
            dfs_helper(i + lx[k], j + ly[k], grid);
    }
};
//P2.2
class P2Solution2
{
public:
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        int maxArea = 0;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[i].size(); j++)
                if (grid[i][j] == 1)
                {
                    int curArea = 0;
                    dfs_helper(i, j, grid, curArea);
                    maxArea = max(curArea, maxArea);
                }
        //changing grid to old state
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[i].size(); j++)
                if (grid[i][j] == 2)
                    grid[i][j] = 1;
        return maxArea;
    }
    void dfs_helper(int i, int j, vector<vector<int>> &grid, int &area)
    {
        if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size())
            return;
        if (grid[i][j] == 0 || grid[i][j] == 2)
            return;
        area += 1;
        grid[i][j] = 2; // changing 1 to 2 know that land has been visited
        int lx[] = {0, 1, 0, -1};
        int ly[] = {1, 0, -1, 0};
        for (int k = 0; k < 4; k++)
            dfs_helper(i + lx[k], j + ly[k], grid, area);
    }
};
// P3.1
class P3Solution1
{
public:
    int closedIsland(vector<vector<int>> &grid)
    {
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (i == 0 || j == 0 | i == grid.size() - 1 || j == grid[0].size() - 1)
                    dfs_helper(i, j, grid, true);
        int closedLand = 0;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == 0)
                {
                    closedLand++;
                    dfs_helper(i, j, grid, false);
                }
        // setting grid to its original state
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == 2 || grid[i][j] == 3)
                    grid[i][j] = 0;

        return closedLand;
    }
    void dfs_helper(int i, int j, vector<vector<int>> &grid, bool outerBoundary)
    {
        if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size())
            return;
        if (grid[i][j] == 1 || grid[i][j] == 2 || grid[i][j] == 3)
            return;
        if (outerBoundary)
            grid[i][j] = 2; // set 2 for lands connected to boundaries
        else
            grid[i][j] = 3; // set 3 for land which are part of closed land
        int lx[] = {0, 1, 0, -1};
        int ly[] = {1, 0, -1, 0};
        for (int k = 0; k < 4; k++)
            dfs_helper(i + lx[k], j + ly[k], grid, outerBoundary);
    }
};

//P4.1
class P4Solution1
{
public:
    int orangesRotting(vector<vector<int>> &grid)
    {
        int totalOrange = 0;
        int rottenOrange = 0;
        queue<pair<int, int>> q;

        //below loop counts all oranges and adds rotten oranges to queue
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 1)
                    totalOrange++;
                else if (grid[i][j] == 2)
                {
                    totalOrange++;
                    q.push({i, j});
                }
            }

        if (q.empty()) //there were no rotten oranges very important case
            return totalOrange == rottenOrange ? 0 : -1;

        int time = -1; // so that at time 0 the queue will have the starting rotten oranges
        while (!q.empty())
        {
            time++;
            int size = q.size(); //size= no of new rotten orange at every second
            for (int i = 0; i < size; i++)
            {
                auto p = q.front();
                q.pop();
                rottenOrange++;
                int lx[] = {1, 0, -1, 0};
                int ly[] = {0, 1, 0, -1};
                for (int k = 0; k < 4; k++)
                {
                    int x = p.first + lx[k];
                    int y = p.second + ly[k];
                    if (!(x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size())) //check indexes not out of bounds
                        if (grid[x][y] == 1)
                        {
                            grid[x][y] = 2;
                            q.push({x, y});
                        }
                }
            }
        }
        return rottenOrange == totalOrange ? time : -1;
    }
};