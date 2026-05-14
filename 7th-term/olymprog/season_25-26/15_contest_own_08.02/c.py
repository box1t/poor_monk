import math
n, q = map(int, input().split())
h = list(map(int, input().split()))

for _ in range(q):
    l, r = map(int, input().split())
    
    stable_markers = 0
    
    for i in range(l, r + 1):
        if math.gcd(h[i - 1], i) == 1:
            stable_markers += 1

    print(stable_markers)