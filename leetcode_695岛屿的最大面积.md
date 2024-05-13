# 695. 岛屿的最大面积
已解答
给你一个大小为 m x n 的二进制矩阵 grid 。

岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在 水平或者竖直的四个方向上 相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。

岛屿的面积是岛上值为 1 的单元格的数目。

计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。

## 题解
这一题和第200题几乎一样，用同样三种方法再做一遍

**1.DFS**
```cpp
class Solution {
public:
    vector<int>count;
    vector<vector<bool>>visited;
    void DFS(vector<vector<int>>& grid,int i,int j,int count_i)
    {
        int n=grid.size();
        int m=grid[0].size();
        count[count_i]++;
        visited[i][j]=true;
        if(i-1>=0&& grid[i-1][j]==1 && (!visited[i-1][j]) )DFS(grid,i-1,j,count_i);
        if(i+1<n&& grid[i+1][j]==1 && (!visited[i+1][j]) )DFS(grid,i+1,j,count_i);
        if(j-1>=0&& grid[i][j-1]==1 && (!visited[i][j-1]) )DFS(grid,i,j-1,count_i);
        if(j+1<m&& grid[i][j+1]==1 && (!visited[i][j+1]) )DFS(grid,i,j+1,count_i);
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        visited=vector(n,vector<bool>(m,false));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(!visited[i][j]&&grid[i][j]==1)
                {
                    count.push_back(0);
                    int size=count.size();
                    //下标size-1
                    DFS(grid,i,j,size-1);
                }
            }
        }
        if (count.empty())
            return 0;
        else
        {
            auto itres=max_element(count.begin(),count.end());
            return *itres;
        }
    }
};
```
**2.BFS**
```cpp
class Solution {
public:
    vector<int>count;
    vector<vector<bool>>visited;
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        visited=vector(n,vector<bool>(m,false));
        queue<pair<int,int>> que;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(!visited[i][j]&&grid[i][j]==1)
                {
                    visited[i][j]=true;
                    count.push_back(0);
                    int size=count.size();
                    que.push({i,j});
                    while(!que.empty())
                    {
                        count[size-1]++;
                        auto p=que.front();
                        que.pop();
                        int cx=p.first;
                        int cy=p.second;
                        if(cx-1>=0&& grid[cx-1][cy]==1 && (!visited[cx-1][cy]) )
                        {
                            que.push({cx-1,cy});
                            visited[cx-1][cy]=true;
                        }
                        if(cx+1<n&& grid[cx+1][cy]==1 && (!visited[cx+1][cy]) )
                        {
                            que.push({cx+1,cy});
                            visited[cx+1][cy]=true;
                        }
                        if(cy-1>=0&& grid[cx][cy-1]==1 && (!visited[cx][cy-1]) )
                        {
                            que.push({cx,cy-1});
                            visited[cx][cy-1]=true;
                        }
                        if(cy+1<m&& grid[cx][cy+1]==1 && (!visited[cx][cy+1]) )
                        {
                            que.push({cx,cy+1});
                            visited[cx][cy+1]=true;
                        }
                    }
                }
            }
        }
        if (count.empty())
            return 0;
        else
        {
            auto itres=max_element(count.begin(),count.end());
            return *itres;
        }
    }
};
```



