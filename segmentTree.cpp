#include<iostream>
#include<vector>
using namespace std;

class SegTree{
    vector<int> nums;   // 下标从0开始
    vector<int> tree;   // 下标从1开始
    vector<int> lazy;  // lazy懒惰标记

public:
    SegTree(vector<int> &nums_): nums(nums_), tree(4*nums_.size()+1, 0), lazy(4*nums_.size()+1, 0) {
        constructTree(0, nums_.size()-1);
    }
    
    // 向外提供的接口都是接收数组下标(从0开始)
    void constructTree(int l, int r, int idx=1){
        // 在nums区间[l, r]上建树, [l, r]是节点对应区间
        // idx当前节点编号(从1开始)

        if(l==r){   // 叶子节点
            tree[idx]=nums[l];
            return;
        }

        int mid=l+(r-l)/2;
        constructTree(l, mid, idx*2);
        constructTree(mid+1, r, idx*2+1);
        tree[idx]=tree[idx*2]+tree[idx*2+1];
    }

    void update(int l, int r, int s, int t, int k, int idx=1){    // 从外部调用时, idx一律为1表示tree的起点
        // 区间[s, t]内的所有元素+k, [s, t]可以越界, [l, r]不可越界

        if(l>=s && r<=t){   // 当前区间[l, r]在查询区间[s, t]内部, 直接修改lazy和节点值并返回
            lazy[idx]+=k;
            tree[idx]+=(r-l+1)*k;
            return;
        }

        // [l, r]不在[s, t]内部, 需要对子节点进行修改
        int mid=l+(r-l)/2;
        if(lazy[idx]!=0){   // 先将当前节点的lazy标记下传到子节点
            lazy[idx*2]+=lazy[idx];
            tree[idx*2]+=(mid-l+1)*lazy[idx];

            lazy[idx*2+1]+=lazy[idx];
            tree[idx*2+1]+=(r-mid)*lazy[idx];

            lazy[idx]=0;
        }

        if(s<=mid) update(l, mid, s, t, k, idx*2);      // 注意mid属于左子树, s=mid时[s, s] [s+1, t]
        if(t>mid) update(mid+1, r, s, t, k, idx*2+1);
        tree[idx]=tree[idx*2]+tree[idx*2+1];            // 修改完子树后再修改当前节点
    }

    int query(int l, int r, int s, int t, int idx=1){ // 写法与update相同但不包含lazy相关操作
        if(l>=s && r<=t) return tree[idx];

        int mid=l+(r-l)/2;
        int lsum=0, rsum=0;
        if(s<=mid) lsum=query(l, mid, s, t, idx*2);
        if(t>mid) rsum=query(mid+1, r, s, t, idx*2+1);
        return lsum+rsum;
    }

};

int main(){
    vector<int> nums={3, 9, 0, 1, 2, -5, 4, 2, -6};
    SegTree segt(nums);

    cout << segt.query(0, nums.size()-1, 0, nums.size()-1) << endl;
    cout << segt.query(0, nums.size()-1, 0, 4) << endl;
    cout << segt.query(0, nums.size()-1, 5, 8) << endl;
    cout << segt.query(0, nums.size()-1, 2, 4) << endl;

    segt.update(0, nums.size()-1, 2, 6, 5);
    cout << segt.query(0, nums.size()-1, 0, 0) << endl;
    cout << segt.query(0, nums.size()-1, 2, 4) << endl;
    return 0;
}