#ifndef PROJEKT_2_ALGORYTMY_SORTOWANIA_MERGESORT_H
#define PROJEKT_2_ALGORYTMY_SORTOWANIA_MERGESORT_H

template <typename T>
void merge(T* array, int start, int middle, int end) {
    // dzielenie na dwie podtablice A i B
    T* temp = new T[end - start + 1];
    int l = start, r = middle + 1, t = 0;  // iteratory dla tablic lewej/prawej/pomocniczej

    // sortowanie
    while (l <= middle && r <= end)
        if (array[r] < array[l])
            temp[t++] = array[r++];
        else
            temp[t++] = array[l++];

    // przepisywanie pozostalych elementow z podtablicy lewej/prawej (gdy skonczyly sie prawej/lewej)
    if (l <= middle)
        while (l <= middle)
            temp[t++] = array[l++];
    else
        while (r <= end)
            temp[t++] = array[r++];

    // przepisywanie wyniku sortowania z tablicy pomocniczej do oryginalnej
    for (t = 0; t <= end - start; t++)
        array[start + t] = temp[t];

    delete[] temp;
}

template <typename T>
void mergeSort(T* array, int start, int end) {
    // rekurencyjne dzielenie na 2 podtablice az do uzyskania jednoelementowych
    if (start >= 0 && start < end) {
        int middle = (start + end) / 2;
        mergeSort(array, start, middle);
        mergeSort(array, middle + 1, end);
        // scalanie kolejnych 2 podtablic w 1 posortowana az do posortowania oryginalnej
        merge(array, start, middle, end);
    }
}

#endif
