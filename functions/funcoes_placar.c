/*
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "pecas.h"
#include "placar.h"
#include <utilis.h>

placar *allocar_placar(int quantidade){
    placar *aux = malloc(quantidade*sizeof(placar));
    if (aux==NULL) 
        return NULL;
    return aux;
}

void iniciar_placar(placar **head,int quant_pecas, pecas* jogador){
    *head = NULL;

} /*

void adicionar_lista(placar **head,int ){

}
*/
/*
void setpontuacao(placar **head,int quant_pecas, pecas* jogador){
    placar *aux = allocar_placar(quant_pecas);
    if (*head!=NULL){
        int i=0;
        while(aux!=NULL){
            (aux)->numero = i;
            (aux)->pecas_jogador = jogador[i].pecas_jogador;
            (aux) = (aux)->proximo;
            i++;
        }
    }
    else{
        (aux)->numero = 0;
        (aux)->pecas_jogador = jogador[0].pecas_jogador;
        *head = aux;
    }
}

void remover_peca(placar **head, int posicao, pecas* jogador){
    placar *aux = *head;
    if (*head!=NULL){
      if (posicao==0){
         *head=aux->proximo ;
         free(aux);
         return; 
      }  
      placar *pres = *head;
      int contador = 0;
      while(pres!=NULL && contador!=posicao){
        contador++;
        pres = aux;
        aux=aux->proximo;
      }
      if (aux!=NULL){
        pres->proximo=aux->proximo;
        free(aux);
      }    
    }else{
        printf("Não é possível remover\n");
        return;
    }

}
void mostrar_placar(placar *head){
    placar *aux = head;
    while (aux!=NULL){
        printf("%c %d",aux->pecas_jogador,aux->numero);
        aux=aux->proximo;
    }

}
*/