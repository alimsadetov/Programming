// 07.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    int zapuskprogrami;
    cout << "введите 1 или 2 для решения задачи угодным вам способом\n";
    cin >> zapuskprogrami;
    if (zapuskprogrami == 1) {
        double s, a, b, c;
        cout << "введите через пробел стороны треугольника";
        cin >> a >> b >> c;
        s = ((a + c + b) / 2 * ((a + c + b) / 2 - a) * ((a + c + b) / 2 - b) * ((a + c + b) / 2 - c));
        if (s <= 0) cout << "такого треугольника не существует в природе";
        else cout << "s=" << sqrt(s);
    }
    if (zapuskprogrami == 2) {
        cout << "введите дальше через пробел в отдельных строчках координаты х и у для трёх вершин треугольника";
        double s, x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1;
        cin >> x2 >> y2;
        cin >> x3 >> y3;
        s = abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2;
        if (s <= 0) cout << "не существует такого треугольника";
        else cout << "s=" << s;
    }
    if (zapuskprogrami != 1 and zapuskprogrami != 2) cout << "перезапустите программу, в условии написано же написать 1 или 2";
}

