a = int(input("Введите число: ")) #ввод
k = 0
for i in range(2, a // 2+1): #проверка на простоту
    if (a % i == 0):
        k = k+1
if (k <= 0):
    print("Число простое")
else:
    print("Число сложное")