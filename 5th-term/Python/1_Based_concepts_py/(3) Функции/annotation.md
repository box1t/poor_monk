
Метка, связанная с переменной, атрибутом класса или параметром функции или возвращаемым значением, используемая по соглашению как [подсказка типа](https://translated.turbopages.org/proxy_u/en-ru.ru.884bf330-66a64c16-b314218d-74722d776562/https/docs.python.org/3.10/glossary.html#term-type-hint).

К аннотациям локальных переменных нельзя получить доступ во время выполнения, но аннотации глобальных переменных, атрибутов класса и функций хранятся в `__annotations__` специальном атрибуте модулей, классов и функций соответственно.



аннотация функции

[Аннотация](https://translated.turbopages.org/proxy_u/en-ru.ru.884bf330-66a64c16-b314218d-74722d776562/https/docs.python.org/3.10/glossary.html#term-annotation) параметра функции или возвращаемого значения.

Аннотации функций обычно используются для [подсказок по типу](https://translated.turbopages.org/proxy_u/en-ru.ru.884bf330-66a64c16-b314218d-74722d776562/https/docs.python.org/3.10/glossary.html#term-type-hint): например, ожидается, что эта функция будет принимать два [`int`](https://translated.turbopages.org/proxy_u/en-ru.ru.884bf330-66a64c16-b314218d-74722d776562/https/docs.python.org/3.10/library/functions.html#int "int") аргумента, а также будет иметь [`int`](https://translated.turbopages.org/proxy_u/en-ru.ru.884bf330-66a64c16-b314218d-74722d776562/https/docs.python.org/3.10/library/functions.html#int "int") возвращаемое значение:

def sum_two_numbers(a: int, b: int) -> int:
   возвращает a + b

Синтаксис аннотаций функций объясняется в разделе [Определения функций](https://translated.turbopages.org/proxy_u/en-ru.ru.884bf330-66a64c16-b314218d-74722d776562/https/docs.python.org/3.10/reference/compound_stmts.html#function).

Смотрите [аннотацию переменной](https://translated.turbopages.org/proxy_u/en-ru.ru.884bf330-66a64c16-b314218d-74722d776562/https/docs.python.org/3.10/glossary.html#term-variable-annotation) и [**PEP 484**](https://translated.turbopages.org/proxy_u/en-ru.ru.884bf330-66a64c16-b314218d-74722d776562/https/www.python.org/dev/peps/pep-0484), которые описывают эту функциональность. Также смотрите [Рекомендации по работе с аннотациями](https://translated.turbopages.org/proxy_u/en-ru.ru.884bf330-66a64c16-b314218d-74722d776562/https/docs.python.org/3.10/howto/annotations.html#annotations-howto), чтобы ознакомиться с рекомендациями по работе с аннотациями.



