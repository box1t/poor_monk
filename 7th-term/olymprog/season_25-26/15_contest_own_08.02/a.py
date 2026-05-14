cups_number, decreasing_rate, heat = map(int, input().split())
heat_of_cups = list(map(int, input().split()))
 
finish_times = [0] * cups_number
 
for i in range(cups_number):
    if heat_of_cups[i] > heat:
        finish_times[i] += (heat_of_cups[i] - heat + decreasing_rate - 1) // decreasing_rate
        # before: finish_times[i] += (heat_of_cups[i] // decreasing_rate) * heat

print(max(finish_times))


