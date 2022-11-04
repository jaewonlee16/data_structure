#include <iostream>

template <typename T>
struct Item{
    T value;
    int priority;
};

template <typename T>
class Queue{
    private:
        int front;
        int rear;
        bool empty;
        int size;
        Item<T> *array;

    public:
        Queue<T>(int _size = 16)
        {
            front = 0;
            rear = _size - 1;
            empty = true;
            size = _size;
            array = new Item<T>[_size];
        }
        ~Queue(){
            delete[] array;
        }

        void enqueue(const T& value, int priority);
        int top();
        T dequeue();        
        bool isFull();
};

template <typename T>
void Queue<T>::enqueue(const T& value, int priority){
    //TODO
    return;
}

template <typename T>
int Queue<T>::top(){
    //TODO
    //returning the array index of the highest priority item
    return NULL;
}

template <typename T>
T Queue<T>::dequeue(){
    //TODO
    return NULL;
}

template <typename T>
bool Queue<T>::isFull(){
    //TODO
    return true;
}