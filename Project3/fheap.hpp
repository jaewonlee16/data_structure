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
        void FibonacciLink(std::shared_ptr<FibonacciNode<T>>& to_be_child, std::shared_ptr<FibonacciNode<T>>& to_be_parent);
};

template <typename T>
FibonacciHeap<T>::~FibonacciHeap() {
	// TODO
	// NOTE: Be aware of memory leak or memory error.
    while (size_ > 0){
        extract_min();
    }
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

        // min_node_left = nullptr;  // ????????????
    }
    size_ = size_ + 1;
}

template <typename T>
std::optional<T> FibonacciHeap<T>::extract_min() {
	// TODO
    if (get_min_node() != nullptr){
        T deletedValue = min_node->key;
        if (min_node->right == min_node && min_node->child == nullptr){
            min_node->right = nullptr;
            min_node = nullptr;
            size_ = size_ - 1;
            return deletedValue;
        }
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
                // min_node_left = nullptr;   // ??????????????????????????
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
        // temp_left = nullptr; // ?????????????????????
        return deletedValue;
    }
	return std::nullopt;
}

template <typename T>
void FibonacciHeap<T>::decrease_key(std::shared_ptr<FibonacciNode<T>>& x, T new_key) {
	// TODO
    if (min_node == nullptr)
        return;
    if (x == nullptr)
        return;
    if (new_key > x->key)
        return;
    
    x->key = new_key;
    std::shared_ptr<FibonacciNode<T>> parent_x = x->parent;
    if (parent_x != nullptr && x->key < parent_x->key){
        cut(x);
        recursive_cut(parent_x);
    }
    if (x->key < min_node->key)
        min_node = x;
}

template <typename T>
void FibonacciHeap<T>::remove(std::shared_ptr<FibonacciNode<T>>& x) {
	// TODO
	if (x == nullptr)
        return;
    decrease_key(x, -9999);
    extract_min(x);
}

template <typename T>
void FibonacciHeap<T>::consolidate() {
	float phi = (1 + sqrt(5)) / 2.0;
	int len = int(log(size_) / log(phi)) + 10;
	// TODO

    size_t degree_x;
	std::vector<std::shared_ptr<FibonacciNode<T>>> A(len, nullptr);
    std::shared_ptr<FibonacciNode<T>> x = min_node;
    std::shared_ptr<FibonacciNode<T>> same_degree_node;
    std::shared_ptr<FibonacciNode<T>> temp_for_swap;

    do{
        degree_x = x->degree;

        while (A[degree_x] != nullptr){
            same_degree_node = A[degree_x];
            if (x->key > same_degree_node->key){
                // swap
                temp_for_swap = x;
                x = same_degree_node;
                same_degree_node = temp_for_swap;
                temp_for_swap = nullptr;
            }
            if (same_degree_node == min_node)
                min_node = x;
            FibonacciLink(same_degree_node, x);
            if (x->right == x)
                min_node = x;
            A[degree_x] = nullptr;
            degree_x++;
        }
        A[degree_x] = x;
        x = x->right;
    } while (x != min_node);

    min_node = nullptr;
    for (int j = 0; j < len; j++){
        if (A[j] != nullptr){
            A[j]->left = A[j];
            A[j]->right = A[j];
            if (min_node != nullptr){
                std::shared_ptr<FibonacciNode<T>> min_node_left = (min_node->left).lock();
                min_node_left->right = A[j];
                A[j]->right = min_node;
                A[j]->left = min_node->left;
                min_node->left = A[j];
                if (A[j]->key < min_node->key)
                    min_node = A[j];
                // min_node_left = nullptr; // ??????????
            }
            else {
                min_node = A[j];
            }
            if (min_node == nullptr)
                min_node = A[j];
            else if (A[j]->key < min_node->key)
                min_node = A[j];
        }
    }
}

template <typename T>
void FibonacciHeap<T>::FibonacciLink(std::shared_ptr<FibonacciNode<T>>& to_be_child, 
                                        std::shared_ptr<FibonacciNode<T>>& to_be_parent) {
    if (to_be_child == to_be_parent)
        return;
    
    std::shared_ptr<FibonacciNode<T>> to_be_child_left = (to_be_child->left).lock();
    to_be_child_left->right = to_be_child->right;
    to_be_child->right->left = to_be_child->left;
    if (to_be_parent->right == to_be_parent)
        min_node = to_be_parent;
    to_be_child->left = to_be_child;
    to_be_child->right = to_be_child;
    to_be_child->parent = to_be_parent;
    if (to_be_parent->child == nullptr)
        to_be_parent->child = to_be_child;
    to_be_child->right = to_be_parent->child;
    to_be_child->left = to_be_parent->child->left;
    std::shared_ptr<FibonacciNode<T>> parent_child_left = (to_be_parent->child->left).lock();
    parent_child_left->right = to_be_child;
    to_be_parent->child->left = to_be_child;
    if (to_be_child->key < to_be_parent->child->key)
        to_be_parent->child = to_be_child;
    to_be_parent->degree++;
    // to_be_child_left = nullptr; // ???????????
    // parent_child_left = nullptr; // ????????
}

template <typename T>
void FibonacciHeap<T>::merge(std::shared_ptr<FibonacciNode<T>>& x, std::shared_ptr<FibonacciNode<T>>& y) {
	// TODO
    std::shared_ptr<FibonacciNode<T>> temp;
    if (x->key < y->key){
        // swap
        temp = x;
        x = y;
        y = temp;
    }
    
    x->parent = y;
    if (y->child == nullptr)
        y->child = x;
    x->right = y->child;
    x->left = y->child->left;
    std::shared_ptr<FibonacciNode<T>> y_child_left = (y->child->left).lock();
    y_child_left->right = x;
    y->child->left = x;
    if (x->key < y->child->key)
        y->child = x;
    
    y->degree++;
}

template <typename T>
void FibonacciHeap<T>::cut(std::shared_ptr<FibonacciNode<T>>& x) {
	// TODO
    std::shared_ptr<FibonacciNode<T>> parent_x = x->parent;
    if (x == x->right)
        parent_x->child = nullptr;
    
    std::shared_ptr<FibonacciNode<T>> left_x = (x->left).lock();
    left_x->right = x->right;
    x->right->left = x->left;
    if (x == parent_x->child)
        parent_x->child = x->right;
    parent_x->degree--;
    x->right = x;
    x->left = x;
    std::shared_ptr<FibonacciNode<T>> min_node_left = (min_node->left).lock();
    min_node_left->right = x;
    x->right = min_node;
    x->left = min_node->left;
    min_node->left = x;
    x->parent = nullptr;
    x->marked = false;
}

template <typename T>
void FibonacciHeap<T>::recursive_cut(std::shared_ptr<FibonacciNode<T>>& x) {
	// TODO
    std::shared_ptr<FibonacciNode<T>> p_x = x->parent;
    if (p_x != nullptr){
        if (x->marked == false)
             x->marked = true;
        else{
            cut(x);
            recursive_cut(p_x);
        }
    } 
    
}

#endif // __FHEAP_H_
