import random

def BozoSort1(arr, isAscending=True):
	sorted = False
	n = len(arr)

	while sorted==False:
		if isAscending:
			x=random.randint(n)
			y=random.randint(n)
			arr[x],arr[y]=arr[y],arr[x]
			sorted = True
			for i in range(1, n):
				if (arr[i - 1] > arr[i]):
					sorted = False
					break
		else:
			x=random.randint(n)
			y=random.randint(n)
			arr[x],arr[y]=arr[y],arr[x]
			for i in range(1,n):
				if (arr[i - 1] < arr[i]):
					sorted = False
					break
	return arr

def BozoSort2(matrix, isAscending=True):
	res = []
	for x in matrix:
    	res.extend(x if isinstance(x, list) else [x])
	return BozoSort1(res)

def BozoSort3(a, b, c, isAscending = True):
	arr=[a, b, c]
	return BozoSort1(arr, isAscending)

print('введите колво элементов\n')
n=int(input())
print('введите сами элементы через пробел')
arr=[]
for i in range(n):
	arr+=[int(input())]
matrix=[[]]
i=0
while i<n:
	for k in range(n**0.5):
		for f in range(n**0.5):
			matrix[k][f]+=[arr[i]]
print(Bozosort1(arr))
print(Bozosort1(arr, False))
print(Bozosort2(matrix))
print(Bozosort2(matrix, False))
print(Bozosort1(arr[0],arr[1],arr[2]))
print(Bozosort1(arr[0],arr[1],arr[2], False))