#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>

#include "introSort.h"
#include "mergeSort.h"
#include "quickSort.h"

void pressEnter() {
    int c;
    do
        c = getchar();
    while ((c != '\n') && (c != EOF));
}

struct movie {
    std::string name;  // nazwa filmu
    short rating;      // ocena filmu (0-10)
    bool operator<(movie compared) { return (rating < compared.rating); }
    bool operator>(movie compared) { return (rating > compared.rating); }
};

int main(int argc, char** argv) {

    // pliki
    std::ifstream dataset;  // baza filmow (wczytywany plik)
    std::string dataset_name = "projekt2_dane.csv";

    // parsowanie .csv
    std::string temp, line;  // pojedynczy wpis w bazie
    char identifier;         // , lub "

    // sortowania
    std::string sorts[3] = { "merge", "quick", "intro" };

    // testy
    unsigned int test = 0;    // numer testu
    unsigned int ntab[] = { 10000, 100000, 500000, 1000000, 1010292 };
    unsigned int unrated, median;  // ilosc nieocenionych filmow, mediana ocen
    float average;                 // srednia ocen

    std::cout << std::fixed << std::setprecision(3);  // precyzja wyswietlania + clear screen

    for (unsigned int n : ntab)
    {
        test++;
        std::cout << "TEST " << test << "/" << std::size(ntab) << ": n = " << n << '\n';
        movie* parsed_dataset = new movie[n];

        // wczytywanie pliku
        unrated = 0;
        dataset.open("C:/Users/kacpe/CLionProjects/projekt_2_algorytmy_sortowania/" + dataset_name);

        if (!dataset.is_open()) {
            std::cout << "Nie udalo sie otworzyc pliku " + dataset_name;
            exit(1);
        }

        std::getline(dataset, line);  // pominiecie headera
        for (unsigned int i = 0; i < n; i++) {
            // format pliku: indeks,nazwa,ocena
            std::getline(dataset, line);  // dzielenie pliku na linie
            std::stringstream split(line);
            // wczytywanie indeksu i przecinka
            std::getline(split, temp, ',');
            // wczytywanie nazwy - pomiedzy " " lub zwykla oddzielona
            // przecinkiem
            std::stringstream::pos_type pos = split.tellg();
            split >> identifier;
            if (identifier == '"') {
                std::getline(split, parsed_dataset[i].name, '"');
                split >> identifier;  // ignoruj ,
            }
            else {
                split.seekg(pos);  // wroc
                std::getline(split, parsed_dataset[i].name, ',');
            }
            // wczytywanie oceny
            if (!(split >> parsed_dataset[i].rating)) {
                unrated++;
                parsed_dataset[i].rating = -1;
            }
            // koniec pliku - zmiana n do liczby wczytanych filmow
            if (dataset.eof()) {
                std::cout << "Plik zawiera za malo danych - wczytane filmy: " << i << " / " << n << '\n';
                n = i + 1;
            }
        }
        dataset.close();

        // filtrowanie - usuwanie filmow bez ocen
        if (unrated > 0) {
            std::cout << "> Filmy bez oceny: " << unrated << '\n';
            pressEnter();
            std::cout << "Filtrowanie danych\n";
        }
        else
            std::cout << "> Wszystkie filmy sa ocenione.\n";
        movie* filtered_dataset = new movie[n - unrated];
        unsigned int i = 0, j = 0;

        auto duration_start = std::chrono::high_resolution_clock::now();  // mierzenie czasu filtrowania
        while (j < n)
            if (parsed_dataset[j].rating != -1)
                filtered_dataset[i++] = parsed_dataset[j++];
            else
                j++;
        auto duration_end = std::chrono::high_resolution_clock::now();  // koniec mierzenia
        auto duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();

        delete[] parsed_dataset;

        if (unrated > 0)
            std::cout << "> Po przefiltrowaniu: " << n - unrated << '\n'
                      << "> Czas filtrowania:   " << duration << " ms\n";

        pressEnter();

        // struktury do przechowywania wynikow sortowan
        movie** sorting_datasets = new movie * [std::size(sorts)];
        for (unsigned int i = 0; i < std::size(sorts); ++i)
            sorting_datasets[i] = new movie[n - unrated];
        for (unsigned int i = 0; i < std::size(sorts); ++i)
            for (unsigned int j = 0; j < n - unrated; ++j)
                sorting_datasets[i][j] = filtered_dataset[j];
        delete[] filtered_dataset;

        // sortowania
        for (unsigned int i = 0; i < std::size(sorts); ++i) {
            std::cout << "Sortowanie ";
            if (sorts[i] == "merge") {
                std::cout << "przez scalanie (mergesort)\n";
                duration_start = std::chrono::high_resolution_clock::now();
                mergeSort(sorting_datasets[i], 0, n - unrated - 1);
                duration_end = std::chrono::high_resolution_clock::now();
            }
            else if (sorts[i] == "quick") {
                std::cout << "szybkie (quicksort)\n";
                duration_start = std::chrono::high_resolution_clock::now();
                quickSort(sorting_datasets[i], 0, n - unrated - 1);
                duration_end = std::chrono::high_resolution_clock::now();
            }
            else if (sorts[i] == "intro") {
                std::cout << "introspektywne (introsort)\n";
                duration_start = std::chrono::high_resolution_clock::now();
                hybridIntroSort(sorting_datasets[i], 0, n - unrated - 1);
                duration_end = std::chrono::high_resolution_clock::now();
            }
            else {
                std::cout << "nie powiodlo sie - brak interfejsow sortowan.\n";
                break;
            }
            duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();
            std::cout << "> Czas sortowania: " << duration << " ms\n";

            // srednia ocen
            average = 0;
            for (unsigned int j = 0; j < n - unrated; ++j)
                average += sorting_datasets[i][j].rating;  // average jako suma
            average /= n - unrated;
            std::cout << "> Srednia ocen:    " << average << '\n';

            // mediana
            median = 0;
            if ((n - unrated) % 2 != 0)
                median = sorting_datasets[i][(n - unrated) / 2].rating;
            else
                median = (sorting_datasets[i][(n - unrated - 1) / 2].rating + sorting_datasets[i][(n - unrated) / 2].rating) / 2;
            std::cout << "> Mediana ocen:    " << median << "\n\n";
        }

        std::cout << "KONIEC TESTU " << test << "/" << std::size(ntab) << '\n';
        pressEnter();
    }
}
