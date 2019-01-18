#include <iostream>
#include "data_structures.h"
#include "algorithm/sort.h"

using std::cout;
using std::endl;

using namespace SvenSort;

int main() {
    vector<int> array{24, 13, 26, 1, 2, 27, 38, 15};
    SvenSort::mergeSort(array);
    cout << "After sort : \n";
    for (int i = 0; i <= array.size() - 1; ++i) {
        cout << array[i];
        if (i + 1 != array.size()) {
            cout << ", ";
        } else {
            cout << endl;
        }
    }

    {
        SearchBinaryTree<int> sbt;
        sbt.insert(20);
        sbt.insert(19);
        sbt.insert(21);

        // ÖÐÐò±éÀú¶þ²æÊ÷
        sbt.levelTraversal2();

        cout << "Tree depth : " << sbt.treeDepth() << endl;

        Stack<int> stack;
        int num = 35;
        stack.push(10);
        stack.push(20);
        stack.push(num);

        while (!stack.empty()) {
            cout << stack.pop() << endl;
        }

        cout << "Test Queue : " << endl;

        Queue<int> queue;
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);
        queue.enqueue(4);
        queue.enqueue(5);

        while (!queue.empty()) {
            num = queue.dequeue();
            cout << num << endl;
        }

        cout << "end test queue" << endl;

        cout << "Test AVLTree" << endl;

        int a{10};

        cout << "int a value = " << a << endl;

        AVLTree<int> avlTree;
        avlTree.insert(1);
        avlTree.insert(2);
        avlTree.insert(3);
        avlTree.insert(4);
        avlTree.insert(5);
        cout << "----------------" << endl;
        avlTree.print();
        cout << "----------------" << endl;
        avlTree.insert(6);
        avlTree.print();
        cout << "----------------" << endl;
        avlTree.remove(6);
        avlTree.print();

        BinaryHeap<int> heap;
        int minItem;
        heap.insert(10);
        heap.insert(8);
        heap.insert(9);
        heap.insert(7);
        heap.insert(1);
        heap.insert(4);

        while (!heap.isEmpty()) {
            heap.deleteMin(minItem);
            cout << "current min : " << minItem << endl;
        }

        cout << "end of block" << endl;
    }

    cout << "Test WeChat Alert" << endl;

    cout << "End of main()" << endl;

    return 0;
}
