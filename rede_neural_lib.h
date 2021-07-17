//
// Created by Edumarek on 27/06/2021.
//

#ifndef REDE_NEURAL_LIB_H
#define REDE_NEURAL_LIB_H
#include "matriz_lib.h"
#include <vector>

using namespace std;

class RedeNeural{
public:
    float LEARNIG_RATE;
    int numero_layers;
    int tam_layer_x;
    int tam_layer_y;
    vector<int> tam_layers;

    vector<Matriz*> weights_layers;
    vector<Matriz*> bias_layers;
    vector<Matriz*> erros;
    vector<Matriz*> saidas;

    RedeNeural(int tam_Lx, int tam_Ly, vector<int> tams_hl, float alfa_learn);//ok
    RedeNeural()=delete;//ok
    ~RedeNeural();//ok

    void imprimir_rede();//ok
    void salvar_rede();//ok

    void FeedFoward(Matriz* input_layer); //ok
    void Calcula_Erros(Matriz* saidas_esperadas); //ok
    void BackPropagation(Matriz* entradas); //ok

    void TreinarRede(const std::string entradas,const std::string saidas_esperadas, int porcentagem_testes, bool logs);
};

void covolucao_saidas(Matriz* m);

int contagem_dados(std::string path_arquivo);
Matriz* separa_dados(std::string linha);

#endif //REDE_NEURAL_LIB_H
