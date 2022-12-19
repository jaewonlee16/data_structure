#ifndef __FHEAP_H_
#define __FHEAP_H_

#include <iostream>
#include <initializer_list>
#include <optional>
#include <vector>
#include <cmath>
#include <memory>
#include <queue>

template <typename T>
class PriorityQueue {
    public:
        virtual void insert(const T& item) = 0;
        virtual std::optional<T> extract_min() = 0;
        virtual bool is_empty() const = 0;
};

template <typename T>
class FibonacciNode {
    public:
        // Constructors
        FibonacciNode();
        FibonacciNode(const T& item)
            :key(item), degree(0), marked(false), child(nullptr), right(nullptr) {}

        // Destructor
		// You can implement your custom destructor.
        ~FibonacciNode() = default;

        T key;
        size_t degree;
		bool marked;

		std::shared_ptr<FibonacciNode<T>> right;
		std::shared_ptr<FibonacciNode<T>> child;
        // NOTE: To prevent circular reference, left/parent pointer should be set to weak_ptr.
        std::weak_ptr<FibonacciNode<T>> left;
        std::weak_ptr<FibonacciNode<T>> parent;
};

template <typename T>
class FibonacciHeap : public PriorityQueue<T> {
    public:
        // Constructors
        FibonacciHeap()
            : min_node(nullptr), size_(0) {}
        FibonacciHeap(const T& item)
            : min_node(nullptr), size_(0) { insert(item); }

        // Disable copy constructor.
        FibonacciHeap(const FibonacciHeap<T> &);

        // Destructor
        ~FibonacciHeap();

        void insert(const T& item) override;
		void insert(std::shared_ptr<FibonacciNode<T>>& node);

        // Return raw pointer of the min_node.
        FibonacciNode<T>* get_min_node() { return min_node.get(); }

        std::optional<T> get_min() const;

        std::optional<T> extract_min() override;

		void decrease_key(std::shared_ptr<FibonacciNode<T>>& x, T new_key);

		void remove(std::shared_ptr<FibonacciNode<T>>& node);

        bool is_empty() const override { return !size_; }

        size_t size() const { return size_; }
		
    private:

        std::shared_ptr<FibonacciNode<T>> min_node;
        size_t size_;

        void consolidate();
        void merge(std::shared_ptr<FibonacciNode<T>>& x, std::shared_ptr<FibonacciNode<T>>& y);
		void cut(std::shared_ptr<FibonacciNode<T>>& x);
		void recursive_cut(std::shared_ptr<FibonacciNode<T>>& x);

};

template <typename T>
FibonacciHeap<T>::~FibonacciHeap() {
	// TODO
	// NOTE: Be aware of memory leak or memory error.
}

template <typename T>
std::optional<T> FibonacciHeap<T>::get_min() const {
	if(!min_node) 
		return std::nullopt;
	else
		return min_node->key;
}

template <typename T>
void FibonacciHeap<T>::insert(const T& item) {
	std::shared_ptr<FibonacciNode<T>> node = std::make_shared<FibonacciNode<T>>(item);
	insert(node);
}

template <typename T>
void FibonacciHeap<T>::insert(std::shared_ptr<FibonacciNode<T>>& node) {
	// TODO
    node->left = node;
    node->right = node;
    if (get_min_node() == nullptr)
        min_node = node;
    else{
        std::shared_ptr<FibonacciNode<T>> min_node_left = (min_node->left).lock();
        min_node_left->right = node;
        node->right = min_node;
        node->left = min_node->left;
        min_node->left = node;
        if (node->key < min_node->key)
            min_node = node;

    }
    size_ = size_ + 1;
}

template <typename T>
std::optional<T> FibonacciHeap<T>::extract_min() {
	// TODO
    if (get_min_node() != nullptr){
        T deletedValue = min_node->key;
        std::shared_ptr<FibonacciNode<T>> temp = min_node;
        std::shared_ptr<FibonacciNode<T>> rchild;
        rchild = temp;
        std::shared_ptr<FibonacciNode<T>> x = nullptr;
        if (temp->child != nullptr){
            x = temp->child;
            do{
                rchild = x->right;
                std::shared_ptr<FibonacciNode<T>> min_node_left = (min_node->left).lock();
                min_node_left->right = x;
                x->right = min_node;
                x->left = min_node->left;
                min_node->left = x;
                if (x->key < min_node->key)
                    min_node = x;
                x->parent = std::weak_ptr<FibonacciNode<T>>();
                x = rchild;
            } while (rchild != temp->child);
        }
        std::shared_ptr<FibonacciNode<T>> temp_left = (temp->left).lock();
        temp_left->right = temp->right;
        temp->right->left = temp->left;
        min_node = temp->right;
        if (temp == temp->right && temp->child == nullptr)
            min_node = nullptr;
        else{
            min_node = temp->right;
            consolidate();
        }
        size_ = size_ - 1;
        return deletedValue;
    }
	return std::nullopt;
}

template <typename T>
void FibonacciHeap<T>::decrease_key(std::shared_ptr<FibonacciNode<T>>& x, T new_key) {
	// TODO
    return;
}

template <typename T>
void FibonacciHeap<T>::remove(std::shared_ptr<FibonacciNode<T>>& x) {
	// TODO
	return;
}

template <typename T>
void FibonacciHeap<T>::consolidate() {
	float phi = (1 + sqrt(5)) / 2.0;
	int len = int(log(size_) / log(phi)) + 10;
	// TODO

	std::vector<std::shared_ptr<FibonacciNode<T>>> A(len, nullptr);
    return;
}

template <typename T>
void FibonacciHeap<T>::merge(std::shared_ptr<FibonacciNode<T>>& x, std::shared_ptr<FibonacciNode<T>>& y) {
	// TODO
    return;
}

template <typename T>
void FibonacciHeap<T>::cut(std::shared_ptr<FibonacciNode<T>>& x) {
	// TODO
    return;
}

template <typename T>
void FibonacciHeap<T>::recursive_cut(std::shared_ptr<FibonacciNode<T>>& x) {
	// TODO
    return;
}

#endif // __FHEAP_H_
