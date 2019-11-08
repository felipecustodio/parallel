# -*- coding: utf-8 -*-

"""
Programa auxiliar para gerar
casos de teste e seus resultados esperados.
"""

import numpy as np
import matplotlib.pyplot as plt
import sys
sys.stdout = open('test_output.out', 'w')


with open('input.in', 'r') as file:
    data = file.read().replace('\n', '')
    R = int(data[0])
    C = int(data[1])
    A = int(data[2])
    S = int(data[3])


np.random.seed(seed=S)
grades = np.random.randint(low=0, high=100, size=(R, C, A))


city_averages = {}
for index_region, region in enumerate(grades):
    if(index_region > 0): 
        print()
    for index_city, city in enumerate(region):
        print(f"Regiao {index_region} - Cid {index_city}: ", end='')
        menor = np.min(city)
        maior = np.max(city)
        mediana = np.median(city)
        media = np.average(city)
        DP = np.std(city)
        city_averages[(index_region, index_city)] = media
        print(f"menor: {menor}, maior: {maior}, mediana: {mediana}, media: {media} e DP: {DP}")


print()


region_averages = {}
for index_region, region in enumerate(grades):
    print(f"Regiao {index_region}: ", end='')
    menor = np.min(region)
    maior = np.max(region)
    mediana = np.median(region)
    media = np.average(region)
    DP = np.std(region)
    region_averages[index_region] = media
    print(f"menor: {menor}, maior: {maior}, mediana: {mediana}, media: {media} e DP: {DP}")


print()


print(f"Brasil: ", end='')
menor = np.min(grades)
maior = np.max(grades)
mediana = np.median(grades)
media = np.average(grades)
DP = np.std(grades)
print(f"menor: {menor}, maior: {maior}, mediana: {mediana}, media: {media} e DP: {DP}")


print()


melhor_regiao = max(region_averages.keys(), key=(lambda key: region_averages[key]))
melhor_cidade_regiao = max(
    city_averages.keys(), key=(lambda key: city_averages[key]))[0]
melhor_cidade = max(
    city_averages.keys(), key=(lambda key: city_averages[key]))[1]


print(f"Melhor regiao: Regiao {melhor_regiao}")
print(f"Melhor cidade: Regiao {melhor_cidade_regiao}, Cidade {melhor_cidade}")
