#include <iostream>

using namespace std;




int* create(int size, int flag = 0, int shag = 0){
    int* array = new int[size];


    for (int i = 0; i < size; i++){
        array[i] = flag;
        flag += shag;
    }

    return array;
}



void create(int** list, int size, int flag, int shag){
    *list = create(size, flag, shag);
}



void destroy(int** list){
    if (list == nullptr){
        return;
    }

    if (*list){
        delete[] *list;
        *list = nullptr;
    }
}




void sort(int* list, int size){



    for (int i = 1; i < size; i++){
        int temp = list[i];
        int item = i - 1;
        while(item >= 0 && list[item] > temp){
            list[item + 1] = list[item];
            list[item] = temp;
            item--;
        }
    }
}



int* print(int* list, int size){



    cout << '[';
    for (int i = 0; i < size; i++){
        cout << list[i];

        if (i < size - 1){
            cout <<", ";
        }
    }




    cout << ']' << endl;

    return list;
}



int main(){
    int size, flag, shag;

    cin >> size >> flag >> shag;




    int* list;
    create(&list, size, flag, shag);
    sort(list, size);
    print(list, size);
    destroy(&list);


    return 0;
}
