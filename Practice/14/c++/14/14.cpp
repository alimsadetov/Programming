// 14.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    setlocale(0, "");
    int n, x;
    cin >> n;  //ввод числа
    x = 0;
    while (pow(2, x) /*возведение в степень*/ <= n) x = x + 1;
    cout << x;
}