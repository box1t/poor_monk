p, q = map(int, input().split())
    
if p < 2 * q or p % q != 0:
    print(-1)
else:
    print(*sorted([q, p - q], reverse=True))

