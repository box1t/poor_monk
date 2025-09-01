

- это отображение (mapping). это коллекция.

### What is a Dictionary in Python?

A dictionary in Python is a collection of key-value pairs. Each key is unique and maps to a specific value. Dictionaries are unordered, meaning that they do not keep track of the order in which items are added.

In Python dictionaries, keys and values cannot be added without association; they must always exist in pairs. Each key in a dictionary must have a corresponding value. This ensures that each key-value pair is complete and there are no "dangling" keys or values.


### Why is it Necessary?

Dictionaries are necessary for situations where you need a logical association between a key and a value, and you need fast lookups, additions, and deletions based on keys.


### How it Works?

Dictionaries work by using a hash table. When a key-value pair is added, the key is hashed and the hash value determines the index in an underlying array where the value is stored. This allows for average O(1) time complexity for lookups, insertions, and deletions.




### Available Operations

- **Creating a Dictionary**:
- **Accessing Values**:
- **Adding or Updating Values**:
- **Deleting Values**:
- **Iterating through a Dictionary**:
- **Checking for Key Existence**:
- **Getting the Length**:



- **Creating a Dictionary**:
  ```python
my_dict = {}  # Empty dictionary
my_dict = {'key1': 'value1', 'key2': 'value2'}
  ```

- **Accessing Values**:
  ```python
value = my_dict['key1']

value = my_dict['key1']
value = my_dict['key1']
value = my_dict['key1']
value = my_dict['key1']

  ```

- **Adding or Updating Values**:
  ```python
my_dict['key3'] = 'value3'

  ```

- **Deleting Values**:
  ```python
  del my_dict['key1']
  ```

- **Iterating through a Dictionary**:
  ```python
  for key, value in my_dict.items():
      print(key, value)
  ```

- **Checking for Key Existence**:
  ```python
  if 'key1' in my_dict:
      print('Key1 exists')
  ```

- **Getting the Length**:
  ```python
  length = len(my_dict)
  ```

### Best Cases and Strategies for Using Dictionaries

- **When to Use**:
  - Use dictionaries when you need a flexible, dynamic structure with fast access and updates based on unique keys.
  - Ideal for associative arrays, hash maps, and look-up tables.

- **Strategies**:
  - **Default Values**: Use `dict.get(key, default)` to avoid `KeyError` if a key is not present.
  - **Counting Items**: Use `collections.defaultdict` for counting occurrences.
    ```python
    from collections import defaultdict
    counts = defaultdict(int)
    for item in items:
        counts[item] += 1
    ```
  - **Grouping Data**: Use `collections.defaultdict` to group data.
    ```python
    from collections import defaultdict
    groupings = defaultdict(list)
    for item in items:
        groupings[item.category].append(item)
    ```
  - **Immutable Keys**: Ensure that keys are immutable (e.g., strings, numbers, tuples).

### Connected Terms

- **Hash Table**: The underlying data structure that dictionaries use to provide fast access.
- **Key-Value Pair**: The basic unit of data in a dictionary.
- **Immutable**: Keys in a dictionary must be immutable types like strings, numbers, or tuples.
- **Defaultdict**: A subclass of the dictionary from the `collections` module that provides default values for nonexistent keys.
- **OrderedDict**: A subclass of the dictionary from the `collections` module that remembers the order in which items were inserted (Python 3.7+ dictionaries are insertion-ordered by default).

### Example Code

Here is an example of how dictionaries can be used to count word frequencies in a text:

```python
text = "example text with some example words in this example text"
word_count = {}

for word in text.split():
    if word in word_count:
        word_count[word] += 1
    else:
        word_count[word] = 1

print(word_count)
```

Output:
```
{'example': 3, 'text': 2, 'with': 1, 'some': 1, 'words': 1, 'in': 1, 'this': 1}
```


### Deep Technical Features of Python Dictionaries

Understanding the technical underpinnings of Python dictionaries can help you use them more effectively and optimize your code. Here are some deep technical features and considerations:

#### 1. **Hashing and Hash Functions**

- **Hashing**: Python dictionaries use hash tables internally. When you add a key-value pair, the dictionary uses a hash function to convert the key into a hash value, which determines the index in an internal array where the value is stored.
- **Hash Function**: The `hash()` function in Python computes the hash value. Immutable types like strings, numbers, and tuples have stable hash values.
- **Custom Objects**: If you use custom objects as keys, you must implement `__hash__` and `__eq__` methods to ensure consistent hashing and equality checks.

#### 2. **Collision Resolution**

- **Collisions**: When two keys hash to the same index, a collision occurs. Python dictionaries handle collisions using open addressing with quadratic probing.
- **Probing**: When a collision happens, the dictionary searches for the next available slot in a predictable sequence based on the initial hash value.

#### 3. **Resizing**

- **Load Factor**: To maintain efficient performance, dictionaries resize themselves when the load factor (number of entries / size of the internal array) exceeds a certain threshold (usually 2/3).
- **Resizing Operation**: When resizing, the dictionary allocates a new, larger array and rehashes all existing keys into the new array. This operation is costly but infrequent.

#### 4. **Amortized Time Complexity**

- **Average Case**: Dictionary operations (insertion, deletion, lookup) have an average time complexity of O(1) due to the hash table implementation.
- **Worst Case**: In the worst case, when many collisions occur, operations can degrade to O(n), but with a good hash function and resizing strategy, this is rare.

#### 5. **Memory Overhead**

- **Memory Usage**: Dictionaries require more memory than simple lists or arrays due to the overhead of storing hash values, key-value pairs, and empty slots for collision resolution and resizing.
- **Space Complexity**: The space complexity is O(n) for n key-value pairs, but the actual memory footprint can be higher due to internal array resizing.

#### 6. **Iterating and View Objects**

- **Dictionary Views**: Methods like `dict.keys()`, `dict.values()`, and `dict.items()` return view objects that provide a dynamic view on the dictionary’s entries, meaning they reflect changes to the dictionary.
- **Efficiency**: Iterating over a dictionary using these views is efficient, but keep in mind that modifying the dictionary while iterating can lead to runtime errors.

#### 7. **Order of Keys (Python 3.7+)**

- **Insertion Order**: Since Python 3.7, dictionaries maintain insertion order as an implementation detail. This means that iterating over a dictionary will yield keys in the order they were added.
- **OrderedDict**: For versions before Python 3.7 or if explicit control over order is required, `collections.OrderedDict` can be used.

### Practical Considerations

#### Custom Hashing and Equality

If you use custom objects as dictionary keys, ensure consistent hashing and equality by implementing the `__hash__` and `__eq__` methods:

```python
class MyKey:
    def __init__(self, attribute):
        self.attribute = attribute

    def __hash__(self):
        return hash(self.attribute)

    def __eq__(self, other):
        return isinstance(other, MyKey) and self.attribute == other.attribute
```

#### Avoiding Key Errors

Use `dict.get(key, default)` to avoid `KeyError` when accessing keys that might not exist:

```python
value = my_dict.get('nonexistent_key', 'default_value')
```

#### Handling Large Data

For large datasets, consider the memory overhead and potential resizing costs. Efficient use of dictionaries includes:

- **Initialization**: Pre-allocate expected size if possible.
- **Batch Operations**: Perform bulk operations to minimize the frequency of resizing.
- **Memory Profiling**: Use memory profiling tools to understand the impact on your application’s memory usage.

### Connected Terms and Concepts

- **Set**: Another hash-based data structure in Python, similar to dictionaries but only stores keys (unique elements).
- **FrozenDict**: An immutable variant of the dictionary (not in standard library but available in some third-party libraries).
- **Defaultdict**: A subclass of `dict` from the `collections` module that provides default values for missing keys.

### Example Code

Here's an example demonstrating custom hashing and handling key errors:

```python
class CustomKey:
    def __init__(self, id, name):
        self.id = id
        self.name = name

    def __hash__(self):
        return hash((self.id, self.name))

    def __eq__(self, other):
        return isinstance(other, CustomKey) and self.id == other.id and self.name == other.name

# Create a dictionary with custom keys
custom_dict = {}
key1 = CustomKey(1, 'Alice')
key2 = CustomKey(2, 'Bob')

custom_dict[key1] = 'Data for Alice'
custom_dict[key2] = 'Data for Bob'

# Accessing values
print(custom_dict.get(key1))  # Output: Data for Alice
print(custom_dict.get(CustomKey(3, 'Charlie'), 'Default Value'))  # Output: Default Value
```

This deeper understanding of Python dictionaries helps optimize their use in various scenarios, ensuring both performance and correctness in your programs.



```python
users = {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}
active_users = {}
for user, status in users.items():
    if status == 'active':
        active_users[user] = status

```

This code would then correctly populate `active_users` with only the active users:

```python
`{'Hans': 'active', '景太郎': 'active'}`
```

Yes, there are alternative ways to iterate over dictionaries without using `.items()`. Here are some common alternatives:

### Using `.keys()` and `.values()`

1. **Using `.keys()`:**
   This method returns a view object displaying a list of all the keys in the dictionary.

   ```python
users = {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}
for user in users.keys():
    print(user)
   ```

2. **Using `.values()`:**
   This method returns a view object displaying a list of all the values in the dictionary.

   ```python
users = {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}
for status in users.values():
    print(status)
   ```

3. **Using `.keys()` and indexing:**
   You can use the keys to access values by indexing the dictionary.

   ```python
users = {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}
for user in users.keys():
    status = users[user]
    print(user, status)
   ```

### Iterating Directly Over the Dictionary

When you iterate directly over a dictionary, it iterates over the keys by default.

```python
users = {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}
for user in users:
    status = users[user]
    print(user, status)
```

### Using List Comprehensions

List comprehensions can also be used to create lists of keys, values, or key-value pairs.

1. **List of keys:**

   ```python
users = {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}
keys = [user for user in users]
print(keys)
   ```

2. **List of values:**

   ```python
users = {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}
values = [status for status in users.values()]
print(values)
   ```

3. **List of key-value pairs:**

   ```python
   users = {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}
   items = [(user, status) for user, status in users.items()]
   print(items)
   ```

### Using `enumerate()` (for iterating with indices)

If you need to keep track of the index while iterating, you can use `enumerate()` in combination with any of the above methods.

```python
users = {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}
for index, user in enumerate(users):
    status = users[user]
    print(index, user, status)
```

Each of these methods offers a different way to interact with dictionary data, depending on your specific needs and preferences.



Dictionaries in Python come with a variety of built-in methods that allow you to manipulate and interact with the data they contain. Here's a comprehensive list of dictionary methods:

### Dictionary Methods

1. **`clear()`**
   - Removes all items from the dictionary.
   - **Example:** `users.clear()`

2. **`copy()`**
   - Returns a shallow copy of the dictionary.
   - **Example:** `users_copy = users.copy()`

3. **`fromkeys(iterable, value=None)`**
   - Creates a new dictionary with keys from an iterable and values set to a specified value.
   - **Example:** `new_dict = dict.fromkeys(['key1', 'key2'], 'default_value')`

4. **`get(key, default=None)`**
   - Returns the value for the specified key if the key is in the dictionary, otherwise returns the default value.
   - **Example:** `value = users.get('Hans', 'Not Found')`

5. **`items()`**
   - Returns a view object displaying a list of a dictionary's key-value tuple pairs.
   - **Example:** `items_view = users.items()`

6. **`keys()`**
   - Returns a view object displaying a list of the dictionary’s keys.
   - **Example:** `keys_view = users.keys()`

7. **`pop(key, default=None)`**
   - Removes the specified key and returns the corresponding value. If the key is not found, returns the default value.
   - **Example:** `value = users.pop('Hans', 'Not Found')`

8. **`popitem()`**
   - Removes and returns an arbitrary (key, value) pair from the dictionary. Raises `KeyError` if the dictionary is empty.
   - **Example:** `key_value_pair = users.popitem()`

9. **`setdefault(key, default=None)`**
   - Returns the value of the specified key. If the key does not exist, inserts the key with the specified default value.
   - **Example:** `value = users.setdefault('Hans', 'default_value')`

10. **`update([other])`**
    - Updates the dictionary with elements from another dictionary object or from an iterable of key-value pairs.
    - **Example:** `users.update({'Hans': 'inactive', 'John': 'active'})`

11. **`values()`**
    - Returns a view object displaying a list of the dictionary’s values.
    - **Example:** `values_view = users.values()`

### Examples of Using Dictionary Methods

```python
# Example dictionary
users = {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}

# clear()
users.clear()
print(users)  # Output: {}

# copy()
users = {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}
users_copy = users.copy()
print(users_copy)  # Output: {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}

# fromkeys()
new_dict = dict.fromkeys(['key1', 'key2'], 'default_value')
print(new_dict)  # Output: {'key1': 'default_value', 'key2': 'default_value'}

# get()
value = users.get('Hans', 'Not Found')
print(value)  # Output: active

# items()
items_view = users.items()
print(list(items_view))  # Output: [('Hans', 'active'), ('Éléonore', 'inactive'), ('景太郎', 'active')]

# keys()
keys_view = users.keys()
print(list(keys_view))  # Output: ['Hans', 'Éléonore', '景太郎']

# pop()
value = users.pop('Hans', 'Not Found')
print(value)  # Output: active
print(users)  # Output: {'Éléonore': 'inactive', '景太郎': 'active'}

# popitem()
key_value_pair = users.popitem()
print(key_value_pair)  # Output: ('景太郎', 'active') or another arbitrary pair
print(users)  # Output: Remaining items in users

# setdefault()
value = users.setdefault('Hans', 'default_value')
print(value)  # Output: 'default_value' if 'Hans' was not present
print(users)  # Output: {'Éléonore': 'inactive', '景太郎': 'active', 'Hans': 'default_value'}

# update()
users.update({'Hans': 'inactive', 'John': 'active'})
print(users)  # Output: {'Éléonore': 'inactive', '景太郎': 'active', 'Hans': 'inactive', 'John': 'active'}

# values()
values_view = users.values()
print(list(values_view))  # Output: ['inactive', 'active', 'inactive', 'active']
```

These methods provide powerful ways to manipulate dictionaries, offering flexibility and efficiency for various operations.


