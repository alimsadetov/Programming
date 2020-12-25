def selection_sort(nums):  
    # Значение i соответствует кол-ву отсортированных значений
    for i in range(len(nums)):
        # Исходно считаем наименьшим первый элемент
        lowest_value_index = i
        # Этот цикл перебирает несортированные элементы
        for j in range(i + 1, len(nums)):
            if nums[j] < nums[lowest_value_index]:
                lowest_value_index = j
        # Самый маленький элемент меняем с первым в списке
        nums[i], nums[lowest_value_index] = nums[lowest_value_index], nums[i]

# Проверяем, что оно работает
# в следующей строчке просто рандомные числа
random_list_of_nums = [126, 84, 33, 201, 111]  
selection_sort(random_list_of_nums)  
print(random_list_of_nums) 