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

        RBNode<T, U>* normalBSTInsertPosition(RBNode<T, U>*& node ,const T& key);
        RBNode<T, U>* insertBalancing(RBNode<T, U>*& node);
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
bool isParentRed(RBNode<T,U>* node){
    return node->parent->color == RED;
}

template<typename T, typename U>
bool isLeftChild(RBNode<T,U>* node){
    RBNode<T, U>* tmp = node;
    if (tmp->parent == nullptr)
        return false;
    return tmp->parent->left == tmp;       
}

template<typename T, typename U>
bool isRightChild(RBNode<T,U>* node){
    RBNode<T, U>* tmp = node;
    if (tmp->parent == nullptr)
        return false;
    return tmp->parent->right == tmp;       
}

template<typename T, typename U>
bool isRoot(const RBNode<T, U>* node){
    if (node == nullptr)
        return false;
    return node->parent == nullptr;
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
    } else if ( isLeftChild(node))
        tmp->parent->left = tmp;
    else if ( isRightChild(node))
        tmp->parent->right = tmp;        

    // third
    tmp->left = node;
    node->parent = tmp;

    return tmp;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::rotate_right(RBNode<T,U>*& node){
    //TODO
    RBNode<T, U>* tmp = node->left;

    //first
    node->left = tmp->right;
    if (node->left != nullptr)
        node->left->parent = node;        

    // second
    tmp->parent = node->parent;
    if (!tmp->parent){
        // when input node is root node
    } else if ( isLeftChild(node))
        tmp->parent->left = tmp;
    else if ( isRightChild(node))
        tmp->parent->right = tmp;        

    // third
    tmp->right = node;
    node->parent = tmp;

    return tmp;
}

template<typename T, typename U>
RBNode<T, U>* RBTree<T, U>::normalBSTInsertPosition(RBNode<T, U>*& node, const T& key){
    RBNode<T, U>* y = node;
    while (1){
        if (node == nullptr)
            break;
        y = node;
        if (key == node->key)
            return y;
        else if (key > node->key)
            node = node->right;
        else if (key < node->key)
            node = node->left;
    }
    return y;
}

template<typename T, typename U>
RBNode<T, U>* RBTree<T, U>::insertBalancing(RBNode<T, U>*& node){
    if (isRoot(node->parent))
        return node;
    else{
        while (!isRoot(node) && isParentRed(node)){
                        
            RBNode<T, U>* grandparent = node->parent->parent;
            RBNode<T, U>* uncle = isLeftChild(node->parent) ? grandparent->right : grandparent->left;
            int uncleColor = uncle ? uncle->color : BLACK;


            // case 3-1: if P id Red and U is Red
            if (isParentRed(node) && uncleColor == RED){
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = isRoot(grandparent) ? BLACK : RED;
                node = grandparent;
            }        
            else{
                // case 3-2-2
                bool isParentLeftChild = isLeftChild(node->parent);
                if (isParentLeftChild ? isRightChild(node) : isLeftChild(node)){
                    node = node->parent;
                    node = isParentLeftChild ? rotate_left(node) : rotate_right(node);
                }
                // case 3-2-1
                node->color = BLACK;
                grandparent->color = RED;
                node = isParentLeftChild ? rotate_right(grandparent) : rotate_left(grandparent);
                break;

            }
        }
        
    }
    if (node){
        while(node->parent != nullptr){
            node = node->parent;
        }
        node->color = BLACK;
    }
    return node;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::insert(RBNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    RBNode<T, U>* insertNode = node;
    RBNode<T, U>* y = normalBSTInsertPosition(insertNode, key);

    // case 0
    if (insertNode != nullptr){   // when key is already detected
        insertNode->value = value;
        return node;
    }

    // new node
    RBNode<T, U>* newNode = new RBNode<T, U>(key, value);
    newNode->color = RED;
    newNode->parent = y;

    // case 1
    if (isRoot(newNode)) { // when root 
        node = newNode;
        newNode->color = BLACK;
        return node;
    }

    if (newNode->key < newNode->parent->key)
        newNode->parent->left = newNode;
    else if (newNode->key > newNode->parent->key)
        newNode->parent->right = newNode;

    //case 2
    if (!isParentRed(newNode))
        return node;
    else
        node = insertBalancing(newNode); 

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
