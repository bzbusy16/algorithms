#include<iostream>
#include<vector>
using namespace std;

vector<int> countingSort(vector<int> &nums, int bot, int top, int radix=1){
    int len=nums.size();
    int *count=new int[top-bot+1]();
    for(int i=0;i<len;++i) ++count[(nums[i]/radix)%10-bot]; // 取对应位置的数字
    for(int i=1;i<top-bot+1;++i) count[i]+=count[i-1];

    vector<int> ret(len);
    for(int i=len-1;i>=0;--i) ret[--count[(nums[i]/radix)%10-bot]]=nums[i];
    return ret;
}

void radixSort(vector<int> &nums){
    int m_num=INT_MIN;
    for(int i=0;i<nums.size();++i) m_num=max(m_num, abs(nums[i]));
    for(int radix=1;radix<m_num;radix*=10){
        // countingSort稳定, 不会打乱那些对应数位为0的数的顺序
        // countingSort本身支持负数, 所以radixSort同样支持负数
        nums=countingSort(nums, -9, 9, radix);
    }
}

int main(){
    vector<int> nums={-21, -213, 552, 25, -8, 1, 0};
    radixSort(nums);

    for(int &num:nums) cout << num << " ";
    cout << endl;
    return 0;
}