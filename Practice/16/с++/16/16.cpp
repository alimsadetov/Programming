#include <iostream>
using namespace std;
const string pattern = "a???55661";    //собственно паттерн
bool isSimvol(char s) {               //это проверка на символы (по условию могут быть только латинские буквы или цифры)
	return ((48 <= int(s) && int(s) <= 57) ||
		(97 <= int(s) && int(s) <= 122));
}
bool isBiletSuslika(string s) {                      // функция проверки билета на искомость (билет суслика)
	if (s.length() != pattern.length())  //проверка по паттерну длины (паттерн выше)
		return false;
	bool b = true;
	for (int i = 0; i < pattern.length(); i++) {
		if (pattern[i] == '?') {
			b = b and isSimvol(s[i]); //проверка на символы
		}
		else {
			b = b and (s[i] == pattern[i]); //сравнение с символами паттерна
		}
		if (!b) break;
	}
	return b;
}


int main() {
	setlocale(LC_ALL, "RUSSIAN");
	int n;
	cout << "Введите количество билетов N: ";
	cin >> n;
	bool isBiletiSuslikaSushestvuyut = false;   //false - если нет искомых билетов
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		if (isBiletSuslika(s)) {
			cout << s << " ";
			isBiletiSuslikaSushestvuyut = true;
		}
	}
	if (!isBiletiSuslikaSushestvuyut)
		cout << -1;
}