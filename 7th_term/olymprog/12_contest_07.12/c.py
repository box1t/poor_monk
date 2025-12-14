# n, x = int(input()), int(input())
# newlst = list(n)

# if x % 2 == 0:
#     for i in range(n, 1, -1):
#         del newlst[i]
# else:
#     for i in range(n, 1, -1):
#         del newlst[i]

# пусть x = 4
# пусть n = 10
# на вход подаем то, что должно остаться -> идем с конца
# если после del остаётся четное, это значит, что
# если после del остаётся нечетное, это значит, что 

n = int(input())
x = int(input())

lsst = []
for i in range(n):
    lsst.append(i)

if x % 2 == 0:
    for i in range(n, 1, -1):
        del lsst[i]

if x % 2 == 1:
    for i in range(n - 1, 0, -1):
        del lsst[i]

# for i in range(n, 0, -1):


# for i in range(n, 0, -1):
#     del

