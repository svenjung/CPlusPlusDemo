//
// Created by svenj on 2019/1/13.
//

/*
 * void offer()     入队
 * void pull()      出队
 * int size()       队列长度
 * bool empty()     是否为空
 * T peek()         队头元素
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <functional>
#include <assert.h>
#include "exceptions.h"

using std::cout;
using std::endl;

template<typename T>
class Queue {
private:
    struct Node {
        T element;
        Node *next;

        Node(const T &t, Node *n)
                : element{t}, next{n} {
            cout << "Queue Node copy create" << endl;
        }

        // 移动函数
        Node(T &&t, Node *n)
                : element{std::move(t)}, next{n} {
            cout << "Queue Node move create" << endl;
        }
    };

    int q_size;
    Node *head;
    Node *tail;

    Node *clone(const Node *&node) const {
        if (node == nullptr)
            return nullptr;
        else {
            return new Node{node->element, clone(node->next)};
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
    Queue() : q_size(0), head{nullptr}, tail{nullptr} {
        cout << "Queue create" << endl;
    }

    Queue(const int &size) : q_size(size), head{nullptr}, tail{nullptr} {
    }

    Queue(const Queue &q) : q_size(q.q_size) {
        head = clone(q.head);
        Node *node = head;
        while (node != nullptr) {
            node = node->next;
        }
        tail = node;
    }

    Queue(Queue &&q) noexcept : q_size(q.q_size), head{q.head}, tail{q.tail} {
        q.head = nullptr;
        q.tail = nullptr;
    }

    ~Queue() {
        cout << "Queue destroy" << endl;
        while (head != nullptr) {
            head = remove(head);
            q_size--;
        }
    }

    void enqueue(const T &t) {
        Node *node = new Node{t, nullptr};
        if (empty()) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = tail->next;
        }
        q_size++;
    }

    void enqueue(T &&t) {
        Node *node = new Node{std::move(t), nullptr};
        if (empty()) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = tail->next;
        }
        q_size++;
    }

    T dequeue() {
        if (empty()) {
            throw UnderflowException{};
        }
        T t = head->element;
        Node *front = head;
        head = front->next;
        delete front;

        q_size--;

        return t;
    }

    const int size() const {
        return q_size;
    }

    bool empty() {
        return head == nullptr;
    }
};

#endif //QUEUE_H
