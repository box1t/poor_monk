
n, t = map(int, input().split())
a = list(map(int, input().split()))

if t < sum(a):
    print(0)
else:
    res = 1 + (t - sum(a)) // max(a)
    print(res)