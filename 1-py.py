str1, str2 = set(map(int, input().split())), set(map(int, input().split()))
s3 = str1.intersection(str2)
print(*sorted(s3, reverse=False))
