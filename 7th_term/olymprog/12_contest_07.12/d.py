N, K = map(int, input().split())
F = list(map(int, input().split()))
    
mf = max(F)
c = [0] * (mf + 1)
for f in F:
    c[f] += 1
    
ds = [0] * (mf + 1)
for i in range(mf + 1):
    s = 0
    j = i
    while j:
        s += j % 10
        j //= 10
    ds[i] = s
    
cm = mf
while cm > 0 and K > 0:
    v = cm
    s = ds[v]
    if c[v] >= K:
        print(s)
        exit()
    K -= c[v]
    vn = v - s
    c[vn] += c[v]
    c[v] = 0
    
    i = v
    while i > 0 and c[i] == 0:
        i -= 1
    cm = i
    
print(0)
