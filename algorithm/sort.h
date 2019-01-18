//
// Created by svenj on 2019/1/18.
//

#ifndef SVEN_SORT_H
#define SVEN_SORT_H

#include <vector>

using std::vector;

namespace SvenSort {
    /**
     * 归并排序
     * 算法描述：
     * 1.新建一个临时数组
     * 2.将原数组分成两段，从左至右依次比较两个小数组中较小的元素，插入临时数组
     * 3.对两个小数组重复执行第2步，直至到达小数组尾部
     * 4.将临时数组内容复制到原数组
     */
    // @@ start merge sort
    template<typename Comparable>
    inline void merge(vector<Comparable> &array, vector<Comparable> &tmp,
               int leftPos, int rightPos, int rightEnd) {
        int leftEnd = rightPos - 1;
        int tmpPos = leftPos;

        int size = rightEnd - leftPos + 1;

        // 主循环，归并排序
        while (leftPos <= leftEnd && rightPos <= rightEnd) {
            if (array[leftPos] <= array[rightPos]) {
                tmp[tmpPos++] = move(array[leftPos++]);
            } else {
                tmp[tmpPos++] = move(array[rightPos++]);
            }
        }

        while (leftPos <= leftEnd) {
            tmp[tmpPos++] = move(array[leftPos++]);
        }

        while (rightPos <= rightEnd) {
            tmp[tmpPos++] = move(array[rightPos++]);
        }

        for(int i = 0; i < size; ++i, --rightEnd) {
            array[rightEnd] = move(tmp[rightEnd]);
        }
    }

    template<typename Comparable>
    inline void mergeSort(vector<Comparable> &array, vector<Comparable> &tmp,
                   int left, int right) {
        if (left < right) {
            int center = (left + right) / 2;
            mergeSort(array, tmp, left, center);
            mergeSort(array, tmp, center + 1, right);

            merge(array, tmp, left, center + 1, right);
        }
    }

    template<typename Comparable>
    void mergeSort(vector<Comparable> &array) {
        vector<Comparable> tmpArray = vector<Comparable>(array.size());
        mergeSort(array, tmpArray, 0, array.size() - 1);
    }
    // @@ end merge sort
}
#endif //SVEN_SORT_H
