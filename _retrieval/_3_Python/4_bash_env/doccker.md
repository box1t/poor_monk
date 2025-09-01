Да, можно запускать и управлять Docker без использования Docker Desktop, полностью через консоль. Для этого необходимо установить Docker Engine на вашей системе. Вот как это можно сделать:

### Установка Docker Engine
Для разных операционных систем процесс установки немного отличается.

#### Ubuntu (и другие Debian-based дистрибутивы)
1. **Удалите старые версии:**
   ```bash
   sudo apt-get remove docker docker-engine docker.io containerd runc
   ```

2. **Установите необходимые пакеты:**
   ```bash
   sudo apt-get update
   sudo apt-get install \
       apt-transport-https \
       ca-certificates \
       curl \
       gnupg \
       lsb-release
   ```

3. **Добавьте официальный Docker GPG ключ:**
   ```bash
   curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
   ```

4. **Добавьте Docker репозиторий:**
   ```bash
   echo \
     "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu \
     $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
   ```

5. **Установите Docker Engine:**
   ```bash
   sudo apt-get update
   sudo apt-get install docker-ce docker-ce-cli containerd.io
   ```

6. **Проверьте установку:**
   ```bash
   sudo docker run hello-world
   ```

#### CentOS
1. **Удалите старые версии:**
   ```bash
   sudo yum remove docker \
                 docker-client \
                 docker-client-latest \
                 docker-common \
                 docker-latest \
                 docker-latest-logrotate \
                 docker-logrotate \
                 docker-engine
   ```

2. **Установите необходимые пакеты:**
   ```bash
   sudo yum install -y yum-utils
   ```

3. **Добавьте Docker репозиторий:**
   ```bash
   sudo yum-config-manager \
       --add-repo \
       https://download.docker.com/linux/centos/docker-ce.repo
   ```

4. **Установите Docker Engine:**
   ```bash
   sudo yum install docker-ce docker-ce-cli containerd.io
   ```

5. **Запустите Docker:**
   ```bash
   sudo systemctl start docker
   sudo systemctl enable docker
   ```

6. **Проверьте установку:**
   ```bash
   sudo docker run hello-world
   ```

### Основные команды Docker через консоль
После установки Docker Engine вы можете использовать следующие команды для управления контейнерами:

- **Запуск контейнера:**
  ```bash
  docker run <image>
  ```
  Например:
  ```bash
  docker run ubuntu
  ```

- **Запуск контейнера в фоновом режиме:**
  ```bash
  docker run -d <image>
  ```

- **Запуск контейнера с интерактивным терминалом:**
  ```bash
  docker run -it <image> /bin/bash
  ```

- **Список запущенных контейнеров:**
  ```bash
  docker ps
  ```

- **Список всех контейнеров:**
  ```bash
  docker ps -a
  ```

- **Остановка контейнера:**
  ```bash
  docker stop <container_id>
  ```

- **Удаление контейнера:**
  ```bash
  docker rm <container_id>
  ```

- **Список изображений:**
  ```bash
  docker images
  ```

- **Удаление изображения:**
  ```bash
  docker rmi <image_id>
  ```

### Дополнительные ресурсы
- [Официальная документация Docker](https://docs.docker.com/)
- [Docker GitHub](https://github.com/docker/docker-ce)

Эти шаги помогут вам использовать Docker без Docker Desktop, полностью через консоль.