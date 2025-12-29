import random

def generate_test(n, filename="input.txt"):
    with open(filename, "w") as f:
        # Записываем размерность n
        f.write(f"{n}\n")
        
        # Генерируем матрицу A (n * n элементов)
        # Для Column-major записи в файл (строка за строкой) 
        # при считывании в твоем коде получится нужная структура.
        for i in range(n):
            row = [f"{random.uniform(-100, 100):.4f}" for _ in range(n)]
            f.write(" ".join(row) + "\n")
            
        # Генерируем вектор b (n элементов)
        b = [f"{random.uniform(-100, 100):.4f}" for _ in range(n)]
        f.write(" ".join(b) + "\n")

if __name__ == "__main__":
    N = 1024  # Можешь поменять на 2048 для еще более долгих тестов
    generate_test(N)
    print(f"Файл input.txt на {N} уравнений успешно создан.")