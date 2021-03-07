#include <stdlib.h>
#include "avl.h"

void avl_initialize(avl* t, int (*cmp)( avl_item i1, avl_item i2)) {
	t->root = 0;
    t->cmp = cmp;
    t->size = 0;
}

void avl_private_destroy(avl_n *p) {
    if (p) {
        avl_private_destroy(p->left);
        avl_private_destroy(p->right);
        free(p);
    }
}

void avl_destroy(avl* t) {
    avl_private_destroy(t->root);
}

//Rotation functions

avl_n* avl_rotLL(avl_n* A) { 
    avl_n *B = A->left;
    A->left = B->right;
    B->right = A;
    A->bal = 0;
    B->bal = 0;
    return B;
}

avl_n* avl_rotRR(avl_n* A) {
    avl_n *B = A->right;
    A->right = B->left;
    B->left = A;
    A->bal = 0;
    B->bal = 0;
    return B;
}

avl_n* avl_rotLR(avl_n* A) {
    avl_n *B = A->left;
    avl_n *C = B->right;
    B->right = C->left;
    C->left = B;
    A->left = C->right;
    C->right = A;

    if (C->bal == -1) {
        A->bal = 1;
        B->bal = 0;
        C->bal = 0;
    }
    else if (C->bal == 1) {
        A->bal = 0;
        B->bal = -1;
        C->bal = 0;
    }
    else {
        A->bal = 0;
        B->bal = 0;
    }
    return C;
}

avl_n* avl_rotRL(avl_n* A) {
    avl_n *B = A->right;
    avl_n *C = B->left;
    B->left = C->right;
    C->right = B;
    A->right = C->left;
    C->left = A;

    if (C->bal == -1) {
        A->bal = 0;
        B->bal = 1;
        C->bal = 0;
    }
    else if (C->bal == 1) {
        A->bal = -1;
        B->bal = 0;
        C->bal = 0;
    }
    else {
        A->bal = 0;
        B->bal = 0;
    }
    return C;
}

avl_n* avl_private_insert(avl_n* p, avl_item data, int *heightChanged, int (*cmp)( avl_item i1, avl_item i2)) {
	
	if(!p) {
		avl_n* new = (avl_n*)malloc(sizeof(avl_n));
		new->data = data;
		new->bal = 0;
		new->right = new->left = 0;
		*heightChanged = 1;
		return new;
	}

    //esquerda
    else if (cmp(data, p->data) < 0) {
		p->left = avl_private_insert(p->left, data, heightChanged, cmp);
        if (*heightChanged && p->bal == -1) { //caso de possivel desbalanceamento
            if (p->left->bal == -1) { //EE
                *heightChanged = 0;
                return avl_rotLL(p);
            }
            else if (p->left->bal == 1) { //ED
                *heightChanged = 0;
                return avl_rotLR(p);
            }
            else { //balanceada
                *heightChanged = 0;
            }
        }
        else if (*heightChanged) { //atualiza variavel de balanceamento
            *heightChanged = 0;
            p->bal--;
        }
	}
    //direita
	else if (cmp(data, p->data) > 0) {
		p->right = avl_private_insert(p->right, data, heightChanged, cmp);
        if (*heightChanged && p->bal == 1) { //caso de possivel desbalanceamento
            if (p->right->bal == 1) { //DD
                *heightChanged = 0;
                return avl_rotRR(p);
            }
            else if (p->right->bal == -1) { //DE
                *heightChanged = 0;
                return avl_rotRL(p);
            }
            else { //balanceada
                *heightChanged = 0;
            }
        }
        else if (*heightChanged) { //atualiza variavel de balanceamento
            *heightChanged = 0;
            p->bal++;
        }
	}
	return p;
}

void avl_insert(avl* t, avl_item data) {
	
	int heightChanged = 0;
	
	t->root = avl_private_insert( t->root, data, &heightChanged, t->cmp );
	
}
    
avl_n* avl_private_ceil(avl_n* p, avl_item data, int (*cmp)( avl_item i1, avl_item i2)) {
    if (p) {
        if (cmp(data, p->data) == 0) { //caso igual, é o avl_ceil
            return p;
        }
        else if (cmp(data, p->data) > 0) { //caso o valor no nó seja menor, avl_ceil deve estar à direita
            return avl_private_ceil(p->right, data, cmp);
        }
        else { //enfim, o avl_ceil deve estar na subarvore à esquerda ou o avl_ceil é a raiz
            avl_n *aux = avl_private_ceil(p->left, data, cmp);
            if (aux) {
                if (cmp(aux->data, data) == 0 || cmp(aux->data, data) > 0) {
                    return aux;
                }
                else {
                    return p;
                }
            }
            else {
                return p;
            }
        }
    }
    else { //chega aqui caso não exista chave maior ou igual
        return NULL;
    }
}

avl_n* avl_private_floor(avl_n* p, avl_item data, int (*cmp)( avl_item i1, avl_item i2)) {
    if (p) {
        if (cmp(data, p->data) == 0) { //caso igual, é o avl_floor
            return p;
        }
        else if (cmp(data, p->data) < 0) { //caso o valor do nó seja maior, avl_floor deve estar à esquerda
            return avl_private_floor(p->left, data, cmp);
        }
        else { //enfim, o avl_floor deve estar na subarvore à direita ou o avl_floor é a raiz
            avl_n *aux = avl_private_floor(p->right, data, cmp);
            if (aux) {
                if (cmp(aux->data, data) == 0 || cmp(aux->data, data) < 0) {
                    return aux;
                }
                else {
                    return p;
                }
            }
            else {
                return p;
            }
        }
    }
    else { //chega aqui caso não exista chave menor ou igual
        return NULL;
    }
}

int avl_ceil(avl* t, int data, int *data_ceil) {
    avl_n* c = avl_private_ceil(t->root, data, t->cmp);
    if(c) {
        *data_ceil = c->data;
        return 1;
    }
    return 0;
}

int avl_floor(avl* t, int data, int *data_floor) {
    avl_n* f = avl_private_floor(t->root, data, t->cmp);
    if(f) {
        *data_floor = f->data;
        return 1;
    }
    return 0;
}
