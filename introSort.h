
#ifndef PROJEKT_2_ALGORYTMY_SORTOWANIA_INTROSORT_H
#define PROJEKT_2_ALGORYTMY_SORTOWANIA_INTROSORT_H

#include <cmath>

#include "quickSort.h"

template <typename T>
void insertionSort(T* array, const int start, const int end) {
    T key;
    for (int i = start + 1; i < end; i++) {
        key = array[i];
        int j = i - 1;

        while (j >= start && key < array[j]) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

template <typename T>
void heapify(T* array, int heap_size, int i) {
    T temp;
    int largest, l = 2 * i, r = (2 * i) + 1;
    if (l <= heap_size && array[l] > array[i])
        largest = l;
    else
        largest = i;
    if (r <= heap_size && array[r] > array[largest])
        largest = r;
    if (largest != i) {
        temp = array[largest];
        array[largest] = array[i];
        array[i] = temp;
        heapify(array, heap_size, largest);
    }
}

template <typename T>
void heapSort(T* array, int heap_size) {
    T temp;
    for (int i = heap_size / 2; i > 0; i--)
        heapify(array, heap_size, i);
    for (int i = heap_size; i > 1; i--) {
        temp = array[i];
        array[i] = array[1];
        array[1] = temp;
        heap_size--;
        heapify(array, heap_size, 1);
    }
}

template <typename T>
void introSort(T* array, int start, int end, int maxdepth) {
    if (maxdepth <= 0) {
        heapSort(array, end - start);
        return;
    }
    int i = partition(array, start, end);
    if (i > 9)
        introSort(array, start, i, maxdepth - 1);
    if (end - i > 9)
        introSort(array, i + 1, end, maxdepth - 1);
}

template <typename T>
void hybridIntroSort(T* array, int start, int end) {
    introSort(array, start, end, (2 * log(end - start)));
    insertionSort(array, start, end);
}

#endif
