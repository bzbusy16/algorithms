#include<iostream>
#include<vector>
using namespace std;

int *tree, *lazy;   // lazy懒惰标记
void constructTree(vector<int> &nums, int idx, int l, int r){
    // 在区间[l, r]上建树, [l, r]是节点对应区间
    // idx当前节点编号

    if(l==r){   // 叶子节点
        tree[idx]=nums[l];
        return;
    }

    int mid=l+(r-l)/2;
    constructTree(nums, idx*2, l, mid);
    constructTree(nums, idx*2+1, mid+1, r);
    tree[idx]=tree[idx*2]+tree[idx*2+1];
}

void update(int idx, int l, int r, int s, int t, int k){
    // 区间[s, t]内的所有元素+d, [s, t]可以越界, [l, r]不可越界

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

    if(s<=mid) update(idx*2, l, mid, s, t, k);      // 注意mid属于左子树, s=mid时[s, s] [s+1, t]
    if(t>mid) update(idx*2+1, mid+1, r, s, t, k);
    tree[idx]=tree[idx*2]+tree[idx*2+1];            // 修改完子树后再修改当前节点
}

int query(int idx, int l, int r, int s, int t){ // 写法与update相同但不包含lazy相关操作
    if(l>=s && r<=t) return tree[idx];

    int mid=l+(r-l)/2;
    int lsum=0, rsum=0;
    if(s<=mid) lsum=query(idx*2, l, mid, s, t);
    if(t>mid) rsum=query(idx*2+1, mid+1, r, s, t);
    return lsum+rsum;
}

int main(){
    vector<int> nums={3, 9, 0, 1, 2, -5, 4, 2, -6};
    tree=new int[4*nums.size()+1]();
    lazy=new int[4*nums.size()+1]();
    constructTree(nums, 1, 0, nums.size()-1);

    cout << query(1, 0, nums.size()-1, 0, nums.size()-1) << endl;
    cout << query(1, 0, nums.size()-1, 0, 4) << endl;
    cout << query(1, 0, nums.size()-1, 5, 8) << endl;
    cout << query(1, 0, nums.size()-1, 2, 4) << endl;

    update(1, 0, nums.size()-1, 2, 6, 5);
    cout << query(1, 0, nums.size()-1, 0, 0) << endl;
    cout << query(1, 0, nums.size()-1, 2, 4) << endl;
    return 0;
}