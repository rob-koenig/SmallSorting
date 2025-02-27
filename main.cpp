// Robert Koenig
// CISC220-011
// 5/3/24

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "testSort.hpp"

using namespace std;

int main() {
	srand(time(0));
	// 1 = insertion
	// 2 = merge
	// 3 = merge-insertion
	int sorts[] = {1, 2, 3};    // list the number(s) of the sorting algorithm you want to run
								// remove any you are not ready to run yet
	int numSizes = 5; // number of differently-sized random arrays to test on
	int insertionTestSizes[] = {1000, 2000, 4000, 8000, 16000};
	int recursiveTestSizes[] = {32000, 64000, 128000, 256000, 512000};
	// if you're getting out-of-memory errors on array allocations, try a smaller set of sizes:
	// int recursiveTestSizes[] = {16000, 32000, 64000, 128000, 256000};

	// to simplify function call
	int* testSizes;
	for(auto sort : sorts) {
		testSizes = (sort == 1) ? insertionTestSizes : recursiveTestSizes;
		runTests(testSizes, numSizes, sort);
	}

	return 0;
}
