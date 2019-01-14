#include <iostream>
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
    }

    cout << "End of main()" << endl;
    return 0;
}
