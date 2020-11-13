#include <iostream>
#include "factorial.h"
#include "sinus.h"
#include "sochetaniya.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    int i;
    cout << "n\t" << "n!\n";
    for (i = 1; i <= 10; i++) {
        cout << i<<"\t"<<factor(i)<<"\n";     //вывод таблицы факториалов
    }




    //вывод таблицы синусов
    const float p = 3.141592653589;
    cout <<"\n"<< "x\t\t\t" << "sin(x)\n";
    float x;
    for (x = 0; x <= (p / 4); x += p / 180) {
        cout << x << "\t\t\t" << sinus(x, 5) << "\n";
    }




    //вывод таблицы сочетаний
    cout << "\nk\t" << "C(k,10)\n";
    int k;
    for (k = 1; k <= 10; k++) {
        cout << k << "\t" << soch(k, 10) << "\n";
    }
}