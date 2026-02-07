import bisect

def sort_and_pref(arr):
    arr_s = sorted(arr)
    pref = [0] * (len(arr) + 1)
    for i in range(len(arr)):
        pref[i + 1] = pref[i] + arr_s[i]
    return arr_s, pref, pref[len(arr)]
    
def sum_ad(x, sorted_arr, pref, total):
    pos = bisect.bisect_right(sorted_arr, x)
    sum_l = pref[pos]
    return (pos * x - sum_l) + ((total - sum_l) - (len(sorted_arr) - pos) * x)
    
n, m = map(int, input().split())
A = list(map(int, input().split()))
B = list(map(int, input().split()))
    
Bs, Bp, Bt = sort_and_pref(B)
si = 0
for i, a in enumerate(A, 1):
    s = sum_ad(a, Bs, Bp, Bt)
    si += i * s
    
As, Ap, At = sort_and_pref(A)
sj = 0
for j, b in enumerate(B, 1):
    s = sum_ad(b, As, Ap, At)
    sj += j * s
    
print(si - sj)

