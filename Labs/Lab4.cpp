#include <iostream>
#include <assert.h>

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
void time_algorithms();
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

	time_algorithms();

	// task 48.
	assert(check_if_palindrome("sos") == true);
	assert(check_if_palindrome("ohsos") == false);
	assert(check_if_palindrome("ohos") == false);
	return 0;
}


// Exersize 46.
void time_algorithms() {
	int arr[5] = { 5, 3, 2, 1, 4 };
	
	insertion_sort(arr, 5);
	print_arr(arr, 5);
	
	selection_sort(arr, 5);
	print_arr(arr, 5);
	
	quick_sort(arr, 5);
	print_arr(arr, 5);
	
	shell_sort(arr, 5);
	print_arr(arr, 5);

	heap_sort(arr, 5);
	print_arr(arr, 5);
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

/// TODO: FINISH ME 
void merge(int* arr, int left, int mid, int right) {
	int i, left_end = mid - 1, num_elements = right - left + 1, tmp_pos = left;
	while (left <= left_end && mid <= right) {
		if (arr[left] <= arr[mid]) {
		}
	}
}

void m_sort(int* arr, int left, int right) {
	int mid;
	if (right > left) {
		mid = (right + left) / 2;
		m_sort(arr, left, mid);
		m_sort(arr, mid + 1, right);
		merge(arr, left, mid + 1, right);
	}
}

void merge_sort(int* arr, int size) {
	int left = 0, right = size - 1;
	m_sort(arr, left, right);
}


void print_arr(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i];
	}
	cout << endl;
}