#include <iostream>
#include <algorithm>
#include <optional>
#include <unistd.h>

template <typename T, typename U>
class AVLNode{
    
    public :
        T key;
        U value;
        AVLNode<T,U> * left;
        AVLNode<T,U> * right;
        int height;

        AVLNode<T,U>(const T& k, const U& v)
        {
            key = k;
            value = v;
            left = nullptr;
            right = nullptr;
            height = 1;
        }        
        
};

template <typename T, typename U>
class AVLTree {
    public : 
        AVLNode<T,U> * root = nullptr;
        ~AVLTree() {
            removeall(root);
        }

        void insert(const T& key, const U& value);
        U search(const T& key);
        bool remove(const T& key);

        //for checking
        void preorder(AVLNode<T,U>*& node){
            if(!node) return;

            std::cout<<node->key<<": "<<node->value<<std::endl;
            preorder(node->left);
            preorder(node->right);
        }
        void inorder(AVLNode<T,U>*& node){
            if(!node) return;

            inorder(node->left);
            std::cout<<node->key<<": "<<node->value<<std::endl;
            inorder(node->right);
        }

    private :
        int getHeight(AVLNode<T,U>*& node);
        int getBalance(AVLNode<T,U>*& node);
        AVLNode<T,U>* rotate_left(AVLNode<T,U>*& node);
        AVLNode<T,U>* rotate_right(AVLNode<T,U>*& node);

        AVLNode<T,U>* insert(AVLNode<T,U>*& node, const T& key, const U& value);
        U search(AVLNode<T,U>*& node, const T& key);
        AVLNode<T,U>* remove(AVLNode<T,U>*& node, const T& key);
        void removeall(AVLNode<T,U>*& node);
        void makeBalance(AVLNode<T,U>*& node, const T& key);
        AVLNode<T,U>* normalBSTRemove(AVLNode<T,U>*& deleteNode);

};

template <typename T, typename U>
int AVLTree<T,U>::getHeight(AVLNode<T,U>*& node){
    if(!node) return 0;
    std::cout << "key: " << node->key << "    height: " << node->height << std::endl;
    return node->height;
}

template <typename T, typename U>
int AVLTree<T,U>::getBalance(AVLNode<T,U>*& node){
    if(!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

template<typename T, typename U>
void AVLTree<T,U>::insert(const T& key, const U& value) {
    root = insert(root, key, value);
}

template<typename T, typename U>
U AVLTree<T,U>::search(const T& key) {
    return search(root, key);
}

template<typename T, typename U>
bool AVLTree<T,U>::remove(const T& key) {
    if(!search(root,key).length()) return false;
    root = remove(root, key);
    return true;
}


template<typename T, typename U>
int maxHeight(const AVLNode<T,U>* node1, const AVLNode<T,U>* node2){
    int height1, height2;
    if (node1 == nullptr)
        height1 = 0;
    else
        height1 = node1->height;

    if (node2 == nullptr)
        height2 = 0;
    else
        height2 = node2->height;


    if (height1 > height2)
        return height1;
    else
        return height2;
}


template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::rotate_left(AVLNode<T,U>*& node){
    //TODO    
//    std::cout << "started left rotate key: " << node->key << std::endl;
    AVLNode<T, U>* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    // change heights
    node->height = maxHeight(node->left, node->right) + 1;
    tmp->height = maxHeight(tmp->left, tmp->right) + 1;
    // std::cout << "finished left rotate key: " << node->key << std::endl;
    return tmp;

}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::rotate_right(AVLNode<T,U>*& node){
    //TODO
    
//    std::cout << "started right rotate key: " << node->key << std::endl;
    AVLNode<T, U>* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    // change heights
    node->height = maxHeight(node->left, node->right) + 1;
    tmp->height = maxHeight(tmp->left, tmp->right) + 1;
    // std::cout << "finished right rotate key: " << node->key << std::endl;
    return tmp;

}


template<typename T, typename U>
void AVLTree<T, U>::makeBalance(AVLNode<T,U>*& node, const T& key){
    
    int balanceDifference = getBalance(node);
    //right-left
    std::cout << "balanceDifference:  " << balanceDifference << std::endl;
    if (balanceDifference < -1 && key < node->right->key){
//        std::cout  << "case: (right, left)" << std::endl;
        node->right = rotate_right(node->right);
        node = rotate_left(node);
    }
    //right-right
    else if (balanceDifference < -1 && key > node->right->key){
//        std::cout  << "case: (right, right)" << std::endl;
        node = rotate_left(node);
    }
    //left-right
    else if (balanceDifference > 1 && key > node->left->key){
 //       std::cout  << "case: (left, right)" << std::endl;
        node->left = rotate_left(node->left);
        node = rotate_right(node);
    }
    //left-left
    else if (balanceDifference > 1 && key < node->left->key){
//        std::cout  << "case: (left, left)" << std::endl;
        node = rotate_right(node);
    }
    // std::cout << "finished Balancing" << std::endl;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::insert(AVLNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    if (node == nullptr){
        AVLNode<T,U>* newNode = new AVLNode<T, U>(key, value);
        node = newNode;
//        std::cout << "new Node generated: " << node->key << std::endl;
        return node;
        
    }
    else if(key < node->key){
        node->left = insert(node->left, key, value);
    }
    else{
        node->right = insert(node->right, key, value);
    }

    node->height = maxHeight(node->left, node->right) + 1;
    // std::cout << "finished changing height after new Node generated" << std::endl;
    makeBalance(node, key);
    
    return node;
}

template<typename T, typename U>
U AVLTree<T,U>::search(AVLNode<T,U>*& node, const T& key) {
    //TODO
    //return NULL if there are no such key, return value if there is
    if (node == nullptr)
        return "";
    else if (node->key == key)
        return node->value;
    else if(key > node->key ){
        return search(node->right, key);
    }else if (key < node->key)
        return search(node->left, key);
    std::cout << "error at searching" << std::endl;
}


template<typename T, typename U>
AVLNode<T, U>* getNextBiggerNodeParent(AVLNode<T, U>* node){
    AVLNode<T, U>* rightNode = node->right;
    AVLNode<T, U>* prightNode = node;
    while (rightNode->left != nullptr){
        prightNode = rightNode;
        rightNode = rightNode->left;
    }
    return prightNode;
        
}

template<typename T, typename U>
AVLNode<T, U>* getNextBiggerNode(AVLNode<T, U>* node){
    AVLNode<T, U>* rightNode = node->right;
    while (rightNode->left != nullptr){
        rightNode = rightNode->left;
    }
    return rightNode;
        
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T, U>::normalBSTRemove(AVLNode<T,U>*& deleteNode){
    AVLNode<T, U>* tmpNode = deleteNode;
    
    if (deleteNode->left == nullptr){
        deleteNode = deleteNode->right; 
    } 
    else if (deleteNode->right == nullptr){
        deleteNode = deleteNode->left;
    }
    else{
        //min node of right child
        // The node that is next to deleteNode
        AVLNode<T, U>* nextBiggerNodeParent = getNextBiggerNodeParent(deleteNode);
        AVLNode<T, U>* nextBiggerNode = getNextBiggerNode(deleteNode);

        deleteNode->key = nextBiggerNode->key;
        deleteNode->value = nextBiggerNode->value;

        if (deleteNode->right == nextBiggerNode){
            deleteNode->right = nextBiggerNode->right;
        }
        else{
            nextBiggerNodeParent->left = nextBiggerNode->right;
        }
        tmpNode = nextBiggerNode;
    }
    delete tmpNode;
    return deleteNode;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::remove(AVLNode<T,U>*& node, const T& key) {
    //TODO
    if (node->key == key){
        normalBSTRemove(node);
    }
    else if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);

    if (node != nullptr){
        node->height = maxHeight(node->left, node->right) + 1;
        makeBalance(node, key);
    }
    return node;
}

template<typename T, typename U>
void AVLTree<T,U>::removeall(AVLNode<T,U>*& node) {
    //TODO
    //for destructor
    if (node){
        removeall(node->left);
        removeall(node->right);
        delete node;
    }
}
