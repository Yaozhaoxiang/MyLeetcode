# 111.二叉树最小深度

给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

说明：叶子节点是指没有子节点的节点。

## 解：

写的有点麻烦，没有官网那么简洁；
首先是`self1_BFS`，结束条件写的不好，因为是层序遍历，而且题目要求最小深度。这说明了，满足条件的第一个值，就是我们想要的结果，就可以返回了，不需要求出来完所有结果。
而且，队列可以使用`queue<pair<TreeNode *, int> > que`,不用使用两个队列来分别保存结果。


其次`self2_DFS`，写的有点麻烦，仍然使用每一分支信息对class全局变量操作；
答案很简单，**分别计算其左右子树的最小叶子节点深度。这样就将一个大问题转化为了小问题**。但是感觉还是有点难想出来！即使看过答案。

**self1_BFS**
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        queue<TreeNode*>que;
        queue<int>quedp;
        vector<int>depth;
        int m=1;
        if(root)
        {
            que.push(root);
            quedp.push(m);
        }
        TreeNode* p;
        int pdp;
        while(!que.empty())
        {
            p=que.front();
            que.pop();
            pdp=quedp.front();
            quedp.pop();
            if(!p->left&&!p->right)
                depth.push_back(pdp);
            if(p->left)
            {
                que.push(p->left);
                quedp.push(pdp+1);
            }
            if(p->right)
            {
                que.push(p->right);
                quedp.push(pdp+1);
            }
        } 
        if(depth.empty())
            return 0;
        else
        {
            auto min=min_element(depth.begin(),depth.end());    
            return *min;
        }  
                

    }
};
```
**self2_DFS**
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int>depth;
    int m;
    void DFS(TreeNode* T)
    {
        if(!T)
            return;
        ++m;
        if(!T->left&&!T->right)
            depth.push_back(m);
        if(T->left)
        {
            DFS(T->left);
            --m;
        }
        if(T->right)
        {
            DFS(T->right);
            --m;
        }

    }
    int minDepth(TreeNode* root) {
        m=0;
        DFS(root);
        if(depth.empty())
            return 0;
        else
        {
            auto min=min_element(depth.begin(),depth.end());    
            return *min;
        }  
    }
};
```
**官网DFS**
感觉很巧妙
```cpp
class Solution {
public:
    int minDepth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        if (root->left == nullptr && root->right == nullptr) {
            return 1;
        }

        int min_depth = INT_MAX;
        if (root->left != nullptr) {
            min_depth = min(minDepth(root->left), min_depth);
        }
        if (root->right != nullptr) {
            min_depth = min(minDepth(root->right), min_depth);
        }

        return min_depth + 1;
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/minimum-depth-of-binary-tree/solutions/382646/er-cha-shu-de-zui-xiao-shen-du-by-leetcode-solutio/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```


