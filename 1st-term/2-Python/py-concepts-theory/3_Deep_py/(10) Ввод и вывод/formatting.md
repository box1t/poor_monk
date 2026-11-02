
```
## Output Formatting
two ways of writing values:
- _expression statements_
- print() function



```



```python
year = 2016
event = 'Referendum'
f'Results of the {year} {event}'


yes_votes = 42_572_654
no_votes = 43_132_495
percentage = yes_votes / (yes_votes + no_votes)
'{:-9} YES votes  {:2.2%}'.format(yes_votes, percentage)


s = 'Hello, world.'
str(s)

repr(s)

str(1/7)

x = 10 * 3.25
y = 200 * 200
s = 'The value of x is ' + repr(x) + ', and y is ' + repr(y) + '...'
print(s)

# The repr() of a string adds string quotes and backslashes:
hello = 'hello, world\n'
hellos = repr(hello)
print(hellos)

# The argument to repr() may be any Python object:
repr((x, y, ('spam', 'eggs')))


```

```python
# Passing an integer after the `':'` will cause that field to be a minimum number of characters wide. This is useful for making columns line up.


table = {'Sjoerd': 4127, 'Jack': 4098, 'Dcab': 7678}
for name, phone in table.items():
    print(f'{name:10} ==> {phone:10d}')




animals = 'eels'
print(f'My hovercraft is full of {animals}.')

print(f'My hovercraft is full of {animals!r}.')
```


```
print()
repr()
str()
str.format()
str.rjust()
str.ljust()
str.center()
str.zfill()
open()
with
f.read()
f.close()
f.readline()
json.bumps()
json.load()

```
