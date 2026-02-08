cups_number, decreasing_rate, heat = map(int, input().split())
heat_of_cups = list(map(int, input().split()))
 
finish_times = [0] * cups_number
 
for i in range(cups_number):
    if heat_of_cups[i] > heat:
        finish_times[i] += (heat_of_cups[i] - heat + decreasing_rate - 1) // decreasing_rate
        # before: finish_times[i] += (heat_of_cups[i] // decreasing_rate) * heat

print(max(finish_times))



# # Считываем входные данные
# n, d, h = map(int, input().split())
# heat_of_cups = list(map(int, input().split()))

# # Нам нужно, чтобы ВСЕ чашки остыли. 
# # Это произойдет тогда, когда остынет самая горячая из них.
# max_heat = max(heat_of_cups)

# if max_heat <= h:
#     print(0)
# else:
#     # Разница температур, которую нужно погасить
#     diff = max_heat - h
#     # Время = diff / d с округлением вверх
#     # Формула (a + b - 1) // b — это стандартный способ округления вверх в целых числах
#     time_needed = (diff + d - 1) // d
#     print(time_needed)
