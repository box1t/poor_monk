
y, u, s, f, r = int(input()), int(input()), int(input()), int(input()), int(input())

if f >= 2 or r >= 6:
    print("-")
elif r == 5 or (y < 2002 and u < 2021):
    if s >= 9:
        print("-")
    else:
        print("?")
else:
    print("+")
