import math
import random


def make2dlist(lst):
	lst2d = []
	tmplst = []
	for i in range(len(lst)):
		tmplst += [lst[i]]
		if (i+1) % math.sqrt(len(lst)) == 0:
			lst2d += [tmplst]
			tmplst = []
	return lst2d 

def isSorted(lst, order):
	if len(lst) <= 1:
		return True
	for i in range(1, len(lst)):
		if order:
			if (lst[i] < lst[i-1]): return False
		else:
			if (lst[i] > lst[i-1]): return False
	return True

def BozoSort(lst, order):
	if type(lst[0]) != list:
		while not (isSorted(lst, order)):
			r1 = random.randint(0, len(lst)-1)
			r2 = random.randint(0, len(lst)-1)

			lst[r1], lst[r2] = lst[r2], lst[r1]
		return lst
	else:
		rezlst = []
		for i in range(len(lst)):
			rezlst.extend(BozoSort(lst[i], order))
		return rezlst


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