
# Write a Python script to take a comma-separated string input and create a sorted list and tuple.

# 1. Take a comma-separated string input from the user
user_input = input("Enter a comma-separated string: ")

# 2. Split the string by commas
raw_items = user_input.split(',')

# 3. Clean up extra spaces using a regular for loop
cleaned_items = []
for item in raw_items:
    cleaned_items.append(item.strip())

# 4. Sort the list
cleaned_items.sort()

# 5. Convert to tuple
sorted_tuple = tuple(cleaned_items)

# 6. Print the results
print("\nSorted List: ", cleaned_items)
print("Sorted Tuple:", sorted_tuple)


