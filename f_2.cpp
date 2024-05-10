#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;
using namespace std::chrono;
class Solution {
public:
    int answer=16;//存放答案
    int num=0;//记录已经使用的贴纸数
    unordered_map<string,int> memo;//保存之前找到某个remains所用的最小num
    void solve(vector<string> &stickers,string &remains)
    {
        if(remains=="")//成功贴出,且num<answer(在上一层控制)
            answer=num;
        if(num>=answer-1)//如果num>=answer-1,最终答案不会比answer小,终止搜索
            return ;
        for(int i=0;i<stickers.size();++i)
        {
            if(stickers[i].find(remains[0])!=stickers[i].npos)
            {
                string temp=stickers[i],copy=remains;//拷贝stickers[i]和remains
                int pos=0;
                for(int j=0;j<remains.size();++j)//删除remains中能用temp贴的所有字母
                    if((pos=temp.find(remains[j]))!=temp.npos)
                    {
                        temp.erase(pos,1);
                        remains.erase(j,1);
                        --j;
                    }
                ++num;//贴纸数+1
                auto it=memo.find(remains);//尝试在memo中找remains
                if(it==memo.end()||it->second>num)//找不到remains或者记录值更大,执行替换和搜索
                {
                    memo[remains]=num;
                    solve(stickers,remains);
                }
                remains=copy;//回溯至原状态
                --num;
            }
        }
    }
    int minStickers(vector<string>& stickers, string target) {
        solve(stickers,target);
        return answer==16?-1:answer;//answer==16说明没找到
    }
};


int main()
{
	string target = "thehat";
	vector <string> stickers = {"with","example","science"};
	int s;
    auto start = steady_clock::now();

	Solution Solution_1;
	s = Solution_1.minStickers(stickers,target);
	cout << s << endl;

	auto end = steady_clock::now();
    auto last = duration_cast<microseconds>(end - start);

	cout <<  last.count() << "um";
	system("pause");
    return 0;
}
