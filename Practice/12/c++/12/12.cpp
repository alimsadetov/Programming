#include <iostream>
using namespace std;

int main()
{
    setlocale(0, "");
    int n, i, otvet;
    cout << "введите в следующей строке число\n";
    cin >> n;
    otvet = 1;
    for (i = 1; i <= n; i++) otvet = otvet * i;
    cout << otvet;
}
