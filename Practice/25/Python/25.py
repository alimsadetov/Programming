def isSorted(lst, order):
	if len(lst) <= 1:
		return True;
	for i in range(1, len(lst)):
		if order:
			if (lst[i] < lst[i-1]): return False
		else:
			if (lst[i] > lst[i-1]): return False
	return True

@dispatch(int, int, int, bool)
def BozoSort(a, b, c, order):
	return BozoSort([a, b, c], order)

lst = list(map(int, input('Введите массив: ').split()))
lst2d = make2dlist(lst)

original_lst = []
original_lst.extend(lst)
print(original_lst)
print('• Отсортированный массив целых чисел: \n')
print(BozoSort(lst, True))
print(BozoSort(lst, False))
print('\n')

print('• Отсортированный двумерный массив целых чисел: \n')
print(BozoSort(lst2d, True))
print(BozoSort(lst2d, False))
print('\n')

lst = original_lst
print('• Отсортированные значения трех отдельных чисел: \n')
print(BozoSort(lst[0], lst[1], lst[2], True))
print(BozoSort(lst[0], lst[1], lst[2], False))