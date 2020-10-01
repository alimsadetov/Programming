import random
print('привет введи число')
x=1 #определитель продолжать игру или нет
i=0 #счётчик попыток
while x==1:
    chislo=random.randint(0,101) #компьютер загадывает число
    for i in range(0,5):
        n=int(input())
        if i==4: #последняя попытка
            if n==chislo:
                print('Поздравляю! Вы угадали')
                break
            else:
                print("Вы проиграли. Было загадано: ",chislo)
                break
        if n>chislo: #сравнения чисел
            print("Загаданное число меньше")
        if n<chislo:
            print("Загаданное число больше")
        if n==chislo:
            print('Поздравляю! Вы угадали')
            break
    x=int(input('Хотите начать сначала? (1 - ДА )'))

