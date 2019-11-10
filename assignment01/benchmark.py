# -*- coding: utf-8 -*-

"""
Programa auxiliar para gerar
casos de teste e comparar os
tempos de execução entre código
sequencial e paralelo.
"""

import numpy as np
import matplotlib.pyplot as plt
import subprocess

# R = np.arange(3, 300, 10)
# C = np.arange(4, 400, 10)
# A = np.arange(6, 600, 10)
# S = 8

R = 3
C = 4
A = 6
S = 8
matrix_size = R * C * A


means_seq = {}
means_par = {}

while(R < 100):
    R = R + 10
    C = C + 10
    A = A + 10
    matrix_size = R * C * A
    print(f"R: {R} C: {C} A: {A} Matriz: {matrix_size}")

    with open("input.in", "w") as file:
        file.write(str(R) + "\n")
        file.write(str(C) + "\n")
        file.write(str(A) + "\n")
        file.write(str(S) + "\n")

    exec_times_seq = []
    exec_times_par = []
    for i in range(10):
        output_seq = subprocess.getoutput("./students_seq < input.in")
        output_par = subprocess.getoutput("./students_par < input.in")
        time_seq = float(output_seq.split(
            "Tempo de resposta sem considerar E/S, em segundos: ")[1])
        time_par = float(output_par.split(
            "Tempo de resposta sem considerar E/S, em segundos: ")[1])
        exec_times_seq.append(time_seq)
        exec_times_par.append(time_par)

    mean_seq = np.mean(exec_times_seq)
    mean_par = np.mean(exec_times_par)
    means_seq[matrix_size] = mean_seq
    means_par[matrix_size] = mean_par
    print(f"Média dos tempos de execução - SEQ: {mean_seq:.4f} PAR: {mean_par:.4f}")


plt.plot(list(means_seq.keys()), list(means_par.values()))
plt.show()

# mean_seq = np.mean(exec_times_seq)
# mean_par = np.mean(exec_times_par)

# print(f"Tempo de execução médio: SEQ: {mean_seq} PAR: {mean_par}")
