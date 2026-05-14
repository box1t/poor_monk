# Находим путь к g++ автоматически
CXX_PATH = $(shell which g++)
NVCC = nvcc
# Добавляем флаг -ccbin
FLAGS = -std=c++11 -Wno-deprecated-gpu-targets -ccbin $(CXX_PATH)

all:
	$(NVCC) $(FLAGS) main.cu -o kp

clean:
	rm -rf *.o kp