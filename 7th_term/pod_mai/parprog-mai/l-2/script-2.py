import struct
import ctypes
from PIL import Image
import binascii

def display_hex_output(data, label):
    """Выводит данные в консоль в шестнадцатеричном формате (по 8 байт)."""
    hex_data = binascii.hexlify(data).decode('utf-8').upper()

    print(f"\n--- {label} (HEX) ---")

    # Форматирование вывода: 8 символов (4 байта) пробел 8 символов (4 байта)
    # 32 символа на строку = 16 байт
    for i in range(0, len(hex_data), 32):
        line = hex_data[i:i+32]
        formatted_line = ""
        for j in range(0, len(line), 8):
            formatted_line += line[j:j+8] + " "
        print(formatted_line.strip())
    print("-----------------------")

try:
    fin = open('out.data', 'rb')
except FileNotFoundError:
    print("Ошибка: Файл 'out.data' не найден. Убедитесь, что ваш CUDA-код скомпилировался и выполнился успешно.")
    exit()

# 1. Чтение и вывод заголовка (W и H)
header = fin.read(8)
(w, h) = struct.unpack('ii', header)

print(f"Image Dimensions (from out.data): W={w}, H={h}")
display_hex_output(header, "out.data Header (W H)")

# 2. Чтение и вывод пиксельных данных
data_size = 4 * w * h
buff = fin.read(data_size)
fin.close()

if len(buff) != data_size:
    print(f"Ошибка: Ожидалось {data_size} байт пиксельных данных, получено {len(buff)}.")
    exit()

display_hex_output(buff, "out.data Pixels")

# 3. Сохранение PNG
img = Image.new('RGBA', (w, h))
pix = img.load()

# Для Pillow, чтобы избежать ошибок с типом char (bytes),
# мы можем использовать буфер итератора
pixels = []
for i in range(0, data_size, 4):
    # struct.unpack_from('BBBB', ...) - это безопаснее,
    # так как компоненты r, g, b, a - это unsigned char (1 байт)
    r, g, b, a = struct.unpack_from('BBBB', buff, i)
    pixels.append((r, g, b, a))

# Загрузка пикселей в изображение
offset = 0
for j in range(h):
  for i in range(w):
    pix[i, j] = pixels[offset]
    offset += 1

img.save('out.png')
print("\n✅ Изображение успешно сохранено в 'out.png'.")