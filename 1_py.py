
# На вход программе подаются натуральное число n, затем n строк, затем ещё одна строка – поисковый запрос.
# Напишите программу, которая выводит все введённые строки, в которых встречается поисковый запрос.

n = int(input())

spis = []
for i in range(n):
    spis.append(input())

q_search = input()

for line in spis:
    if q_search in line:
        print(line)

