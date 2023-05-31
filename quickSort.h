#ifndef PROJEKT_2_ALGORYTMY_SORTOWANIA_QUICKSORT_H
#define PROJEKT_2_ALGORYTMY_SORTOWANIA_QUICKSORT_H

template <typename T>
int partition(T* array, int start, int end) {
    T temp, pivot = array[(start + end) / 2];  // element srodkowy
    int l = start, r = end;                    // iteratory dla podtablic lewej i prawej
    while (1) {
        while (array[l] < pivot) l++;  // dopoki po lewej sa mniejsze od srodkowego
        while (array[r] > pivot) r--;  // dopoki po prawej sa wieksze od srodkowego

        if (l >= r)
            return r;  // element osiowy

        // zamien elementy - mniejszy na lewo, wiekszy na prawo
        temp = array[l];
        array[l++] = array[r];

        array[r--] = temp;
    }
}

template <typename T>
void quickSort(T* array, int start, int end) {
    // rekurencyjne dzielenie na 2 podtablice az do uzyskania jednoelementowych
    if (start >= 0 && start < end) {
        int pivot = partition(array, start, end);  // element osiowy
        quickSort(array, start, pivot);            // lewa podtablica
        quickSort(array, pivot + 1, end);          // prawa podtablica
    }
}
#endif
