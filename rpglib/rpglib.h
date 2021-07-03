#ifndef RPGLIB_H
#define RPGLIB_H

int numero_jogadores;
int numero_deTorneios;
int gerar_dataLogs;
int numero_bots;

typedef struct jogador jogador;
struct jogador{
    int identificador;
    char* classe;
    int vida;
    int defesa;
    int ataque;
    jogador *anterior;
    jogador *proximo;
};

void inserir_elemento(jogador* lista, char* classe, int vida, int defesa, int ataque, int identificador);
void gerar_dados(jogador *populacao);
char* classifica_elemento(int vida, int defesa, int ataque);
void analisar_classes(jogador *populacao, int nome);
void shuffle_atributos(int* atributo);
void torneios(jogador* populacao);
void batalha(jogador* populacao, jogador* vencedores);
void remove_individuo_final(jogador* populacao);
void remove_individuo_inicial(jogador* lista);
void remove_individuo_n(jogador *lista, int n);
void verifica_paridade(jogador* lista);
int numero_populacao(jogador* lista);
void imprimi_quantidade_torneios(int i);
void imprimi_vencedor(jogador* lista);
void shuffle_grupo(jogador *lista);

#endif //RPGLIB_H
