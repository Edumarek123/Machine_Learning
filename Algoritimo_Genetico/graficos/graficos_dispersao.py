import numpy  as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.cm as cm
import matplotlib
import random

vida=[]
defesa=[]
ataque=[]

#Spearador de Dados
def separador_atributos(arquivo):
    vida_max=0
    vida_min=18
    def_max=0
    def_min=18
    atk_max=0
    atk_min=18
    numero_pontos=0
    linha=arquivo.readline()
    while linha:
        atributos=linha.split()
        #transfere para txt
        vida.append(int(atributos[0]))
        if(int(atributos[0])>vida_max):
            vida_max=int(atributos[0])
        if(int(atributos[0])<vida_min):
            vida_min=int(atributos[0])
        defesa.append(int(atributos[1]))
        if(int(atributos[1])>def_max):
            def_max=int(atributos[1])
        if(int(atributos[1])<def_min):
            def_min=int(atributos[1])
        ataque.append(int(atributos[2]))
        if(int(atributos[2])>atk_max):
            atk_max=int(atributos[2])
        if(int(atributos[2])<atk_min):
            atk_min=int(atributos[2])
        numero_pontos+=1
        linha=arquivo.readline()
    arquivo.close()
    return(vida_max, vida_min, def_max, def_min, atk_max, atk_min, numero_pontos)


def frequencia_absoluta(atributo ,atributo_max, atributo_min, numero_pontos):
    num_atributo=[0]*18
    maior_F=0
    for i in range((atributo_max-atributo_min)+1): #verifica todos valores de atributo
        for j in range(numero_pontos): #varre todo os pontos
            if(atributo[j]==(i+1)): #se a atributo bater com a que esta sendo avaliada
                num_atributo[i]+=((1/numero_pontos)) #armazena vetor def atk para atributo=[i]
        if(num_atributo[i]>maior_F):
            maior_F=num_atributo[i]
    return(num_atributo)

def ajuste_cmap(frequencia_vida, frequencia_def, frequencia_atk, numero_pontos):
    c=[]
    for i in range(numero_pontos):
            c.append((frequencia_vida[(vida[i]-1)])*(frequencia_def[(defesa[i]-1)])*(frequencia_atk[(ataque[i]-1)]))
    return(c)

def modelo_calculado():
    modelo=open("../modelo.txt", "r")
    linha=modelo.readline()
    coeficientes=linha.split()
    vida_amostras=[]
    atk_amostras=[]
    def_amostras=[0]*90
    for i in range(90):
        if(i!=0):
            def_amostras[i]=def_amostras[i-1]+0.2
        else:
            def_amostras[i]=0.2
    for i in range(90):
        atk_amostras.append(((float(coeficientes[1])*def_amostras[i])+(np.random.randint(int(coeficientes[3]),float(coeficientes[4])))+float(coeficientes[0]))/float(coeficientes[2]))
    for i in range(90):
            vida_amostras.append((float(coeficientes[1])*def_amostras[i])+(float(coeficientes[2])*(atk_amostras[i]))+float(coeficientes[0]))
    return(def_amostras, atk_amostras, vida_amostras)


#recolhe dados
arquivo=open("../dados/vencedor.txt", "r")
vida_max, vida_min, def_max, def_min, atk_max, atk_min, numero_pontos=separador_atributos(arquivo)
frequencia_vida=frequencia_absoluta(vida ,vida_max, vida_min, numero_pontos)
frequencia_def=frequencia_absoluta(defesa ,def_max, def_min, numero_pontos)
frequencia_atk=frequencia_absoluta(ataque ,atk_max, atk_min, numero_pontos)
c=ajuste_cmap(frequencia_vida, frequencia_def, frequencia_atk, numero_pontos)
def_amostras, atk_amostras, vida_amostras=modelo_calculado()

#plotando
fig=plt.figure()
ax=fig.add_subplot(111, projection='3d')
ax.text2D(0.05, 0.95, "Dispersao & Concentração Atributos(Vencedores)", transform=ax.transAxes)
ax.scatter(defesa, ataque, vida, cmap="cool", c=c)
ax.plot_trisurf(def_amostras, atk_amostras, vida_amostras, color="red")
ax.set_xlabel("Defesa",fontsize=13)
ax.set_ylabel("Ataque",fontsize=13)
ax.set_zlabel("Vida",fontsize=13)
#ax.legend(loc=3, bbox_to_anchor=(-0.5, -0.1))

#saida
ax.view_init(elev=30, azim=45)
fig=plt.gcf()
fig.savefig("dispersao_concentraca_atributos_entre_vencedores1.png", format='png')
ax.view_init(elev=30, azim=-20)
fig=plt.gcf()
fig.savefig("dispersao_concentraca_atributos_entre_vencedores2.png", format='png')
ax.view_init(elev=15, azim=-50)
fig=plt.gcf()
fig.savefig("dispersao_concentraca_atributos_entre_vencedores3.png", format='png')
