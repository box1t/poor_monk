# Write a Python program to display the current date and time.
# Write a Python program that prints the current date and time in UTC format.

import datetime

now = datetime.datetime.now()

print(now.strftime("%Y-%m-%d %H:%M:%S"))

current_utc_time = datetime.datetime.now(datetime.timezone.utc)
print("Current UTC Date and Time:", current_utc_time.strftime("%Y-%m-%d %H:%M:%S UTC"))
