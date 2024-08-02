#ifndef PROJEKT_2_ALGORYTMY_SORTOWANIA_MERGESORT_H
#define PROJEKT_2_ALGORYTMY_SORTOWANIA_MERGESORT_H

template <typename T>
void merge(T* array, const int start, const int middle, const int end) {
    T* temp = new T[end - start + 1];
    int l = start, r = middle + 1, t = 0;

    while (l <= middle && r <= end)
        if (array[r] < array[l])
            temp[t++] = array[r++];
        else
            temp[t++] = array[l++];

    if (l <= middle)
        while (l <= middle)
            temp[t++] = array[l++];
    else
        while (r <= end)
            temp[t++] = array[r++];

    for (t = 0; t <= end - start; t++)
        array[start + t] = temp[t];

    delete[] temp;
}

template <typename T>
void mergeSort(T* array, int start, int end) {

    if (start >= 0 && start < end) {
        int middle = (start + end) / 2;
        mergeSort(array, start, middle);
        mergeSort(array, middle + 1, end);

        merge(array, start, middle, end);
    }
}

#endif
