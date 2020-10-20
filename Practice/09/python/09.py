chas1,minut1=input().split(':') #ввод первого времени
chas2,minut2=input().split(':') #ввод второго времени
if (int(chas2)*60+int(minut2))-(int(chas1)*60+int(minut1))<=15: #переводим время в минуты и выитаем из второго времени первое
    print('встреча состтоится')
else:
    print('встреча не состоится')