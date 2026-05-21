/*
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "pecas.h"
#include "placar.h"
#include <utilis.h>
#include <constants.h>

placar *allocar_placar(int quantidade){
    placar *aux = malloc(quantidade*sizeof(placar));
    if (aux==NULL) 
        return NULL;
    return aux;
}

void iniciar_placar(placar **head,int quant_pecas, pecas* jogador){
    *head = NULL;

}

void adicionar_lista(placar **head,int pecas, int time){
    if (*head!=NULL){
        placar *aux = *head;
        if (time==1){
            aux->numero = pecas;
        }
        else{
        aux=aux->next;
        aux->numero=pecas;}
    }else{
        placar *aux = allocar_placar(2);
        aux->numero = pecas;
        aux=aux->next;
        aux->numero=pecas;
        return;
    }
} 

void mostrar_placar(placar *head){
    placar *aux = head;
    int i=0;
    while (aux!=NULL){
        DrawText(TextFormat("Pecas eliminadas pelo jogador %d: %d",i,aux->numero),,BLACK);
        aux=aux->proximo;
        i++;
    }

}

void liberar_placar(placar **head){
    placar *aux = *head;
    free(aux->next);
    free(aux);
    aux=NULL;
}




*/