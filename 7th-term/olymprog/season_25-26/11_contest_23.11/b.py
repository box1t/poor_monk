# https://gemini.google.com/app/982cacf144ca705b - b

n, q = map(int, input().split())

for _ in range(q):
    a = int(input())
    if a == 0:
        print(0)
        continue
    
    target = abs(a)
    if target % 2 == 0:
        print(-1)
        continue
    
    k = 0 
    mx_len = 0 
    jump_len = 1

    while mx_len < target:
        k += 1
        mx_len += jump_len
        jump_len *= 2
        
    print(k)
