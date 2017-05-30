#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

TCabeca *criaCabeca(){
    // Criando um nó cabeça
	TCabeca *cabeca = (TCabeca *) malloc(sizeof(TCabeca));
    if (cabeca == NULL)
        return NULL;

    cabeca->prim = NULL;
    cabeca->ult = NULL;

    return cabeca;
}

TNo *insereInicio(TCabeca *cabeca, char k){
	// caso não houver cabeça criada
	if(cabeca == NULL)
		return NULL;

    // novo nó
	TNo *novo = malloc(sizeof(TNo));
    	if(novo == NULL)
		return NULL;

	novo->digito = k;
	novo->prox = cabeca->prim;
	cabeca->prim = novo;

	// caso a lista seja vazia, o cabeca->prim e cabeca->ult receberão o novo nó.
	if(cabeca->ult == NULL)
		cabeca->ult = novo;
	// caso contrário, o cabeca->ult continua tendo o mesmo nó.

	return novo;
}

TNo *insereFim(TCabeca *cabeca, char digito){
	if(cabeca == NULL) //se não houver cabeça criada
		return NULL;

	if(cabeca->ult == NULL) //se não tiver nenhum elemento, o prim e o ult são iguais: nó recém criado.
		return insereInicio(cabeca, digito);

	TNo *novo = (TNo*)malloc(sizeof(TNo)); //novo nó
	if(novo == NULL)
		return NULL;

	(cabeca->ult)->prox = novo; //o nó que até então é o último, passa a apontar para o novo último
	novo->prox = NULL;
	novo->digito = digito;
	cabeca->ult = novo; //ponteiro para o último é atualizado para o novo último

	return novo;
}

void deletaLista(TCabeca *cabeca){
    if(cabeca == NULL)
        return;

    TNo *ant = cabeca->prim;
    TNo *atual = cabeca->prim;

    while(atual != NULL){
        atual = ant->prox;
        free(ant);
        ant = atual;
    }

    cabeca->prim = NULL;
    cabeca->ult = NULL;
}

TCabeca *retornaMaiorLista(TCabeca *c1, TCabeca *c2){
	TNo *aux = c1->prim;
	TNo *aux2 = c2->prim;

	while(aux != NULL){
    	aux = aux->prox;
    	aux2 = aux2->prox;
    	if(aux2 == NULL) // se o aux2 já acabou, o c1 é a maior lista
        	return c1;
	}

	return c2; // se o aux já acabou, o c2 é a maior lista
}

TCabeca *somaListas(TCabeca *lista1, TCabeca *lista2){
    TCabeca *aux1 = lista1;
    TCabeca *aux2 = lista2;

    TCabeca *resultado = criaCabeca();
    unsigned short int vai = 0;
    unsigned short int n = 0;

    while(aux1->prim != NULL || aux2->prim != NULL){
        if(aux1->prim == NULL)
            insereInicio(aux1, '0');

        if(aux2->prim  == NULL)
            insereInicio(aux2, '0');
 
        n = (((aux1->prim->digito)-48) + ((aux2->prim->digito)-48) + vai) % 10;
        vai = (((aux1->prim->digito)-48) + ((aux2->prim->digito)-48) + vai) / 10;
        insereFim(resultado, n+48);

        aux1->prim = (aux1->prim)->prox;
        aux2->prim = (aux2->prim)->prox;
    }

    if(vai > 0)
        insereFim(resultado, vai+48);

    return resultado;
}

