/**
 * Created by svenj on 2019/1/16.
 * ����һ����ȫ�������Ķ��������п��ܵ������ڵײ㣬�ײ��ϵ�Ԫ�ش�����������
 * С�ѣ�ÿһ�����ڵ㶼С���������ӽڵ�
 */

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <iostream>
#include <vector>
#include "exceptions.h"

using std::vector;
using std::cout;
using std::endl;

template<typename Comparable>
class BinaryHeap {
public:
    explicit BinaryHeap(int capacity = 100)
            : array(capacity + 1), currentSize{0} {
    }

    explicit BinaryHeap(const vector<Comparable> &items)
            : array(items.size() + 10), currentSize{items.size()} {
        for (int i = 0; i < items.size(); ++i) {
            array[i + 1] = items[i];
        }
        buildHeap();
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    void insert(Comparable &&x) {
        if (currentSize == array.size() - 1) {
            array.reserve(array.size() * 2);
        }

        // ����
        int hole = ++currentSize;
        for (; x < array[hole / 2]; hole /= 2) {
            array[hole] = move(array[hole / 2]);
        }

        array[hole] = move(x);
    }

    void insert(const Comparable &x) {
        if (currentSize == array.size() - 1) {
            array.reserve(array.size() * 2);
        }

        // ����
        int hole = ++currentSize;
        Comparable copy = x;
        array[0] = move(copy);
        for (; x < array[hole / 2]; hole /= 2) {
            array[hole] = move(array[hole / 2]);
        }

        array[hole] = move(array[0]);
    }

    void deleteMin() {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        array[1] = move(array[currentSize--]);
        // ����ǰ���ڵ����³������������
        percolateDown(1);
    }

    /**
     * ɾ����СԪ�ز���ֵ��minItem
     */
    void deleteMin(Comparable &minItem) {
        if (isEmpty())
            throw UnderflowException{};

        minItem = move(array[1]);
        array[1] = move(array[currentSize--]);
        percolateDown(1);
    }

    // �ڲ�ʹ���˱�׼��vector������ʱ�Զ�����vector����������
    void makeEmpty() {
        currentSize = 0;
    }

private:
    int currentSize;
    vector<Comparable> array;

    /**
     * �������һ���п�ʼ������������
     * ������ʱ������
     */
    void buildHeap() {
        for (int i = currentSize / 2; i > 0; --i) {
            percolateDown(i);
        }
    }

    void percolateDown(int hole) {
        int child;
        Comparable x = move(array[hole]);
        for (; hole * 2 < currentSize; hole = child) {
            child = hole * 2;

            // ���ҵ����Һ����н�С��һ��
            if (child != currentSize && array[child + 1] < array[child]) {
                child++;
            }

            if (array[child] < x) {
                // ����������Ӷ�С�ڸ��ڵ��򽫽�С�ĺ����ƶ������ڵ㣨hole������λ��
                array[hole] = move(array[child]);
            } else {
                // ������Ӵ��ڸ��ڵ㣬��xӦ���ƶ�����ǰhole����λ��
                break;
            }
        }

        array[hole] = move(x);
    }
};

#endif //BINARY_HEAP_H
