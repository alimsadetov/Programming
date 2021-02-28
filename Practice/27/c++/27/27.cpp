// 27.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>



void sort(int* arr, int n = 5) {

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temporary = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temporary;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    int n;
    std::cout << "vvedite n: ";
    std::cin >> n;
    int* lst = new int[5];

    for (int i = 0; i < 5; i++) {
        lst[i] = -1;
    }


    if (n <= 5) {
        for (int i = 0; i < n; i++) {
            std::cin >> lst[i];
            sort(lst);

            for (int j = 0; j < i + 1; j++) {
                std::cout << lst[j] << ' ';
            }
            std::cout << '\n';
        }
    }
    else {
        for (int i = 0; i < 5; i++) {
            std::cin >> lst[i];
            sort(lst);

            for (int j = 0; j < i + 1; j++) {
                std::cout << lst[j] << ' ';
            }
            std::cout << '\n';
        }

        for (int i = 5; i < n; i++) {
            int cin;
            std::cin >> cin;

            bool ifSorted = true;

            for (int j = 4; j >= 0; j--) {
                if (cin < lst[j]) {
                    lst[0] = cin;
                    ifSorted = false;
                    break;
                }
            }
            if (!ifSorted) {
                sort(lst);
            }

            for (int j = 0; j < 5; j++) {
                std::cout << lst[j] << ' ';
            }
            std::cout << '\n';
        }
    } delete[] lst;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
