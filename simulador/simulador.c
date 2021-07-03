#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../rpglib/rpglib.h"


void configura(){
  numero_jogadores=1000000;
  numero_bots=10000;
  numero_deTorneios=1000;
  gerar_dataLogs=1;
}


void gerar_bots(jogador *populacao, float *modelo);
float* carrega_modelo();

int main()
{
    configura();
    jogador *populacao=(jogador* )malloc(sizeof(jogador));
    populacao->anterior = NULL;
    populacao->proximo = NULL;
    float *modelo=(float*)malloc(7*sizeof(float));
    //comeca
    modelo=carrega_modelo();
    gerar_bots(populacao, modelo);
    gerar_dados(populacao);
    analisar_classes(populacao, 0);
    torneios(populacao);
}

void gerar_bots(jogador *populacao,float *modelo)
{
    int i, j, vida, defesa, ataque;
    float ataque_temp;
    char* classe;
    srand(time(NULL));
    for(i=1;i<=numero_bots;i++)
    {
      do
      {
        defesa=rand()%19;
        vida=(rand()%18)+1;
      }while((defesa<modelo[5])&&(defesa>modelo[6]) && (vida<modelo[3])&&(vida>modelo[4]));
      ataque_temp=(((modelo[1]*defesa)-vida+modelo[0])/modelo[2]);
      ataque=ataque_temp;
      classe="Dalek";
      inserir_elemento(populacao, classe, vida, defesa, ataque, i+numero_jogadores);
    }
}

float* carrega_modelo()
{
  float *modelo=(float*)malloc(7*sizeof(float));
  FILE *arquivo=fopen("../modelo.txt", "r");
  fscanf(arquivo, "%f %f %f %f %f %f %f", &modelo[0], &modelo[1], &modelo[2], &modelo[3], &modelo[4], &modelo[5], &modelo[6]);
  return(modelo);
}
