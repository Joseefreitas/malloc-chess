#ifndef SALVAR_PONTUACAO_H
#define SALVAR_PONTUACAO_H
#include <stdio.h>


void criar_arquivo(char *arquivo);

void inserir_texto_arquivo(char *arquivo, char *texto);

void mostrar_texto_arquivo(char *arquivo,int linhas, int colunas, char saida[linhas][colunas]);

#endif