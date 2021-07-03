@echo off
cd dados\
gcc -o gerador_deDados gerador_deDados.c ..\rpglib\rpglib.c

@echo Gerando Dados:
FOR /L %%A IN (1,1,1000) DO (gerador_deDados.exe && cls && @echo Gerando Dados: && @echo Simulacao: [%%A / 1000])
@echo Ok.
cd ..\treinar_modelo\
gcc -o treinar_modelo treinar_modelo.c

@echo Treinando Modelo:
treinar_modelo.exe
@echo Ok.
cd ..\graficos\
@echo Plotando Graficos:
py graficos_dispersao.py
cd ..\
@echo Ok.

@echo Movendo Dados Importantes:
copy dados\vencedor.txt logs\
move graficos\dispersao_concentraca_atributos_entre_vencedores1.png logs\
move graficos\dispersao_concentraca_atributos_entre_vencedores2.png logs\
move graficos\dispersao_concentraca_atributos_entre_vencedores3.png logs\
move modelo.txt logs\
@echo Ok.

@echo Apagando Arquivos Residuais:
del dados\gerador_deDados.exe
del treinar_modelo\treinar_modelo.exe
@echo Ok.

cd simulador\
gcc -o simulador simulador.c ..\rpglib\rpglib.c

@echo Realizando Simulacao:
simulador.exe
del vencedor.txt
@echo Ok.

cd ..\graficos\

@echo Gerando Graficos:
py graficos_populacao.py
@echo Ok.

cd ../

@echo Organizando Graficos:
move graficos\populacao_inicial.png logs\
FOR /L %%A IN (0,1,17) DO (move graficos\populacao_torneio%%A.png logs)
@echo Ok.

@echo Deletando Arquivos Residuais:
FOR /L %%A IN (1,1,19) DO (del simulador\dados_torneio_%%A.txt)
del simulador\dados_classes.txt
del simulador\simulador.exe
del dados\vencedor.txt
@echo Ok.

pause
