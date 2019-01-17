/**
 * Created by svenj on 2019/1/16.
 * 堆是一颗完全被填满的二叉树，有可能的例外在底层，底层上的元素从左至右排列
 * 小堆：每一个父节点都小于两个孩子节点
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

        // 上滤
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

        // 上滤
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
        // 将当前根节点向下沉，以满足堆序
        percolateDown(1);
    }

    /**
     * 删除最小元素并赋值给minItem
     */
    void deleteMin(Comparable &minItem) {
        if (isEmpty())
            throw UnderflowException{};

        minItem = move(array[1]);
        array[1] = move(array[currentSize--]);
        percolateDown(1);
    }

    // 内部使用了标准库vector，析构时自动调用vector的析构函数
    void makeEmpty() {
        currentSize = 0;
    }

private:
    int currentSize;
    vector<Comparable> array;

    /**
     * 从项的任一排列开始建立堆序性质
     * 以线性时间运行
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

            // 先找到左右孩子中较小的一个
            if (child != currentSize && array[child + 1] < array[child]) {
                child++;
            }

            if (array[child] < x) {
                // 如果两个孩子都小于父节点则将较小的孩子移动到父节点（hole）所在位子
                array[hole] = move(array[child]);
            } else {
                // 如果孩子大于父节点，则x应该移动到当前hole所在位子
                break;
            }
        }

        array[hole] = move(x);
    }
};

#endif //BINARY_HEAP_H
