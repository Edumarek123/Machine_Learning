#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../rpglib/rpglib.h"


void configura(){
  numero_jogadores=1000;
  numero_deTorneios=1000;
  gerar_dataLogs=0;
}

int main(int argc, char const *argv[])
{
    configura();
    jogador *populacao=(jogador* )malloc(sizeof(jogador));
    populacao->anterior = NULL;
    populacao->proximo = NULL;
    gerar_dados(populacao);
    // shuffle_grupo(populacao);
    if(gerar_dataLogs)
      analisar_classes(populacao, 0);
    torneios(populacao);
    return(0);
}
