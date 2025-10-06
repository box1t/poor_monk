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
    base_dn: int  # число отказов "base" из таблицы (до +N)


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
    """Возвращает список строк-результатов и накопительные величины."""
    intervals = make_intervals()
    rows = []
    n_start = N0
    cum_fail = 0

    for k, iv in enumerate(intervals, start=1):
        dn = iv.base_dn + N
        n_end = n_start - dn
        if n_end < 0:
            raise ValueError(f"На интервале {iv.t_start}-{iv.t_end} число выживших стало отрицательным."
                             f" Проверьте параметры (N0={N0}, N={N}).")
        lam = dn / (n_start * dt)        # интенсивность отказов на интервале
        freq = dn / (N0 * dt)            # частота отказов
        P = n_end / N0                   # вероятность безотказной работы (к концу интервала)
        Q = 1.0 - P
        t_mid = 0.5 * (iv.t_start + iv.t_end)

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

    return rows, [cum_fail, n_start]


def save_csv(rows: list, path: pathlib.Path):
    fieldnames = ["k", "t_start", "t_end", "t_mid", "Δt", "Δn",
                  "n_start", "n_end", "λ(t)", "f(t)", "P(t)", "Q(t)"]
    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for r in rows:
            writer.writerow(r)


def plot_all(rows: list, stem: pathlib.Path):
    """Рисует 4 графика: λ(t), f(t), P(t), Q(t)."""
    t_mid = [r["t_mid"] for r in rows]
    t_end = [r["t_end"] for r in rows]
    lam = [r["λ(t)"] for r in rows]
    freq = [r["f(t)"] for r in rows]
    P = [r["P(t)"] for r in rows]
    Q = [r["Q(t)"] for r in rows]

    # λ(t)
    plt.figure()
    plt.step(t_mid, lam, where="mid")
    plt.xlabel("t, ч")
    plt.ylabel("λ(t), 1/ч")
    plt.title("Интенсивность отказов λ(t)")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.tight_layout()
    plt.savefig(stem.with_name(stem.name + "_lambda.png"))

    # f(t)
    plt.figure()
    plt.step(t_mid, freq, where="mid")
    plt.xlabel("t, ч")
    plt.ylabel("f(t), 1/ч")
    plt.title("Частота отказов f(t)")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.tight_layout()
    plt.savefig(stem.with_name(stem.name + "_freq.png"))

    # P(t)
    plt.figure()
    plt.step(t_end, P, where="post")
    plt.xlabel("t, ч")
    plt.ylabel("P(t)")
    plt.title("Вероятность безотказной работы P(t)")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.tight_layout()
    plt.savefig(stem.with_name(stem.name + "_P.png"))

    # Q(t)
    plt.figure()
    plt.step(t_end, Q, where="post")
    plt.xlabel("t, ч")
    plt.ylabel("Q(t)")
    plt.title("Вероятность отказа Q(t)")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.tight_layout()
    plt.savefig(stem.with_name(stem.name + "_Q.png"))

    # показать на экране (можно закомментировать в headless-средах)
    plt.show()


def main():
    ap = argparse.ArgumentParser(description="Задача 1: расчёт и графики.")
    ap.add_argument("--N", type=int, default=19, help="номер варианта N (сколько прибавлять к base)")
    ap.add_argument("--N0", type=int, default=2000, help="число образцов на старте")
    ap.add_argument("--dt", type=int, default=100, help="ширина интервала Δt, ч")
    ap.add_argument("--out", type=pathlib.Path, default=pathlib.Path("reliability_variant"),
                    help="префикс имени выходных файлов (без расширения)")
    args = ap.parse_args()

    rows, (cum_fail, survivors_last) = compute(args.N, args.N0, args.dt)

    # Итог в консоль
    print(f"Всего отказов: {cum_fail}  |  Выжило к 3000 ч: {survivors_last} "
          f"({survivors_last/args.N0:.4f} из N0)")

    # CSV и графики
    csv_path = args.out.with_suffix(".csv")
    save_csv(rows, csv_path)
    print(f"CSV сохранён: {csv_path}")

    plot_all(rows, args.out)
    print("Графики сохранены с суффиксами: _lambda.png, _freq.png, _P.png, _Q.png")


if __name__ == "__main__":
    main()


#python3 main.py --N 8 --N0 2000 --dt 100 --out variant8