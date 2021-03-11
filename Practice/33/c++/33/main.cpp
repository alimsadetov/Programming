#include <iostream>

using namespace std;



int* create(int size, int flag = 0, int shag = 0) {
    int* list = new int[size];

    for (int i = 0; i < size; i++)
    {
        list[i] = flag;
        flag += shag;
    }


    return list;
}




void sort(int* list, int size) {
    for (int i = 1; i < size; i++)
    {
        int temp = list[i];
        int element = i - 1;
        while(element >= 0 && list[element] > temp)
        {
            list[element + 1] = list[element];
            list[element] = temp;
            element--;
        }
    }
}






int* print(int* list, int size) {
    cout << '[';
    for (int i = 0; i < size; i++)
    {
        cout << list[i];


        if (i < size - 1)
        {
            cout <<", ";
        }
    }

    cout << ']' << endl;

    return list;
}















int main() {
    int size, flag, shag;

    cin >> size >> flag >> shag;


    int* list = create(size, flag, shag);
    sort(list, size);
    print(list, size);



    delete[] list;



    return 0;
}
