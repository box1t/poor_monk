n = int(input())
m = int(input())


# 1. Вложенный цикл с .append() (самый понятный для новичка)
mult = []
for _ in range(n):
    row = []
    for _ in range(m):
        row.append(0)
    mult.append(row)


# 2. Гибрид: цикл + умножение строки

mult = []
for _ in range(n):
    mult.append([0]*m)


# 3. Генератор списка с вложенным генератором (полностью «развёрнутый»)

mult = [[0 for _ in range(m)] for _ in range(n)]


# 4. «Создать список из n строк, где каждая строка — это m нулей».

mult = [[0]*m for _ in range(n)]


# 5. Ввод матрицы с клавиатуры

mult = []
for _ in range(n):
    row = list(map(int, input().split()))
    mult.append(row)

# 6. Ввод в одну строку через генератор

mult = [list(map(int, input().split)) for _ in range(n)]