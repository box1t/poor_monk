
from itertools import permutations

d = list(map(int, input().split()))
# Номера граней: 0=top, 1=bottom, 2=left, 3=right, 4=front, 5=back

# Соседство граней (индексы)
adj = {
    0: {2, 3, 4, 5},
    1: {2, 3, 4, 5},
    2: {0, 1, 4, 5},
    3: {0, 1, 4, 5},
    4: {0, 1, 2, 3},
    5: {0, 1, 2, 3},
}

max_num = -1

# Перебираем все перестановки 6 граней
for perm in permutations(range(6)):
    valid = True
    for i in range(5):
        if perm[i+1] not in adj[perm[i]]:
            valid = False
            break
    if valid:
        num = int(''.join(str(d[i]) for i in perm))
        max_num = max(max_num, num)

print(max_num)

# https://chatgpt.com/c/69106113-8680-8332-ba13-e61f1b2b0d01
