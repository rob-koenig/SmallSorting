// Robert Koenig
// CISC220-011
// 5/3/24

#include <iostream>
#include "Sort.hpp"

using namespace std;

Sort::Sort() {
	resetCounts();
}

void Sort::insertion_sort(int *array, int size) {
    // reset the count
    resetCounts();
    // counts for first element
    comparisons++;
    for(int i=0; i<size; i++) {
        int pivot = array[i];
        int temp = i - 1;
        // checks pivot against previous value
        while (temp >= 0 && array[temp] > pivot) {
            comparisons++;
            moves++;
            array[temp+1] = array[temp];
            temp-=1;
        }
        moves++;
        array[temp+1] = pivot;
    }
}

void Sort::merge_sort(int *array, int size) {
	resetCounts();
    merge_sort(array, 0, size-1, size/2);
}

void Sort::merge_insert_sort(int *array, int size) {
	resetCounts();
    merge_sort(array, 0, size-1, size/10);
    insertion_sort(array, size);
    merge_sort(array, 0, size-1, size/2);
}

// optional, if you choose to write a recursive merge sort
// you can use rec_stop to set the size of the base case for merge-insertion sort
void Sort::merge_sort(int *array, int start, int end, int rec_stop) {
    if (start < end && rec_stop > 0) {
        int mid = start + (end - start) / 2;
        merge_sort(array, start, mid, rec_stop-1);
        merge_sort(array, mid+1, end, rec_stop-1);
        merge(array, start, mid, end);
    }
}

// optional, if you choose to write a recursive merge sort
void Sort::merge(int *array, int start, int mid, int end) {
    int size1 = mid - start + 1;       // size of first half
    int size2 = end - mid;             // size of second half
    int left[size1];                   // left side of array
    int right[size2];                  // right side of array
    for (int i=0; i<size1; i++){
        left[i] = array[start+i];
    }
    for (int i=0; i<size2; i++){
        right[i] = array[mid+i+1];
    }
    int a = 0;
    int b = 0;
    int c = start;
    while (a < size1 && b < size2) {
        if (left[a] <= right[b]) {
            comparisons++;
            moves++;
            array[c] = left[a];
            a++;
        } else {
            comparisons++;
            moves++;
            array[c] = right[b];
            b++;
        }
        +c++;
    }
    while (a < size1) {
        //comparisons++;
        moves++;
        array[c] = left[a];
        a++;
        c++;
    }
    while (b < size2) {
        //comparisons++;
        moves++;
        array[c] = right[b];
        b++;
        c++;
    }
}

int Sort::getComparisons() {
	return comparisons;
}

int Sort::getMoves() {
	return moves;
}

void Sort::resetCounts() {
	moves = 0;
	comparisons = 0;
}


