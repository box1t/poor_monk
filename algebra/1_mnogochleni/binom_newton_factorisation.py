def calculate_power(base, exponent):
    """Вычисляет степень числа."""
    return base ** exponent

def factorize_binomial(a, b, n, operation):
    """
    Пытается разложить двучлен a^n +/- b^n на множители.
    """
    print(f"\n--- Разложение {a}^{n} {operation} {b}^{n} ---")

    # 1. Вычисление значения двучлена
    if operation == '+':
        binomial_value = calculate_power(a, n) + calculate_power(b, n)
    elif operation == '-':
        binomial_value = calculate_power(a, n) - calculate_power(b, n)
    else:
        print("Некорректная операция. Используйте '+' или '-'.")
        return

    print(f"Исходное значение двучлена: {binomial_value}")

    # 2. Попытка факторизации
    if operation == '-':  # Формула для a^n - b^n
        if n == 0: # Особый случай 0-й степени
            print("Нельзя разложить на множители при n=0 по данной формуле.")
            return

        factor1 = (a - b)
        factor2_sum = 0
        for i in range(n):
            term = calculate_power(a, n - 1 - i) * calculate_power(b, i)
            factor2_sum += term
        
        factor2 = factor2_sum
        
        print(f"Факторизация: ({a} - {b}) * ({' + '.join([f'{a}^{n-1-i}*{b}^{i}' for i in range(n)])})")
        print(f"Полученные множители: ({factor1}) * ({factor2})")

        # 3. Проверка
        product_of_factors = factor1 * factor2
        print(f"Произведение множителей: {product_of_factors}")
        if product_of_factors == binomial_value:
            print(f"Проверка успешна: {product_of_factors} == {binomial_value}")
        else:
            print(f"Проверка не удалась: {product_of_factors} != {binomial_value}")

    elif operation == '+':  # Формула для a^n + b^n
        if n % 2 != 0:  # n нечетное
            factor1 = (a + b)
            factor2_sum = 0
            for i in range(n):
                term = calculate_power(a, n - 1 - i) * calculate_power(b, i)
                if i % 2 == 1: # Чередуем знаки
                    factor2_sum -= term
                else:
                    factor2_sum += term
            
            factor2 = factor2_sum
# проблема в знаке факторизации при случае factorize_binomial(4, 3, 3, '+') # Пример a^2 + b^2
            print(f"Факторизация: ({a} + {b}) * ({' - '.join([f'{a}^{n-1-i}*{b}^{i}' if i % 2 == 0 else f'-{a}^{n-1-i}*{b}^{i}' for i in range(n)]).replace('--', '+')})") # Упрощенное отображение
            print(f"Полученные множители: ({factor1}) * ({factor2})")

            # 3. Проверка
            product_of_factors = factor1 * factor2
            print(f"Произведение множителей: {product_of_factors}")
            if product_of_factors == binomial_value:
                print(f"Проверка успешна: {product_of_factors} == {binomial_value}")
            else:
                print(f"Проверка не удалась: {product_of_factors} != {binomial_value}")
        else:  # n четное
            if n > 2: # Согласно тексту, при n > 2 и четном, не раскладывается на линейные множители
                 print(f"Для {a}^{n} + {b}^{n} при четном n={n} > 2, этот двучлен не раскладывается на линейные множители согласно указанным формулам.")
            elif n == 2: # a^2 + b^2 - не раскладывается в действительных числах
                 print(f"Для {a}^{n} + {b}^{n} при четном n={n}, этот двучлен не раскладывается на линейные множители в действительных числах.")
            elif n == 0:
                print("Нельзя разложить на множители при n=0 по данной формуле.")


# Примеры использования:
factorize_binomial(2, 3, 4, '-')
factorize_binomial(2, 3, 4, '+')
factorize_binomial(2, 3, 3, '+') # Пример для нечетного n
factorize_binomial(5, 2, 5, '-')
factorize_binomial(4, 3, 3, '+') # Пример a^2 + b^2
factorize_binomial(1, 1, 0, '-') # Пример n=0
factorize_binomial(1, 1, 0, '+') # Пример n=0