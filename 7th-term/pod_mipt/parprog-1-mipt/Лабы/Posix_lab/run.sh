#!/bin/bash

# Провера количества переданных параметров при вызове: минимум 1
if [ "$#" -lt 1 ]; then
    echo "Expected 2 params : $0 <FILE_NAME ~ hello.c/cpp>"
    exit 1
fi

# Проверка ввода 1ого параметра: введено название файла формата <hello.c>
if ! [[ "$1" =~ ^[a-zA-Z0-9_-]+\.c(pp)?$ ]]; then
    echo "Wrong 1st param input: Expected: <~(hello.c)>, Got: ($1)."
    exit 1
fi

# Сохраняем переданные параметры в переменные
SOURCE_FILE="$1"
N_THREAD="$2"

# Сдвиг маркера аргументов вызова. Все остальные аргументы передаются в вызываемую функцию.
shift 1

# Очищать ли папки ERRORS,OUTPUTS?
echo "Clear ERRORS and OUTPUTS dirs? [Y/any]"
read input
if [ "$input" == "Y" ]; then
     rm -r "./ERRORS" "./OUTPUTS"
     echo "Directories cleared."
fi

# Создание необходимых директорий
mkdir -p "./UTILS" "./ERRORS" "./OUTPUTS"

# Компиляция файла
if ["${SOURCE_FILE##*.}" == "c"]; then
     gcc "./$SOURCE_FILE" -o "./UTILS/compiled_code" -pthread
else
     g++ -pthread "./$SOURCE_FILE" -o "./UTILS/compiled_code"
fi

# Проверка кода исполнения
if [ $? -eq 0 ]; then
    echo "Compilation of $SOURCE_FILE successful."
else
    echo "Compilation of $SOUTCE_FILE failed."
    exit 1
fi

# Создание нового .sh файла для последующего добавления в очередь задач
# ===========
cat <<EOF > "./UTILS/mpi_script.sh"
#!/bin/bash
#SBATCH --job-name=${SOURCE_FILE%%.*}
#SBATCH --output=./OUTPUTS/${SOURCE_FILE%%.*}-%j.out
#SBATCH --error=./ERRORS/${SOURCE_FILE%%.*}-%j.err
#SBATCH --ntasks=$N_THREAD
#SBATCH --time=00:05:00

# Запуск задачи и передача всех оставшихся аргументов вызова run.sh в неё
./UTILS/compiled_code $@
EOF
#===========

# Отправка новой задачи в очередь
chmod +x ./UTILS/mpi_script.sh
OUTPUT=$(sbatch ./UTILS/mpi_script.sh)

# Проверка кода завершения
if [ $? -ne 0 ]; then
    echo "SBATCH error: Can't add new task."
    exit 1
fi

# Вывод возврата вызова постановки в консоль
echo "$OUTPUT"

# Извлечение Job ID добавленной задачи
job_id=$(echo "$OUTPUT" | awk '{print $4}')

# Бинд Ctrl+C на завершение исполнения кода задачи
cleanup() {
    echo -e "\nCtrl+C detected. Shutting down..."
    echo -e "\nRemoving job from squeue..."
    scancel "$job_id"
    exit 0
}
trap cleanup SIGINT

# Вывод результата проверки занятости задачи
squeue -j "$job_id" 2>/dev/null
# Функция для проверки состояния задачи
check_job_status() {
    squeue -j "$job_id" 2>/dev/null | awk 'NR==2'
}
# Циклический опрос состояния задачи
while true; do
    sleep 1
    job_status=$(check_job_status)
    if [ -z "$job_status" ]; then
        break
    fi
    echo "$job_status"
done

scontrol show job "$job_id"

echo -e "\n\n===ERROR==="
cat "./ERRORS/${SOURCE_FILE%%.*}-${job_id}.err"
echo -e "\n\n===OUTPUT==="
cat "./OUTPUTS/${SOURCE_FILE%%.*}-${job_id}.out"
