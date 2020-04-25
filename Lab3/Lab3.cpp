#include <iostream>
/*
 * Синтез и анализ на алгоритми
 * Ивай Ивайлов Милев Група 52 ФК№121218022
 * Упражение №3. Рекурсия.
 */
using namespace std;

string reverse(string input);

// Exercise 21. Да се намери броя на двойките елементи симетрични на главният диагонал на
// двумерен масив, в които елементът над главният диагонал е по - малък от елементът
// под главният диагонал
template<int R, int C>
int number_of_duos_in_matrix(double(&arr)[R][C]) {
	int sum = 0;
	for (int i = 0; i < C; i++) {
		for (int k = 0; k < R; k++) {
			sum += i < k&& arr[i][k] > arr[k][i];
		}
	}
	return sum;
}


// Exercise 24. Да се състави рекурсивна функция, преобразуваща цяло десетично положително
// число в двоично.
string convert_to_double(int number, string result) {
	if (result.empty() && number < 0) {
		result.push_back('-'); // indicate that it is negative number, also could add head 1
	}

	if (number == 0) {
		return reverse(result);
	}

	result.push_back(abs(number % 2) + '0');

	return convert_to_double(number / 2, result);
}

// Exercise 25. Да се състави рекурсивна функция, изчисляваща x ^n
// (n - цяло число)
double power(double x, int n) {
	if (n == 0) {
		return 1;
	}

	if (n < 0) {
		return power(1. / x, -n);
	}

	if (n > 0) {
		return x * power(x, n - 1);
	}
}
// Exercise 27. Да се състави рекурсивна функция, изчисляваща сумата на елементите на даден
// едномерен масив.
int sum_of_array(int x[], int size) {
	if (size == 0) {
		return 0;
	}
	return x[size - 1] + sum_of_array(x, size - 1);
}

// Exercise 28. Да се състави рекурсивна функция, проверяваща за наличие на дадена цифра в
// дадено естествено число.
bool exists_in_number(int number, int number_to_check) {
	number = abs(number);
	if (number % 10 == number_to_check) {
		return true;
	}

	if (number == 0) {
		return false;
	}


	return exists_in_number(number / 10, number_to_check);
}

//int main()
//{
//	double arr[4][4] = {
//		{1, 6, 2, 4},
//		{5, 1, 3, 5},
//		{2, 3, 1, 6},
//		{4, 1, 6, 1},
//	};
//
//	cout << "Exercise 21 output:" << number_of_duos_in_matrix(arr) << endl;
//
//	cout << "Exercise 24 output: 9 in binary = " << convert_to_double(9, "") << " | -42 in binary = " << convert_to_double(-42, "") << endl;
//
//	cout << "Exercise 25 output: 2 ^ 7 = " << power(2, 7) << " | 3 ^ -3 = " << power(3., -3) << endl;
//
//	int arr1d[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	cout << "Exercise 27 output: sum of {1, 2, 3, 4, 5, 6, 7, 8, 9} = " << sum_of_array(arr1d, 10) << endl;
//
//	cout << "Exercise 28 output: 7 in 27 " << exists_in_number(27, 7) << " | 8 in 8209 " << exists_in_number(8209, 8) << " | 9 in -73973 " << exists_in_number(-73973, 9) <<
//		" | 2 in 10543 " << exists_in_number(10543, 2) << endl;
//}

string reverse(string input) {
	string rev;
	for (int i = input.size() - 1; i >= 0; i--) {
		if (input[i] != '-') {
			rev.push_back(input[i]);
		}
	}

	if (input[0] == '-') {
		rev.insert(0, "-");
	}

	return rev;
}
