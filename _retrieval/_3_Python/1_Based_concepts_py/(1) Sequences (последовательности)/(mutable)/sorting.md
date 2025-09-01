
- https://docs.python.org/3.10/howto/sorting.html

### Methods of Sorting in Python

1. **`sorted(iterable, key=None, reverse=False)`**:
   - **`iterable`**: The collection to be sorted (e.g., list, tuple, string).
   - **`key`**: A function to execute to decide the order. Default is `None`.
   - **`reverse`**: If `True`, the list elements are sorted as if each comparison were reversed.

2. **`list.sort(key=None, reverse=False)`**: Sorts the list in place.

### Connected Terms to Sorting

- **Timsort**: Hybrid sorting algorithm derived from merge sort and insertion sort, used in Python’s built-in sorting.
- **Stability**: A sorting algorithm is stable if it maintains the relative order of equal elements.
- **In-place**: Sorting that rearranges the elements within the original collection without needing additional space.

### Deep Technical Features

- **Complexity**: Python's Timsort has a time complexity of O(n log n) for the worst, average, and best cases.
- **Memory usage**: Timsort is designed to be space-efficient.
- **Stability**: Timsort is stable, preserving the order of equal elements.

### Examples

#### Example 1: Using `sorted()`
```python
numbers = [4, 1, 3, 2]
sorted_numbers = sorted(numbers)
print(sorted_numbers)  # Output: [1, 2, 3, 4]
```

#### Example 2: Using `list.sort()`
```python
numbers = [4, 1, 3, 2]
numbers.sort()
print(numbers)  # Output: [1, 2, 3, 4]
```

#### Example 3: Custom Sorting with `key`
```python
words = ["banana", "apple", "cherry"]
sorted_words = sorted(words, key=len)
print(sorted_words)  # Output: ['apple', 'banana', 'cherry']
```

#### Example 4: Sorting in Descending Order
```python
numbers = [4, 1, 3, 2]
sorted_numbers = sorted(numbers, reverse=True)
print(sorted_numbers)  # Output: [4, 3, 2, 1]
```

### Conclusion

Sorting is a fundamental operation in Python with various applications. Understanding its methods, best practices, and optimization techniques is crucial for effective programming. Leveraging Python's built-in sorting functions ensures efficient and clean code.



```
what keys are available do decide the order? len? what else?
what is the difference between reverse order and key?

```

