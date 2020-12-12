#include <iostream>
#include <vector>


using namespace std;

//сортировка массива
vector<int> BozoSort(vector<int> array, bool isAscending = true)
{
	bool sorted = false;
	int len = array.size();

	while (!sorted)
	{
		//сама сортировка по возрастанию
		if (isAscending)
		{
			swap(array[rand() % len], array[rand() % len]);
			sorted = true;

			for (int i = 1; i < len; i++)
			{
				if (array[i - 1] > array[i])
				{
					sorted = false;
					break;
				}
			}
		}

		//сортирвка по убыванию
		else
		{
			swap(array[rand() % len], array[rand() % len]);

			sorted = true;

			for (int i = 1; i < len; i++)
			{
				if (array[i - 1] < array[i])
				{
					sorted = false;
					break;
				}
			}
		}
	}

	return array;
}

//сортировка матрицы
vector<int> BozoSort(vector<vector<int>> matrix, bool isAscending = true)
{
	vector<int> arr;
	for (auto& row : matrix)
	{
		for (auto item : row)
		{
			arr.push_back(item);
		}
	}
	return BozoSort(arr, isAscending);
}

//сортировка трёх первых чисел массива
vector<int> BozoSort(int first, int second, int third, bool isAscending = true)
{
	vector<int> arr{ first, second, third };
	return BozoSort(arr, isAscending);
}

//вывод векторов
void CoutVector(vector<int> arr)
{
	for (auto item : arr)
	{
		cout << item << " ";
	}
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int n, koren;
	cout << "Введите количество элементов n:\n";
	cin >> n;
	koren = sqrt(n);
	vector<int> masiv(n);    //создание одномерного массива
	vector<vector<int>> matrix(koren, vector<int>(koren));     //создание двумерного массива

	cout << "Введите значения массива\n";
	for (int i = 0; i < n; i++)        //заполнение массива введёнными данными
	{
		cin >> masiv[i];
	}

	int i = 0;
	while (i < n)    //заполнение двумерного массива введёнными данными
	{
		for (int j = 0; j < koren; j++)
		{
			for (int k = 0; k < koren; k++)
			{
				matrix[j][k] = masiv[i];
				i++;
			}
		}
	}


	//вывод всех векторов через функцию
	CoutVector(BozoSort(masiv));
	CoutVector(BozoSort(masiv, false));
	CoutVector(BozoSort(matrix));
	CoutVector(BozoSort(matrix, false));
	CoutVector(BozoSort(masiv[0], masiv[1], masiv[2]));
	CoutVector(BozoSort(masiv[0], masiv[1], masiv[2], false));
}