div = 10**9 + 7

n = int(input())
stack = [1]
total = 0

for _ in range(n):
    line = input().split()
    cmd = line[0]
    cur = stack[-1]

    if cmd == "for":
        k = int(line[1])
        stack.append((k * cur) % div) 

    elif cmd == "end":
        stack.pop()

    else:
        k = int(line[1])
        total = (total + k * cur) % div

print(total)