#ifndef PROJEKT_2_ALGORYTMY_SORTOWANIA_QUICKSORT_H
#define PROJEKT_2_ALGORYTMY_SORTOWANIA_QUICKSORT_H

template <typename T>
int partition(T* array, const int start, const int end) {
    T temp, pivot = array[(start + end) / 2];
    int l = start, r = end;
    while (true) {
        while (array[l] < pivot) l++;
        while (array[r] > pivot) r--;

        if (l >= r)
            return r;

        temp = array[l];
        array[l++] = array[r];
        array[r--] = temp;
    }
}

template <typename T>
void quickSort(T* array, int start, int end) {
    if (start >= 0 && start < end) {
        int pivot = partition(array, start, end);
        quickSort(array, start, pivot);
        quickSort(array, pivot + 1, end);
    }
}
#endif
