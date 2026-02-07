
s = input()
cnt = {}
for c in s:
    if c in cnt:
        cnt[c] += 1
    else:
        cnt[c] = 1

flag_odd = False
for c in cnt:
    if cnt[c] % 2 != 0:
        if flag_odd:
            print("No")
            exit()
        flag_odd = True
print("Yes")
