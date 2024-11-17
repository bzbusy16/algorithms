#include<iostream>
#include<vector>
using namespace std;

int oneSort(vector<int> &nums, int l, int r){   // 一轮排序, 要求[l, r]都能访问
    // pivot中枢, 这里直接取区间最左边的数
    // 按理说应该在[l, r]范围内随机取, 但只要数据不是特地设计过效果是一样的
    int piv=nums[l];
    int ll=l, rr=r;
    while(ll<rr){
        while(rr>ll && nums[rr]>piv) --rr;          // 从右往左找小于等于, 取等的情况一定会交换一次(即使并到大于里)，所以快速排序不稳定
        if(nums[rr]<=piv) swap(nums[rr], nums[ll]); // 注意nums[ll]就是piv
        while(ll<rr && nums[ll]<=piv) ++ll;         // 从左往右找大于
        if(nums[ll]>piv) swap(nums[ll], nums[rr]);  // nums[rr]是piv
    }
    // 结束循环时ll一定等于rr
    return ll;
}

void quickSort(vector<int> &nums, int l, int r){    // 递归实现快速排序
    if(l>=r) return;

    int mid=oneSort(nums, l, r);
    quickSort(nums, l, mid-1);      // 对区间左边排序
    quickSort(nums, mid+1, r);      // 对区间右边排序
}

int main(){
    vector<int> nums={45, 2, 90, -1, -110, 222, -1};
    quickSort(nums, 0, nums.size()-1);
    for(int &num:nums) cout << num << " ";
    cout << endl;
    return 0;
}