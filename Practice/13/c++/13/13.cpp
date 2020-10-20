// 13.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

int main()
{
    setlocale(0, "");
    cout << "введите число\n";
    int k, a, i;
    cin >> a;
    k = 0;
    for (i = 2; i <= (a / 2); i++) /*проверка на простоту*/ {
        if (a % i == 0) { k = k + 1; }
    } 
    if (k <= 0) cout << "число простое"; else cout << "число сложное";
}

