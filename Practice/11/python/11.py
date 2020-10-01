a=float(input()) #ввод числа
b=int(input()) #ввод степени
chislo=a
for i in range(1,b): #возведение в степень
    chislo*=a
if chislo%1==0:
    print(int(chislo))
else:
    print(chislo)