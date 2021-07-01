@echo off
cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\dados\
gcc -o gerador_deDados gerador_deDados.c

@echo Gerando Dados:
FOR /L %%A IN (1,1,1000) DO (gerador_deDados.exe && cls && @echo Gerando Dados: && @echo Simulacao: [%%A / 1000])
@echo Ok.
cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\treinar_modelo\
gcc -o treinar_modelo treinar_modelo.c

@echo Treinando Modelo:
treinar_modelo.exe
@echo Ok.
cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\graficos\
@echo Plotando Graficos:
py -3.7-64 graficos_dispersao.py
@echo Ok.

@echo Movendo Dados Importantes:
copy C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\dados\vencedor.txt C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\logs
move C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\graficos\dispersao_concentraca_atributos_entre_vencedores1.png C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\logs
move C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\graficos\dispersao_concentraca_atributos_entre_vencedores2.png C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\logs
move C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\graficos\dispersao_concentraca_atributos_entre_vencedores3.png C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\logs
move C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\modelo.txt C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\logs
@echo Ok.

@echo Apagando Arquivos Residuais:
cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\dados\ && del gerador_deDados.exe
cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\treinar_modelo\ && del treinar_modelo.exe
@echo Ok.

cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\simulador\
gcc -o simulador simulador.c

@echo Realizando Simulacao:
simulador.exe
@echo Ok.

cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\graficos\

@echo Gerando Graficos:
py -3.7-64 graficos_populacao.py
@echo Ok.

@echo Organizando Graficos:
move C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\graficos\populacao_inicial.png C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\logs
FOR /L %%A IN (0,1,18) DO (move C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\graficos\populacao_torneio%%A.png C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\logs)
@echo Ok.

@echo Deletando Arquivos Residuais:
FOR /L %%A IN (0,1,19) DO (del C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\simulador\dados_torneio_%%A.txt)
del C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\simulador\dados_classes.txt
del C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\simulador\simulador.exe
del C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Machine_Learning\dados\vencedor.txt

pause
