
T = int(input())
for _ in range(T):
    x, n = map(int, input().split())
    
    ans = [0] * n
    full_part = x // n 
    rem = x % n
    if n > x:
        print("-1")
        continue

    for i in range(n - rem):
        ans[i] = full_part
    for i in range(n - rem, n):
        ans[i] = full_part + 1
    print(*ans)

# T = int(input())
# for _ in range(T):
#     x, n = map(int, input().split())
    
#     if n > x:
#         print(-1)
#         continue
    
#     res = [x // n] * (n - (x % n)) + [(x // n) + 1] * (x % n)
#     print(" ".join(map(str, res)))
