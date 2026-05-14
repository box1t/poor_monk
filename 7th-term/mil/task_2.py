#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from pathlib import Path
import csv
import argparse
import math
import matplotlib.pyplot as plt

def task1(N:int, m:int=30, dt:int=100, out_prefix:Path=Path("task1_variant")):
    bases = [9,12,7,5,6,7,5,5,7,6]
    intervals = [(i*100, (i+1)*100) for i in range(10)]
    dn = [b + N for b in bases]
    omega = [d/(m*dt) for d in dn]
    rows = []
    for i,(t0,t1) in enumerate(intervals, start=1):
        rows.append({"k":i,"t_start":t0,"t_end":t1,"t_mid":0.5*(t0+t1),"Δn":dn[i-1],"ω̂":omega[i-1]})
    csv_path = out_prefix.with_suffix(".csv")
    with csv_path.open("w", newline="", encoding="utf-8") as f:
        w=csv.DictWriter(f, fieldnames=rows[0].keys()); w.writeheader(); w.writerows(rows)
    plt.figure()
    plt.step([r["t_mid"] for r in rows], [r["ω̂"] for r in rows], where="mid")
    plt.xlabel("t (ч)"); plt.ylabel("ω̂(t) (1/ч на комплект)"); plt.title("Оценка потока отказов ω̂(t)")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5); plt.tight_layout()
    png_path = out_prefix.with_name(out_prefix.name + "_omega.png"); plt.savefig(png_path); plt.close()
    return rows, csv_path, png_path

def task1_prob_after(Texp:int, tau_list, omega_last):
    import math
    return [math.exp(-omega_last * tau) for tau in tau_list]

def task2(N:int, tmins_base:list):
    tmins = [x + N for x in tmins_base]
    mean_min = sum(tmins) / len(tmins)
    mean_h = mean_min / 60.0
    mu = 1.0 / mean_h
    return tmins, mean_min, mean_h, mu

def task2_probs(mu:float, times_h:list):
    import math
    return [1.0 - math.exp(-mu*t) for t in times_h]

def task3_required_time(mu:float, p:float):
    import math
    return -math.log(1.0 - p) / mu

def task4_poisson(N:int):
    import math
    rates = [0.0001,0.0002,0.0004,0.0006,0.0007]
    lam = N * sum(rates)
    p0 = math.exp(-lam)
    p_ge1 = 1 - p0
    p1 = lam * p0
    return lam, p0, p_ge1, p1

def main():
    ap = argparse.ArgumentParser(description="Комплексный расчёт задач 1–4")
    ap.add_argument("--N", type=int, default=19)
    args = ap.parse_args()
    N = args.N

    rows, csv1, png1 = task1(N, out_prefix=Path(f"task1_N{N}"))
    print(f"[Task 1] CSV: {csv1}, PNG: {png1}")
    omega_last = rows[-1]["ω̂"]
    probs = task1_prob_after(1000, [0.5, 2, 8, 24], omega_last)
    print(f"[Task 1B] ω_last={omega_last:.6f}; P0(0.5,2,8,24h)={tuple(round(p,6) for p in probs)}")

    tmins_base = [58,22,12,30,46,18,24,10,25,55]
    tmins, mean_min, mean_h, mu = task2(N, tmins_base)
    print(f"[Task 2] times(min)+N: {tmins}; TB={mean_min:.2f} min={mean_h:.4f} h; mu={mu:.5f} 1/h")

    times_h = [mean_h, 1.0, 1.5, 2.0, 2.5]
    probs2 = task2_probs(mu, times_h)
    print(f"[Task 2] P<= (TB,1,1.5,2,2.5h)={tuple(round(p,6) for p in probs2)}")

    for p in [0.95, 0.90]:
        t_req = task3_required_time(mu, p)
        hh = int(t_req); mm = int(round((t_req - hh)*60))
        print(f"[Task 3] t for P≥{p}: {t_req:.3f} h ≈ {hh}h {mm}m")

    lam, p0, p_ge1, p1 = task4_poisson(N)
    print(f"[Task 4] λ_total={lam:.6f}; P0={p0:.6f}; P>=1={p_ge1:.6f}; P1={p1:.6f}")

if __name__ == "__main__":
    main()