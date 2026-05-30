#ifndef FUNCOES_PLACAR_H
#define FUNCOES_PLACAR_H
#include "pecas.h"
#include "placar.h"


placar *allocar_placar();
void iniciar_placar(placar **head,int quant_pecas);

void adicionar_lista(placar **head,int pecas);
void liberar_placar(placar **head1, placar **head2);

#endif
