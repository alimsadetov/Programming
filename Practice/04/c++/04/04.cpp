#include <iostream>
using namespace std;
int main()
{
	setlocale(0, "");
	cout << "введите два числа через пробел\n";
	int a, b, obmen;
	cin >> a >> b;
	obmen = a; a = b; b = obmen;
	cout << "После обмена первое число= " << a << ", второе= " << b << "\n"; //первый способ
	cout << "введите два числа\n";
	cin >> a >> b;
	a += b; b = a - b; a -= b;
	cout << "После обмена первое число=  " << a << ", второе= " << b << "\n"; //второй способ
}