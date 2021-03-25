#ifndef SORTING_H
    #define SORTING_H

    #include "vetor.h"

    void bubble_sort(VETOR *vetor);
    void selection_sort(VETOR *vetor);
    void insertion_sort(VETOR *vetor);
    void merge_sort(VETOR *vetor);
    void quick_sort(VETOR *vetor);
    void heap_sort(VETOR *vetor);
    void counting_sort(VETOR *vetor);
    void bucket_sort(VETOR *vetor);
    void radix_sort_10(VETOR *vetor);
    void radix_sort_256(VETOR *vetor);

#endif