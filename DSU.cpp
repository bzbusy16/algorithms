/*
Disjoint Set Union
并查集
*/
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

unordered_map<int, int> pre;

void init(vector<int> &list){    // 初始化：将每个节点的父节点设置为自己 
    for(int &x:list) pre[x]=x;
}

int find1(int x){   // 查找x所在集合（的根节点）
    while(pre[x]!=x) x=pre[x];
    return x;
}

int find2(int x){   // 路径压缩，递归实现
    if(pre[x]==x) return x;

    pre[x]=find2(pre[x]);   // 将查找路径上的所有节点都改到根节点下
    return pre[x];
}

int join(int x, int y){ // 合并x y所在集合
    int prex=find2(x), prey=find2(y);
    if(prex!=prey) pre[prex]=prey;  // 将x根节点放到y根节点下
}

int main(){
    
}