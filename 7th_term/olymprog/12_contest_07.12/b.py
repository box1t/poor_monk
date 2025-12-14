
T = int(input())
for _ in range(T):
    x, n = map(int, input().split())
    if n == 1:
        print(x)
        continue
 
    a = x // (2 * n - 2)
    cnt = [0] * n
    for i in range(n):
        if i == 0 or i == n - 1:
            cnt[i] = a
        else:
            cnt[i] = 2 * a
 
    curr = 0
    d = 1
    r = x % (2 * n - 2)
    for i in range(r):
        cnt[curr] += 1
        curr += d
        if curr == n - 1 or curr == 0:
            d *= -1
 
    print(' '.join(map(str, cnt)))


