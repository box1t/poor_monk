#!/bin/bash

mkdir -p "./UTILS" "./ERRORS" "./OUTPUTS"
SOURCE_FILE="Lab_1.cpp"

# Проверка существования файла
if [ ! -f "./$SOURCE_FILE" ]; then
  echo "error: файл ./$SOURCE_FILE не найден!"
  exit 1
fi

# Компиляция файла
if ["${SOURCE_FILE##*.}" == "c"]; then
     mpicc "./$SOURCE_FILE" -o "./UTILS/compiled_code"
else
     mpic++ -o "./UTILS/compiled_code" "./$SOURCE_FILE"
fi

# Проверка кода исполнения
if [ $? -eq 0 ]; then
    echo "Compilation of $SOURCE_FILE successful."
else
    echo "Compilation of $SOUTCE_FILE failed."
    exit 1
fi


create_task_script() {
	local p=$1  # Первый параметр
	local N_t=$2  # Второй параметр

	# Создание нового .sh файла для последующего добавления в очередь задач
# =====================
cat << EOF > "./UTILS/mpi_script.sh"
#!/bin/bash
#SBATCH --job-name=${SOURCE_FILE%%.*}
#SBATCH --output=./OUTPUTS/${SOURCE_FILE%%.*}-%j.out
#SBATCH --error=./ERRORS/${SOURCE_FILE%%.*}-%j.err
#SBATCH --time=00:05:00
#SBATCH --ntasks=$p

# Загрузка нужного модуля (если требуется)
module load mpi

# Запуск задачи и передача всех оставшихся аргументов вызова run.sh в неё
mpirun -np $p ./UTILS/compiled_code $N_t
EOF
# =====================
}

# Функция для проверки состояния задачи
check_job_status() {
    squeue -j "$1" 2>/dev/null | awk 'NR==2'
}

rm -f results.txt

# Двойной цикл по всем комбинациям параметров
for p in {1..10}; do
  for N_t in {100..1000..100}; do
    echo "Запуск тестов> size:$p , N_t:$N_t"

    create_task_script $p $N_t

    chmod +x ./UTILS/mpi_script.sh
    OUTPUT=$(sbatch ./UTILS/mpi_script.sh)
    # Проверка кода завершения
    if [ $? -ne 0 ]; then
        echo "SBATCH error: Can't add new task."
        exit 1
    fi

    # Извлечение Job ID добавленной задачи
    job_id=$(echo "$OUTPUT" | awk '{print $4}')

    # Циклический опрос состояния задачи
    while true; do
    	sleep 1
    	job_status=$(check_job_status $job_id)
    	if [ -z "$job_status" ]; then
       		break
    	fi
    	echo "$job_status"
    done

    result=$(tr -d '\n' < "./OUTPUTS/${SOURCE_FILE%%.*}-${job_id}.out")
    # Запись в таблицу
    echo "$result" >> results.txt

  done
done
