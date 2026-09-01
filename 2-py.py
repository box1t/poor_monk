
input_string = input()

raw_items = input_string.split(',')

cleaned_items = []
for item in raw_items:
    cleaned_items.append(item.strip())

cleaned_items.sort()

sorted_tuple = tuple(cleaned_items)

print("Sorted List: ", cleaned_items)
print("Sorted Tuple:", sorted_tuple)

input_string = input()

raw_items = input_string.split(',')
cleaned_items = []
for item in raw_items:
    cleaned_items.append(item.strip())

cleaned_items.sort()
sorted_tuple = tuple(cleaned_items)
print("Sorted List: ", cleaned_items)
print("Sorted Tuple:", sorted_tuple)
