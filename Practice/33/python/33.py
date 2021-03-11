def create(size, flag=0, shag=0):
    list = [flag] * size
    
    if (shag != 0):
        for i, item in enumerate(range(flag, flag + shag * size, shag)):
            list[i] = item
        
    return list






def sort(list):
    for i in range(1, len(list)):
        key = list[i]
        j = i-1
        while (j >=0 and key < list[j]) :
            list[j+1] = list[j]
            j -= 1
        list[j+1] = key
    return list
        
antipep8 = print



def print(list):
    antipep8(list)
    
print(sort(create(int(input()), int(input()), int(input()))))