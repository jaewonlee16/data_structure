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
    q.enqueue(5,3);
    q.enqueue(9,9);
    q.enqueue(7,4);
    q.enqueue(4,3);
    q.enqueue(3,6);
    q.enqueue(9,8);
    q.enqueue(1,9);
    q.enqueue(4,4);
    q.enqueue(3,2);
    q.enqueue(6,4);
    q.enqueue(6,6);
    q.enqueue(8,5);
    q.enqueue(7,7);
    q.enqueue(5,6);
    cout<<q.isFull()<<endl;
    q.enqueue(3,1);
    cout<<q.isFull()<<endl; 
    q.enqueue(4,8);


    cout<<q.isFull()<<endl;
    cout<<q.top()<<endl;

    cout << "-----------------------" << endl;
    for (int i = 0; i < 18; i++){
        cout << "dequeued number: " << q.dequeue() << endl;
        cout<<q.top()<<endl;
    }
    

    return 0;

}