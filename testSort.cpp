// Robert Koenig
// CISC220-011
// 5/3/24

#include "testSort.hpp"
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <iostream>
#include "Sort.hpp"

using namespace std;
using namespace std::chrono;

int randNum(int n) {
	return rand() % n;
}

void randArr(int* array, int n) {
	for(int i=0; i<n; i++) {
		array[i] = randNum(1000000);
	}
}

bool validate(int *array, int n) {
	for(int i=0; i<n-1; i++) {
		if(array[i] > array[i+1]) {
			return false;
		}
	}
	return true;
}

/* run the tests requested
 * arraySizes is an array of sizes to test on
 * n is the number of different sizes to test
 * sort indicates which sorting function to run
 */
void runTests(int arraySizes[], int numSizes, int sort) {
	int numTests = 10; // how many tests per array size per algorithm to run
	string names[] = {"", "insertion sort\t\t", "merge sort\t\t", "merge-insertion sort\t"};
	unsigned long totalTime = 0;
	unsigned long totalComps = 0;
	unsigned long totalMoves = 0;
	Sort s; // sorting object for running the algorithms

	for(int i=0; i<numSizes; i++) { // for each test size
		cout << names[sort];
		printf("n=%7d: ", arraySizes[i]);
		for (int t=0; t<numTests; t++) { // generate tests
			int* const unsorted = new int[arraySizes[i]];
			int* const sorted = new int[arraySizes[i]];
			if (!unsorted || !sorted) {
				cerr << "Error: out of memory on array creation.  Exiting." << endl;
				exit(-1);
			}
			randArr(unsorted, arraySizes[i]);
			copy(unsorted, unsorted+arraySizes[i], sorted);
			int duration;
			// check which sorting algorithm we're running
			auto begin = high_resolution_clock::now();
			switch(sort) {
				case 1: // insertion sort
					s.insertion_sort(sorted, arraySizes[i]);
					break;
				case 2:
					s.merge_sort(sorted, arraySizes[i]);
					break;
				case 3:
					s.merge_insert_sort(sorted, arraySizes[i]);
					break;
				default:
					cerr << "No valid sort selected.  Exiting." << endl;
					exit(-1);
			}
			auto dur = high_resolution_clock::now() - begin;
			duration = (int) duration_cast<milliseconds>(dur).count();

			totalTime += duration;
			totalComps += s.getComparisons();
			totalMoves += s.getMoves();

			assert(validate(sorted, arraySizes[i]));
			delete [] unsorted;
			delete [] sorted;
		} // numTests
		// print test results, using integer division to avoid scientific notation
		cout << totalMoves / numTests << " moves (avg),\t";
		cout << totalComps / numTests << " comparisons (avg),\t";
		cout << totalTime / (double) numTests << "ms (avg)" << endl;
	} // for each test size

}  // end runTests
