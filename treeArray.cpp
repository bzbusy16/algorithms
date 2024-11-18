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

int lowbit(int x){
    // 实际上是在求x二进制最低位的1对应的数
    // 例如 6 110 对应 2 10
    return x&(-1*x);
}

void updateNode(int *tree, int pos, int len, int k){    // 更新节点值(+k), len是数组长度
    for(int i=pos;i<=len;i+=lowbit(i)){
        tree[i]+=k;
    }
}

int queryPresum(int *tree, int pos){    // 查询从pos开始的前缀和[..., pos]
    int sum=0;
    for(int i=pos;i>0;i-=lowbit(i)){    // 注意必须默认tree下标从1开始, 否则将死循环
        sum+=tree[i];
    }
    return sum;
}

int queryInterval(int *tree, int left, int right){  // 查询区间和(left, right]
    int pre_l=queryPresum(tree, left);
    int pre_r=queryPresum(tree, right);
    return pre_r-pre_l;
}

int main(){
    vector<int> nums={3, 9, 0, 1, 2, -5, 4, 2, -6};
    int *tree=new int[nums.size()+1]();
    for(int i=0;i<nums.size();++i){
        updateNode(tree, i+1, nums.size(), nums[i]);
    }

    for(int i=1;i<=nums.size();++i){
        cout << queryPresum(tree, i) << " ";
    }
    cout << endl;

    cout << queryInterval(tree, 1, 5) << endl;
    cout << queryInterval(tree, 6, 9) << endl;
    return 0;
}