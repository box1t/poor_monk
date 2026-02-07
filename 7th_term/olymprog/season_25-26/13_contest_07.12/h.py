n, k = map(int, input().split())
a = list(map(int, input().split()))
    
ma = max(a)
    
cnt = [0] * (ma + 1)
for x in a:
    cnt[x] += 1
    
res = 0
for d in range(k + 1, ma + 1):
    if cnt[d] == 0:
        continue
    
    curr = 0
    if k == 0:
        s = d
    else:
        s = k
    for x in range(s, ma + 1, d):
        curr += cnt[x]
    res += curr * cnt[d]
print(res)

