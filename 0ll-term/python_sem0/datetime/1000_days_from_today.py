# Write a Python script that calculates and prints the date and time exactly 1000 days from today.

import datetime

# 1. Получаем текущие дату и время
now = datetime.datetime.now()

# 2. Создаем объект timedelta, представляющий интервал в 1000 дней
time_delta = datetime.timedelta(days=1000)

# 3. Прибавляем этот интервал к текущему времени
future_date = now + time_delta

# 4. Выводим результат в понятном формате
print("Сегодня:", now.strftime("%d.%m.%Y %H:%M:%S"))
print("Через 1000 дней будет:", future_date.strftime("%d.%m.%Y %H:%M:%S"))