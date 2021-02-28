#include <Windows.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 



void vivod(std::vector<int> v) {
	for (int i = 0; i < v.size(); i++) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

void vhod(std::vector<int>& v, int n) {
	v.resize(0);
	for (int i = 0; i < n; i++) {
		int element;
		std::cin >> element;
		v.push_back(element);
	}
}

std::vector<std::vector<int>> makeVector(std::vector<int> v) {
	std::vector<int> tempvec;
	std::vector<std::vector<int>> rez;
	for (int i = 0; i < v.size(); i++) {
		tempvec.push_back(v[i]);
		if ((i + 1) % (int)sqrt(v.size()) == 0) {
			rez.push_back(tempvec);
			tempvec.resize(0);
		}
	}
	return rez;
}

bool isSorted(std::vector<int> v, bool order) {
	if (v.size() <= 1)
		return true;
	for (int i = 1; i < v.size(); i++) {
		if (order) {
			if (v[i] < v[i - 1]) return false;
		}
		else {
			if (v[i] > v[i - 1]) return false;
		}
	}
	return true;
}

//BozoSort std::vector<int>
std::vector<int> BozoSort(std::vector<int> v, bool order = true) {
	srand(time(NULL));
	while (!isSorted(v, order)) {
		int r1 = rand() % v.size();
		int r2 = rand() % v.size();
		std::swap(v[r1], v[r2]);
	}
	return v;
}

//BozoSort 2d vector
std::vector<int> BozoSort(std::vector<std::vector<int>> v2d, bool order = true) {
	std::vector<int> rezvect;
	for (int i = 0; i < v2d.size(); i++) {
		v2d[i] = BozoSort(v2d[i], order);
		for (int j = 0; j < v2d[i].size(); j++) {
			rezvect.push_back(v2d[i][j]);
		}
	}
	return rezvect;
}

//BozoSort 3 values
std::vector<int> BozoSort(int a, int b, int c, bool order = true) {
	std::vector<int> v{ a, b, c };
	return BozoSort(v, order);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	std::vector<int> v;
	std::vector < std::vector<int> > v2d;
	std::cout << "введите колво чисел: ";
	std::cin >> n;
	std::cout << "введите элементы массива: ";
	vhod(v, n);
	v2d = makeVector(v);

	std::cout << std::endl;
	std::cout << "Отсортированный массив чисел: " << "\n\n\n";
	vivod(BozoSort(v, true));
	vivod(BozoSort(v, false));
	std::cout << "\n\n";

	std::cout << "Отсортированная матрица целых чисел: " << "\n\n\n";
	vivod(BozoSort(v2d, true));
	vivod(BozoSort(v2d, false));
	std::cout << "\n\n";

	std::cout << "Отсортированные три числа: " << "\n\n\n";
	vivod(BozoSort(v[0], v[1], v[2], true));
	vivod(BozoSort(v[0], v[1], v[2], false));
}