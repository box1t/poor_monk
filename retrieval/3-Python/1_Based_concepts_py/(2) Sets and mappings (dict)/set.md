

In Python, a `set` is an unordered collection of unique elements. It is used to store multiple items in a single variable, where duplicate elements are not allowed. Sets are commonly used for membership testing, eliminating duplicate entries, and performing mathematical operations like union, intersection, and difference.

### Methods and Signatures

Here are all the methods available for a `set` in Python:

1. **Adding Elements**
    - `add(elem)` - Adds an element to the set.
    ```python
    s.add(elem)
    ```

2. **Removing Elements**
    - `remove(elem)` - Removes an element from the set. Raises `KeyError` if the element is not present.
    ```python
    s.remove(elem)
    ```
    - `discard(elem)` - Removes an element from the set if it is a member. If the element is not a member, it does nothing.
    ```python
    s.discard(elem)
    ```
    - `pop()` - Removes and returns an arbitrary set element. Raises `KeyError` if the set is empty.
    ```python
    s.pop()
    ```
    - `clear()` - Removes all elements from the set.
    ```python
    s.clear()
    ```

3. **Set Operations**
    - `union(*others)` or `|` - Returns a new set with elements from the set and all others.
    ```python
    s.union(t) or s | t
    ```
    - `intersection(*others)` or `&` - Returns a new set with elements common to the set and all others.
    ```python
    s.intersection(t) or s & t
    ```
    - `difference(*others)` or `-` - Returns a new set with elements in the set that are not in the others.
    ```python
    s.difference(t) or s - t
    ```
    - `symmetric_difference(other)` or `^` - Returns a new set with elements in either the set or other but not both.
    ```python
    s.symmetric_difference(t) or s ^ t
    ```
    - `update(*others)` or `|=` - Updates the set, adding elements from all others.
    ```python
    s.update(t) or s |= t
    ```
    - `intersection_update(*others)` or `&=` - Updates the set, keeping only elements found in it and all others.
    ```python
    s.intersection_update(t) or s &= t
    ```
    - `difference_update(*others)` or `-=` - Updates the set, removing elements found in others.
    ```python
    s.difference_update(t) or s -= t
    ```
    - `symmetric_difference_update(other)` or `^=` - Updates the set, keeping only elements found in either set, but not in both.
    ```python
    s.symmetric_difference_update(t) or s ^= t
    ```

4. **Subset and Superset**
    - `issubset(other)` or `<=` - Returns True if the set is a subset of other.
    ```python
    s.issubset(t) or s <= t
    ```
    - `issuperset(other)` or `>=` - Returns True if the set is a superset of other.
    ```python
    s.issuperset(t) or s >= t
    ```
    - `isdisjoint(other)` - Returns True if the set has no elements in common with other.
    ```python
    s.isdisjoint(t)
    ```

5. **Miscellaneous**
    - `copy()` - Returns a shallow copy of the set.
    ```python
    s.copy()
    ```

### Connected Terms

- **Frozen Set**: An immutable version of a set.
- **Hashable**: Objects that can be used as an element in a set (must have a `__hash__` method).
- **Mutable**: The set itself can be changed (adding or removing elements).
- **Iterable**: A set can be iterated over (used in loops).
- **Unordered**: Elements in a set have no specific order.

### Deep Technical Features

1. **Hash Table**: Sets are implemented using a hash table, providing average O(1) time complexity for add, remove, and membership tests.
2. **Immutability of Elements**: Only hashable (immutable) elements can be added to a set.
3. **Memory Usage**: Sets can be memory efficient compared to lists for large collections of unique items.
4. **Performance**: Sets are faster for membership tests compared to lists or tuples.

### Comparison to Other Approaches

- **Lists**: Allow duplicates and are ordered. Sets are faster for membership testing.
- **Tuples**: Immutable and ordered. Sets are mutable and unordered.
- **Dictionaries**: Keys in dictionaries can act like a set. Dictionaries provide key-value pairs, whereas sets only store unique elements.

### Examples

```python
# Creating a set
fruits = {"apple", "banana", "cherry"}
print(fruits)  # {'apple', 'banana', 'cherry'}

# Adding elements
fruits.add("orange")
print(fruits)  # {'apple', 'banana', 'cherry', 'orange'}

# Removing elements
fruits.remove("banana")
print(fruits)  # {'apple', 'cherry', 'orange'}

# Set operations
a = {1, 2, 3}
b = {3, 4, 5}

print(a | b)  # Union: {1, 2, 3, 4, 5}
print(a & b)  # Intersection: {3}
print(a - b)  # Difference: {1, 2}
print(a ^ b)  # Symmetric Difference: {1, 2, 4, 5}

# Subset and Superset
c = {1, 2}
print(c <= a)  # True
print(a >= c)  # True

# Checking membership
print(3 in a)  # True
print(6 in a)  # False
```

By understanding these features and methods, you can leverage sets in Python to efficiently handle collections of unique items and perform various set operations.