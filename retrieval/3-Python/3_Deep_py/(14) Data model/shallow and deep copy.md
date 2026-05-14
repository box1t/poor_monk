
# in dictionary

```python
users = {'Hans': 'active', 'Éléonore': 'inactive', '景太郎': 'active'}

for user, status in users.copy().items():
    if status == 'inactive':
        del users[user]

```



Shallow and deep copy concepts apply not only to dictionaries but to other data structures in Python as well. Here’s a detailed explanation:


### Shallow Copy

A shallow copy creates a new object, but inserts references into it to the objects found in the original. Thus, the copied object is a new collection, but the items within the collection are references to the same objects that were in the original collection.

#### Shallow Copy Methods:

1. **Lists:**
   - Using slicing: `new_list = old_list[:]`
   - Using the `list` constructor: `new_list = list(old_list)`
   - Using the `copy` method: `new_list = old_list.copy()`

2. **Dictionaries:**
   - Using the `dict` constructor: `new_dict = dict(old_dict)`
   - Using the `copy` method: `new_dict = old_dict.copy()`

3. **Sets:**
   - Using the `set` constructor: `new_set = set(old_set)`
   - Using the `copy` method: `new_set = old_set.copy()`

4. **Using the `copy` module:**
   - `import copy`
   - `new_obj = copy.copy(old_obj)`

### Deep Copy

A deep copy creates a new object and recursively copies all objects found in the original, creating copies of nested objects as well. Thus, the new collection and all objects it contains are distinct from those in the original collection.

#### Deep Copy Method:

1. **Using the `copy` module:**
   - `import copy`
   - `new_obj = copy.deepcopy(old_obj)`

### Examples:

#### Shallow Copy:

```python
import copy

original_list = [1, 2, [3, 4]]
shallow_copied_list = copy.copy(original_list)

# Modifying the nested list in the shallow copy
shallow_copied_list[2][0] = 'a'

# Both lists reflect the change
print(original_list)  # Output: [1, 2, ['a', 4]]
print(shallow_copied_list)  # Output: [1, 2, ['a', 4]]
```

#### Deep Copy:

```python
import copy

original_list = [1, 2, [3, 4]]
deep_copied_list = copy.deepcopy(original_list)

# Modifying the nested list in the deep copy
deep_copied_list[2][0] = 'a'

# Only the deep copy reflects the change
print(original_list)  # Output: [1, 2, [3, 4]]
print(deep_copied_list)  # Output: [1, 2, ['a', 4]]
```

### Applicable Data Structures:

1. **Lists**
2. **Dictionaries**
3. **Sets**
4. **Tuples (when containing mutable objects)**
5. **User-defined objects (when implementing `__copy__` and `__deepcopy__` methods)**

### Key Takeaways:

- **Shallow copy** is faster and works well when you don’t need to copy nested objects.
- **Deep copy** is more thorough, ensuring all objects are copied recursively, but it’s slower due to its recursive nature.


> any copy is shallow if not mentioned to be deep (from module copy)


