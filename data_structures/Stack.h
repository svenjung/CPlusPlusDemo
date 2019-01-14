//
// Created by svenj on 2019/1/13.
//

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <functional>
#include "exceptions.h"

using std::cout;
using std::endl;

template<typename T>
class Stack {
private:
    struct Node {
        T e;
        Node *next;

        Node(const T &t, Node *n)
                : e{t}, next{n} {
        }

        // 移动函数
        Node(T &&t, Node *n)
                : e{std::move(t)}, next{n} {
        }
    };

    int s_size;
    Node *top;

    Node *clone(Node *node) const {
        if (node == nullptr) {
            return nullptr;
        } else {
            return new Node{node->e, clone(node->next)};
        }
    }

    Node *remove(Node *node) {
        if (node == nullptr) {
            return nullptr;
        } else {
            Node *old = node;
            node = old->next;
            delete old;

            return node;
        }
    }

public:
    Stack() : s_size(0), top{nullptr} {
    }

    Stack(int size) : top{nullptr} {
        cout << "Can't create stack with size" << endl;
        throw IllegalArgumentException{};
    }

    // 复制构造函数
    Stack(const Stack &stack) {
        s_size = stack.s_size;
        // TODO define clone function
        top = stack.top;
    }

    // 移动构造函数
    Stack(Stack &&stack) noexcept :
            s_size(stack.s_size) {
        top = clone(stack.top);
    }

    ~Stack() {
        cout << "STACK DESTRUCTOR" << endl;
        while (top != nullptr) {
            top = remove(top);
            s_size--;
        }
    }

    int size() const {
        return size;
    }

    bool empty() const {
        return s_size == 0;
    }

    void push(const T &t) {
        Node *pNode = new Node{t, nullptr};
        if (top == nullptr) {
            top = pNode;
        } else {
            pNode->next = top;
            top = pNode;
        }
        s_size++;
    }

    void push(T &&t) {
        Node *pNode = new Node{std::move(t), nullptr};
        if (top == nullptr) {
            top = pNode;
        } else {
            pNode->next = top;
            top = pNode;
        }
        s_size++;
    }

    T &peek() const {
        if (s_size == 0) {
            throw UnderflowException{};
        } else {
            return top->e;
        }
    }

    T pop() {
        if (s_size == 0) {
            throw UnderflowException{};
        } else {
            s_size--;

            T t = top->e;
            Node *old = top;
            top = top->next;
            delete old;

            return t;
        }
    }
};

#endif //STACK_H
