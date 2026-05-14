#!/bin/bash

# 1. Формат даты
TIMESTAMP=$(date +"%Y-%m-%d_%H-%M-%S")

# 2. Правильный путь (через $HOME)
TARGET_DIR="$HOME/Documents/poor_monk/poor_monk/os_admin_scripts/shell_ops/bash_hist"
OUTPUT_FILE="$TARGET_DIR/bash_hist_$TIMESTAMP.txt"

# 3. Создаем дерево папок, если его нет
mkdir -p "$TARGET_DIR"

# 4. Сохраняем историю текущей сессии в файл ~/.bash_history
history -a

# 5. Копируем файл истории в архив
# Исправлено расширение на .bash_history
if [ -f "$HOME/.bash_history" ]; then
    cat "$HOME/.bash_history" > "$OUTPUT_FILE"
    echo "История успешно выгружена в: $OUTPUT_FILE"
else
    echo "Ошибка: файл ~/.bash_history не найден."
fi
