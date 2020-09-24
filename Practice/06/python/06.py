print("введите далее отдельно в каждой строчке a,b,c")
a=float(input())
b=float(input())
c=float(input())
d=b*b-4*a*c
if d<0:
    print("ответов нет")
if d==0:
    print("x=",-b/(2*a))
if d>0:
    print('x1=',(-b+d**0.5)/(2*a))
    print('x2=',(-b-d**0.5)/(2*a))