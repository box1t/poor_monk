
В Python существует множество способов форматирования чисел, включая форматирование с ведущими нулями, форматирование с фиксированной точностью, форматирование с тысячными разделителями и другие. Вот несколько примеров:

### 1. Форматирование с ведущими нулями

```python
number = 7
print(f"Number: {number:02}")  # Number: 07
print(f"Number: {number:03}")  # Number: 007
```

### 2. Форматирование с фиксированной точностью

```python
pi = 3.14159
print(f"Pi is approximately {pi:.2f}")  # Pi is approximately 3.14
print(f"Pi is approximately {pi:.4f}")  # Pi is approximately 3.1416
```

### 3. Форматирование с тысячными разделителями

```python
number = 1234567
print(f"Number: {number:,}")  # Number: 1,234,567
```

### 4. Форматирование с процентами

```python
percentage = 0.25
print(f"Percentage: {percentage:.2%}")  # Percentage: 25.00%
```

### 5. Форматирование с научной нотацией

```python
number = 123456789
print(f"Number: {number:.2e}")  # Number: 1.23e+08
```

### 6. Форматирование с заполнением пробелами

```python
number = 7
print(f"Number: {number:5}")  # Number:     7
print(f"Number: {number:>5}")  # Number:     7
print(f"Number: {number:<5}")  # Number: 7
print(f"Number: {number:^5}")  # Number:  7
```

### 7. Форматирование с заполнением символами

```python
number = 7
print(f"Number: {number:*<5}")  # Number: 7****
print(f"Number: {number:*>5}")  # Number: ****7
print(f"Number: {number:*^5}")  # Number: **7**
```


