#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

vector<int> countingSort(vector<int> &nums, int bot, int top){  // nums值域[bot, top]
    int len=nums.size();
    int *count=new int[top-bot+1]();                    // [bot, top]数字个数
    for(int i=0;i<len;++i) ++count[nums[i]-bot];        // 统计各个数字出现的个数
    for(int i=1;i<top-bot+1;++i) count[i]+=count[i-1];  // 求前缀数, 实际上是每个数字的编号

    vector<int> ret(len);
    for(int i=len-1;i>=0;--i) ret[--count[nums[i]-bot]]=nums[i];    // 查询数字nums[i]-bot的编号, 并按编号保存在ret中
    return ret;
}

int main(){
    vector<int> nums={3, 3, 2, 5};
    countingSort(nums, 2, 5);
    return 0;
}