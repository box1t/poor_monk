
- https://docs.python.org/3.10/howto/regex.html
- https://docs.python.org/3.10/library/re.html#module-re


### Why is it Necessary? Where is it Applied?

Regular expressions are necessary for tasks that involve searching, matching, and manipulating strings based on patterns. They are applied in:
- Validating input (e.g., email addresses, phone numbers)
- Searching and replacing text
- Extracting specific parts of a string
- Splitting strings based on patterns

### How It Works? What Operations are Available?

Regex works by defining a search pattern. Patterns consist of literal characters and special characters (metacharacters) that describe rules for matching strings.

**Common operations:**
- `re.match(pattern, string)`: Checks for a match only at the beginning of the string.
- `re.search(pattern, string)`: Searches for the first location where the pattern matches.
- `re.findall(pattern, string)`: Returns a list of all non-overlapping matches.
- `re.finditer(pattern, string)`: Returns an iterator yielding match objects.
- `re.sub(pattern, repl, string)`: Replaces the matches with `repl`.
- `re.compile(pattern)`: Compiles a regex pattern into a regex object.
- `re.split(pattern, string)`: Splits the string by the occurrences of the pattern.

### Comparison to Other Approaches

- **String methods**: Simpler and often faster for straightforward tasks (e.g., `str.split()`, `str.replace()`) but less flexible.
- **Parser libraries**: More powerful for complex parsing needs but also more complex (e.g., `pyparsing`).


### Examples

#### Basic Matching
```python
import re

pattern = r'\d+'  # Matches one or more digits
string = 'There are 123 apples and 456 oranges.'
matches = re.findall(pattern, string)
print(matches)  # Output: ['123', '456']

```


#### Validating an Email
```python
import re

email_pattern = r'^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$'
email = 'test@example.com'
if re.match(email_pattern, email):
    print("Valid email")
else:
    print("Invalid email")

```

#### Substitution
```python
import re

pattern = r'\bfoo\b'  # Matches 'foo' as a whole word
string = 'foo bar baz foo'
new_string = re.sub(pattern, 'qux', string)
print(new_string)  # Output: 'qux bar baz qux'


```

#### Findall
```python
import re

pattern = r'\b\w+(?=\sis)'  # Matches words followed by ' is'
string = 'This is a test. That is an example.'
matches = re.findall(pattern, string)
print(matches)  # Output: ['This', 'That']


```

```
is there any list of these short keywords to understand regex?

how to work with one word after a specific word?
with 2 words?


```