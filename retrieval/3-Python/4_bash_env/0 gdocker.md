

# 1. Docker Container

```shell
# 1. Команды для работы с образами Docker

docker pull [имя_образа] # Загрузить образ из сети
docker images  # Список доступных образов 
docker build [путь_к_Dockerfile] # Создание образа на основе Dockerfile
docker rmi [id_образа] # Удалить образ

# 2. Команды управления контейнерами

docker run [id_образа] # Запуск контейнера на основе выбранного образа
    # Некоторые флаги для команды run:
    -d # Запуск с возвратом в консоль
    --name [имя] # Задать имя контейнеру
    --rm # Удалить контейнер после остановки
    -p [локальный_порт][порт_внутри_контейнера] # Проброс портов


docker stop [id/имя_контейнера] # Остановить контейнер
docker start [id/имя_контейнера] # Запустить существующий контейнер

docker attach [id/имя_контейнера] # Подключится к консоли контейнера
docker logs [id/имя_контейнера] # Вывести логи контейнера

docker ps # Список запущенных контейнеров
docker ps -a # Список всех контейнеров

# 3. Команды освобождения ресурсов

docker rm [id/имя_контейнера] # Удалить контейнер
docker container prune # Удалить все контейнеры


```

# 2. Docker Compose

```shell

# 1. Команды подготовки:

docker compose build # Создаёт образ автоматически и добавляет к нему метку (id).
docker compose up --no-build --detach 
docker compose up --remove-orphans

# 2. Команды управления контейнерами:

docker compose exec task-manager # запускает не контейнер, а службу. 
docker compose run task-manager sh/app 

docker compose pause task-manager
docker compose unpause task-manager - возобновили работу

docker compose start task-manager
docker compose stop task-manager
docker compose restart task-manager
docker compose kill task-manager

docker compose ps # выводит список запущенных контейнеров 
docker compose ps --services
docker compose ps --quiet
docker compose ps -a

# 3. Команды освобождения ресурсов

docker compose down # освободит ресурсы, занятые приложением compose
docker compose down --rmi local # удалит образ, созданный при запуске приложения. 
# относится к образам, созданным с учетом информации из файла Compose и не имеющим имен. 

docker compose down --rmi all # тег all в случае, если есть метка в yaml-файле
docker compose rm [name] # удаляет контейнеры по отдельности


# 4. Команды управления образами

docker compose images # выводит созданные образы

# 5. Команды мониторинга



# 6. Другие команды




```

# 3. Dockerfile

```dockerfile
FROM [имя_образа] # Задание базового образа
WORKDIR [путь] # Задание корневой директории внутри контейнера
COPY [путь_относительно_Dockefile] [путь_в_контейнере] # Копирование файлов
ADD [путь] [путь] # Аналогично команде выше
RUN [команда] # Команда которая запускается только при инициализации образа
CMD ["команда"] # Команда которая отрабатывает каждый раз при запуске контейнера
ENV КЛЮЧ="ЗНАЧЕНИЕ" # Установка переменных окружения
ARG ИМЯ=ЗНАЧЕНИЕ # Задание переменных для передачи Docker во время сборки образа
ENTRYPOINT ["команда"] # Команда которая запускается во время работы контейнера
EXPOSE порт/протокол # Указывает на необходимость открыть порт
VOLUME ["путь"] # Создаёт точку монтирования для работы с постоянным хранилищем
```

# 4. Dockerignore





# 5. YAML-file

