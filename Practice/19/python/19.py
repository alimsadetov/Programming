def DFS(original, new, queue, n):
	if sum(queue) == n:
		if not 0 in queue:
			print(new, end=' ')
		return
	for i in range(len(queue)):
		queue[i] += 1
		DFS(original, new+original[i], queue, n)
		queue[i] -= 1

n = int(input('Введите количество символов: '))
s = input('Введите символы: ')
queue = len(s)*[0]
DFS(s, '', queue, n)