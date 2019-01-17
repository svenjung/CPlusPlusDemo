//
// Created by svenj on 2019/1/15.
// 平衡二叉树
//

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include "exceptions.h" // For exceptions

// 定义左右子树的高度差最大为 1
#define ALLOWED_IMBALANCE 1

using std::move;
using std::cout;
using std::endl;
using std::max;

template<typename T>
struct AvlNode {
    T element;
    AvlNode *left;
    AvlNode *right;
    // 记录节点高度
    int height;

    AvlNode(const T &t, AvlNode *ln, AvlNode *rn, int h)
            : element(t), left{ln}, right{rn}, height(h) {
    }

    AvlNode(T &&t, AvlNode *ln, AvlNode *rn, int h)
            : element(move(t)), left{ln}, right{rn}, height(h) {
    }
};

template<typename T>
class AVLTree {
private:
    AvlNode<T> *root;

    void insert(const T &, AvlNode<T> *&);

    void insert(T &&, AvlNode<T> *&);

    void remove(T &, AvlNode<T> *&);

    bool contains(const T &, AvlNode<T> *) const;

    AvlNode<T> *&findMin(AvlNode<T> *&) const;

    AvlNode<T> *&findMax(AvlNode<T> *&) const;

    void balance(AvlNode<T> *&);

    void rotateWithLeftChild(AvlNode<T> *&);

    void rotateWithRightChild(AvlNode<T> *&);

    void doubleWithLeftChild(AvlNode<T> *&);

    void doubleWithRightChild(AvlNode<T> *&);

    int height(AvlNode<T> *&) const;

    AvlNode<T> *clone(const AvlNode<T> *) const;

    void print(const AvlNode<T> *) const;

    void clear(AvlNode<T> *&) const;
public:
    AVLTree();

    AVLTree(const AVLTree &);

    AVLTree(AVLTree &&) noexcept;

    ~AVLTree();

    void insert(const T &);

    void insert(T &&);

    void remove(const T &);

    void remove(T &&);

    T &findMin() const;

    T &findMax() const;

    bool contains(T &) const;

    void print() const;
};

template<typename T>
AVLTree<T>::AVLTree() : root{nullptr} {
}

template<typename T>
AVLTree<T>::AVLTree(const AVLTree &tree) : root{nullptr} {
    root = clone(tree.root);
}

template<typename T>
AVLTree<T>::AVLTree(AVLTree &&tree) noexcept : root{tree.root} {
    tree.root = nullptr;
}

template<typename T>
AVLTree<T>::~AVLTree() {
    clear(root);
}

template<typename T>
void AVLTree<T>::insert(const T &t) {
    insert(t, root);
}

template<typename T>
void AVLTree<T>::insert(T &&t) {
    insert(t, root);
}


template <typename T>
void AVLTree<T>::remove(const T &t) {
    remove(t, root);
}

template <typename T>
void AVLTree<T>::remove(T &&t) {
    remove(t, root);
}

template <typename T>
T &AVLTree<T>::findMin() const {
    if (root == nullptr) {
        throw UnderflowException{};
    }

    return findMin(root)->element;
}

template <typename T>
T &AVLTree<T>::findMax() const {
    if (root == nullptr) {
        throw UnderflowException{};
    }

    return findMax(root)->element;
}

template <typename T>
bool AVLTree<T>::contains(T &t) const {
    return contains(t, root);
}

template<typename T>
void AVLTree<T>::print() const {
    print(root);
}

// ********** private functions **********
template<typename T>
void AVLTree<T>::insert(const T &t, AvlNode<T> *&n) {
    if (n == nullptr) {
        n = new AvlNode<T>{t, nullptr, nullptr, 0};
    } else if (t < n->element) {
        insert(t, n->left);
    } else if (n->element < t) {
        insert(t, n->right);
    } else { ; // Duplicate; do nothing
    }

    balance(n);
}

template<typename T>
void AVLTree<T>::insert(T &&t, AvlNode<T> *&n) {
    if (n == nullptr) {
        n = new AvlNode<T>{move(t), nullptr, nullptr, 0};
    } else if (t < n->element) {
        insert(move(t), n->left);
    } else if (n->element < t) {
        insert(move(t), n->right);
    } else { ; // Duplicate; do nothing
    }

    balance(n);
}

template<typename T>
int AVLTree<T>::height(AvlNode<T> *&node) const {
    return node == nullptr ? -1 : node->height;
}

template<typename T>
void AVLTree<T>::balance(AvlNode<T> *&node) {
    if (node == nullptr) {
        return;
    }

    if (height(node->left) - height(node->right) > ALLOWED_IMBALANCE) {
        if (height(node->left->left) >= height(node->left->right)) {
            //左旋转
            rotateWithLeftChild(node);
        } else {
            //双旋转
            doubleWithLeftChild(node);
        }
    } else if (height(node->right) - height(node->left) > ALLOWED_IMBALANCE) {
        if (height(node->right->right) >= height(node->right->left)) {
            //右旋转
            rotateWithRightChild(node);
        } else {
            //双旋转
            doubleWithRightChild(node);
        }
    }

    node->height = max(height(node->left), height(node->right)) + 1;
}

template<typename T>
void AVLTree<T>::rotateWithLeftChild(AvlNode<T> *&node) {
    AvlNode<T> *k2 = node;
    AvlNode<T> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;

    k2 = k1;
    node = k2;
}

template<typename T>
void AVLTree<T>::rotateWithRightChild(AvlNode<T> *&node) {
    AvlNode<T> *k1 = node;
    AvlNode<T> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;

    k1 = k2;
    node = k1;
}

template<typename T>
void AVLTree<T>::doubleWithLeftChild(AvlNode<T> *&node) {
    AvlNode<T> *k3 = node;

    rotateWithLeftChild(k3->left);
    rotateWithRightChild(k3);

    node = k3;
}

template<typename T>
void AVLTree<T>::doubleWithRightChild(AvlNode<T> *&node) {
    AvlNode<T> *k1 = node;

    rotateWithRightChild(k1->right);
    rotateWithLeftChild(k1);

    node = k1;
}

template<typename T>
AvlNode<T> *AVLTree<T>::clone(const AvlNode<T> *n) const {
    if (n == nullptr) {
        return nullptr;
    } else {
        return new AvlNode<T>{n->height, clone(n->left), clone(n->right)};
    }
}

template<typename T>
void AVLTree<T>::print(const AvlNode<T> *node) const {
    if (node != nullptr) {
        print(node->left);

        cout << node->element << " height -> " << node->height << endl;

        print(node->right);
    }
}

template<typename T>
void AVLTree<T>::clear(AvlNode<T> *&node) const {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);

        delete node;
    }
}

template<typename T>
void AVLTree<T>::remove(T &t, AvlNode<T> *&node) {
    if (node == nullptr) {
        return;
    }

    if (t < node->element) {
        remove(t, node->left);
    } else if (t > node->element) {
        remove(t, node->right);
    } else if (node->left != nullptr && node->right != nullptr) {
        node->element = findMin(node->right)->element;
        remove(node->element, node->right);
    } else {
        AvlNode<T> *old = node;
        node = (node->left != nullptr) ? node->left : node->right;
        delete old;
    }

    balance(node);
}

template<typename T>
bool AVLTree<T>::contains(const T &t, AvlNode<T> *n) const {
    if (n == nullptr) {
        return false;
    } else if (t < n->element) {
        return contains(t, n->left);
    } else if (n->element < t) {
        return contains(t, n->right);
    } else {
        return true;
    }
}

template<typename T>
AvlNode<T> *&AVLTree<T>::findMin(AvlNode<T> *&node) const {
    if (node == nullptr) {
        return node;
    }

    if (node->left == nullptr) {
        return node;
    } else {
        return findMin(node->left);
    }
}

template<typename T>
AvlNode<T> *&AVLTree<T>::findMax(AvlNode<T> *&node) const {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->right == nullptr) {
        return node;
    } else {
        return findMax(node->left);
    }
}

#endif //AVL_TREE_H
