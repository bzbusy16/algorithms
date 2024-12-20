#include<iostream>
#include<stack>
#include<queue>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int _val): val(_val), left(nullptr), right(nullptr) {}
};

void dfs_recursion(TreeNode *cur){  // 深度优先（递归实现）
    cout << cur->val << endl;   // 先序
    if(cur->left) dfs_recursion(cur->left);
    // cout << cur->val << endl;   // 中序
    if(cur->right) dfs_recursion(cur->right);
    // cout << cur->val << endl;   // 后序
}

void dfs_loop1(TreeNode *root){  // 深度优先（非递归实现）方法1
    stack<TreeNode *> stk;  // stk无法记录路径
    TreeNode *cur=root;

    while(cur || !stk.empty()){
        if(cur){    // 优先向左
            cout << cur->val << endl;   // 先序
            stk.push(cur);
            cur=cur->left;
        }
        else{       // cur空则不断回溯，直到找到右边能走的节点，进入右子树
            cur=stk.top();
            // cout << cur->val << endl;   // 中序
            stk.pop();
            cur=cur->right;
        }
    }
}

void dfs_loop2(TreeNode *root){  // 深度优先（非递归实现）方法2
    stack<TreeNode *> stk;
    stk.push(root);

    while(!stk.empty()){
        TreeNode *cur=stk.top();
        stk.pop();
        
        cout << cur->val << endl;   // 先序
        if(cur->right) stk.push(cur->right);    // 栈先进后出
        if(cur->left) stk.push(cur->left);
    }
}

void bfs(TreeNode *root){   // 广度优先
    queue<TreeNode *> que;
    if(root) que.push(root);
    
    while(!que.empty()){
        int n=que.size();
        while(n--){
            TreeNode *cur=que.front();
            que.pop();

            cout << cur->val << endl;

            if(cur->left) que.push(cur->left);
            if(cur->right) que.push(cur->right);
        }
        // 每一层的结尾
    }
}

int main(){

    return 0;
}