
#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	double x, chislo;
	int y;
	std::cout << "Введите число: ";
	std::cin >> x;
	std::cout << "Введите степень: ";
	std::cin >> y;
	if (y < 0) { //proverka na otricatelnost stepeni
		x = 1 / x;
		y = -y;
	}
	chislo = 1;
	for (int i = 0; i < y; i++) { //sobstvenno vozvedenie
		chislo *= x;
	}
	std::cout << chislo;
}