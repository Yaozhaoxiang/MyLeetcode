问题:

给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。


示例 1：

    输入：grid = [
    ["1","1","1","1","0"],
    ["1","1","0","1","0"],
    ["1","1","0","0","0"],
    ["0","0","0","0","0"]
    ]
输出：1

示例 2：

    输入：grid = [
    ["1","1","0","0","0"],
    ["1","1","0","0","0"],
    ["0","0","1","0","0"],
    ["0","0","0","1","1"]
    ]
输出：3



解答：本质就是遍历树，进行集合分类，首先想到就是用**DFS和BFS和并查集**。用着三种方法求解

**DFS**
```cpp
class Solution {
public:
    void Dfs(vector<vector<char>>& grid,int i,int j)
    {
        int n=grid.size();
        int m=grid[0].size();
        grid[i][j]='0';
        if(i-1>=0&&grid[i-1][j]=='1')Dfs(grid,i-1,j);
        if(i+1<n&&grid[i+1][j]=='1')Dfs(grid,i+1,j);
        if(j-1>=0&&grid[i][j-1]=='1')Dfs(grid,i,j-1);
        if(j+1<m&&grid[i][j+1]=='1')Dfs(grid,i,j+1);
    }
    int numIslands(vector<vector<char>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        int count=0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++) //遍历所有的点
            {
                if(grid[i][j]=='1')//若是全通的，只进行一次。相当于遍历各个集合
                {
                    count++;
                    Dfs(grid,i,j);
                }
            }
        }
        return count;
    }
};
```

**BFS**
```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        int count=0;
        queue<pair<int,int>>que;
        //BFS
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(grid[i][j]=='1')
                {
                    count++;
                    que.push({i,j});
                    grid[i][j]='0';
                    while(!que.empty())
                    {
                        auto pa=que.front();
                        que.pop();
                        int x=pa.first;
                        int y=pa.second;
                        if(x-1>=0&&grid[x-1][y]=='1')
                        {
                            que.push({x-1,y});
                            grid[x-1][y]='0';
                        }
                        if(x+1<n&&grid[x+1][y]=='1')
                        {
                            que.push({x+1,y});
                            grid[x+1][y]='0';
                        }
                        if(y-1>=0&&grid[x][y-1]=='1')
                        {
                            que.push({x,y-1});
                            grid[x][y-1]='0';
                        }
                        if(y+1<m&&grid[x][y+1]=='1')
                        {
                            que.push({x,y+1});
                            grid[x][y+1]='0';
                        }
                    }
                }
            }
        }
        return count;
    }
};
```
**并查集**
```cpp
//二维数组，把每个点都当作节点，每个节点的位置都是从0从左到右递增
class Djset{
public:
    vector<int>rank;
    vector<int>fa;
    int count;
    // n行数，m列数
    Djset(vector<vector<char>>& grid)
    {
        int n=grid.size();
        int m=grid[0].size();
        count=0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(grid[i][j]=='1')
                {
                    fa.push_back(i*m+j);
                    count++;
                }
                else{
                    fa.push_back(-1);
                }
                rank.push_back(0);
            }
        }
    }
    int find( int i){
        if(fa[i]==i)
            return i;
        else
            return fa[i]=find(fa[i]);
    }
    void merge(int i,int j){
        int rooti=find(i);
        int rootj=find(j);
        if(rooti==rootj)
            return;
        if(rank[rooti]<rank[rootj])
            swap(rooti,rootj);
        fa[rootj]=rooti;
        if(rank[rooti]==rank[rootj])
            rank[rooti]++;
        count--;
    }
};
class Solution {
public:

    int numIslands(vector<vector<char>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        //并查集
        Djset D(grid);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(grid[i][j]=='1')
                {
                    grid[i][j]='0';
                    if(i-1>=0&&grid[i-1][j]=='1')D.merge(i*m+j,(i-1)*m+j);
                    if(i+1<n&&grid[i+1][j]=='1')D.merge(i*m+j,(i+1)*m+j);
                    if(j-1>=0&&grid[i][j-1]=='1')D.merge(i*m+j,i*m+j-1);
                    if(j+1<m&&grid[i][j+1]=='1')D.merge(i*m+j,i*m+j+1);
                }
            }
        }
    return D.count;
    }
};
```



