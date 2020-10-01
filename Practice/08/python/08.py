chislo1,znak,chislo2=input().split() #ввод
if znak=='+':
    print(float(chislo1)+float(chislo2)) #сложение
if znak=='-':
    print(float(chislo1)-float(chislo2)) #вычитание
if znak=='*':
    print(float(chislo1)*float(chislo2)) #умножение
if znak=='/': #деление
    if chislo2!='0':
        print(float(chislo1)/float(chislo2))
    else:
        print('ошибка, нельзя на ноль делить')