n = int(input('Введите n: '))

arr = 5*[float("inf")]
numbers = list(map(int, input('теперь введите n чисел: ').split()))


for i in range(len(numbers)):
	#добавление элементов
	if max(arr) > numbers[i]:
		arr += [numbers[i]]
		arr.sort()
		if len(arr) > 5:
			arr.pop()
	#вывод
	for j in range(len(arr)-1, -1, -1):
		if arr[j] != float("inf"): print(arr[j], end=' ')
	print()