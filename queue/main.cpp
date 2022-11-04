#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include "queue.hpp"

using namespace std;

int main() {

    //You can check if your code works well.

    cout<<__cplusplus<<endl;

    Queue<int> q;

    cout<<boolalpha;
    cout<<q.isFull()<<endl;

    q.enqueue(1,2);
    q.enqueue(2,3);

    cout<<q.isFull()<<endl;
    cout<<q.top()<<endl;

    q.dequeue();
    cout<<q.top()<<endl;

    return 0;

}