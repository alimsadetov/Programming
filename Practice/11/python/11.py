  
a = float(input("Введите число: "))
b = int(input("Введите степень: "))
if (b < 0):
	a = 1/a
	b = -b
chislo = 1
for i in range(b):
	chislo *= a
print(chislo)