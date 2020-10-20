#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    double chislo1, chislo2;
    char znak;
    cout << "введите в следующей строке через пробел первое число знак и второе число\n";
    cin >> chislo1 >> znak >> chislo2;
    if (int(znak) == 43) cout << chislo1 + chislo2; //проверка знака по ascii коду
    if (int(znak) == 45) cout << chislo1 - chislo2;
    if (int(znak) == 42) cout << chislo1 * chislo2;
    if (int(znak) == 47) {
        if (chislo2 != 0) cout << chislo1 / chislo2;
        else cout << "нельзя делить на нол";
    }
}