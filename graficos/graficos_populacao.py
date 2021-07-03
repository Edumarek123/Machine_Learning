import numpy  as np
import matplotlib.pyplot as plt
import matplotlib
import os

graficos_existentes=os.listdir("../simulador/")
cont=(len(graficos_existentes)-3)
for i in range(cont-1):
    file= open("../simulador/dados_torneio_"+str(i+1)+".txt", "r")
    nHumano=0
    nDalek=0
    linha=file.readline()
    while linha:
        classe=linha.split()
        if(classe[0]=="Humano"):
          nHumano+=1
        if(classe[0]=="Dalek"):
          nDalek+=1
        linha=file.readline()
    file.close()
    labels = ['Humanos', 'Daleks']
    sizes = [nHumano, nDalek]
    fig1, ax1=plt.subplots()
    ax1=plt.pie(sizes, labels=labels)
    #save
    fig = plt.gcf()
    fig.savefig('populacao_torneio'+str(i)+'.png', format='png')

file= open("../simulador/dados_classes.txt", "r")
nHumano=0
nDalek=0
linha=file.readline()
while linha:
    classe=linha.split()
    if(classe[0]=="Humano"):
      nHumano+=1
    if(classe[0]=="Dalek"):
      nDalek+=1
    linha=file.readline()
file.close()
labels = ['Humanos', 'Daleks']
sizes = [nHumano, nDalek]
fig1, ax1=plt.subplots()
ax1=plt.pie(sizes, labels=labels)
#save
fig = plt.gcf()
fig.savefig('populacao_inicial.png', format='png')
