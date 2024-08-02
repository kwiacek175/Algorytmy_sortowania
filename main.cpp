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
    std::string name;
    short rating{};
    bool operator<(const movie& compared) const { return (rating < compared.rating); }
    bool operator>(const movie& compared) const { return (rating > compared.rating); }
};

int main(int argc, char** argv) {

    std::ifstream dataset;
    std::string dataset_name = "projekt2_dane.csv";

    std::string temp, line;
    char identifier;

    std::string sorts[3] = { "merge", "quick", "intro" };

    unsigned int test = 0;
    unsigned int ntab[] = { 10000, 100000, 500000, 1000000, 1010292 };
    unsigned int unrated, median;
    float average;

    std::cout << std::fixed << std::setprecision(3);

    for (unsigned int n : ntab)
    {
        test++;
        std::cout << "TEST " << test << "/" << std::size(ntab) << ": n = " << n << '\n';
        auto* parsed_dataset = new movie[n];


        unrated = 0;
        dataset.open("C:/Users/Kacper/CLionProjects/Algorytmy_sortowania/" + dataset_name);

        if (!dataset.is_open()) {
            std::cout << "Nie udalo sie otworzyc pliku " + dataset_name;
            exit(1);
        }

        std::getline(dataset, line);
        for (unsigned int i = 0; i < n; i++) {

            std::getline(dataset, line);
            std::stringstream split(line);

            std::getline(split, temp, ',');

            std::stringstream::pos_type pos = split.tellg();
            split >> identifier;
            if (identifier == '"') {
                std::getline(split, parsed_dataset[i].name, '"');
                split >> identifier;
            }
            else {
                split.seekg(pos);
                std::getline(split, parsed_dataset[i].name, ',');
            }

            if (!(split >> parsed_dataset[i].rating)) {
                unrated++;
                parsed_dataset[i].rating = -1;
            }

            if (dataset.eof()) {
                std::cout << "Plik zawiera za malo danych - wczytane filmy: " << i << " / " << n << '\n';
                n = i + 1;
            }
        }
        dataset.close();

        if (unrated > 0) {
            std::cout << "> Filmy bez oceny: " << unrated << '\n';
            pressEnter();
            std::cout << "Filtrowanie danych\n";
        }
        else
            std::cout << "> Wszystkie filmy sa ocenione.\n";
        auto* filtered_dataset = new movie[n - unrated];
        unsigned int i = 0, j = 0;

        auto duration_start = std::chrono::high_resolution_clock::now();
        while (j < n)
            if (parsed_dataset[j].rating != -1)
                filtered_dataset[i++] = parsed_dataset[j++];
            else
                j++;
        auto duration_end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();

        delete[] parsed_dataset;

        if (unrated > 0)
            std::cout << "> Po przefiltrowaniu: " << n - unrated << '\n'
                      << "> Czas filtrowania:   " << duration << " ms\n";

        pressEnter();

        auto** sorting_datasets = new movie * [std::size(sorts)];
        for (unsigned int i = 0; i < std::size(sorts); ++i)
            sorting_datasets[i] = new movie[n - unrated];
        for (unsigned int i = 0; i < std::size(sorts); ++i)
            for (unsigned int j = 0; j < n - unrated; ++j)
                sorting_datasets[i][j] = filtered_dataset[j];
        delete[] filtered_dataset;

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

            average = 0;
            for (unsigned int j = 0; j < n - unrated; ++j)
                average += sorting_datasets[i][j].rating;
            average /= n - unrated;
            std::cout << "> Srednia ocen:    " << average << '\n';

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
