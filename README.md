# Projekt: Algorytmy Sortowania

## Opis projektu

Projekt demonstruje różne algorytmy sortowania na zestawie danych filmów. W ramach projektu zaimplementowano trzy algorytmy sortowania:

1. **Sortowanie przez scalanie (Merge Sort)**
2. **Sortowanie szybkie (Quick Sort)**
3. **Sortowanie introspektywne (IntroSort)**

## Pliki projektu

- `main.cpp`: Główny plik programu, który wczytuje dane, filtruje je, sortuje za pomocą trzech różnych algorytmów i mierzy czas sortowania oraz inne statystyki.
- `mergeSort.h`: Implementacja algorytmu sortowania przez scalanie.
- `quickSort.h`: Implementacja algorytmu sortowania szybkiego.
- `introSort.h`: Implementacja algorytmu sortowania introspektywnego.

## Struktura danych

### Struktura `movie`

Reprezentuje film i zawiera:
- `name` - Nazwa filmu (ciąg znaków).
- `rating` - Ocena filmu (krótkiej liczby całkowitej).

### Operatory porównania

- `<` - Porównuje oceny filmów (mniejsze oceny są sortowane przed większymi).
- `>` - Odwrócone porównanie dla celów sortowania w odwrotnej kolejności.

## Algorytmy Sortowania

### Sortowanie przez scalanie (Merge Sort)

Algorytm sortowania przez scalanie dzieli tablicę na mniejsze części, sortuje je rekurencyjnie, a następnie scala posortowane części.

### Sortowanie szybkie (Quick Sort)

Algorytm sortowania szybkie wykorzystuje pivot, aby podzielić tablicę na mniejsze i większe części, a następnie sortuje je rekurencyjnie.

### Sortowanie introspektywne (IntroSort)

IntroSort łączy sortowanie szybkie z sortowaniem przez kopcowanie. W przypadku, gdy sortowanie szybkie nie daje dobrych rezultatów (głębokość rekurencji), używa sortowania przez kopcowanie.

## Kompilacja i Uruchamianie

Aby skompilować projekt, użyj kompilatora C++ (np. g++):

```bash
g++ -o sortowanie main.cpp
