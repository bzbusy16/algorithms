#include<iostream>
#include<vector>
using namespace std;

// 第一个大于tar的位置
int binSearchLarger_upper(vector<int> &nums, int tar, int l, int r){
    if(l>=r) return l;  // 大于返回l
    int mid=l+(r-l)/2;  // 大于向下取整
    if(nums[mid]>tar) return binSearchLarger_upper(nums, tar, l, mid);  // nums[mid]>tar 符号对应
    else return binSearchLarger_upper(nums, tar, mid+1, r); // 总是else差1
}
// 第一个大于等于tar的位置
int binSearchLarger_lower(vector<int> &nums, int tar, int l, int r){
    if(l>=r) return l;
    int mid=l+(r-l)/2;
    if(nums[mid]>=tar) return binSearchLarger_lower(nums, tar, l, mid);
    else return binSearchLarger_lower(nums, tar, mid+1, r);
}
// 第一个小于tar的位置
int binSearchSmaller_upper(vector<int> &nums, int tar, int l, int r){
    if(l>=r) return r;      // 小于返回r
    int mid=l+(r-l)/2+1;    // 小于向上取整
    if(nums[mid]<tar) return binSearchSmaller_upper(nums, tar, mid, r);
    else return binSearchSmaller_upper(nums, tar, l, mid-1);
}
// 第一个小于等于tar的位置
int binSearchSmaller_lower(vector<int> &nums, int tar, int l, int r){
    if(l>=r) return r;
    int mid=l+(r-l)/2+1;
    if(nums[mid]<=tar) return binSearchSmaller_upper(nums, tar, mid, r);
    else return binSearchSmaller_lower(nums, tar, l, mid-1);
}

int main(){
    vector<int> nums={0, 2, 4, 6, 8, 10};
    cout << binSearchLarger_upper(nums, 6, 0, nums.size()-1) << endl;
    cout << binSearchLarger_lower(nums, 6, 0, nums.size()-1) << endl;
    cout << binSearchSmaller_upper(nums, 4, 0, nums.size()-1) << endl;
    cout << binSearchSmaller_lower(nums, 4, 0, nums.size()-1) << endl;
    return 0;
}