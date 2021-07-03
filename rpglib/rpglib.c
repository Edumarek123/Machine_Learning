#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../rpglib/rpglib.h"


void inserir_elemento(jogador* lista, char* classe, int vida, int defesa, int ataque, int identificador)
{
    jogador *novo_individuo=(jogador* )malloc(sizeof(jogador));
    novo_individuo->classe=classe;
    novo_individuo->vida=vida;
    novo_individuo->defesa=defesa;
    novo_individuo->ataque=ataque;
    novo_individuo->identificador=identificador;
    novo_individuo->proximo=NULL;
    if(lista->anterior==NULL)
    {
        lista->proximo=novo_individuo;
        lista->anterior=novo_individuo;
        novo_individuo->anterior=NULL;
    }
    else
    {
        novo_individuo->anterior=lista->proximo;
        lista->proximo->proximo=novo_individuo;
        lista->proximo=novo_individuo;
    }
}

void gerar_dados(jogador *populacao)
{
    int i, j, atributo[3]={0, 0, 0},somatorio=0, vida, defesa, ataque;
    char* classe;
    srand(time(NULL));
    for(i=1;i<=numero_jogadores;i++)
    {
        do
        {
            for(j=0;j<=3;j++)
                atributo[j]=rand()%19;
            shuffle_atributos(atributo);
            vida=atributo[0];
            defesa=atributo[1];
            ataque=atributo[2];
            somatorio=(vida+ataque+defesa);
        }while(somatorio>=18 || vida==0);
        classe=classifica_elemento(vida, defesa, ataque);
        //printf("%d - ", i);
        //printf("Classe: %s | Vida: %d | Defesa: %d | Ataque: %d\n", classe, vida, defesa, ataque);
        inserir_elemento(populacao, classe, vida, defesa, ataque, i);
    }
}

char* classifica_elemento(int vida, int defesa, int ataque)
{
    //Classes Defensivas
    if (defesa>13) //Tank
        return("Tank");
    //Classes Ofensivas
    if (ataque>13) //Assassino
        return("Assassino");
    //Classes Resistentes
    if (vida>13) //Barbaro
        return("Barbaro");
    //Padrao
    return("Humano");
}

void analisar_classes(jogador *lista, int nome)
{
    char* classe;
    jogador *temporario;
    FILE *arquivo;
    char str[25];
    temporario=lista->anterior;
    sprintf(str, "dados_torneio_%d.txt", nome);
    //Abrindo arquivo
    if(nome==0)
    {
        arquivo = fopen("dados_classes.txt", "w");
    }
    else
    {
        arquivo = fopen(str, "w");
    }
    //Varredura
    do
    {
        classe=temporario->classe;
        //printf("\n%s",classe);
        //transfere para o bloco de notas
        fprintf(arquivo, "%s\n",classe);
        //------//-----//
        temporario=temporario->proximo;
    }while(temporario!=NULL);
    //Fechando arquivo
    fclose(arquivo);
}

void shuffle_atributos(int* atributo)
{
    int rodadas=10;
    int i, temporario, escolhido1=0, escolhido2=0;
    for(i=0;i<=rodadas;i++)
    {
        escolhido1=rand()%3;
        escolhido1=escolhido2;
        while(escolhido2==escolhido1)
            escolhido2=rand()%3;
        temporario=atributo[escolhido1];
        atributo[escolhido1]=atributo[escolhido2];
        atributo[escolhido2]=temporario;
    }
}

void torneios(jogador* populacao)
{
    int i;
    for(i=1; i<=numero_deTorneios; i++)
    {
      jogador *vencedores=(jogador* )malloc(sizeof(jogador));
      vencedores->proximo=NULL;
      vencedores->anterior=NULL;
      verifica_paridade(populacao);
      do
      {
          batalha(populacao, vencedores);
          remove_individuo_final(populacao);
          remove_individuo_inicial(populacao);
      }while(populacao->proximo!=NULL && populacao->anterior!=NULL);
      populacao=vencedores;
      if(gerar_dataLogs)
        analisar_classes(vencedores, i);
      if(numero_populacao(populacao)==1)
        break;
    }
    imprimi_vencedor(populacao);
}

void batalha(jogador* populacao, jogador* vencedores)
{
    int turno;
    turno=rand()%2;
    int vida_anterior_inicial, vida_proximo_inicial;
    vida_anterior_inicial=populacao->anterior->vida;
    vida_proximo_inicial=populacao->proximo->vida;
    int dano=0;
    do
    {
      if(turno==0)
      {
        if(populacao->anterior->ataque>=populacao->proximo->defesa)//atk 1o > def 2o
        {
          dano=populacao->anterior->ataque-populacao->proximo->defesa;
          if(dano==0)
            dano=1;
          populacao->proximo->vida-=dano;
        }
        else //def 2o > atk 1o
        {
          dano=populacao->proximo->defesa-populacao->anterior->ataque;
          if(dano==0)
            dano=1;
          populacao->anterior->vida-=dano;
        }
        turno=1;
      }
      else
      {
        if(populacao->proximo->ataque>=populacao->anterior->defesa) //atk 2o > def 1o
        {
          dano=populacao->proximo->ataque-populacao->anterior->defesa;
          if(dano==0)
            dano=1;
          populacao->anterior->vida-=dano;
        }
        else //def 1o > atk 2o
        {
          dano=populacao->anterior->defesa-populacao->proximo->ataque;
          if(dano==0)
            dano=1;
          populacao->proximo->vida-=dano;
        }
        turno=0;
      }
    }while((populacao->anterior->vida>0) && (populacao->proximo->vida>0));
    //saida de dados
    if(populacao->proximo->vida<=0)
    {
      inserir_elemento(vencedores, populacao->anterior->classe, vida_anterior_inicial, populacao->anterior->defesa, populacao->anterior->ataque, populacao->anterior->identificador);
    }
    if(populacao->anterior->vida<=0)
    {
      inserir_elemento(vencedores, populacao->proximo->classe, vida_proximo_inicial, populacao->proximo->defesa, populacao->proximo->ataque, populacao->proximo->identificador);
    }
}

void remove_individuo_final(jogador* lista)
{
  if(lista->proximo->anterior!=NULL)
  {
    lista->proximo=lista->proximo->anterior;
    free(lista->proximo->proximo);
    lista->proximo->proximo=NULL;
  }
  else
  {
    free(lista->proximo);
    lista->proximo=NULL;
  }
}

void remove_individuo_inicial(jogador* lista)
{
  if(lista->anterior->proximo!=NULL)
  {
    lista->anterior=lista->anterior->proximo;
    free(lista->anterior->anterior);
    lista->anterior->anterior=NULL;
  }
  else
  {
    free(lista->anterior);
    lista->anterior=NULL;
  }
}

void remove_individuo_n(jogador *lista, int n)
{
  int i;
  jogador *temporario;
  jogador *deletar;
  temporario=lista->anterior;
  for(i=0;i<n-1;i++)
    temporario=temporario->proximo;
  deletar=temporario->proximo;
  temporario->proximo=temporario->proximo->proximo;
  temporario->proximo->anterior=temporario;
  free(deletar);
  printf("\nDeletado\n");
}

int numero_populacao(jogador* lista)
{
  int cont=0;
  jogador *temporario;
  temporario=lista->anterior;
  do
  {
    temporario=temporario->proximo;
    cont++;
  }while(temporario!=NULL);
  return(cont);
}

void verifica_paridade(jogador* lista)
{
  int cont=0, paridade;
  jogador *temporario;
  temporario=lista->anterior;
  do
  {
    temporario=temporario->proximo;
    cont++;
  }while(temporario!=NULL);
  paridade=cont%2;
  if (paridade!=0)
  {
    // shuffle_grupo(lista);
    remove_individuo_final(lista);
  }
}

void shuffle_grupo(jogador *lista)
{
  int n_total, i, j, sorteado;
  jogador *temporario;
  jogador *embaralhados=(jogador* )malloc(sizeof(jogador));
  n_total=numero_populacao(lista);
  for(i=0;i<n_total;i++, n_total--){
    do{
      sorteado=rand()%1000;
    }while(sorteado>=n_total);
    printf("%d  %d\n", n_total, sorteado);
    temporario=lista->anterior;
    for(j=0;j<sorteado;j++)
      temporario=temporario->proximo;
    inserir_elemento(embaralhados, temporario->classe, temporario->vida, temporario->defesa, temporario->ataque, temporario->identificador);
    remove_individuo_n(lista, sorteado);
  }
  lista=embaralhados;
}

void imprimi_quantidade_torneios(int i)
{
  FILE *arquivo;
  arquivo = fopen("iteracoes.txt", "w");
  fprintf(arquivo, "%d\n", i);
  fclose(arquivo);
}

void imprimi_vencedor(jogador* lista)
{
  FILE *arquivo=fopen("vencedor.txt", "a");
  jogador *temporario=lista->anterior;
  //Varredura
  do
  {
      fprintf(arquivo, "%d %d %d\n", temporario->vida, temporario->defesa, temporario->ataque);
      temporario=temporario->proximo;
  }while(temporario!=NULL);
  fclose(arquivo);
}
