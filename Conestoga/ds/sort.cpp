/*
 * FILE: sort.cpp
 * AUTHOR: Lev Potomkin
 * DATE: Mar 6, 2019
 * DESCRIPTION:
 *   File contains an implementation of a generic
 *   function `sort` that performs a bubble sort on
 *   an array (in-place).
 *   The test harness consists of 3 tests on 3 different datatypes.
 * DESIGN:
 *   function sort(array):
 *		let n be the length of array
 *		for n times do:
 *			for each element of the array:
 *				if the element is greater than the next one, swap them
 */
#include <iostream>
#include <typeinfo>
#define ARRAY_SIZE 6

using std::cout;

/*
 * FUNCTION: sort
 * DESCRIPTION:
 *   sorts an array in-place by performing bubble sort
 * PARAMETERS:
 * 	 T array[]: an array to sort (any type the implements < operator)
 *   int n: size of the array
 * RETURNS: none
 */
template <typename T>
void sort(T array[], int size) {
	int count = size;
	// output the initial array
	cout << "Array of " << typeid(T).name() << "'s:\n";
	for (int j = 0; j < size; j++) {
		cout << array[j] << ' ';
	}
	// perform the sort
	while (count--) {
		for (int j = 0; j+1 < size; j++) {
			if (array[j] > array[j+1]) {
				T temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
	// output the sorted array
	cout << "\n Sorted:\n";
	for (int j = 0; j < size; j++) {
		cout << array[j] << ' ';
	}
	cout << '\n';
}

int main() {
	int ints[ARRAY_SIZE] = {7, 5, 8, 9, 4, 1};
	double doubles[ARRAY_SIZE] = {7.5, 5.5, 8.5, 9.5, 4.5, 1.5};
	char chars[ARRAY_SIZE] = {'f', 'a', 's', 'l', 't', 'b'};
	sort(ints, ARRAY_SIZE);
	sort(doubles, ARRAY_SIZE);
	sort(chars, ARRAY_SIZE);
	return 0;
}
