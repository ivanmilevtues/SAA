/*
 * Курсова работа по "Синтез и анализ на алгоритми"
 * Автор на кода: Иван Ивайлов Милев Факултетен №: 121218022, КСИ, ФКСТ група 52Б
 * Date: 12.05.2020
 * Author: Ivan Ivaylov Milev
 */
#include <iostream>
#include <queue>

using namespace std;

/*
 * Задача №2:
 * Да се състави алгоритъм, който намира броя на седловите точки на даден двумерен масив. Седлова точка на двумерен масив е такъв
 * елемент, който едновременно е минимален за стълба и максимален за реда, в който се намира или обратно. Освен това за да бъде точката
 * седлова, то в съответния ред или стълб не трябва да има друг елемент със същия екстремум.
 */
int* max_in_row(int* arr, int size) {
	int max[2]; // 0 индекс отговаря за максималната стойност, на индекс 1 ще пазим индекса на максимума
	bool duplicate_min = false;
	for (int i = 0; i < size; i++) {
		if (i == 0) {
			// инициализираме масива при първата опиколка
			max[0] = arr[i];
			max[1] = i;
			continue;
		}
		// отбелязваме ако има дупликат на "моментния" максимум
		if (max[0] == arr[i]) {
			duplicate_min = true;
		}
		// Проверка дали за нов максимум, ако има такъв го запазваме
		if (max[0] < arr[i]) {
			duplicate_min = false;
			max[0] = arr[i];
			max[1] = i;
		}
	}
	// По условеи за да имаме абсолютен максимум(без дупликати)
	if (duplicate_min) {
		throw "Duplicate minimum in rows";
	}

	return max;
}

template <size_t rows, size_t cols>
bool is_min_in_col(int(&arr)[rows][cols], int min, int col) {
	int visits = 0;
	// итерираме през елементите на една колона и проверяваме дали търсеният елемент е минимум
	for (int i = 0; i < rows; i++) {
		if (min > arr[i][col]) {
			return false;
		}
		// проверка за дупликати
		if (min == arr[i][col]) {
			visits++;
		}
		if (visits > 1) {
			return false;
		}
	}
	return true;
}

template <size_t rows, size_t cols>
int get_sadle_numbers(int(&arr)[rows][cols]) {
	int counter = 0;
	int* min;
	// итерираме през всички редове 
	for (int i = 0; i < rows; i++) {
		try {
			// взимаме максимума за съответния ред
			min = max_in_row(arr[i], cols);
			// проверяваме дали този максимум е минимум в колоната си
			if (is_min_in_col<rows, cols>(arr, min[0], min[1])) {
				counter++;
			}
		}
		catch (const char* msg) {
			// при намиране на дупликат тук се прихваща изключението и се продължава.
			continue; // just skip
		}
	}
	return counter;
}

void print(int* the_longest, int size) {
	for (size_t i = 0; i < size; i++) {
		cout << the_longest[i] << " ";
	}
	cout << endl;
}

/*
 * Задача №6:
 * Даден е едномерен масив с n елемента. Да се напише програма, която намира броя на намаляващите редици от елементи в масива, тяхната
 * дължина и най-дългата от тях.
 */
void find_consecutive_order(int* arr, int size) {
	int max_consecutive = 0; // дължината на най-дългата поредица
	int number_of_orders = 0; // брой намаляващи редици
	int length = 0; // дължината на моментната редица
	int* the_longest = new int[0]; // масив, който пази най-дългата редица

	// итерира се през масива
	for (int i = 1; i < size; i++) {
		int prev_indx = i - 1;
		// ако новия елемент е по-малък от предходния => има придължение(начала на намаляваща редица)
		if (arr[prev_indx] > arr[i]) {
			length++;
		}
		else { // настъпил е край на намаляващата редица.
			if (length > 1) {
				number_of_orders++;
			}
			length = 1;
		}

		// проверка за това дали моментната редица не е най-дългата
		if (length > max_consecutive) {
			// запис на новата най-дълга редица
			max_consecutive = length;
			delete[] the_longest;
			the_longest = new int[length];
			// copy the longest array;
			for (int k = length - 1; k >= 0; k--) {
				the_longest[k] = arr[i - (length - k - 1)];
			}
		}

		if (i == size - 1 && length > 0) {
			number_of_orders++;
		}
	}
	cout << "Number of orders: " << number_of_orders << endl;
	cout << "The orders with max elements has " << number_of_orders << " elements." << endl;
	print(the_longest, max_consecutive);
	delete[] the_longest;
}

/* Задача 18:
 * Да се напише програма, която намира сумата на четните и нечетните стойности от върховете на дадено двоично дърво.
 */
class Node {
public:
	Node* left;
	Node* right;
	int data;
	Node(int data) :data(data), left(NULL), right(NULL) {
	}

	bool is_leaf() {
		return left == NULL && right == NULL;
	}
};

class Tree {
	// Имплементация на двоично дърво
public:
	Node* root;

	Tree(int data) {
		root = new Node(data);
	}

	// добавяне на нов елемент
	void add_element(int data) {
		Node* new_node = new Node(data);
		Node* curr_el = this->root;
		Node* parent = NULL;
		// търсим правилното листо
		while (curr_el != NULL) {
			// ако новият елемент е по-голям от сегашния, то отиваме в дясната част на под-дървото
			if (curr_el->data > data) {
				parent = curr_el;
				curr_el = curr_el->left;
			}
			// ако новият елемент е по-малък от сегапния, то отиваме в лявата част на под-дървото
			else {
				parent = curr_el;
				curr_el = curr_el->right;
			}
		}

		// след като сме намерили листото, за което трябва да закачим новия елемент, спрямо
		// това дали е по-голямо/по-малко от родителя отива съответно в дясно/ляво
		if (parent->data > data) {
			parent->left = new_node;
		}
		else {
			parent->right = new_node;
		}
	}
};

/* Задача 18:
 * Да се напише програма, която намира сумата на четните и нечетните стойности от върховете на дадено двоично дърво.
 */
int* sums_of_leafs(Tree* tree) {
	Node* root = tree->root;
	int odds_sum = 0;
	int evens_sum = 0;
	queue<Node*> visit;
	visit.push(root); // добавяме корена на дървото
	// дървото се обхожда в широчина(BFS)
	while (!visit.empty()) {
		// взимаме следващият елемент от опашката
		Node* curr = visit.front();
		visit.pop();

		// ако елемента до който сме стигнали е краен(листо) добавяме към съответната сума неговата стойност.
		if (curr->is_leaf()) {
			odds_sum += curr->data % 2 == 1 ? curr->data : 0;
			evens_sum += curr->data % 2 == 0 ? curr->data : 0;
		}
		// за всеки елемент се добавят неговите деца(ако има такива)
		if (curr->left != NULL) {
			visit.push(curr->left);
		}
		if (curr->right != NULL) {
			visit.push(curr->right);
		}
	}
	// правим и връщаме резултата с двете суми
	int res[2] = { odds_sum, evens_sum };

	return res;
}

int main() {
	// 3, 8, 18, 21, 23
	int array[27] = { 5, 4, 3, 10, 12, 14, 10, 1, 2, 3, 8, 7, 6, 5, 4, 3, 2, 1, 25, 23, 19, 40, 33, 4, 5, 7, 8 };
	int arr[5][5] = {
		{1, 1, 3, 4, 5},
		{2, 3, 4, 5, 6},
		{3, 4, 5, 1, 7},
		{4, 5, 1, 2, 8},
		{5, 1, 2, 3, 9}
	};
	find_consecutive_order(array, 27);
	cout << "Number of saddle points: " << get_sadle_numbers<5, 5>(arr) << endl;


	Tree* tree = new Tree(2);
	tree->add_element(6);
	tree->add_element(9);
	tree->add_element(10);
	tree->add_element(4);
	tree->add_element(7);
	tree->add_element(12);
	tree->add_element(5);

	int* a = sums_of_leafs(tree);
	cout << "odds = " << a[0] << " evens = " << a[1] << endl;
	return 0;
}
