#include <iostream>
#include "factorial.h"
#include "sinus.h"
#include "sochetaniya.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    int i;
    cout << "выводим таблицу факториалов:\n";
    for (i = 1; i <= 10; i++) {
        cout << i<<"       "<<factor(i)<<"\n";     //вывод таблицы факториалов
    }
}