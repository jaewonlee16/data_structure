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
    s.push(89);
    s.push(75);
    s.push(35);
    s.push(98);
    s.push(45);
    s.push(68);
    s.push(78);
    s.push(96);
    s.push(47);
    s.push(87);
    s.push(68);
    s.push(95);
    s.push(76);
    s.push(36);
    s.push(98);
    s.push(87);
    s.push(63);
    s.push(36);
    s.push(12);

    cout<<s.isEmpty()<<endl;
    cout<<s.isFull()<<endl;
    for (int i = 0; i < 18; i++){
        cout<<s.pop()<<endl;
    }
    

    pair<char,char> p = make_pair('(',')');
    pair<char,char> q = make_pair('{','}');
    vector<pair<char,char>> v;
    v.push_back(p);
    v.push_back(q);

    string a = "((3))";
    cout<<checkParentheses(a, v)<<endl;

    string b = "12+(12-(32.-(2.-(-32.)-2.12)+43.)*.9949+15232)*6314*.00013/55322-(((-131)*.23)-12.012)";
    
    cout << calculate(b) <<endl;

    return 0;

}