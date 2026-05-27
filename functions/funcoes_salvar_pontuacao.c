#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_salvar_pontuacao.h"


void criar_arquivo(char *arquivo){
    FILE *arq;
    arq = fopen(arquivo,"a");
    if (arq!=NULL){
        fclose(arq);
    }
    return;    
}

void inserir_texto_arquivo(char *arquivo, char *texto){
    FILE *arq = fopen(arquivo, "a");
    if (arq != NULL){
        fprintf(arq,"%s\n",texto);
        fprintf(arq,"",texto);
        fclose(arq);
    }
    return;
}

void mostrar_texto_arquivo(char *arquivo,int linhas, int colunas, char saida[linhas][colunas]){
    FILE *arq = fopen(arquivo,"r");
    if (arq==NULL)
        return;
    for (int i=0;i<linhas,!feof(arq), fgets(saida[i], sizeof(saida[i]), arq) != NULL;i++){   
            int len = strlen(saida[i]);
            if (len > 0 && saida[i][len - 1] == '\n') {
                saida[i][len - 1] = '\0';
            }
    }
    fclose(arq);
}


