#ifndef TREE
#define TREE


/* ----- Bibliotecas ----- */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "product.h"


/* ----- Definicao do tipo link ----- */
typedef struct TREEnode* link;


struct TREEnode {
  Item item;  
  link l, r;
  int height; /*Estrutura TREEnode - representa um no da arvore, que contem um Item item,'um inteiro height, 
  correspondente a altura do no, e dois link l e r, correspondentes a ponteiros: um para o filho da esquerda e outro para o filho da direita*/
};


/* ----- Prototipos ----- */
//Funcoes que dao informacao sobre a arvore
int height(link h);
int balance(link h);
int count(link h);
link max(link h);


//Funcoes que equilibram arvore
link rotL(link h);
link rotR(link h);
link rotLR(link h);
link rotRL(link h);
link AVLbalance(link h); 


//Funcoes que alteram elementos da arvore ou que os percorrem
Item search_r(link h, KEYWORD);
void sort_r(link h, void (*visit)(Item));
link delete_r(link h, KEYWORD);
link NEW(Item item, link l, link r); //Cria um novo no da arvore
link insert_r(link h, Item item);


//Funcoes que manipulam uma arvore
void tree_init(link*); //inicializa a arvore
Item tree_search(link, KEYWORD); //procura na arvore pelo Item que contenha KEYWORD 
void tree_insert(link*, Item); // insere um Item na arvore
void tree_delete(link*, KEYWORD v); //remove um no da arvore
void tree_free(link*); //liberta a memoria da arvore e dos Items inseridos nela
int tree_empty(link*); //testa se a arvore esta vazia
void tree_sort(link, void (*visit)(Item)); //visita todos os nos da arvore e aplica a acao correspondente a funcao visit


#endif