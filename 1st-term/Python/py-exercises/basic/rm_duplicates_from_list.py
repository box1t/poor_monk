
# Write a Python program that removes duplicate numbers from a list before converting it into a tuple.

lst = input().split(',')
unduplicated_lst = []
for item in lst:
    if item not in unduplicated_lst:
        unduplicated_lst.append(item)
print(unduplicated_lst)
print(tuple(unduplicated_lst))
