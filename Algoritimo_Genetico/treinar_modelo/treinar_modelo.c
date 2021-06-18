#include <stdlib.h>
#include <stdio.h>

typedef struct atributoi atributoi;
struct atributoi{
    int atributo;
    atributoi *anterior;
    atributoi *proximo;
};

int vida_minima=18;
int vida_maxima=0;
int defesa_minima=18;
int defesa_maxima=0;

void coleta_dados(atributoi* vidai,atributoi* defesai,atributoi* ataquei);
void saida_modelo(float b0, float b1, float b2);
void coleta_dados(atributoi* vidai,atributoi* defesai,atributoi* ataquei);
int somatorio(atributoi* lista1, atributoi* lista2, int constante);
float calculaB2(int matrizA[3][3], int matrizC[3]);
float calculaB1(int matrizA[3][3], int matrizC[3], float b2);
float calculaB0(int matrizA[3][3],int matrizC[3], float b1, float b2);
void inserir_elemento(atributoi* lista, int atributo);

int main()
{
  // [n, s_defesai, s_ataquei]
  // [s_defesai, s_defesai2, s_defesaixataquei]
  // [s_ataquei, s_defesaixataquei, s_ataquei2]
  //Inicia Listas
  int n=10000, s_defesai, s_ataquei, s_defesaixataquei, s_defesai2, s_ataquei2; //matrizA
  int s_vidai, s_vidaixdefesai, s_vidaixataquei; //matrizC
  int matrizA[3][3], matrizC[3]; //matrizes
  float b0, b1, b2; //coeficientes
  atributoi *vidai=(atributoi* )malloc(sizeof(atributoi));
  atributoi *defesai=(atributoi* )malloc(sizeof(atributoi));
  atributoi *ataquei=(atributoi* )malloc(sizeof(atributoi));
  vidai->anterior = NULL;
  vidai->proximo = NULL;
  defesai->anterior = NULL;
  defesai->proximo = NULL;
  ataquei->anterior = NULL;
  ataquei->proximo = NULL;
  //Coleta Dados
  coleta_dados(vidai, defesai, ataquei);
  s_defesai=somatorio(defesai, defesai, 1);
  s_ataquei=somatorio(ataquei, ataquei, 1);
  s_defesaixataquei=somatorio(defesai, ataquei, 0);
  s_defesai2=somatorio(defesai, defesai, 0);
  s_ataquei2=somatorio(ataquei, ataquei, 0);
  s_vidai=somatorio(vidai, vidai, 1);
  s_vidaixdefesai=somatorio(vidai, defesai, 0);
  s_vidaixataquei=somatorio(vidai, ataquei, 0);
  //carrega matrizA
  matrizA[0][0]=n;
  matrizA[1][0]=s_defesai;
  matrizA[2][0]=s_ataquei;
  matrizA[0][1]=s_defesai;
  matrizA[1][1]=s_defesai2;
  matrizA[2][1]=s_defesaixataquei;
  matrizA[0][2]=s_ataquei;
  matrizA[1][2]=s_defesaixataquei;
  matrizA[2][2]=s_ataquei2;
  //carrega matrizC
  matrizC[0]=s_vidai;
  matrizC[1]=s_vidaixdefesai;
  matrizC[2]=s_vidaixataquei;
  //calcula coeficientes
  b2=calculaB2(matrizA, matrizC);
  b1=calculaB1(matrizA, matrizC, b2);
  b0=calculaB0(matrizA, matrizC, b1, b2);
  //saida de dados
  saida_modelo(b0, b1, b2);
}

int somatorio(atributoi* lista1, atributoi* lista2, int constante)
{
  atributoi *temporarioA=lista1->anterior;
  atributoi *temporarioB=lista2->anterior;
  int somatorio=0;
  //Varredura
  if(constante==0)
    do
    {
      somatorio+=(temporarioA->atributo*temporarioB->atributo);
      temporarioA=temporarioA->proximo;
      temporarioB=temporarioB->proximo;
    }while(temporarioA!=NULL && temporarioB!=NULL);
  else
    do
    {
      somatorio+=(temporarioA->atributo*1);
      temporarioA=temporarioA->proximo;
    }while(temporarioA!=NULL);
  return(somatorio);
}

void coleta_dados(atributoi* vidai, atributoi* defesai, atributoi* ataquei)
{
  FILE *arquivo=fopen("../dados/vencedor.txt", "r");
  int atributos[3],i=0;
  //Coleta de Dados
  while((fscanf(arquivo, "%d %d %d", &atributos[0], &atributos[1], &atributos[2]))!=EOF)
  {
    inserir_elemento(vidai ,atributos[0]);
    inserir_elemento(defesai ,atributos[1]);
    inserir_elemento(ataquei ,atributos[2]);
    if(atributos[0]<vida_minima)
      vida_minima=atributos[0];
    if(atributos[0]>vida_maxima)
      vida_maxima=atributos[0];
    if(atributos[1]<vida_minima)
      defesa_minima=atributos[1];
    if(atributos[1]>vida_maxima)
      defesa_maxima=atributos[1];

  }
  fclose(arquivo);
}

void saida_modelo(float b0, float b1, float b2)
{
  //saida do modelo
  FILE *modelo=fopen("../modelo.txt", "w");
  fprintf(modelo, "%.4f %.4f %.4f %d %d %d %d", b0, b1, b2, vida_minima, vida_maxima, defesa_minima, defesa_maxima);
  fclose(modelo);
}

void inserir_elemento(atributoi* lista, int atributo)
{
    atributoi *novo_individuo=(atributoi* )malloc(sizeof(atributoi));
    novo_individuo->atributo=atributo;
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

float calculaB2(int matrizA[3][3], int matrizC[3])
{
  float b2, numerador, denominador;
  //calculos
  //numerador
  numerador=(((matrizC[0]*matrizA[0][1])-(matrizC[1]*matrizA[0][0])) * ((matrizA[0][2]*matrizA[0][1])-(matrizA[0][1]*matrizA[1][2]))); //2 primeiros pares
  numerador-=(((matrizC[1]*matrizA[0][2])-(matrizC[2]*matrizA[0][1])) * ((matrizA[0][1]*matrizA[1][0])-(matrizA[0][0]*matrizA[1][0]))); //2 pares restantes
  //denominador
  denominador=(((matrizA[0][1]*matrizA[2][0])-(matrizA[0][0]*matrizA[2][1])) * ((matrizA[0][2]*matrizA[1][0])-(matrizA[0][1]*matrizA[1][2]))); //2 primeiros pares
  denominador-=(((matrizA[0][2]*matrizA[2][1])-(matrizA[0][1]*matrizA[2][2])) * ((matrizA[0][1]*matrizA[1][0])-(matrizA[0][0]*matrizA[1][1])));
  //mata o monstro
  b2=numerador/denominador;
  return(b2);
}

float calculaB1(int matrizA[3][3], int matrizC[3], float b2)
{
  float b1, numerador, denominador;
  //calculos
  //numerador
  numerador=((matrizC[0]*matrizA[0][1])-(matrizC[1]*matrizA[0][0])); //primeiro pare
  numerador-=(((matrizA[0][1]*matrizA[2][0])-(matrizA[0][0]*matrizA[2][1])) * b2); //ultimo par.k
  //denominador
  denominador=((matrizA[0][1]*matrizA[1][0])-(matrizA[0][0]*matrizA[1][1])); //unico par
  //mata o monstro
  b1=numerador/denominador;
  return(b1);
}

float calculaB0(int matrizA[3][3],int matrizC[3], float b1, float b2)
{
  float b0, numerador, denominador;
  //calculos
  //numerador
  numerador=(matrizC[0]-(matrizA[1][0]*b1)-(matrizA[2][0]*b2));
  //denominador
  denominador=matrizA[0][0];
  //mata o monstro
  b0=numerador/denominador;
  return(b0);
}
