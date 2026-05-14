


https://docs.python.org/3.10/reference/lexical_analysis.html#formatted-string-literals

- строковые литералы



str.split
str.replace


In Python, the `str` class is essential for representing and manipulating textual data. Strings are immutable sequences of characters and are one of the most commonly used data types in Python. Here is an in-depth look at the `str` class, its methods, related concepts, and some examples to illustrate its usage.

### Methods and Signatures of `str`

Here is a list of methods available for the `str` class along with their signatures:

1. `capitalize(self, /)`
2. `casefold(self, /)`
3. `center(self, width, fillchar=' ', /)`
4. `count(self, sub, start=0, end=9223372036854775807, /)`
5. `encode(self, encoding='utf-8', errors='strict')`
6. `endswith(self, suffix, start=0, end=9223372036854775807, /)`
7. `expandtabs(self, tabsize=8)`
8. `find(self, sub, start=0, end=9223372036854775807, /)`
9. `format(self, /, *args, **kwargs)`
10. `format_map(self, mapping, /)`
11. `index(self, sub, start=0, end=9223372036854775807, /)`
12. `isalnum(self, /)`
13. `isalpha(self, /)`
14. `isascii(self, /)`
15. `isdecimal(self, /)`
16. `isdigit(self, /)`
17. `isidentifier(self, /)`
18. `islower(self, /)`
19. `isnumeric(self, /)`
20. `isprintable(self, /)`
21. `isspace(self, /)`
22. `istitle(self, /)`
23. `isupper(self, /)`
24. `join(self, iterable, /)`
25. `ljust(self, width, fillchar=' ', /)`
26. `lower(self, /)`
27. `lstrip(self, chars=None, /)`
28. `maketrans(self, x, y=None, z=None, /)`
29. `partition(self, sep, /)`
30. `removeprefix(self, prefix, /)`
31. `removesuffix(self, suffix, /)`
32. `replace(self, old, new, count=-1, /)`
33. `rfind(self, sub, start=0, end=9223372036854775807, /)`
34. `rindex(self, sub, start=0, end=9223372036854775807, /)`
35. `rjust(self, width, fillchar=' ', /)`
36. `rpartition(self, sep, /)`
37. `rsplit(self, sep=None, maxsplit=-1)`
38. `rstrip(self, chars=None, /)`
39. `split(self, sep=None, maxsplit=-1)`
40. `splitlines(self, keepends=False)`
41. `startswith(self, prefix, start=0, end=9223372036854775807, /)`
42. `strip(self, chars=None, /)`
43. `swapcase(self, /)`
44. `title(self, /)`
45. `translate(self, table, /)`
46. `upper(self, /)`
47. `zfill(self, width, /)`

### Connected Terms

- **Unicode**: `str` objects in Python are Unicode by default, allowing for a wide range of characters from different languages and symbols.
- **Immutability**: Strings in Python are immutable, meaning once created, their values cannot be changed.
- **String Literals**: Strings can be created using single quotes, double quotes, triple single quotes, or triple double quotes.
- **f-strings**: Formatted string literals (introduced in Python 3.6) for embedding expressions inside string literals using curly braces `{}`.
- **Bytes**: A related class for handling binary data, often used for I/O operations where raw bytes are needed instead of text.

### Deep Technical Features

1. **Encoding and Decoding**: Conversion between string objects and bytes objects using various encodings like UTF-8, ASCII, etc.
2. **String Interpolation**: Mechanisms like `str.format()` and f-strings for including expressions inside string literals.
3. **Efficient Memory Usage**: Interning of strings for efficiency, where certain strings are stored in a common location to save memory.
4. **Rich Set of Methods**: As shown above, a comprehensive set of methods for various string operations.
5. **Slicing and Indexing**: Supports slicing and indexing, which are common operations for extracting substrings.

### Comparison to Other Approaches

- **Raw Strings**: Prefix with `r` to create raw strings, useful for regular expressions or Windows file paths (e.g., `r"C:\path\to\file"`).
- **Byte Strings**: Represent binary data using the `bytes` type, useful for non-text data or specific encodings.
- **Mutable Strings**: Use `bytearray` for mutable sequences of bytes, though they are not as commonly used for text data as `str`.

### Examples

1. **Basic String Operations**
   ```python
   text = "Hello, World!"
   print(text.upper())  # Output: "HELLO, WORLD!"
   print(text.lower())  # Output: "hello, world!"
   print(text.count('o'))  # Output: 2
   ```

2. **String Formatting**
   ```python
   name = "Alice"
   age = 30
   print(f"My name is {name} and I am {age} years old.")  # f-string
   print("My name is {} and I am {} years old.".format(name, age))  # format method
   ```

3. **Slicing and Indexing**
   ```python
   text = "Python"
   print(text[0])  # Output: "P"
   print(text[-1])  # Output: "n"
   print(text[1:4])  # Output: "yth"
   ```

4. **Encoding and Decoding**
   ```python
   text = "Hello, World!"
   encoded_text = text.encode('utf-8')
   print(encoded_text)  # Output: b'Hello, World!'
   decoded_text = encoded_text.decode('utf-8')
   print(decoded_text)  # Output: "Hello, World!"
   ```

5. **Joining and Splitting**
   ```python
   words = ["Python", "is", "awesome"]
   sentence = " ".join(words)
   print(sentence)  # Output: "Python is awesome"
   split_words = sentence.split()
   print(split_words)  # Output: ['Python', 'is', 'awesome']
   ```

The `str` class in Python is powerful and versatile, providing extensive functionality for textual data manipulation and supporting various encoding schemes to handle a wide range of text.