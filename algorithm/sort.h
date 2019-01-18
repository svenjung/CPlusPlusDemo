//
// Created by svenj on 2019/1/18.
//

#ifndef SVEN_SORT_H
#define SVEN_SORT_H

#include <vector>

using std::vector;

namespace SvenSort {
    /**
     * �鲢����
     * �㷨������
     * 1.�½�һ����ʱ����
     * 2.��ԭ����ֳ����Σ������������αȽ�����С�����н�С��Ԫ�أ�������ʱ����
     * 3.������С�����ظ�ִ�е�2����ֱ������С����β��
     * 4.����ʱ�������ݸ��Ƶ�ԭ����
     */
    // @@ start merge sort
    template<typename Comparable>
    inline void merge(vector<Comparable> &array, vector<Comparable> &tmp,
               int leftPos, int rightPos, int rightEnd) {
        int leftEnd = rightPos - 1;
        int tmpPos = leftPos;

        int size = rightEnd - leftPos + 1;

        // ��ѭ�����鲢����
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
