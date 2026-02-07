

value_n, value_x = map(int, input().split())
actions_list = []

start = 1
step = 1

while value_n > 1:
    idx_x_cur = (value_x + step - start) // step

    if idx_x_cur % 2 == 0:
        actions_list.append(1)
        start += step
        value_n //= 2

    else:
        actions_list.append(0)
        value_n = (value_n + 1) // 2
    
    step *= 2

print(*actions_list)

# n, x = map(int, input().split())
# k = []
# while n > 1:
#     if x % 2 == 1:
#         k.append(0)
#         x = (x + 1) // 2
#         n = (n + 1) // 2
#     else:
#         k.append(1)
#         x //= 2
#         n //= 2
# print(*k)
