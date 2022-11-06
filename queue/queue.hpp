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
    // newItem
    Item<T> newItem;
    newItem.priority = priority;
    newItem.value = value;
    
    
    if (empty){
    	array[front] = newItem;
    	rear = front;
    	empty = false;
    	
    	return;
	}
	
	if (isFull()){
		// double array size
		
		//copy
		Item<T> *newArray = new Item<T>[size * 2];
		for (int i = 0; i < size; i++){
			newArray[i] = array[(i + front) % size];
		}
		delete [] array;
		//paste
		array = newArray;
		front = 0;
		rear = size - 1;
		size *= 2;
		empty = false;
		
	}
	
	// enqueue
	array[++rear] = newItem;
	
    return;
}

template <typename T>
int Queue<T>::top(){
    //TODO
    //returning the array index of the highest priority item
    int index = front;
    int max_priority = -1;
    int max_priority_index = front;
    
    while (index != rear){
    	if (array[index].priority > max_priority){
    		max_priority = array[index].priority;
    		max_priority_index = index;
		}
		
		index = (index + 1) % size;
	}
	
	// when index == rear
	if (array[index].priority > max_priority){
    	max_priority = array[index].priority;
    	max_priority_index = index;
	}
		
	
    return max_priority_index;
}

template <typename T>
T Queue<T>::dequeue(){
    //TODO
    T value;
    if (front == rear){
    	value = array[front].value;
        rear--;
    	empty = true;
	}
    else{
        int index = top();
        value = array[index].value;
        while (index != rear){
            array[index] = array[index + 1];
            index = (index + 1) % size;
        }
        rear--;
    }
    return value;
}

template <typename T>
bool Queue<T>::isFull(){
    //TODO
    if (empty)
    	return false;
    else if ((rear + 1) % size == front)
    	return true;
    
    return false;
}
