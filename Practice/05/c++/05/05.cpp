#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	cout << "введите х0, в0 и т через пробел\n";
	double x0, v0, t, xt; // лучше взять double, так как редко встретишь целые числа у физвеличин
	cin >> x0 >> v0 >> t;
	xt = x0 + v0 * t + 9.8 * t * t / 2; // абсолютно никакой разницы нет между двумя вариантами записи в условии
	cout << "расстояние = " << abs(xt - x0);
}