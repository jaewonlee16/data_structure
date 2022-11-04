#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include "stack.hpp"

using namespace std;

int main() {

    //You can check if your code works well.

    cout<<__cplusplus<<endl;

    Stack<int> s;

    cout<<boolalpha;
    cout<<s.isEmpty()<<endl;
    cout<<s.isFull()<<endl;
    
    s.push(10);
    cout<<s.isEmpty()<<endl;
    cout<<s.isFull()<<endl;
    cout<<s.pop()<<endl;

    pair<char,char> p = make_pair('(',')');
    vector<pair<char,char>> v;
    v.push_back(p);

    string a = "(3))";
    cout<<checkParentheses(a, v)<<endl;

    return 0;

}