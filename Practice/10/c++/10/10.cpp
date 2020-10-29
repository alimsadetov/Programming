
#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int s, l1, r1, l2, r2;
	cout << "Введите числа s, l1, r1, l2, r2:\n";
	cin >> s >> l1 >> r1 >> l2 >> r2;
	int x = l1;
	int y = r2;

	if (x + y < s) {
		x = min(s - y, r1);
	}
	else {
		y = max(s - x, l2);
	}

	if (x + y == s) {
		cout << x << " " << y;
	}
	else {
		cout << -1;
	}
}