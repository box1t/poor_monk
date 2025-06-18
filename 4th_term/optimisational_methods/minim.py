import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import minimize

# 1. Определяем целевую функцию
def objective_function(X):
    x1, x2 = X
    return x1**2 + (x2 - 1)**2

# 2. Определяем функции ограничений
# Для scipy.optimize.minimize, неравенства должны быть в формате g(X) >= 0
def constraint1_ineq(X):
    """x1^2 + x2^2 <= 4  =>  4 - (x1^2 + x2^2) >= 0"""
    x1, x2 = X
    return 4 - (x1**2 + x2**2)

def constraint2_ineq(X):
    """x2 <= 0  =>  -x2 >= 0"""
    x1, x2 = X
    return -x2

# Список ограничений для scipy.optimize.minimize
constraints = [
    {'type': 'ineq', 'fun': constraint1_ineq},
    {'type': 'ineq', 'fun': constraint2_ineq}
]

# Начальная точка для поиска (можно выбрать любую точку в допустимой области или рядом с ней)
initial_guess = [0.0, -1.0] # Например, точка (0, -1)

print("--- Поиск минимума ---")
# Поиск минимума
res_min = minimize(objective_function, initial_guess, method='SLSQP', constraints=constraints)

if res_min.success:
    print(f"\nУсловный локальный минимум найден в точке: x = {res_min.x}")
    print(f"Минимальное значение f(X): f(x) = {res_min.fun}")
    min_point = res_min.x
    min_value = res_min.fun
else:
    print("Поиск минимума не удался:", res_min.message)
    min_point = None
    min_value = None


print("\n--- Поиск максимума ---")
# Для поиска максимума минимизируем отрицательную целевую функцию
def negative_objective_function(X):
    return -objective_function(X)

res_max = minimize(negative_objective_function, initial_guess, method='SLSQP', constraints=constraints)

if res_max.success:
    print(f"\nУсловный локальный максимум найден в точке: x = {res_max.x}")
    # Не забудьте обратить знак обратно для истинного максимального значения
    print(f"Максимальное значение f(X): f(x) = {-res_max.fun}")
    max_point = res_max.x
    max_value = -res_max.fun
else:
    print("Поиск максимума не удался:", res_max.message)
    max_point = None
    max_value = None

print("\n--- Проверка с результатами из картинки ---")
print(f"Минимум на картинке: (0,0), f(0,0) = 0^2 + (0-1)^2 = 1")
print(f"Максимум на картинке: (0,-2), f(0,-2) = 0^2 + (-2-1)^2 = (-3)^2 = 9")


# --- Построение графика ---
plt.figure(figsize=(8, 8))
ax = plt.gca()
ax.set_aspect('equal', adjustable='box')

# Определяем диапазон для осей x1 и x2
x1_vals = np.linspace(-2.5, 2.5, 400)
x2_vals = np.linspace(-2.5, 2.5, 400)
X1, X2 = np.meshgrid(x1_vals, x2_vals)

# Область допустимых значений (федеральная область)
# Круг x1^2 + x2^2 <= 4
circle_mask = X1**2 + X2**2 <= 4
# Нижняя полуплоскость x2 <= 0
lower_half_mask = X2 <= 0
# Пересечение обеих областей
feasible_region_mask = circle_mask & lower_half_mask

# Отображаем допустимую область
plt.imshow(feasible_region_mask, extent=(x1_vals.min(), x1_vals.max(), x2_vals.min(), x2_vals.max()),
           origin='lower', cmap='Greens', alpha=0.3)

# Рисуем окружность x1^2 + x2^2 = 4
theta = np.linspace(0, 2*np.pi, 100)
plt.plot(2 * np.cos(theta), 2 * np.sin(theta), 'b--', label='Ограничение $x_1^2 + x_2^2 = 4$')

# Рисуем линию x2 = 0
plt.axhline(0, color='red', linestyle='--', label='Ограничение $x_2 = 0$')

# Контурные линии целевой функции f(X) = const
Z = objective_function([X1, X2])
# Выбираем уровни так, чтобы они проходили через найденные экстремумы и другие интересные точки
levels = sorted(list(set([1, 9, 0.5, 2, 5, 8]))) # f(0,0)=1, f(0,-2)=9
plt.contour(X1, X2, Z, levels=levels, colors='purple', linestyles='solid', alpha=0.7)
plt.colorbar(label='$f(X) = x_1^2 + (x_2 - 1)^2$')

# Отмечаем найденные точки
if min_point is not None:
    plt.plot(min_point[0], min_point[1], 'ro', markersize=8, label=f'Минимум ({min_point[0]:.2f}, {min_point[1]:.2f})')
    plt.text(min_point[0] + 0.1, min_point[1] + 0.1, f'A (f={min_value:.2f})', color='black', fontsize=10)

if max_point is not None:
    plt.plot(max_point[0], max_point[1], 'bo', markersize=8, label=f'Максимум ({max_point[0]:.2f}, {max_point[1]:.2f})')
    plt.text(max_point[0] + 0.1, max_point[1] + 0.1, f'B (f={max_value:.2f})', color='black', fontsize=10)


# Центр целевой функции (1,0)
plt.plot(0, 1, 'kx', markersize=8, label='Центр $f(X)$ (0,1)')

plt.xlabel('$x_1$')
plt.ylabel('$x_2$')
plt.title('Графическое решение задачи оптимизации')
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend()
plt.xlim(-2.5, 2.5)
plt.ylim(-2.5, 2.5)
plt.show()