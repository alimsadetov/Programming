per=int(input())
if per==1:
    a=float(input())
    b=float(input())
    c=float(input())
    print('s=',end='')
    s=((a+c+b)/2*((a+c+b)/2-a)*((a+c+b)/2-b)*((a+c+b)/2-c))
    if s<=0:
        print("не существует такого треугольника")
    else:
        print(s**0.5)
if per==2:
    x1,y1=input().split()
    x2,y2=input().split()
    x3,y3=input().split()
    print('s=',end='')
    s=abs((float(x2)-float(x1))*(float(y3)-float(y1))-(float(x3)-float(x1))*(float(y2)-float(y1)))/2
    if s<=0:
        print('не существует такого треугольника')
    else:
        print(s)
if per!=1 and per!=2:
    print('перезапустите программу')

