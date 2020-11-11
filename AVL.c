#include"A.h"
#include<stdio.h>
  int main() {
    char opcao;
    int chave;
    nodo *raiz = NULL;
    while ( 0 < scanf("%c %i\n", &opcao, &chave)) {
      switch (opcao) {
        case 'i':
          raiz = insert(chave, raiz, 0);

          break;

        case 'r':
          raiz = busca(raiz,raiz, chave);
          raiz = balanceamento(raiz);
          break;
      }
    }
    listar(raiz,0);
    return 0;
  }
