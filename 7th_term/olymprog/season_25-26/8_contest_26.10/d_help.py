s1, s2, s3 = input().strip(), input().strip(), input().strip()

i = 0
j = 0
k = 0
res = []

while i < len(s1) or j < len(s2) or k < len(s3): 
    if i < len(s1) and j < len(s2) and s1[i] == s2[j]: # ограничение выхода за гр. массива
        res += s1[i]
        i += 1
        j += 1 
        # continue
    if i < len(s1) and k < len(s3) and s1[i] == s3[k]:
        res += s1[i]
        i += 1
        k += 1 
        # continue
    if j < len(s2) and k < len(s3) and s2[j] == s3[k]:
        res += s2[j]
        j += 1
        k += 1
        # continue
print(''.join(res))
