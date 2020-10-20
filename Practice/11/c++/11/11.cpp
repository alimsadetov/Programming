// 11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    double a, chislo;
    int stepen,i;
    cout << "далее в отдельных строкав введите число и степень\n";
    cin >> a;
    cin >> stepen;
    chislo = a;
    for (i = 1; i <= stepen - 1; i++) {
        chislo = chislo * a;
    }
    cout << chislo;
}
