def bmi(weight: float, height: float):
    return weight/((height/100)*(height/100)) #рост переводим в метры
def print_bmi(bmi: float):
    if bmi < 18.5:
        print("Underweight")
    if bmi >= 18.5 and bmi<25.0:
        print("Normal weight")
    if bmi < 30.0 and bmi >=25.0:
        print("Overweight")
    if bmi > 30.0:
        print("Obesity")
a,b=input().split()
a=float(a)
b=float(b)
print_bmi(bmi(a,b))
