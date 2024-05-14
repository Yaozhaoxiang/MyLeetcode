# Leetcod 112路径总和

给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。

叶子节点 是指没有子节点的节点。



## 解
写的有点吃力，递归不是很熟悉；
自己写用的是深搜，主要利用了每个路径的信息,返回上一节点的权值;
其实没那么麻烦

**1.自己写的**
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
    int sum;
    bool res=false;
    int DFS(TreeNode* T,int targetSum)
    {
        if(T==NULL)
        {
            return 0;
        }
        sum+=T->val;
        if(T->left==nullptr&&T->right==nullptr&&sum==targetSum)
            res=true;
        int a=DFS(T->left,targetSum);
        sum-=a;
        int b=DFS(T->right,targetSum);
        sum-=b;
        return T->val;
    }
    bool hasPathSum(TreeNode* root, int targetSum) {
        sum=0;
        if(!root)
            return false;
        DFS(root,targetSum);
        return res;
    }
};
```
**官方，递归**
感觉有点像求全部节点数;
感觉最巧妙的就是用sum-root->val;这样就不用每次返回上一个节点的值；
将这个大问题转化为一个小问题：是否存在从当前节点的子节点到叶子的路径，满足其路径和为 `sum - val`。
这样的话就每个层都有字节的sum，就不用来回减val，很巧妙。
```cpp
class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (root == nullptr) {
            return false;
        }
        if (root->left == nullptr && root->right == nullptr) {
            return sum == root->val;
        }
        return hasPathSum(root->left, sum - root->val) ||
               hasPathSum(root->right, sum - root->val);
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/path-sum/solutions/318487/lu-jing-zong-he-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

**官方BFS**
其实BFS应该首先想到的，用广搜很简单，直接判断是否是子节点，来判断返回结果，一层一层搜索
```cpp
class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (root == nullptr) {
            return false;
        }
        queue<TreeNode *> que_node;
        queue<int> que_val;
        que_node.push(root);
        que_val.push(root->val);
        while (!que_node.empty()) {
            TreeNode *now = que_node.front();
            int temp = que_val.front();
            que_node.pop();
            que_val.pop();
            if (now->left == nullptr && now->right == nullptr) {
                if (temp == sum) {
                    return true;
                }
                continue;
            }
            if (now->left != nullptr) {
                que_node.push(now->left);
                que_val.push(now->left->val + temp);
            }
            if (now->right != nullptr) {
                que_node.push(now->right);
                que_val.push(now->right->val + temp);
            }
        }
        return false;
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/path-sum/solutions/318487/lu-jing-zong-he-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```