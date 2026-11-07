

**Any()** принимает последовательность и возвращает true, если какой-либо элемент в последовательности равен true.  
**All()** возвращает истину, только если все элементы в последовательности истинны.

```
a = [False, False, False]
b = [True, False, False]
c = [True, True, True]

print( any(a) )
print( any(b) )
print( any(c) )
#=> False
#=> True
#=> True

print( all(a) )
print( all(b) )
print( all(c) )
#=> False
#=> False
#=> True

```

