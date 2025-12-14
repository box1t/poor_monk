    
T = int(input())
for _ in range(T):
    x, n = map(int, input().split())
    
    if n > x:
        print(-1)
        continue
    
    res = [x // n] * (n - (x % n)) + [(x // n) + 1] * (x % n)
    print(" ".join(map(str, res)))
