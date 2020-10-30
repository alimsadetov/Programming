n=int(input("введите колво билетов: "))
bileti=list(map(str,input().split())) #заполняем массив всеми введёнными билетами
bileti_suslika=[] # ввод массив будем добавлять искомые билеты (билеты суслика)
kolvo=0 #количество искомых билетов
for i in bileti: # проверка каждого билета на соответствие условиям
    if i[0]=="a" and i[4]=="5" and i[5]=="5" and i[6]=="6" and i[7]=="6" and i[8]=="1":
        kolvo+=1
        bileti_suslika+=[i]
if kolvo==0:
    print(-1)
else: #вывод искомых билетов
    for i in bileti_suslika:
        print(i,end=" ")

