@echo off
cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\dados\
gcc -o gerador_deDados gerador_deDados.c
@echo Gerando Dados:
FOR /L %%A IN (1,1,10000) DO (gerador_deDados.exe && cls && @echo Gerando Dados: && @echo Simulacao: [%%A / 10000])
@echo Ok.
cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\treinar_modelo\
gcc -o treinar_modelo treinar_modelo.c
@echo Treinando Modelo:
treinar_modelo.exe
@echo Ok.
cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\graficos\
@echo Plotando Graficos:
py -3.7-64 graficos_dispersao.py
@echo Ok.
@echo Movendo Dados Importantes:
copy C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\dados\vencedor.txt C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\logs
move C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\graficos\dispersao_concentraca_atributos_entre_vencedores1.png C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\logs
move C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\graficos\dispersao_concentraca_atributos_entre_vencedores2.png C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\logs
move C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\graficos\dispersao_concentraca_atributos_entre_vencedores3.png C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\logs
move C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\modelo.txt C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\logs
@echo Ok.
@echo Apagando Arquivos Residuais:
cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\dados\ && del gerador_deDados.exe
cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\treinar_modelo\ && del treinar_modelo.exe
@echo Ok.
@echo off
cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\simulador\
gcc -o simulador simulador.c
@echo Realizando Simulacao:
simulador.exe
@echo Ok.
cd C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\graficos\
@echo Gerando Graficos:
py -3.7-64 graficos_populacao.py
@echo Ok.
@echo Organizando Graficos:
move C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\graficos\populacao_inicial.png C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\logs
FOR /L %%A IN (0,1,19) DO (move C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\graficos\populacao_torneio%%A.png C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\logs)
@echo Ok.
@echo Deletando Arquivos Residuais:
FOR /L %%A IN (0,1,19) DO (del C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\simulador\dados_torneio_%%A.txt)
del C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\simulador\dados_classes.txt
del C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\simulador\simulador.exe
del C:\Users\Edumarek\Desktop\bakcup2\projetos\estudoIA\Algoritimo_Genetico\dados\vencedor.txt
pause
