// 26.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

template <typename T>
std::vector<T> BozoSort(std::vector<T> arr, bool bl = 1) {
    bool chkr = 1;
    while (chkr) {

        long r1 = rand() * arr.size() / RAND_MAX;
        long r2 = rand() * arr.size() / RAND_MAX;

        T tmp = arr[r1];
        arr[r1] = arr[r2];
        arr[r2] = tmp;

        if (bl) {
            bool tmpb = 1;
            for (auto i = arr.begin(); i != arr.end() - 1; i++)
                if (*i > *(i + 1)) {
                    tmpb = 0;
                    break;
                }
            chkr = !tmpb;
        }
        else {
            bool tmpb = 1;
            for (auto i = arr.begin(); i != arr.end() - 1; i++)
                if (*i < *(i + 1)) {
                    tmpb = 0;
                    break;
                }
            chkr = !tmpb;
        }
    }

    return arr;
}

template <typename T>
std::vector <std::vector<T>> bozoSort(std::vector<std::vector<T>> arr, bool bl = 1) {
    const int m = arr.size();
    const int n = arr[0].size();

    bool checker = 1;
    while (checker) {
        int rand_1_1 = rand() * n / RAND_MAX;
        int rand_1_2 = rand() * m / RAND_MAX;
        int rand_2_1 = rand() * n / RAND_MAX;
        int rand_2_2 = rand() * m / RAND_MAX;

        T tmp = arr[rand_1_2][rand_1_1];
        arr[rand_1_2][rand_1_1] = arr[rand_2_2][rand_2_1];
        arr[rand_2_2][rand_2_1] = tmp;

        if (bl) {
            bool tmpb = 1;
            T prev = arr[0][0];
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++) {
                    if (prev > arr[i][j]) {
                        tmpb = 0;
                    }
                    prev = arr[i][j];
                }
            checker = !tmpb;
        }
        else {
            bool tmpb = 1;
            T previousNumber = arr[0][0];

            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++) {
                    if (previousNumber < arr[i][j]) {
                        tmpb = 0;
                    }
                    previousNumber = arr[i][j];
                }
            checker = !tmpb;
        }
    }

    return arr;
}

template <typename T>
std::vector<T> bozoSort(T a, T b, T c, bool bl = 1) {
    std::vector<T> lst;
    lst.push_back(a);
    lst.push_back(b);
    lst.push_back(c);
    return bozoSort(lst, bl);
}

template <typename T>
void printVector(std::vector<T> vec) {
    for (auto i = vec.begin(); i != vec.end(); i++) {
        std::cout << *i << ' ';
    } std::cout << '\n';
}




template <typename T>
void printVector(std::vector<std::vector<T>> vec) {
    for (auto i = 0; i < vec.size(); i++) {
        for (auto j = 0; j < vec[i].size(); j++) {
            std::cout << vec[i][j] << ' ';
        }
    } std::cout << '\n';
}


int main()
{
    setlocale(LC_ALL, "RUSSIOAN");
    srand(time_t(NULL));
    int n;
    std::cout << "vvedite n: ";
    std::cin >> n;
    std::vector<double> lst(n);

    auto lst1 = BozoSort<double>(lst);


    return 0;
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
