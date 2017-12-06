#include "product.h"


int product_exists(Product a) {
    return a != NULL;
}

Product new_product(char *key, int value) {
	new = (Product) malloc(sizeof(struct product));
	strcpy(keyword(new), key);
	quantity(new) = value;
    return new;
}

void change_unities(Product a, int value){
	quantity(a) += value;

	if(decrease_unities(quantity(a))){
		cancel_unities(quantity(a));
	}
}

int cmpProduct(Product a, Product b) {
	return strcmp(keyword(a), keyword(b));
}

void printProduct(Product a) {
    printf("%s %d\n", keyword(a), quantity(a));
}