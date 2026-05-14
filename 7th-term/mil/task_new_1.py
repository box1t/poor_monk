#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Расчёт показателей надёжности для Задачи 1 и построение графиков.
Формулы:
  n_start[0] = N0
  n_end[i]   = n_start[i] - Δn[i]
  λ_i        = Δn[i] / (n_start[i] * Δt)
  f_i        = Δn[i] / (N0 * Δt)
  P(t_end_i) = n_end[i] / N0,   Q = 1 - P
  
  T_cp_1 (до отказа всех объектов): T_cp = 1/n * Сумма(t_pi)
  T_cp_2 (из N0 отказало только n): T_cp = 1/n * [ Сумма(t_pi) + T * (N0 - n) ] = W_общ / n
  
Сохраняет CSV и PNG-графики в текущую папку.
"""

from dataclasses import dataclass
import argparse
import math
import csv
import pathlib
from typing import List, Tuple

import matplotlib.pyplot as plt


@dataclass
class Interval:
    t_start: int
    t_end: int
    base_dn: int

def make_intervals() -> List[Interval]:
    """Интервалы 0..3000 с шагом 100 и 'base' из таблицы (30 штук)."""
    bases = [
        50, 40, 32, 25, 20, 17, 16, 16, 15, 14,       # 0..1000
        15, 14, 14, 13, 14, 13, 13, 13, 14, 12,       # 1000..2000
        12, 13, 12, 13, 14, 16, 20, 25, 30, 40        # 2000..3000
    ]
    ints: List[Interval] = []
    t = 0
    for b in bases:
        ints.append(Interval(t, t + 100, b))
        t += 100
    return ints

def compute(N: int, N0: int, dt: int) -> Tuple[list, list]:
    """
    Возвращает список строк-результатов и накопительные величины:
    [общее_число_отказов, число_выживших_в_конце, общая_наработка_W_общ, W_отказавших].
    """
    intervals = make_intervals()
    rows = []
    n_start = N0
    cum_fail = 0
    total_working_hours = 0.0      # Общая наработка всех объектов (W_общ)
    failed_working_hours = 0.0     # Сумма наработок только отказавших объектов (Сумма t_pi)

    for k, iv in enumerate(intervals, start=1):
        dn = iv.base_dn + N
        n_end = n_start - dn
        if n_end < 0:
            raise ValueError(f"На интервале {iv.t_start}-{iv.t_end} число выживших стало отрицательным."
                             f" Проверьте параметры (N0={N0}, N={N}).")
        
        # Общая наработка на текущем интервале: n_start * dt
        total_working_hours += n_start * dt
        
        # Наработка отказавших объектов: dn * (t_start + dt/2) - (среднее по интервалу)
        # В интервальном анализе, каждый отказавший объект наработал t_mid
        t_mid = 0.5 * (iv.t_start + iv.t_end)
        failed_working_hours += dn * t_mid
        
        lam = dn / (n_start * dt)        # интенсивность отказов на интервале
        freq = dn / (N0 * dt)            # частота отказов
        P = n_end / N0                   # вероятность безотказной работы (к концу интервала)
        Q = 1.0 - P

        rows.append({
            "k": k,
            "t_start": iv.t_start,
            "t_end": iv.t_end,
            "t_mid": t_mid,
            "Δt": dt,
            "Δn": dn,
            "n_start": n_start,
            "n_end": n_end,
            "λ(t)": lam,
            "f(t)": freq,
            "P(t)": P,
            "Q(t)": Q
        })

        # подготовка к следующему интервалу
        n_start = n_end
        cum_fail += dn

    return rows, [cum_fail, n_start, total_working_hours, failed_working_hours]


def save_csv(rows: list, path: pathlib.Path):
    fieldnames = ["k", "t_start", "t_end", "t_mid", "Δt", "Δn",
                  "n_start", "n_end", "λ(t)", "f(t)", "P(t)", "Q(t)"]
    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for r in rows:
            writer.writerow(r)


def plot_all(rows: list, stem: pathlib.Path):
    """Рисует 4 графика: λ(t), f(t) (как гистограммы), P(t), Q(t) (сглаженные), а также совместный график P(t) и Q(t)."""
    t_start = [r["t_start"] for r in rows]
    t_mid = [r["t_mid"] for r in rows]
    t_end = [r["t_end"] for r in rows]
    dt = rows[0]["Δt"]  # Ширина интервала
    lam = [r["λ(t)"] for r in rows]
    freq = [r["f(t)"] for r in rows]
    P = [r["P(t)"] for r in rows]
    Q = [r["Q(t)"] for r in rows]
    
    # Добавим начальную точку для P(t) и Q(t) для лучшего вида на графике
    t_full = [0] + t_end
    P_full = [1.0] + P
    Q_full = [0.0] + Q

    # λ(t) - Гистограмма (используем plt.bar)
    plt.figure()
    plt.bar(t_start, lam, width=dt, align='edge', edgecolor='black', alpha=0.7, label='λ(t)')
    plt.xlabel("t, ч")
    plt.ylabel("λ(t), 1/ч")
    plt.title("Интенсивность отказов λ(t) (Гистограмма)")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.tight_layout()
    plt.savefig(stem.with_name(stem.name + "_lambda_hist.png"))

    # f(t) - Гистограмма (используем plt.bar)
    plt.figure()
    plt.bar(t_start, freq, width=dt, align='edge', edgecolor='black', alpha=0.7, label='f(t)')
    plt.xlabel("t, ч")
    plt.ylabel("f(t), 1/ч")
    plt.title("Частота отказов f(t) (Гистограмма)")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.tight_layout()
    plt.savefig(stem.with_name(stem.name + "_freq_hist.png"))
    
    # Совместный график P(t) и Q(t)
    plt.figure()

    # Добавляем прозрачные столбцы (как было в предыдущем варианте)
    plt.bar(t_start, P, width=dt, align='edge', color='lightblue', alpha=0.3, label='P(t) (интервалы)')
    plt.bar(t_start, Q, width=dt, align='edge', color='lightsalmon', alpha=0.3, label='Q(t) (интервалы)')

    # Затем рисуем линии поверх столбцов
    plt.plot(t_full, P_full, linestyle='-', label='P(t) - Кривая надежности', color='blue')
    plt.plot(t_full, Q_full, linestyle='-', label='Q(t) - Функция распределения наработки до отказа', color='orange')
    
    plt.xlabel("t, ч")
    plt.ylabel("P(t), Q(t)")
    plt.title("P(t) и Q(t) с точкой пересечения $P=Q=0.5$ (с интервалами)")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    
    # Поиск точки пересечения (где P(t) ≈ Q(t) ≈ 0.5) с помощью линейной интерполяции
    cross_k = -1
    for k in range(len(P_full) - 1):
        if P_full[k] >= 0.5 and P_full[k+1] < 0.5:
            cross_k = k
            break

    if cross_k != -1:
        t1, t2 = t_full[cross_k], t_full[cross_k+1]
        P1, P2 = P_full[cross_k], P_full[cross_k+1]
        
        t_cross = t1 
        if (P2 - P1) != 0:
            t_cross = t1 + (0.5 - P1) * (t2 - t1) / (P2 - P1)

        if 0 <= t_cross <= t_full[-1]:
            plt.axvline(x=t_cross, color='r', linestyle=':', linewidth=1.5, 
                        label=f'$T_{{0.5}}$ (Медианная наработка) $\\approx {t_cross:.2f}$ ч')
            plt.plot(t_cross, 0.5, 'ro', markersize=6)
            plt.text(t_cross + 50, 0.55, f'({t_cross:.0f}, 0.5)', 
                     color='r', verticalalignment='bottom')
                     
    plt.axhline(y=0.5, color='gray', linestyle='--', linewidth=0.5)

    plt.legend()
    plt.tight_layout()
    plt.savefig(stem.with_name(stem.name + "_P_Q_cross_with_bars.png"))

    # УДАЛЕНО: plt.show() - для предотвращения зависания

def calculate_T_cp_variants(N0: int, n: int, W_obj: float, W_fail: float, T_end: int) -> str:
    """
    Рассчитывает и форматирует вывод средней наработки до отказа по двум предположениям.
    W_obj - общая наработка (W_общ)
    W_fail - сумма наработок отказавших объектов (Сумма t_pi)
    """
    if n == 0:
        return "\nНевозможно рассчитать среднюю наработку: нет отказов (n=0)."

    # --- Предположение 1: Учитываются только отказавшие образцы ---
    # T_cp_1 = (Сумма t_pi) / n
    T_cp_1 = W_fail / N0
    
    # --- Предположение 2: Учитываются все образцы (Формула 5) ---
    # T_cp_2 = W_общ / n
    T_cp_2 = W_obj / n
    
    W_survivors = T_end * (N0 - n)

    output = f"""
--- Расчет средней наработки до отказа (T_cp) ---
Общие данные:
  T_общ (T_end) = {T_end} ч
  N_0 (начальное число объектов) = {N0}
  n (число отказавших объектов) = {n}
  W_общ (общая наработка всех объектов) = {W_obj:.0f} ч
  W_отказавших (Сумма t_pi) = {W_fail:.0f} ч
  W_выживших (наработка выживших объектов) = {W_survivors:.0f} ч ({N0 - n} объектов)

1. Испытание: до отказа всех объектов.
   Формула: T_cp_1 = Сумма(t_pi) / n
   T_cp_1 = {W_fail:.0f} / {N0} = {T_cp_1:.2f} ч

2. Испытание: из N0 отказало только n.
   Формула: T_cp_2 = 1/n * [ Сумма(t_pi) + T * (N0 - n) ] = W_общ / n
   T_cp_2 = {W_obj:.0f} / {n} = {T_cp_2:.2f} ч
"""
    return output


def main():
    ap = argparse.ArgumentParser(description="Задача 1: расчёт и графики.")
    ap.add_argument("--N", type=int, default=19, help="номер варианта N (сколько прибавлять к base)")
    ap.add_argument("--N0", type=int, default=2000, help="число образцов на старте")
    ap.add_argument("--dt", type=int, default=100, help="ширина интервала Δt, ч")
    ap.add_argument("--out", type=pathlib.Path, default=pathlib.Path("reliability_variant"),
                    help="префикс имени выходных файлов (без расширения)")
    args = ap.parse_args()

    # T_end - общее время испытаний (последний t_end)
    intervals = make_intervals()
    T_end = intervals[-1].t_end
    
    # total_working_hours (W_общ) и failed_working_hours (W_отказавших) добавлены в возвращаемое значение
    rows, results = compute(args.N, args.N0, args.dt)
    cum_fail, survivors_last, total_working_hours, failed_working_hours = results

    # Расчет T_cp по обоим предположениям
    T_cp_details = calculate_T_cp_variants(args.N0, cum_fail, total_working_hours, failed_working_hours, T_end)

    # Итог в консоль
    print("=" * 60)
    print("ИТОГОВЫЕ ПОКАЗАТЕЛИ НАДЕЖНОСТИ")
    print("=" * 60)
    print(f"Всего отказов: {cum_fail}  |  Выжило к {T_end} ч: {survivors_last} "
          f"({survivors_last/args.N0:.4f} из N0)")
    print("-" * 60)
    print(T_cp_details)
    print("=" * 60)

    # CSV и графики
    csv_path = args.out.with_suffix(".csv")
    save_csv(rows, csv_path)
    print(f"CSV сохранён: {csv_path}")

    plot_all(rows, args.out)
    print("Графики сохранены с суффиксами: _lambda_hist.png, _freq_hist.png, _P_Q_cross_with_bars.png (и другие)")


if __name__ == "__main__":
    main()