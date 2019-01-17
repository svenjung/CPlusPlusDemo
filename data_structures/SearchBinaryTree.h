//
// Created by svenj on 2019/1/11.
// 二叉搜索树的C++实现
//

#ifndef SEARCH_BINARY_TREE_H
#define SEARCH_BINARY_TREE_H

#include <iostream>
#include <functional>   // For std::less
#include "exceptions.h" // For exceptions
#include "Queue.h"      // For Stack

using std::cout;
using std::endl;
using std::less;

// 待处理：需要对 T 定义输出操作符 operator<<
template<typename T>
struct TreeNode {
    T element;
    TreeNode *left;
    TreeNode *right;

    TreeNode(const T &t, TreeNode *ln, TreeNode *rn)
            : element{t}, left{ln}, right{rn} {
    }

    // 使用移动函数“掏空”右值t，之后不能再使用t
    TreeNode(T &&t, TreeNode *ln, TreeNode *rn)
            : element{std::move(t)}, left{ln}, right{rn} {
    }
};

template<typename T>
class SearchBinaryTree {
private:
    typedef TreeNode<T> Node;

    Node *root;

    Queue<const Node *> queue;

    void insert(const T &, Node *&);

    void insert(T &&t, Node *&);

    void remove(const T &, Node *&);

    bool contains(const T &, Node *) const;

    Node *findMin(const Node *) const;

    Node *findMax(const Node *) const;

    void clear(Node *&);

    Node *clone(Node *) const;

    // 二叉树的中序遍历
    void inOrderTraversal(const Node *) const;

    // 二叉树的层序遍历（非递归实现）
    void levelTraversal(const Node *) const;

    // 二叉树的层序遍历（递归实现）
    void levelTraversal(const Node *, const int &) const;

    int treeDepth(const Node *) const;

public:
    SearchBinaryTree();

    SearchBinaryTree(const SearchBinaryTree &);

    SearchBinaryTree(SearchBinaryTree &&) noexcept;

    ~SearchBinaryTree();

    void insert(const T &);

    void insert(T &&);

    void remove(const T &);

    bool contains(const T &) const;

    bool isEmpty() const;

    const T &findMin() const;

    const T &findMax() const;

    void clear();

    void inOrderTraversal() const;

    void levelTraversal() const;

    int treeDepth() const;

    void levelTraversal2() const;
};

// 默认构造函数
template<typename T>
SearchBinaryTree<T>::SearchBinaryTree() : root{nullptr} {
    cout << "SBT DEFAULT CONSTRUCTOR" << endl;
}

// 复制构造函数
template<typename T>
SearchBinaryTree<T>::SearchBinaryTree(const SearchBinaryTree &rhs) : root{nullptr} {
    root = clone(rhs.root);
}

// 移动构造函数
template<typename T>
SearchBinaryTree<T>::SearchBinaryTree(SearchBinaryTree &&rhs) noexcept : root{rhs.root} {
    rhs.root = nullptr;
}

template<typename T>
SearchBinaryTree<T>::~SearchBinaryTree() {
    clear(root);
}

// ******************PUBLIC OPERATIONS*********************
// void insert(x)        --> Insert x
// void remove(x)        --> Remove x
// bool contains(x)      --> Return true if x is present
// Comparable findMin()  --> Return smallest item
// Comparable findMax()  --> Return largest item
// boolean isEmpty()     --> Return true if empty; else false
// void clear()          --> Remove all items
// void printTree()      --> Print tree in sorted order

template<typename T>
void SearchBinaryTree<T>::insert(const T &t) {
    insert(t, root);
}

template<typename T>
void SearchBinaryTree<T>::insert(T &&t) {
    insert(t, root);
}

template<typename T>
void SearchBinaryTree<T>::remove(const T &t) {
    remove(t, root);
}

template<typename T>
bool SearchBinaryTree<T>::contains(const T &t) const {
    return contains(t, root);
}

template<typename T>
const T &SearchBinaryTree<T>::findMin() const {
    if (isEmpty()) {
        throw UnderflowException{};
    }
    return findMin(root)->element;
}

template<typename T>
const T &SearchBinaryTree<T>::findMax() const {
    if (isEmpty()) {
        throw UnderflowException{};
    }

    return findMax(root)->element;
}

template<typename T>
bool SearchBinaryTree<T>::isEmpty() const {
    return root == nullptr;
}

template<typename T>
void SearchBinaryTree<T>::clear() {
    clear(root);
}

template<typename T>
void SearchBinaryTree<T>::inOrderTraversal() const {
    inOrderTraversal(root);
}

template<typename T>
void SearchBinaryTree<T>::levelTraversal() const {
    levelTraversal(root);
}

template <typename T>
int SearchBinaryTree<T>::treeDepth() const {
    return treeDepth(root);
}

template <typename T>
void SearchBinaryTree<T>::levelTraversal2() const {
    int depth = treeDepth(root);
    levelTraversal(root, depth);
}

// ******************PRIVATE OPERATIONS*********************
template<typename T>
bool SearchBinaryTree<T>::contains(const T &t, SearchBinaryTree::Node *n) const {
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
TreeNode<T> *SearchBinaryTree<T>::findMin(const TreeNode<T> *n) const {
    if (n == nullptr) {
        return nullptr;
    } else if (n->left == nullptr) {
        return n;
    } else {
        return findMin(n->left);
    }
}

template<typename T>
TreeNode<T> *SearchBinaryTree<T>::clone(TreeNode<T> *t) const {
    if (t == nullptr)
        return nullptr;
    else {
        return new Node{t->element, clone(t->left), clone(t->right)};
    }
}

template<typename T>
TreeNode<T> *SearchBinaryTree<T>::findMax(const TreeNode<T> *n) const {
    if (n == nullptr) {
        return nullptr;
    } else if (n->right == nullptr) {
        return n;
    } else {
        return findMax(n->right);
    }
}

template<typename T>
void SearchBinaryTree<T>::clear(SearchBinaryTree::Node *&n) {
    if (n == nullptr) {
        return;
    } else {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

template<typename T>
void SearchBinaryTree<T>::insert(const T &t, SearchBinaryTree::Node *&n) {
    if (n == nullptr) {
        n = new Node{t, nullptr, nullptr};
    } else if (t < n->element) {
        insert(t, n->left);
    } else if (n->element < t) {
        insert(t, n->right);
    } else { ; // Duplicate; do nothing
    }
}

template<typename T>
void SearchBinaryTree<T>::insert(T &&t, SearchBinaryTree::Node *&n) {
    if (n == nullptr)
        n = new Node{std::move(t), nullptr, nullptr};
    else if (t < n->element)
        insert(std::move(t), n->left);
    else if (n->element < t)
        insert(std::move(t), n->right);
    else;  // Duplicate; do nothing
}

template<typename T>
void SearchBinaryTree<T>::remove(const T &t, SearchBinaryTree::Node *&n) {
    if (n == nullptr) {
        return;
    } else if (t < n->element) {
        remove(t, n->left);
    } else if (n->element < t) {
        remove(t, n->right);
    } else if (n->left != nullptr && n->right != nullptr) {
        // 先用右子树中最小值替换当前节点的值，然后删除右子树中的最小值所在节点
        n->element = findMax(n->right)->element;
        remove(n->element, n->right);
    } else {
        Node *old = n;
        n = n->left != nullptr ? n->left : n->right;
        delete old;
    }
}

template<typename T>
void SearchBinaryTree<T>::inOrderTraversal(const SearchBinaryTree::Node *n) const {
    if (n != nullptr) {
        inOrderTraversal(n->left);
        cout << n->element << endl;
        inOrderTraversal(n->right);
    }
}

template<typename T>
void SearchBinaryTree<T>::levelTraversal(const SearchBinaryTree::Node *n) const {
    if (n != nullptr) {
        queue.enqueue(n);

        while (!queue.empty()) {
            const Node *node = queue.dequeue();

            T element = node->element;
            cout << element << endl;

            if (node->left != nullptr) {
                queue.enqueue(node->left);
            }
            if (node->right != nullptr) {
                queue.enqueue(node->right);
            }
        }
    }
}

template <typename T>
int SearchBinaryTree<T>::treeDepth(const SearchBinaryTree::Node *n) const {
    if (n == nullptr) {
        return 0;
    }

    int leftDepth = treeDepth(n->left);
    int rightDepth = treeDepth(n->right);

    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

template <typename T>
void SearchBinaryTree<T>::levelTraversal(const SearchBinaryTree::Node *n, const int &depth) const {
    if (n == nullptr || depth == 0) {
        return;
    }

    cout << n->element << endl;

    if (depth == 1) {
        return;
    }

    levelTraversal(n->left, depth - 1);
    levelTraversal(n->right, depth - 1);
}

#endif //SEARCH_BINARY_TREE_H
