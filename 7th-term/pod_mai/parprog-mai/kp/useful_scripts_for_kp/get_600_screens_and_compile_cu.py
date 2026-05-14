import os

# 1. Настройка путей CUDA (чтобы не было ошибок toolchain)
os.environ['PATH'] += ':/usr/local/cuda/bin'
os.environ['LD_LIBRARY_PATH'] += ':/usr/local/cuda/lib64'

# 2. Установка системных библиотек (OpenGL и утилиты сборки)
print("Установка системных библиотек...")
!sudo apt-get update > /dev/null
!sudo apt-get install -y libglew-dev freeglut3-dev libglu1-mesa-dev libgl1-mesa-dev build-essential xvfb > /dev/null

# 3. Создание Makefile
# Флаг -arch=sm_75 критически важен для Tesla T4 в Colab
makefile_content = """
NVCC = nvcc
# sm_75 соответствует видеокарте Tesla T4 в Colab
FLAGS = -std=c++11 -arch=sm_75 -Wno-deprecated-gpu-targets
LIBS = -lGL -lGLU -lglut -lGLEW

all:
\t$(NVCC) $(FLAGS) main.cu -o kp $(LIBS)

clean:
\trm -rf kp
"""

with open('Makefile', 'w') as f:
    f.write(makefile_content.replace('\\t', '\t'))

# 4. Сборка проекта
print("\n--- Сборка проекта через Make ---")
!make clean
!make all

# 5. Проверка и запуск (через виртуальный дисплей, чтобы не было ошибок GLUT)
if os.path.exists('kp'):
    print("\n--- Сборка завершена! ---")
    print("Запускаю программу (через xvfb)...")
    # Используем xvfb-run, чтобы обмануть GLUT/OpenGL в облаке
    !xvfb-run -s "-screen 0 1024x768x24" ./kp
else:
    print("\n--- Ошибка компиляции. Проверьте main.cu ---")