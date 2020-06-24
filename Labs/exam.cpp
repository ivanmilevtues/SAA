#include <iostream>
#include "exam.h"

using namespace std;

void print(int * arr) {
	for (int i = 0; i < 10; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void print(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void relations() {
	int i, p, q, t, id[10];
	for (i = 0; i < 10; i++) {
		id[i] = i;
	}

	for (int k = 0; k < 10; k++) {
		cin >> p;
		cin >> q;
		if (id[p] == id[q]) {
			cout << "relation exists";
			continue;
		}
		for (t = id[p], i = 0; i < 10; i++) {
			if (id[i] == t) {
				id[i] = id[q];
				cout << "new relation";
			}
		}
		print(id);
	}
}


void bubble_sort() {
	int arr[] = { 2, 4, 1, 3, 5, 8, 0,9, 6, 7 };

	for (int i = 0; i < 9; i++) {
		for (int k = i + 1; k < 10; k++) {
			if (arr[i] > arr[k]) {
				arr[i] += arr[k];
				arr[k] = arr[i] - arr[k];
				arr[i] = arr[i] - arr[k];
			}
		}
	}

	print(arr);
}

void selection_sort() {
	int arr[] = { 2, 4, 1, 3, 5, 8, 0,9, 6, 7 };
	int min, indx;
	for (int i = 0; i < 9; i++) {
		min = arr[i];
		indx = i;
		for (int k = i + 1; k < 10; k++) {
			if (min > arr[k]) {
				min = arr[k];
				indx = k;
			}
		}

		arr[indx] = arr[i];
		arr[i] = min;
	}

	print(arr);
}

void insertion_sort() {
	int arr[] = { 2, 4, 1, 3, 5, 8, 0,9, 6, 7 };

	for (int i = 0; i < 10; i++) {
		int j = i;
		int temp = arr[i];
		while (j > 0 && temp < arr[j - 1]) {
			arr[j] = arr[j - 1];
			j--;
		}

		arr[j] = temp;
	}
	print(arr);
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int* L = new int[n1];
	int * R = new int[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
}

void merge_sort_helper(int* arr, int start, int end) {
	if (start < end) {
		int mid = (end + start) / 2;
		merge_sort_helper(arr, start, mid);
		merge_sort_helper(arr, mid + 1, end);
		merge(arr, start, mid, end);
	}
}

void merge_sort() {
	int arr[] = { 2, 4, 1, 3, 5, 8, 0,9, 6, 7 };

	merge_sort_helper(arr, 0, 9);
	print(arr);
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high]; 
	int i = low - 1;

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			arr[i] += arr[j];
			arr[j] = arr[i] - arr[j];
			arr[i] = arr[i] - arr[j];
		}
	}
	arr[i+1] += arr[high];
	arr[high] = arr[i+1] - arr[high];
	arr[i+1] = arr[i+1] - arr[high];
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void quick_sort() {
	int arr[] = { 2, 4, 1, 3, 5, 8, 0,9, 6, 7 };
	quickSort(arr, 0, 9);
	print(arr);
}

/*
 * ЗАДАЧИ ОТ ИЗПИТИ
 */

/*
 * 9 Поток група А
 * в O(n)
 */
void intersect() {
	int a[] = { 1, 2, 3, 4, 5, 6, 7 };
	int size_a = sizeof(a) / sizeof(int);
	int min_size = size_a;
	int max_size = size_a;

	int b[] = { 3, 4, 1, 10, 12, 34, 7 , 99};
	int size_b = sizeof(b) / sizeof(int);
	min_size = min_size > size_b ? size_b : min_size;
	max_size = max_size < size_b ? size_b : max_size;

	int c[] = { 4, 12, 11, 4, 15, 28, 7 , 13};
	int size_c = sizeof(c) / sizeof(int);
	min_size = min_size > size_c ? size_c : min_size;
	max_size = max_size < size_c ? size_c : max_size;

	int *d = new int[min_size]; // result array
	bool intersection[100][3];
	fill((bool *)intersection, (bool *)intersection + sizeof(intersection) / sizeof(bool), false);
	for (int i = 0; i < max_size; i++) {
		if (i < size_a) {
			// -1 cause the range is 1..100 and indexes are from 0 to 99
			intersection[a[i] - 1][0] = true;
		}
		if (i < size_b) {
			intersection[b[i] - 1][1] = true;
		}
		if (i < size_c) {
			intersection[c[i] - 1][2] = true;
		}
	}

	// get the intersection
	int k = 0;
	for (int i = 0; i < 100; i++) {
		if (intersection[i][0] && intersection[i][1] && intersection[i][2]) {
			d[k] = i + 1;
			k++;
		}
	}

	print(d, k);
	delete[] d;
}

/*
 * 9 Поток група B
 * в O(n)
 */
void calculate_avrg_max_min() {
	// Sorted by the task
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int arr_size = sizeof(arr) / sizeof(int);

	// cause it is sorted
	int min = arr[0];
	int max = arr[arr_size - 1];

	int even_min = arr[0];
	int even_max = arr[arr_size - 1 - ((arr_size - 1) % 2)];

	int sum = 0;
	int sum_even = 0;
	for (int i = 0; i < arr_size; i++) {
		sum += arr[i];
		if (i % 2 == 0) {
			sum_even += arr[i];
		}
	}
	cout << "S1 Min=" << min << " Max=" << max << " Avrg=" << sum / arr_size << endl;
	cout << "S2 Min=" << even_min << " Max=" << even_max << " Avrg=" << sum_even / (arr_size / 2) << endl;

}

/*
 * 10 Поток Група 2
 */
void biggest_common_divisor() {
	int arr[] = { 35, 42, 49, 70, 28 }; // it is 7
	int arr_size = sizeof(arr) / sizeof(int);

	int divisor = -1;
	// O(N * logN)
	for (int i = 0; i < arr_size - 1; i++) {
		int a = arr[i] > arr[i + 1]? arr[i]: arr[i + 1];
		int b = arr[i] > arr[i + 1]? arr[i + 1]: arr[i];
		if (divisor > 0 && a % divisor == 0 && b % divisor == 0) {
			continue;
		}

		// euclid
		while (a % b != 0) {
			b = a % b;
		}
		if (divisor < 0 || divisor > b) {
			divisor = b;
		}
	}
	cout << divisor << endl;
}

/*
 * 10 Поток поправка - Група 1
 */
void common_divisor_max_even_odd() {
	int arr[] = { 130, 42, 49, 70, 91 }; // it is 13
	int arr_size = sizeof(arr) / sizeof(int);

	int max_odd = -9999; // include the min.int
	int min_even = 9999; // same

	for (int i = 0; i < arr_size; i++) {
		if (arr[i] % 2 == 1) {
			max_odd = max_odd < arr[i] ? arr[i] : max_odd;
		}
		else {
			min_even = min_even > arr[i] ? arr[i] : min_even;
		}
	}

	// Euclid
	if (max_odd < min_even) {
		// swap
		max_odd += min_even;
		min_even = max_odd - min_even;
		max_odd -= min_even;
	}

	while (max_odd % min_even != 0) {
		min_even = max_odd % min_even;
	}

	cout << min_even << endl; // O(n + logN) => O(n)
}

/*
 * 10 Поток поправка - Група 2
 */
void pointless_function() { // ?XD?XD
	int a[] = { 1, 2, 3, 4, 5, 9 };
	int arr_size = sizeof(a) / sizeof(int);
	int b[] = { 23, 99, 1, 2, 3, 9 };
	int c[6]; // could be dynamicaly created;

	int sum = 0;
	for (int i = 0; i < arr_size; i++) {
		c[i] = a[i] > b[i] ? a[i] : b[i];
		sum += c[i];
	}
	print(c, 6);
	if (sum >= 100 && sum <= 999) {
		cout << "SUM=" << sum << " last num "<< sum % 10 << endl;
	}
}


/*
 * 2016 1.
 */
void sort_parts_of_matrix() {
	int A[3][3] = {
		{1, 2, -2},
		{2, 3, 5},
		{-1, 4, 5}
	};
	// num of rows + 1(sum) + 1(count)
	int b[3 + 1 + 1];
	int k = 0;

	// set the mins of each row
	for (int i = 0; i < 3; i++) {
		int min = 999; // set to int.max
		for (int j = 0; j < 3; j++) {
			if (min > A[i][j]) {
				min = A[i][j];
			}
		}
		b[k++] = min;
	}

	// sum of the primary diagonal 
	int sum = 0;
	for (int i = 0; i < 3; i++) {
		sum += A[i][i];
	}
	b[k++] = sum;

	// count of negatives in the secondary diagonal
	int count = 0;
	for (int i = 0, k = 2; i < 3; i++, k--) {
		if (A[i][k] < 0) {
			count++;
		}
	}
	b[k++] = count;

	// sort b with insertion
	for (int i = 0; i < 5; i++) {
		int temp = b[i];
		int j = i ;
		while (j > 0 && temp < b[j - 1]) {
			b[j] = b[j - 1];
			j--;
		}

		b[j] = temp;
	}

	print(b, k);
}

/*
 * 2016 2.
 */
void sort_rows_sums() {
	// as n^2 => square matrix
	// n = 3
	int A[3][3] = {
		{1, 2, -2},
		{2, 3, 5},
		{-1, 4, 5}
	};

	int sums[3] = {0, 0, 0}; // n
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			sums[i] += A[i][k];
		}
	}

	// sort with selection cause why not
	int min = 0; // replace with max.int;
	for (int i = 0; i < 3; i++) {
		for (int k = 1; k < 3; k++) {
			if (sums[min] > sums[k]) {
				min = k;
			}
		}
		// swap
		int temp = sums[i];
		sums[i] = sums[min];
		sums[min] = temp;
		min = i; // don't forget this bad boy
	}
	print(sums, 3);
}

/*
 * 2016 3.
 */
void avrg_of_matrix_numbers() {
	double sum_pos = 0, sum_neg = 0, sum_primary_diag = 0, sum_secondary_diag = 0, count_pos = 0, count_neg = 0, count_zero = 0;
	// if there is primary diagonal -> square matrix
	int A[3][3] = {
		{1, 2, -2},
		{2, 0, 5},
		{-1, 4, 5}
	};

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			if (A[i][k] > 0) {
				sum_pos += A[i][k];
				count_pos++;
			}
			else if (A[i][k] < 0) {
				sum_neg += A[i][k];
				count_neg++;
			}
			else {
				count_zero++;
			}

			if (i == k) {
				sum_primary_diag += A[i][k];
			}
			if (i + k == 2) {
				sum_secondary_diag += A[i][k];
			}
		}
	}
	// TODO check for 0 division 
	cout << "AVRG pos=" << sum_pos / count_pos << " AVRG neg=" << sum_neg / count_neg 
		 << " AVRG of diags=" << sum_primary_diag / 3 << " " << sum_secondary_diag / 3
		<< " Number of zeros" << count_zero;
}

// Другите се поватарят или са под случай на вече решените

int main() {
	// bubble_sort();
	// selection_sort();
	// insertion_sort();
	// merge_sort();
	// quick_sort();
	// intersect();
	// calculate_avrg_max_min();
	// biggest_common_divisor();
	// pointless_function();
	// sort_parts_of_matrix();
	sort_rows_sums();
	avrg_of_matrix_numbers();
	return 0;
}