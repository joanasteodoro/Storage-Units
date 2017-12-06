#include "tree.h"

//Determina a altura de um no
int height(link h) {
    if (h == NULL) {
        return 0;
    }
    return h->height;
}

// Determina o factor de balanco entre dois nos
int balance(link h) { 
    if (h == NULL) {
        return 0; 
    }  
    return height(h->l)-height(h->r); 
} 

//Faz uma rotacao a esquerda a um no e restrutura uma sub-arvore
link rotL(link h) {
    int height_left, height_right;
    link x = h->r;
    h->r = x->l;
    x->l = h;

    //Atualiza as alturas dos nos 
    height_left = height(h->l);
    height_right = height(h->r);
    h->height = height_left > height_right ? height_left + 1 : height_right + 1;

    height_left = height(h->l);
    height_right = height(x->r);
    x->height = height_left > height_right ? height_left + 1 : height_right + 1;

    return x;
}

//Faz uma rotacao a direita a um no e restrutura uma sub-arvore 
link rotR(link h) {
    int height_left, height_right;
    link x = h->l;
    h->l = x->r;
    x->r = h;

    //atualiza as alturas dos nos 
    height_left = height(h->l);
    height_right = height(h->r);
    h->height = height_left > height_right ? height_left + 1 : height_right + 1;

    height_left = height(x->l);
    height_right = height(h->r);
    x->height = height_left > height_right ? height_left + 1 : height_right + 1;

    return x; 
}

//Faz uma rotacao a esquerda e depois a direita
link rotLR(link h) {
    if (h==NULL) return h;
        h->l=rotL(h->l);
        
    return rotR(h); 
}

//Faz uma rotacao a direita e depois a esquerda
link rotRL(link h) {
    if (h==NULL) return h;
        h->r=rotR(h->r); 
    return rotL(h); 
}

//Funcao de equilibrio da arvore, apos um elemento ser inserido ou removido 
link AVLbalance(link h) {    
    int balanceFactor, height_left, height_right;

    if (h==NULL) return h;

    balanceFactor = balance(h); 

    if (balanceFactor > 1) { 
        if (balance(h->l) > 0) h = rotR(h); 
        else h = rotLR(h);  
    } 
    else if (balanceFactor < -1) { 
        if (balance(h->r) < 0) h = rotL(h); 
        else h = rotRL(h); 
    } 
    else {
        height_left = height(h->l);
        height_right = height(h->r);
        h->height = height_left > height_right ?  height_left + 1 : height_right + 1;
    }

    return h; 
} 

//Conta o numero de elementos que existem na arvore
int count(link h) {
    if (h==NULL) return 0;
    else return count(h->r)+count(h->l)+1;
}

//Procura na arvore pelo elemento que contenha a KEYWORD v
Item search_r(link h, KEYWORD v) {
    if (h == NULL)
        return NULL;
    if (same_key(v, keyword(h->item)))
        return h->item;
    if (less_key(v, keyword(h->item)))
        return search_r(h->l, v);
    else
        return search_r(h->r, v);
}

//Aplica a funcao visit a todos os elementos da arvore, por ordem alfabetica
void sort_r(link h, void (*visit)(Item)) {
    if (h == NULL) return;
    
    sort_r(h->l, visit);
    visit(h->item);
    sort_r(h->r, visit);
}

//Procura pelo elemento maximo na arvore 
link max(link h) {
    if (h == NULL || h->r == NULL) {
        return h;
    }
    else {
        return max(h->r);
    }
}

//Elimina o no que contenha item com a KEYWORD v na arvore
link delete_r(link h, KEYWORD v) {
    Item x;
    if (h==NULL){
        return h;   
    } 
    else if(less_key(v, keyword(h->item))) {
        h->l = delete_r(h->l, v);
    }
    else if(less_key(keyword(h->item), v)) {
        h->r = delete_r(h->r, v);
    }
    else {
        if (h->l != NULL && h->r != NULL) {
            link aux = max(h->l);
    
            x = h->item;
            h->item = aux->item;
            aux->item=x;
    
            h->l = delete_r(h->l, keyword(aux->item));
        } 
        else {
            link aux = h;
            if (h->l == NULL && h->r == NULL) {
                h = NULL;
            }
            else if (h->l == NULL) {
                h = h->r;
            }
            else {
                h = h->l;
            }
            deleteItem(aux->item);
            free(aux);
        }
  } 

  h = AVLbalance(h); //volta a balancear a arvore depois do elemento ser retirado
  return h;
}

//Liberta um no da arvore
link free_r(link h) {
    if (h==NULL) {
        return h;
    }
    h->l=free_r(h->l);
    h->r=free_r(h->r);
    return delete_r(h,keyword(h->item));
}

//Cria um novo no da arvore
link NEW(Item item, link l, link r) {
    link x = (link) malloc(sizeof(struct TREEnode));
    x->item = item;
    x->l = l;
    x->r = r;
    x->height=1;
    return x;
}

//Insere um novo no na arvore
link insert_r(link h, Item item) {
    if (h == NULL) {
        return NEW(item, NULL, NULL);
    }
    if (less_product(item,h->item)) {
        h->l = insert_r(h->l, item);
    }
    else {
        h->r = insert_r(h->r, item);
    }
    h = AVLbalance(h);

    return h;
}

/* ---- FUNCOES QUE MANIPULAM DIRETAMENTE A ARVORE ---- */

//Inicializa a arvore a NULL
void tree_init(link*head) {
    *head = NULL;
}

//Procura o elemento do tipo Item com a KEYWORD v
Item tree_search(link head, KEYWORD v) {
    return search_r(head, v);
}

//Insere um elemento do tipo Item na arvore
void tree_insert(link*head, Item item) {
    *head = insert_r(*head, item);
}

//Elimina o elemento do tipo Item com a KEYWORD v
void tree_delete(link*head, KEYWORD v) {   
    *head = delete_r(*head, v);
}

//Liberta a memoria alocada para a arvore
void tree_free(link*head) {
    *head=free_r(*head);
}

//Verifica se a arvore esta vazia
int tree_empty(link *head) {
    return *head == NULL;
}

//Percorre a arvore executando a acao visit
void tree_sort(link head, void (*visit)(Item)) {
    sort_r(head, visit);
}