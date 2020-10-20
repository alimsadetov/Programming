

#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    cout << "далее в отдельных строчках введите время1 и время2\n";
    char vremya1[5], vremya2[5];
    int schetchik1, schetchik2, vremyavminutah1,vremyavminutah2 ;
    cin >> vremya1;
    cin >> vremya2; 
    schetchik1 = strlen(vremya1); //считаем колво символов во временах
    schetchik2 = strlen(vremya2);
    if (schetchik1 == 5) { //далее переводим первое и второе времена в минуты 
        vremyavminutah1 = int(vremya1[1] + vremya1[2]) * 60 + int(vremya1[4] + vremya1[5]);
    }
    else vremyavminutah1 = int(vremya1[1]) * 60 + int(vremya1[3] + vremya1[4]);
    if (schetchik2 == 5) {
        vremyavminutah2 = int(vremya2[1] + vremya2[2]) * 60 + int(vremya2[4] + vremya2[5]);
    }
    else vremyavminutah2 = int(vremya2[1]) * 60 + int(vremya2[3] + vremya2[4]);
      if ((vremyavminutah2 - vremyavminutah1) <= 15) cout << "встреча состоится"; //вычиатем из второго времени первое
      else cout << "встреча не состоится";
}