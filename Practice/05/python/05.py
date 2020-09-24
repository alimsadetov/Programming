g=9.8
print('введите х0, v0 и t через пробел')
x,v,t=input().split()
print('расстояние=',float(x)+(float(v)*float(t))-float(g)*float(t)*float(t)/2)