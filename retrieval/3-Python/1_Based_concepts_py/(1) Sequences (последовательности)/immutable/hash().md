

The only operation that immutable sequence types generally implement that is not also implemented by mutable sequence types is support for the [`hash()`](https://docs.python.org/3.10/library/functions.html#hash "hash") built-in.


Return the hash value of the object (if it has one). Hash values are integers. They are used to quickly compare dictionary keys during a dictionary lookup. Numeric values that compare equal have the same hash value (even if they are of different types, as is the case for 1 and 1.0).


This support allows immutable sequences, such as [`tuple`](https://docs.python.org/3.10/library/stdtypes.html#tuple "tuple") instances, to be used as [`dict`](https://docs.python.org/3.10/library/stdtypes.html#dict "dict") keys and stored in [`set`](https://docs.python.org/3.10/library/stdtypes.html#set "set") and [`frozenset`](https://docs.python.org/3.10/library/stdtypes.html#frozenset "frozenset") instances.



### Immutable and Mutable Sequences

- **Immutable Sequences**: Cannot be changed after creation. Examples: `tuple`, `str`.
- **Mutable Sequences**: Can be changed after creation. Examples: `list`.

### `hash()` and Its Importance

- **`hash()`**: A built-in function that returns the hash value of an object. Hashable objects can be used as keys in dictionaries and stored in sets or frozensets.

Immutable sequences support `hash()`, making them usable as dictionary keys or set elements. Mutable sequences do not support `hash()` because their contents can change, which would invalidate their hash values.

### Example with Code

Let's illustrate this with code:

#### Immutable Sequence (Tuple)

1. **Using Tuple as a Dictionary Key**:

```python
# Creating a dictionary with tuples as keys
my_dict = {
    ('john', 'A', 15): 'Student1',
    ('jane', 'B', 12): 'Student2',
}

# Accessing dictionary using a tuple key
key = ('john', 'A', 15)
print(my_dict[key])  # Output: Student1

# Checking if the tuple is hashable
print(hash(key))  # Output: Some integer hash value
```

2. **Using Tuple in a Set**:

```python
# Creating a set with tuples
my_set = {('john', 'A', 15), ('jane', 'B', 12)}

# Adding a tuple to the set
my_set.add(('dave', 'B', 10))
print(my_set)  # Output: {('john', 'A', 15), ('jane', 'B', 12), ('dave', 'B', 10)}

# Checking if the tuple is hashable
print(hash(('john', 'A', 15)))  # Output: Some integer hash value
```

#### Mutable Sequence (List)

1. **Attempting to Use List as a Dictionary Key (Will Fail)**:

```python
# Attempting to create a dictionary with lists as keys (will raise TypeError)
try:
    my_dict = {
        ['john', 'A', 15]: 'Student1',  # TypeError
        ['jane', 'B', 12]: 'Student2',  # TypeError
    }
except TypeError as e:
    print(e)  # Output: unhashable type: 'list'
```

2. **Attempting to Use List in a Set (Will Fail)**:

```python
# Attempting to create a set with lists (will raise TypeError)
try:
    my_set = {['john', 'A', 15], ['jane', 'B', 12]}  # TypeError
except TypeError as e:
    print(e)  # Output: unhashable type: 'list'
```

### Hashing with Unhashable Values

Even immutable sequences cannot be hashed if they contain unhashable values. For example, a tuple containing a list (which is unhashable) cannot be hashed.

1. **Tuple Containing Unhashable Values**:

```python
# Creating a tuple that contains a list
tuple_with_list = ('john', ['A', 15])

# Attempting to hash this tuple (will raise TypeError)
try:
    print(hash(tuple_with_list))  # TypeError
except TypeError as e:
    print(e)  # Output: unhashable type: 'list'
```

### Summary

- **Immutable Sequences** like tuples support `hash()` and can be used as dictionary keys or set elements.
- **Mutable Sequences** like lists do not support `hash()` and cannot be used as dictionary keys or set elements.
- Attempting to hash an immutable sequence containing unhashable values (like a list within a tuple) will result in a `TypeError`.

These characteristics are essential for understanding how to use different sequence types effectively in Python, especially when working with data structures like dictionaries and sets.