
n = int(input())

maxnum = 0
minnum = 9
while n != 0:
    if n % 10 > maxnum:
        maxnum = n % 10
    if n % 10 < minnum:
        minum = n % 10
    n = n // 10


print("Максимальная цифра равна", maxnum,
"Минимальная цифра равна", minnum)
