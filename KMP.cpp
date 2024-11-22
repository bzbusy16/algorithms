#include<iostream>
#include<vector>
#include<string>
using namespace std;

// prefix()前缀函数, 计算pi数组: pi[i]是子串s[0...i]的最大(真)前后缀相同长度
vector<int> prefix1(string &s){
    int len=s.size();
    vector<int> pi(len);
    for(int i=1;i<len;i++){
        // 遍历一个长度j
        for(int j=i;j>=0;j--){
            if(s.substr(0, j)==s.substr(i-j+1, j)){
                // 找到前后缀相同
                pi[i]=j;
                break;
            }
        }
    }
    return pi;
}

// 第一次优化
vector<int> prefix2(string &s) {
    int len=s.size();
    vector<int> pi(len);
    for(int i=1;i<len;i++){
        // 注意到pi[i]最多比pi[i-1]多1
        // 将j改为从pi[i-1]+1开始遍历
        for(int j=pi[i-1]+1;j>=0;j--){
            if(s.substr(0, j)==s.substr(i-j+1, j)) {
                pi[i]=j;
                break;
            }
        }
    }
    return pi;
}

// 第二次优化
vector<int> prefix3(string &s){
    int len=s.size();
    vector<int> pi(len);
    for(int i=1;i<len;++i){
        // 注意到s[pi[i-1]]就是s[i-1]对应的最大前缀的末尾(后一个位置)
        // 所以可以根据新字符s[i]和s[pi[i-1]]是否相同来判断j的取值
        // 记j=pi[i-1]
        // 若s[i]==s[j], 则pi[i]=j+1=pi[i-1]+1
        // 若s[i]!=s[j], 则应递归判断s[i]和s[pi[j-1]]是否相同...直到s[i]==s[j]或j(长度)为0
        int j=pi[i-1];
        while(j>0 && s[j]!=s[i]) j=pi[j-1];
        if(s[j]==s[i]) ++j;
        pi[i]=j;
    }
    return pi;
}

vector<int> KMP(string &text, string &pattern){
    // 通过前缀函数实现KMP
    int len1=text.size(), len2=pattern.size();
    string str=pattern+"#"+text;    // 非法字符'#'作分隔
    vector<int> pi=prefix3(str);
    vector<int> pos;
    for(int i=len2+1;i<=len1+len2;++i){
        // pi[i]==len2说明pattern完整地出现在str的i-len+1处
        // 但返回结果应该是pattern在text中的位置，所以返回i-len+1-len-1=i-len*2
        if(pi[i]==len2) pos.emplace_back(i-len2*2);
    }
    return pos;
}

int main(){
    string text="aabcdgffdxzcabcddabcffabcd";
    string pattern="abcd";
    // 出现位置: 1 12 22
    vector<int> pos=KMP(text, pattern);
    for(int &p:pos) cout << p << " ";
    cout << endl;
    return 0;
}