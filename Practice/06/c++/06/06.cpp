// 06.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    cout << "введите далее отдельно в каждой строчке a,b,c\n";
    double a, b, c, d;
    cin >> a;
    cin >> b;
    cin >> c;
    d = b * b - 4 * a * c;//нахождение дискриминанта
    if (a != 0) { //решение уравнения если оно квадратное
        if (b != 0) {
            if (d < 0) cout << "ответов нет";
            if (d == 0) cout << "x=" << -b / (2 * a);
            if (d > 0) {
                cout << "x1=" << (-b + sqrt(d)) / (2 * a);
                cout << "x2=" << (-b - sqrt(d)) / (2 * a);
            }
        }
        else cout << "x=" << sqrt(-c / a);
    }
    else {
        if (b != 0) cout << 'x=' << -c / b; else cout << "это не уравнениеЭ";
    }

}

