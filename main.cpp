#include <iostream>
#include "matriz_lib.h"
#include "rede_neural_lib.h"
#include <time.h>


using namespace std;


int main()
{
  srand(time(NULL));

  float LEARNING_RATE=0.02;
  int tam_Lx=784, tam_Ly=10;
  vector<int> tams_Lh {64};

  RedeNeural* NN=new RedeNeural(tam_Lx, tam_Ly, tams_Lh, LEARNING_RATE);

  NN->TreinarRede("dataset/entradas.txt", "dataset/saidas.txt", 10, false);

  NN->salvar_rede();

  delete NN;

  return 0;
}

//g++ -o mnist main.cpp rede_neural_lib.cpp matriz_lib.cpp
