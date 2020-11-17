import math
x=float(input()) #принимаем значение x
e=float(input()) #принимаем значение эпсилон
n=int(input()) #принимаем значение количества выполнений цикла
k=1 #номер итерации
chislitel=x
znamenatel=1
term=chislitel/znamenatel #сюда будет считаться член суммы при итерации k
sum=term #здесь будет считаться сумма
while (abs(term)>e) and (k<=n):    #abs-модуль  
    chislitel=chislitel*x*x   #числитель
    znamenatel=znamenatel+2   #знаменатель
    term=((-1)**k)*chislitel/znamenatel
    k=k+1  #переход к следующей итерации
    sum=sum+term
if sum>math.atan(x):   #сравнение с точным значением
    print("точное значение меньше")
else:
    print("точное значение меньше")
print(x,e,sum)