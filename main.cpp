#include <iostream>
#include "AVLTree.h"
#include "SearchBinaryTree.h"
#include "Stack.h"
#include "Queue.h"

using std::cout;
using std::endl;

int main() {
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
    }

    cout << "Test WeChat Alert" << endl;

    cout << "End of main()" << endl;
    return 0;
}
