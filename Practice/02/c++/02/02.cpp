
#include <iostream>
#include <locale>
using namespace std;

int main()
{
    setlocale(0, "");
    int a = 3, b = 3.14; //b отпадает дробная часть, так как тип инт
    double c = 3, d = 3.14;
    std::cout << a << endl << b << endl << c << endl << d;

}
