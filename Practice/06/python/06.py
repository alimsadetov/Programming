print("введите далее отдельно в каждой строчке a,b,c")
a=float(input())
b=float(input())
c=float(input())
d=b*b-4*a*c #нахождение дискриминанта
if a!=0: #решение уравнения если оно квадратное
    if b!=0:
        if d<0:
            print("ответов нет")
        if d==0:
            print("x=",-b/(2*a))
        if d>0:
            print('x1=',(-b+d**0.5)/(2*a))
            print('x2=',(-b-d**0.5)/(2*a))
    else:
        print('x=',(-c/a)**0.5)
else: #решение уравнения если оно линейное
    if b!=0:
        print('x=',-c/b)
    else:
        print('это не уравнение')