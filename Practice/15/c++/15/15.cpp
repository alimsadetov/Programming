// 15.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    setlocale(0, "");
    cout << "привет введи число\n";
    int x=1, i=0, chislo, n;
    while (x == 1) {
        chislo = rand() % 101;
        for (i = 0; i <= 4; i++) {
            cin >> n;
            if (i == 4) {
                if (n == chislo) {
                    cout << "пмпоздравляю, вы угадали ";
                    break;
                }
                else {
                    cout << "вы програли. было загадано: " << chislo<<"\n";
                    break;
                }
            }
            if (n > chislo) cout << "загаданное число меньше ";
            if (n < chislo) cout << "загаданное число больше ";
            if (n == chislo) {
                cout << "поздравляю число успешно угадано"; break;
            }
            
        }
        cout << "хотите сыграть ещё раз? (1-ДА)";
        cin >> x;
    }
}

