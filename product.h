#ifndef PRODUCT
#define PRODUCT


/* ----- Bibliotecas ----- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ----- Abstracoes ----- */
#define Item Product
#define KEYWORD char*
#define keyword(A) A->key
#define QUANTITY int
#define quantity(A) A->quantity

#define less_product(A, B) (cmpProduct(A, B) < 0)
#define same_product(A, B) (cmpProduct(A, B) == 0)
#define less_key(A, B) (strcmp(A, B) < 0)
#define same_key(A, B) (strcmp(A, B) == 0)
#define bigger_quantity(A, B) (A > B)
#define equal_quantity(A, B) (A == B)

#define increase_unities(A) (A > 0)
#define decrease_unities(A) (A < 0)
#define cancel_unities(A) (A = 0)
#define deleteItem(A) (free(A)) 


/* ----- Constantes ----- */
#define MAX_KEY 9 //define o tamanho de cada chave, 8 caracteres + 1 para o '\0'


/* ----- Definicao do tipo produto ----- */
typedef struct product {
	char key[MAX_KEY];
	int quantity;
} *Product; //product e um ponteiro para um elemento do tipo produto, com uma chave de oito caracteres e um inteiro correspondente ao numero de unidades em stock


/* ----- Variavel generica do tipo produto ----- */
Product new;


/* ----- Prototipos ----- */
int product_exists(Product); //verifica se um produto ja existe no armazem
Product new_product(KEYWORD, int); //aloca memoria para um novo produto e cria-o com o respetivo codigo e numero de unidades
void change_unities(Product a, int); //atualiza o numero de unidades dos produtos ja existentes
int cmpProduct(Product, Product); //compara os produtos alfabeticamente pelo seu codigo
void printProduct(Product); //imprime um produto


#endif