d, v, p = map(float, input().split())

t = p * d / 100

start = v * t % 360

arc = p / 100 * 360

end = (start + arc) % 360

print(start, end, sep=' ')