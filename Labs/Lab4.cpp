#include <iostream>
#include <assert.h>
#include <ctime>
#include <chrono> 
#include <sstream>
#include <fstream>

using namespace std;

// Exercise 33. Алчен алгоритъм за плащане с най-малък брой монети(рекурсивен)
int coins[6] = { 50,20,10,5,2,1 };
void change(int sum, int i) {
	if (i == 6 || sum == 0) {
		return;
	}
	cout << "Broi moneti po " << coins[i] << " st. = " << sum / coins[i] << endl;
	change(sum % coins[i], i + 1);
}

// Exercise 48. Алчен алгоритъм за плащане с най-малък брой монети(рекурсивен)
bool check_if_palindrome(string word) {
	for (int front = 0, back = word.size() - 1; front < back; front++, back--) {
		if (word.at(front) != word.at(back)) {
			return false;
		}
	}
	return true;
}

// Sorting algorithms:
void generate_arr(int* arr, const int size);
long evaluate_algorithm(void (*algo)(int*, int), int * arr, int size, string algorithm_name);
void time_algorithms(const int size);
void bubble_sort(int* arr, int size);
void insertion_sort(int* arr, int size);
void selection_sort(int* arr, int size);
void quick_sort(int* arr, int size);
void shell_sort(int* arr, int size);
void heap_sort(int* arr, int size);
void merge_sort(int* arr, int size);
void print_arr(int* arr, int size);

int main() {
	change(125, 0);

	time_algorithms(10000);

	// task 48.
	assert(check_if_palindrome("sos") == true);
	assert(check_if_palindrome("ohsos") == false);
	assert(check_if_palindrome("ohos") == false);
	return 0;
}


void generate_arr(int* arr, const int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % size;
	}
}

void generate_arr_semi_sorted(int* arr, const int size) {
	int chunk = size / 1000;
	int old_i = 0;
	for (int i = chunk; i <= size; i += chunk) {
		for (int k = old_i; k < i; k++) {
			arr[k] = rand() % chunk + old_i;
		}
		old_i = i;
	}
}

long evaluate_algorithm(void (*algo)(int*, int), int* arr, int size, string algorithm_name) {
	int* arr_cpy = new int[size];
	memcpy(arr_cpy, arr, size);
	
	// time the algorithm
	auto start = chrono::high_resolution_clock::now();
	(*algo)(arr, size);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	
	cout << "Time for " << algorithm_name << " and size: " << size  <<  ", " << duration.count() << " microsecs" << endl;
	return duration.count();
	delete [] arr_cpy;
}

// Exersize 46.
void time_algorithms(const int size) {
	stringstream xlsFormatResult;
	char delimiter = '\t'; 
	// Add headers
	xlsFormatResult << "Size" << delimiter
		<< "Bubble sort time in microseconds"<< delimiter
		<< "Insertion sort time in microseconds" << delimiter
		<< "Selection sort time in microseconds" << delimiter
		<< "Quick sort time in microseconds" << delimiter
		<< "Shell sort time in microseconds"<< delimiter
		<< "Heap sort time in microseconds"<< delimiter
		<< "Merge sort time in microseconds" << endl; 

	for (int size = 10000; size <= 200000; size+= 10000) {
		int* base_arr = new int[size];
		generate_arr_semi_sorted(base_arr, size);
		// generate_arr(base_arr, size);
		long bubble_sort_time = evaluate_algorithm(bubble_sort, base_arr, size, "Bubble sort");
		long insertion_sort_time = evaluate_algorithm(insertion_sort, base_arr, size, "Insertion sort");
		long selection_sort_time = evaluate_algorithm(selection_sort, base_arr, size, "Selection sort");
		long quick_sort_time = evaluate_algorithm(quick_sort, base_arr, size, "Quick sort");
		long shell_sort_time = evaluate_algorithm(shell_sort, base_arr, size, "Shell sort");
		long heap_sort_time = evaluate_algorithm(heap_sort, base_arr, size, "Heap sort");
		long merge_sort_time = evaluate_algorithm(merge_sort, base_arr, size, "Merge sort");
		xlsFormatResult << size << delimiter
			<< bubble_sort_time << delimiter
			<< insertion_sort_time << delimiter
			<< selection_sort_time << delimiter
			<< quick_sort_time << delimiter
			<< shell_sort_time << delimiter
			<< heap_sort_time << delimiter
			<< merge_sort_time << endl;
		delete[] base_arr;
	}

	ofstream resultsFile;
	resultsFile.open("AlgorithmsEvaluationSemiSorted.xls");
	resultsFile << xlsFormatResult.str();
	resultsFile.close();
}

void bubble_sort(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 1; j <= i; j++) {
			if (arr[j - 1] > arr[j]) {
				// swap
				arr[j - 1] += arr[j];
				arr[j] = arr[j - 1] - arr[j];
				arr[j - 1] = arr[j - 1] - arr[j];
			}
		}
	}
}

void insertion_sort(int* arr, int size) {
	int index, j;
	for (int i = 0; i < size; i++) {
		index = arr[i];
		j = i;
		while (j > 0 && arr[j - 1] > index) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = index;
	}
}

void selection_sort(int* arr, int size) {
	int min, min_indx;
	for (int i = 0; i < size; i++) {
		min = arr[i];
		min_indx = i;
		for (int j = i + 1; j < size; j++) {
			if (min > arr[j]) {
				min = arr[j];
				min_indx = j;
			}
		}
		arr[min_indx] = arr[i];
		arr[i] = min;
	}
}

void qsort(int* arr, int lo, int hi);
void quick_sort(int* arr, int size) {
	int lo = 0, hi = size - 1;
	qsort(arr, lo, hi);
}

void qsort(int* arr, int lo, int hi) {
	int i = lo, j = hi;
	int pivot = arr[(i + j) / 2];
	int swap;
	do {
		while (arr[i] < pivot) i++;
		while (arr[j] > pivot) j--;
		// swap
		if (i <= j) {
			swap = arr[i];
			arr[i] = arr[j];
			arr[j] = swap;
			i++;
			j--;
		}
	} while (i <= j);

	if (lo < j) {
		qsort(arr, lo, j);
	}
	if (hi > i) {
		qsort(arr, i, hi);
	}
}

void shell_sort(int* arr, int size) {
	int increment = size - 1, j, temp;
	while (increment > 0) {
		for (int i = 0; i < size; i++) {
			j = i;
			temp = arr[j];
			while (j >= increment && arr[j - increment] > temp) {
				arr[j] = arr[j - increment];
				j = j - increment;
			}
			if (increment / 2 != 0) {
				increment /= 2;
			}
			else if (increment == 1) {
				increment = 0;
			}
			else {
				0;
			}
		}
	}
}

void sift_down(int* arr, int root, int size) {
	int max_child, temp;
	bool done = false;
	while (root * 2 <= size && !done) {
		if (root * 2 == size) {
			max_child = root * 2;
		} else if (arr[root * 2] > arr[root * 2 + 1]) {
			max_child = root * 2;
		}
		else {
			max_child = root * 2 + 1;
		}

		if (arr[root] < arr[max_child]) {
			temp = arr[root];
			arr[root] = arr[max_child];
			arr[max_child] = temp;
			root = max_child;
		}
		else {
			done = true;
		}
	}
}

void heap_sort(int* arr, int size) {
	int temp;
	for (int i = (size / 2) - 1; i >= 0; i--) {
		sift_down(arr, i, size);
	}
	for (int i = size - 1; i >= 1; i--) {
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		sift_down(arr, 0, i - 1);
	}
}

void merge(int * temp, int* arr, int left, int mid, int right) {
	int i, left_end = mid - 1, num_elements = right - left + 1, tmp_pos = left;
	while (left <= left_end && mid <= right) {
		if (arr[left] <= arr[mid]) {
			temp[tmp_pos] = arr[left];
			tmp_pos++;
			left++;
		}
		else {
			temp[tmp_pos] = arr[mid];
			tmp_pos++;
			mid++;
		}
	}

	while (left <= left_end) {
		temp[tmp_pos] = arr[left];
		left++;
		tmp_pos++;
	}

	while (mid <= right) {
		temp[tmp_pos] = arr[mid];
		mid++;
		tmp_pos++;
	}

	for (i = 0; i <= num_elements; i++) {
		arr[right] = temp[right];
		right--;
	}
}

void m_sort(int * temp, int* arr, int left, int right) {
	int mid;
	if (right > left) {
		mid = (right + left) / 2;
		m_sort(temp, arr, left, mid);
		m_sort(temp, arr, mid + 1, right);
		merge(temp, arr, left, mid + 1, right);
	}
}

void merge_sort(int* arr, int size) {
	int * temp = new int[size];
	int left = 0, right = size - 1;
	m_sort(temp, arr, left, right);
	delete[] temp;
}

void print_arr(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i];
	}
	cout << endl;
}