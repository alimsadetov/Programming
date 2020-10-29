#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	char dvoetochie;
	int h1, m1, h2, m2;
	cout << "Введите время начальное: ";
	cin >> h1 >> dvoetochie >> m1;
	cout << "Введите время конечное: ";
	cin >> h2 >> dvoetochie >> m2;
	m1 = (h1 * 60) + m1; //перевод времени в минуты
	m2 = (h2 * 60) + m2;
	if (abs(m2 - m1) <= 15) //сравнение первого времени в минутах и второго
		cout << "Встреча состоится\n";
	else
		cout << "Встреча так и не состоится\n";
}