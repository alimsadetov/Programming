

#include <iostream>
using namespace std;
// Принимает вес в килограммах и рост в метрах. Возвращает индекс массы тела. 
double BMI(double weight, double height) {
    return (weight / ((height / 100) * (height / 100))); //рост в метрах, поэтому делим на сто
}
// Принимает численное значение ИМТ и печатает на экран соответствующую категорию
void printBMI(double BMI) {
    if (BMI < 18.5)
        cout << "Underweight";
    if ((BMI >= 18.5) and (BMI < 25.0))
        cout << "Normal weight";
    if ((BMI < 30.0) and (BMI >= 25.0))
        cout << "Overweight";
    if (BMI > 30.0)
        cout << "Obesity";
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    double a, b;
    cin >> a >> b;
    printBMI(BMI(a, b));
}

