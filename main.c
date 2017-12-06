/*                    PROJETO 2 - Armazem de Produtos                               
                              GRUPO AL056                                    
                         86403 - Daniela Lopes                                
                         86440 - Joana Teodoro                     */                             

/* ----- Bibliotecas ----- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ----- Ficheiros ----- */
#include "product.h" //produto
#include "tree.h" //arvore AVL ordenada segundo a ordem alfabetica dos produtos (TAD - Tipos Abstratos de Dados)


/* ----- Constantes ----- */
#define TRUE 1
#define FALSE 0
#define UNDEFINED -1                         


/* ----- Prototipos ----- */
void reavaluate_max_product(); //prepara as variaveis do produto maximo para que este seja recalculado
void max_unities(Product b); //funcao que verifica se o numero de unidades de um produto e maior que o numero maximo de unidades
void max_unities2(char key[], int value); //o mesmo que a anterior, no entanto em vez de comparar um produto compara uma chave e um numero de unidades


/* ----- Variaveis Estaticas ----- */
static link head; // head do ADT tree 


/* ----- Variaveis Globais ----- */
char key_max[MAX_KEY]; //string do codigo do produto com numero maximo de unidades
int max_quantity = UNDEFINED; //numero de unidades do produto com numero maximo de unidades, inicializado com -1
int flag_m = FALSE; //flag que esta a 1 ou a 0 consoante e preciso percorrer a arvore para recalcular o produto maximo ou nao


/* ----- Main ----- */
int main(){
	char key[MAX_KEY]; 
	int value;
	int executa = TRUE;
	char command;
	Product a;
	
	tree_init(&head);//inicializacao dos ADT

	while (executa == TRUE){
		command = getchar();
		switch (command){
			
			/* comando a - incrementa ou reduz o numero de unidades associadas ao produto com o codigo dado. 
			Se o codigo nao existir, devera ser criado um novo produto com esse codigo */
			case 'a': 
				scanf("%s %d", key, &value);
				a = tree_search(head, key); //procura o produto com a chave key
				
				if (!product_exists(a)) { //se o produto ainda nao existir            	               	
                	tree_insert(&head, new_product(key, value)); //insercao de novos produtos no ADT
                	max_unities2(key, value); //verifica se o novo produto introduzido tem o numero maximo de unidades 
	            }

                else{ //se o produto ja existir
                	change_unities(a, value); //atualizacao do numero de unidades do produto
                	if (same_key(key, key_max)){ //caso em que o valor de unidades do produto maximo e alterado
                		if (decrease_unities(value)){ //se o numero de quantidades do produto maximo for descrementada, o produto maximo tem de ser recalculado atravez da arvore
                			reavaluate_max_product();	
                		}
                		else{
                			max_quantity += value;
                		}
                	}
                	else if (increase_unities(value)){ //se o numero de unidades for incrementado noutro produto, tem de se verificar se esse fica o produto maximo
                		max_unities(a);
                	}
                }
				getchar();
				break;
			
			/* comando l - lista alfabeticamente todos os produtos */
			case 'l':					
				if (!tree_empty(&head))
                    tree_sort(head, printProduct); //percorre a arvore ordenada alfabeticamente e imprime os produtos
				getchar();
				break;
			
			/* comando m - escreve o produto com maior numero de unidades em stock */
			case 'm':
				if(!tree_empty(&head)){
					if (flag_m == TRUE){ //recalcular o produto com numero de unidades maximo, percorrendo a arvore
						tree_sort(head, max_unities); //percorre a arvore e atribui o produto com numero de unidades maximo
						flag_m = FALSE; //volta se a por a flag a 0 pois o produto maximo ja foi recalculado
					}
				printf("%s %d\n", key_max, max_quantity);
				}	
				getchar();
				break;
			
			/* comando r - remove o produto com o codigo dado */
			case 'r':
				scanf("%s", key);
				
				if(same_key(key_max, key)){ //caso o produto com numero maximo de unidades seja removido, tem de se fazer uma nova procura pelo produto com maior numero de unidades
					reavaluate_max_product();
				}
                	
                tree_delete(&head, key); //remocao de produtos do ADT
				getchar();
				break;
			
			/* comando x - termina o programa e imprime o numero de produtos diferentes existentes no armazem */
			case 'x':
				getchar();
				printf("%d\n", count(head)); //imprime o numero total de produtos no armazem
				
				tree_free(&head); //liberta a memoria do ADT
				executa = FALSE;
				break;
		}
	}
	return 0;
}

void reavaluate_max_product(){
	key_max[0] = '\0';
	max_quantity = UNDEFINED;
	flag_m = TRUE;
}

void max_unities(Product b){
	if (bigger_quantity(quantity(b), max_quantity)){
		strcpy(key_max, keyword(b));
		max_quantity = quantity(b);
	}

	else if (equal_quantity(max_quantity, quantity(b))){
		if (less_key(keyword(b), key_max)){
			strcpy(key_max, keyword(b));
			max_quantity = quantity(b);
		}
	}
}

void max_unities2(char key[], int value){
	if (bigger_quantity(value, max_quantity)){
		strcpy(key_max, key);
		max_quantity = value;
	}

	else if (equal_quantity(max_quantity, value)){
		if (less_key(key, key_max)){
			strcpy(key_max, key);
			max_quantity = value;
		}
	}

}
