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
import sys
out_file = open("benchmark.csv", "w+")

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

out_file.write("R,C,A,matrix_size,mean_seq,mean_par\n")

while(R < 300):
    R = R + 10
    C = C + 10
    A = A + 10
    matrix_size = R * C * A
    out_file.write(f"{R},{C},{A},{matrix_size},")

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
        print(f"R: {R} C: {C} A: {A} Matriz: {matrix_size} - Teste {i+1}/10 - SEQ: {time_seq:.4f} PAR: {time_par:.4f}")

    mean_seq = np.mean(exec_times_seq)
    mean_par = np.mean(exec_times_par)
    means_seq[matrix_size] = mean_seq
    means_par[matrix_size] = mean_par
    out_file.write(f"{mean_seq:.4f},{mean_par:.4f}\n")
    print(f"R: {R} C: {C} A: {A} Matriz: {matrix_size} - MEAN SEQ: {mean_seq:.4f}, MEAN PAR: {mean_par:.4f}")


fig, ax = plt.subplots()
ax.plot(list(means_seq.keys()), list(means_seq.values()),
        label='Sequencial', color='#394a6d')
ax.plot(list(means_par.keys()), list(means_par.values()),
        label='Paralelo', color='#52de97')
ax.legend()
ax.grid()

ax.set(xlabel='tamanho da matriz', ylabel='tempo de execução médio para 10 testes')

plt.savefig('exec_times.png')

out_file.close()
