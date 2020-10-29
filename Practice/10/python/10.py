s, l1, r1, l2, r2 =  input('Введите числа s, l₁, r₁, l₂, r₂:\n').split()
x = int(l1)
y = int(r2)

if x + y < int(s):
  x = min(int(s)-y, int(r1))
else:
  y = max(int(s)-x, int(l2))

if x + y == int(s):
  print(x, y)
else:
  print(-1)