#include <iostream>
#include <algorithm>
#include <optional>
#include <unistd.h>

#define RED 1
#define BLACK 0

template <typename T, typename U>
class RBNode{
    
    public :
        T key;
        U value;
	RBNode<T,U> * parent;
        RBNode<T,U> * left;
        RBNode<T,U> * right;
        int color; // 1 -> red, 0 -> black

        RBNode<T,U>(const T& k, const U& v)
        {
            key = k;
            value = v;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }        
        
};

template <typename T, typename U>
class RBTree {
    public : 
        RBNode<T,U> * root = nullptr;
        ~RBTree() {
            removeall(root);
        }

        void insert(const T& key, const U& value);
        U search(const T& key);
        bool remove(const T& key);

        //for checking
        void preorder(RBNode<T,U>*& node){
            if(!node) return;

            std::cout<<node->key<<": "<<node->value<<std::endl;
            preorder(node->left);
            preorder(node->right);
        }
        void inorder(RBNode<T,U>*& node){
            if(!node) return;

            inorder(node->left);
            std::cout<<node->key<<": "<<node->value<<std::endl;
            inorder(node->right);
        }

    private :
        RBNode<T,U>* rotate_left(RBNode<T,U>*& node);
        RBNode<T,U>* rotate_right(RBNode<T,U>*& node);

        RBNode<T,U>* insert(RBNode<T,U>*& node, const T& key, const U& value);
        U search(RBNode<T,U>*& node, const T& key);
        RBNode<T,U>* remove(RBNode<T,U>*& node, const T& key);
        void removeall(RBNode<T,U>*& node);

        void normalBSTInsertPosition(RBNode<T, U>*& node ,const T& key);
};

template<typename T, typename U>
void RBTree<T,U>::insert(const T& key, const U& value) {
    root = insert(root, key, value);
}

template<typename T, typename U>
U RBTree<T,U>::search(const T& key) {
    return search(root, key);
}

template<typename T, typename U>
bool RBTree<T,U>::remove(const T& key) {
    if(!search(root,key).length()) return false;
    root = remove(root, key);
    return true;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::rotate_left(RBNode<T,U>*& node){
    //TODO    
    RBNode<T, U>* tmp = node->right;

    //first
    node->right = tmp->left;
    if (node->right != nullptr)
        node->right->parent = node;        

    // second
    tmp->parent = node->parent;
    if (!tmp->parent){
        // when input node is root node
    } else if (node->parent->left == tmp)
        tmp->parent->left = tmp;
    else if (node->parent->right == tmp)
        tmp->parent->right = tmp;        

    // third
    tmp->left = node;
    node->parent = tmp;

    return tmp;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::rotate_right(RBNode<T,U>*& node){
    //TODO
    AVLNode<T, U>* tmp = node->left;

    //first
    node->left = tmp->right;
    if (node->left != nullptr)
        node->left->parent = node;        

    // second
    tmp->parent = node->parent;
    if (!tmp->parent){
        // when input node is root node
    } else if (node->parent->left == tmp)
        tmp->parent->left = tmp;
    else if (node->parent->right == tmp)
        tmp->parent->right = tmp;        

    // third
    tmp->right = node;
    node->parent = tmp;

    return tmp;
}

template<typename T, typename U>
void RBTree<T, U>::normalBSTInsertPosition(RBNode<T, U>*& node, const T& key){
    while (1){
        if (node == nullptr)
            break;
        else if (key == node->key)
            return;
        else if (key > node->key)
            node = node->right;
        else if (key < node->key)
            node = node->left;
    }
}


template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::insert(RBNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    RBNode<T, U>* insertNode = node;
    normalBSTInsertPosition(insertNode);

    if (node != nullptr){   // when key is already detected
        node->value = value;
        return node;
    }
    else{
        // new node
        RBNode<T, U>* newNode = new RBNode<T, U>(key, value);
        newNode->color = RED;
        newNode->parent = insertNode // error ....  add parent to newNode and add left or right to parent of newNode
        insertBalancing(insertNode); // did't define the function yet.  MUST BE added
    }

    return node;
}

template<typename T, typename U>
U RBTree<T,U>::search(RBNode<T,U>*& node, const T& key) {
    //TODO
    //return NULL if there are no such key, return value if there is
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::remove(RBNode<T,U>*& node, const T& key) {

    //TODO

}

template<typename T, typename U>
void RBTree<T,U>::removeall(RBNode<T,U>*& node) {
    //TODO
    //for destructor
        
    
    
}
