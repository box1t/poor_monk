# Write a Python script that displays the current time in 12-hour format with AM/PM notation.

import datetime

# Получаем текущее время
now = datetime.datetime.now()

# Форматируем время в 12-часовой формат с AM/PM
time_12h = now.strftime("%I:%M:%S %p")

print("Текущее время (12-часовой формат):", time_12h)