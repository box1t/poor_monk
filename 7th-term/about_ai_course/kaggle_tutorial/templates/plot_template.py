
import numpy as np
from scipy import sparse
import matplotlib.pyplot as plt
from datetime import datetime
from pathlib import Path

# -------- Переменные для создания графика --------
timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
filename = f"plot_{timestamp}.png"
output_dir = Path("charts")
output_dir.mkdir(exist_ok=True)
file_path = output_dir / filename
# --------                                 --------

# -------- Папка для каждого дня --------
day_timestamp = datetime.now().strftime('%Y-%m-%d')
daily_dir = Path(f"plots_{day_timestamp}")
daily_dir.mkdir(exist_ok=True)
current_hour_sec_timestamp = datetime.now().strftime('%H-%M-%S')
#file_path = daily_dir / f"result_{current_hour_sec_timestamp}.png"
# --------                       --------


x = np.linspace(-10, 10, 100)
y = np.sin(x)
plt.plot(x, y, marker="x")

plt.savefig(file_path)