#include"A.h"

  nodo* acha_antecessor(nodo * no){
    nodo * antecessor = no -> esquerda;
    while(antecessor -> direita != NULL){
      antecessor = antecessor -> direita;
    }
    return antecessor;
  }

  int calcula_altura(nodo* no) {
    if (no == NULL) {
      return 0;
    }
    int alt_dir = calcula_altura(no -> direita);
    int alt_esq = calcula_altura(no -> esquerda);
    if (alt_dir > alt_esq ) return (alt_dir + 1);
    else  return (alt_esq + 1);

  }

  int calcula_raiz(nodo *aux) {
    return (calcula_altura(aux -> direita) - calcula_altura(aux -> esquerda));
  }

  void listar ( nodo * no, int altura ){
  	if (no != NULL ){
      listar(no -> esquerda, altura + 1);
  		printf( "%d", no -> chave);
  		no -> altura = altura;
  		printf(", %d\n", no -> altura);
  		listar(no -> direita , altura+1);
  	}
  }

  nodo *encontra_raiz(nodo*no){
    if (no == NULL){
      return NULL;
    }
    while(no -> pai != NULL)
      no = no -> pai;
    return no;
  }

  nodo *balanceamento(nodo *no) {
    nodo *raiz = no;
    nodo *aux = no;
      aux -> altura = calcula_raiz(aux);
      if (aux -> altura < -1) { // desbalanceado para a esquerda
        if ((aux -> esquerda -> esquerda) != NULL) {
          aux = LL(aux);
        }
        else{
          aux = LR(aux);
      }
    }
      else if (aux -> altura > 1) {// desbalanceado para a direita
        if ((aux -> direita -> direita) != NULL) {
          aux = RR(aux);
        }
        else{
          aux = RL(aux);
      }
    }
    raiz = aux;
    return raiz;
  }

  nodo *excluir_chave_raiz(nodo *no, nodo *antecessor)  {
    no -> chave = antecessor -> chave;
    if (antecessor -> esquerda != NULL) {
      nodo *antecessor_filho = antecessor -> esquerda;
      antecessor -> pai -> direita = antecessor_filho;
      antecessor_filho -> pai = no -> pai;
    }
    else antecessor -> pai -> direita = NULL;
    return no;
  }

  nodo* excluir_um (nodo *no, nodo *sub){
  	if (no -> pai -> esquerda -> chave == no -> chave) {
    	no -> pai -> esquerda = sub;
    }
    if (no -> pai -> direita -> chave == no -> chave) {
    	no -> pai -> direita = sub;
    }
    sub -> pai = no -> pai;
    return no;
  }

  nodo *excluir_dois(nodo *no, nodo *antecessor) {
    no -> chave = antecessor -> chave;
    if ((antecessor-> esquerda == NULL) && (antecessor -> direita == NULL)){
    	if ( antecessor -> pai -> direita -> chave == antecessor -> chave)
    		antecessor -> pai -> direita = NULL;
    	else antecessor -> pai -> esquerda = NULL;
       	free(antecessor);
        return no;
    }
    if (antecessor -> esquerda != NULL) {
    	antecessor -> pai -> esquerda = antecessor -> esquerda ;
        antecessor -> esquerda -> pai = antecessor -> pai;
    }

    if (no -> pai -> esquerda -> chave == no -> chave) {
     	if (antecessor -> chave != no -> esquerda -> chave)
            antecessor -> esquerda = no -> esquerda;
        no -> pai -> esquerda = antecessor;
        antecessor -> pai = no -> pai;
        antecessor -> direita = no -> direita;
        no -> esquerda -> pai = antecessor;
    }
    if (no -> pai -> direita -> chave == no -> chave) {
        if (antecessor -> chave != no -> esquerda -> chave) {
    	    antecessor -> esquerda = no -> esquerda;
        }
        no -> pai -> direita = antecessor;
        antecessor -> pai = no -> pai;
        antecessor -> direita = no -> direita;
        no -> direita -> pai = antecessor;
    }

    return no;
  }

  nodo* excluir(nodo *raiz, nodo* no){

    if ((no -> direita == NULL) && (no -> esquerda == NULL) ){ // CASO I = NO É FOLHA
        nodo *papai = no -> pai;
        if (papai -> direita == no) papai -> direita = NULL;
        else papai -> esquerda = NULL;
        return no;
    }
    if (raiz -> chave == no -> chave) {
      nodo *antecessor = acha_antecessor(no);
      excluir_chave_raiz(no, antecessor);
    }
    else if ((no -> direita != NULL) && (no -> esquerda != NULL) ) { // CASO IV = NO TEM DOIS FILHO A ESQUERDA
      nodo *antecessor = acha_antecessor(no);
      excluir_dois(no, antecessor);
    }
    else if ((no -> direita != NULL )|| (no -> esquerda != NULL )) {
      if (no -> esquerda != NULL) {
         // CASO II = NO TEM UM FILHO A ESQUERDA
        no = excluir_um(no, no -> esquerda);
      }
      else {
         // CASO III = NO TEM UM FILHO A DIREITA
        no = excluir_um(no, no -> direita);
      }
    }
    return no;
  }

  nodo *busca(nodo* raiz, nodo* no, int chave) {
    if (chave < no -> chave )
      busca(raiz, no -> esquerda, chave);
    else if (chave > no -> chave )
      busca(raiz,no -> direita, chave);
    else {
      no = excluir(raiz, no);
    }
    return no ;
  }

  nodo *insert(int chave,  nodo *no, int altura_h) {
    if (no == NULL) {
      nodo *no = malloc(sizeof(nodo));
      no -> chave = chave;
      no -> direita = NULL;
      no -> esquerda = NULL;
      no -> altura = altura_h;
      no -> pai = NULL;
      return no;
    }
    if (chave > no -> chave) {
      no -> direita = insert(chave, no -> direita, altura_h + 1);
      no -> altura_dir ++;
      no -> direita -> pai = no;
    } else {
      no -> esquerda = insert(chave, no -> esquerda, altura_h + 1);
      no -> altura_esq++;
      no -> esquerda -> pai = no;
    }
    no = balanceamento(no);
    return no;
  }

  nodo* LL(nodo * no) {
    nodo * temp = no;
    nodo * esq = no -> esquerda;
    temp -> esquerda = esq -> direita;
    if ( esq -> direita != NULL)esq -> direita -> pai = temp;
    esq -> direita = temp;
    esq -> pai = temp -> pai;
    temp -> pai = esq;
    return esq;
  }

  nodo* LR(nodo * no) {
    nodo * temp = no;
    nodo * esq = no -> esquerda;
    nodo * dir = esq -> direita;
    dir -> pai = temp -> pai;
    esq -> direita = dir -> esquerda;
    temp -> esquerda = dir -> direita;
    dir -> direita = temp;
    dir -> esquerda = esq;
    temp -> pai = dir;
    esq -> pai = dir;
    return dir;
  }

  nodo* RL(nodo * no) {
    nodo * temp = no;
    nodo * dir = no -> direita;
    nodo * esq = dir -> esquerda;
    esq -> pai = temp -> pai;
    dir -> esquerda = esq -> direita;
    temp -> direita = esq -> esquerda;
    esq -> esquerda = temp;
    esq -> direita = dir;
    temp -> pai = esq;
    dir -> pai = esq;
    return esq;
  }

  nodo* RR(nodo * no) {
    nodo * temp = no;
    nodo * dir = no -> direita;
    temp -> direita = dir -> esquerda;
    if ( dir -> esquerda != NULL) dir -> esquerda -> pai = temp;
    dir -> esquerda = temp;
    dir -> pai = temp -> pai;
    temp -> pai = dir;
    return dir;
  }
