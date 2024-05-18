# 13 三数之和

给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请

你返回所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

## 解： 

**self_使用双指针遍历**
主要是防止重复元素，使用若是和前一个元素相同，直接下一层循环
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>>res;
        int len=nums.size();
        sort(nums.begin(),nums.end());
        if(len<3)
            return res;
        for(int i=0;i<len-2;i++)
        {
            if(nums[i]>0) return res;
            if(i>0 && nums[i]==nums[i-1])
                continue;
            int left=i+1;
            int right=len-1;
            int target=-nums[i];
            while(left<right)
            {
                if(left>i+1 && nums[left]==nums[left-1])
                {
                    left++;
                    continue;
                }
                if(nums[left]+nums[right]==target)
                {
                    res.push_back({nums[i],nums[left],nums[right]});
                    left++;
                    right--;
                }
                else if(nums[left]+nums[right]>target)
                    right--;
                else if(nums[left]+nums[right]<target)
                    left++;
            }
        }
        return res;
    }
};
```
**第二种方法可以用哈希表——一个解答写的，感觉很好**
很巧妙，i和j循环后，使`j=umap.at(nums[j]);`，这样的话，就直接跳到重复值的最后一个位置。
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>>res;
        int len=nums.size();
        // 2. 排序，便于后续去重
        sort(nums.begin(),nums.end());
        unordered_map<int,int>umap;
        // 1. 考虑边界情况
        if(len<3)
            return res;
        // 3. 用一个map来存放某个数最后的index，达到去重的目的
        for(int i=0;i<len;i++) //利用覆盖性，直接使得存放某个数值最后一个下标
            umap[nums[i]]=i;
        // 4. 遍历数组找满足符合条件的组合
        for(int i=0;i<len-2;i++)
        {
            for(int j=i+1;j<len-1;j++)
            {
                int target=-nums[i]-nums[j];
                if(umap.count(target) && umap.at(target)>j)
                    res.push_back({nums[i],nums[j],target});
                // j换为它所在的最后一个index，达到去重的目的
                j=umap.at(nums[j]);
            }
            // i换为它所在的最后一个index，达到去重的目的
            i=umap.at(nums[i]);
        }
        return res;
    }
};
```







