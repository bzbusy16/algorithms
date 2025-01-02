#include<iostream>
#include<vector>
using namespace std;

/*
树状数组
适用于涉及前缀和、区间和的问题
能以O(logN)的时间复杂度解决单点修改+区间查询的问题
也可以用于解决区间修改+区间/单点查询问题, 但实现起来较麻烦, 不如直接用线段树

可以看做线段树的简化版
*/

class TreeArray{
    vector<int> tree;   // 树，下标从1开始，维护数组的前缀和
    vector<int> nums;   // 数组，下标从0开始

public:
    int lowbit(int x){
        // 实际上是在求x二进制最低位的1对应的数
        // 例如 6 110 对应 2 10
        return x&(-1*x);
    }

    // 向外提供的接口都是接收数组下标(从0开始)
    void updateNode(int idx, int k){    // 更新节点值(+k)
        for(int i=idx+1;i<=nums.size();i+=lowbit(i)){   // 更新前缀和
            tree[i]+=k;
        }
        nums[idx]+=k;   // 更新数组元素
    }

    int preSum(int idx){    // 获取前缀和 [0 ... idx]
        int sum=0;
        for(int i=idx+1;i>0;i-=lowbit(i)){    // 注意必须默认tree下标从1开始, 否则将死循环
            sum+=tree[i];
        }
        return sum;
    }

    int getSum(int left, int right){  // 获取区间和 [left, right]
        int lsum=preSum(left-1);
        int rsum=preSum(right);
        return rsum-lsum;
    }

    TreeArray(vector<int> &nums_): nums(nums_), tree(nums_.size()+1, 0){
        for(int i=0;i<nums.size();++i) updateNode(i, nums[i]);
    }
};

int main(){
    vector<int> nums={7, 2, 7, 2, 0};
    TreeArray tree_array(nums);
    tree_array.updateNode(4, 6); // nums[4]+=6;
    tree_array.updateNode(0, -5); // nums[0]+=-5
    tree_array.updateNode(0, 7); // nums[0]+=7
    cout << tree_array.getSum(4, 4) << endl;
    tree_array.updateNode(3, 6); // nums[3]+=6
    cout << tree_array.getSum(0, 4) << endl;
    tree_array.updateNode(4, -5); // nums[4]+=-5
    cout << tree_array.getSum(0, 3) << endl;
    cout << tree_array.getSum(0, 4) << endl;

    return 0;
}