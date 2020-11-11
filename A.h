#ifndef __A__
#define __A__
#include<stdio.h>
#include<stdlib.h>

 typedef struct nodo {
  int chave;
  int altura;
  int altura_dir;
  int altura_esq;
  struct nodo* direita;
  struct nodo* esquerda;
  struct nodo* pai;
} nodo;

 nodo* insert(int chave,  nodo *no, int altura_h);
 void listar ( nodo * no, int altura);
 nodo *excluir_chave_raiz(nodo *no, nodo *antecessor) ;
 nodo* excluir_um (nodo *no, nodo *sub);
 nodo *excluir_dois(nodo *no, nodo *antecessor);
 nodo* excluir(nodo *raiz, nodo* no);
 int calcula_altura(nodo *no);
 int calcula_raiz(nodo *aux);
 nodo *encontra_raiz(nodo*no);
 nodo *busca(nodo* raiz, nodo* no, int chave);
 nodo *balanceamento(nodo *no);
 nodo* LL(nodo * no);
 nodo* LR(nodo * no);
 nodo* RL(nodo * no);
 nodo* RR(nodo * no);
#endif
