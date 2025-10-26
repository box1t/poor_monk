c, n = map(int, input().split())

if n > c:
    opt = c + 1
elif n == c:
    opt = c
else:
    opt = 0
print(opt)