#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "pecas.h"
#include "placar.h"
#include "funcoes_placar.h"
#include "utilis.h"
#include "constants.h"

placar *allocar_placar(){
    placar *aux = malloc(sizeof(placar));
    if (aux==NULL) 
        return NULL;
    return aux;
}

void iniciar_placar(placar **head,int quant_pecas){
    *head = NULL;
}

void adicionar_lista(placar **head,int pecas){
    if (*head!=NULL){
        placar *aux = *head;
        aux->numero = pecas;
    }else{
        placar *aux = allocar_placar();
        aux->numero=pecas;
        aux->proximo=NULL;
        *head = aux;
        }
        return;
    }

void mostrar_placar(placar **head1, placar **head2){
    placar *aux1 = *head1;
    placar *aux2= *head2;
    DrawText(TextFormat("Peças mortas pelo jogador 1 : %d",aux1->numero),3*280,60,20,BLACK);
    DrawText(TextFormat("Peças mortas pelo jogador 2 : %d",aux2->numero),3*280,90,20,BLACK);
        
}

void liberar_placar(placar **head1, placar **head2){
    placar *aux1 = *head1;
    placar *aux2= *head2;

    free(aux1);
    aux1=NULL;
    free(aux2);
    aux2=NULL;
}





