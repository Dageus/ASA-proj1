# !!!! meter os tempos na variável tempos e o x na variável tamanhos
# !!!! para evitar possíveis erros metam os tamanhos com string e os tempos como inteiros
# !!!! o array dos tamanhos tem de ter dimensão igual ao dos tempos
import matplotlib.pyplot as plt


#Primeiro gráfico
tamanhos1 = [4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]
tempos = [9, 9, 10, 10, 15, 15, 22, 70, 150, 472, 1138]

plt.plot(tamanhos1, tempos, marker = '|', alpha=1)
plt.xlabel('Tamanho')
plt.ylabel('Tempo')
plt.title('', fontsize=10)     # meter o título entre as plicas

plt.show()


#Segundo gráfico
tamanhos2 = [2**x for x in tamanhos1]
tempos = [9, 9, 10, 10, 15, 15, 22, 70, 150, 472, 1138]


plt.plot(tamanhos2, tempos, marker = '|', alpha=1)
plt.xlabel('Tamnho')
plt.ylabel('Tempo')
plt.title('', fontsize=10)     # meter o título entre as plicas

plt.show()
