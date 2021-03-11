#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;


struct IntArray {
    int *data;
    int size;
};




void check_null(void* ptr){
    if (ptr == nullptr){
        cerr << "Разыменовывание нулевого указателя." << endl;
        exit(-1);
        return;
    }
}

void create(IntArray& arr, const int size){
    if (size <= 0){
        cerr << "Невозможно создать массив с размером '" << size << "' так как он является отрицательным" << std::endl;
        return;
    }

    arr.data = new int[size];

    if (!arr.data){
        cerr << "Невозможно создать массив с размером " << size << endl;
        return;
    }

    arr.size = size;
}



void create(IntArray* arr, const int size){
    check_null(arr);
    create(*arr, size);
}



int get(IntArray& arr, const int index){
    if (index < 0 || index >= arr.size){
        cerr << "Индекс за пределами массива. Размер массива: " << arr.size << "Полученный индекс: " << index << endl;
        exit(-1);
        return -1;
    }

    return arr.data[index];
}



int get(IntArray* arr, const int index){
    check_null(arr);
    return get(*arr, index);
}



void set(IntArray& arr, const int index, const int value){
    if (index < 0 || index >= arr.size){
        cerr << "Индекс за пределами массива. Размер массива: " << arr.size << "Полученный индекс: " << index << endl;
        exit(-1);
        return;
    }

    arr.data[index] = value;
}



void set(IntArray* arr, const int index, const int value){
    check_null(arr);
    set(*arr, index, value);
}





void print(IntArray& arr){
    cout << '[';
    for (int i = 0; i < arr.size; i++){
        cout << arr.data[i];

        if (i < arr.size - 1){
            cout <<", ";
        }
    }

    cout << ']' << endl;
}




void print(IntArray* arr){
    check_null(arr);
    print(*arr);
}

void resize(IntArray& arr, const int newSize){
    if (newSize < 0){
        return;
    }

    if (newSize == arr.size){
        return;
    }

    if (newSize > arr.size){
        int* newArr = new int[newSize];

        if (!newArr){
            cerr << "Невозможно создать массив с размером " << newSize << endl;
            return;
        }

        memcpy(newArr, arr.data, sizeof(int) * arr.size);

        for (int i = arr.size; i < newSize; ++i){
            newArr[i] = 0;
        }

        delete[] arr.data;

        arr.data = newArr;
        arr.size = newSize;

        return;
    }

    int* newArr = new int[newSize];

    if (!newArr){
        cerr << "Невозможно создать массив с размером " << newSize << endl;
        return;
    }

    memcpy(newArr, arr.data, sizeof(int) * newSize);

    delete[] arr.data;
    arr.data = newArr;
    arr.size = newSize;
}

void resize(IntArray* arr, const int newSize){
    check_null(arr);
    resize(*arr, newSize);
}

void destroy(IntArray& arr){
    if (!arr.data){
        return;
    }

    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
}

void destroy(IntArray* arr){
    check_null(arr);
    destroy(*arr);
}

int main(){
    setlocale(LC_ALL, "Russian");
    constexpr int size = 30;



    IntArray arr;

    create(arr, size);

    for (int i = 0; i < size; i++){
        set(arr, i, i + 1);
    }

    print(arr);

    resize(arr, 50);
    print(arr);

    resize(arr, 10);
    print(arr);

    destroy(arr);

    return 0;
}
