#include <stdlib.h>
#include "bst.h"

//retorna o no do elemento de valor passado, iterativamente
bst_n* bst_getn(bst_n* root, int (*comp)( bst_item i1, bst_item i2), bst_item item) {
    if (root) {
        bst_n *node = root;
        int cmp = comp(node->item, item);

        // busca o elemento binariamente na arvore ate encontra-lo, ou nao ser possivel sua existencia
        while (cmp != 0) {
            if (cmp > 0 && node->l) {
                node = node->l;
                cmp = comp(node->item, item);
            }
            else if (cmp < 0 && node->r) {
                node = node->r;
                cmp = comp(node->item, item);
            }
            else
                break;
        }

        if (cmp == 0)
            return node;    //retorna o node se for encontrado
        else
            return NULL;    //retorna nulo se nao for encontrado
    }
    return NULL;
}

bst_n* bst_putn(bst_n* root, int (*comp)( bst_item i1, bst_item i2), bst_item item) {
    if(root) {
        int cmp = comp(root->item, item);
        if(cmp > 0)
            root->l = bst_putn(root->l, comp, item);
        else if (cmp < 0)
            root->r = bst_putn(root->r, comp, item);
        return root;
    } 
    else {
        bst_n* novo = (bst_n*)malloc(sizeof(bst_n));
        novo->item = item;
        novo->l = novo->r = NULL;
        return novo;
    }
}

//procura recursivamente o menor elemento da arvore/subarvore
bst_n* bst_maxn(bst_n* root) {
    if(root) {
        if(!root->l)
            return root;
        else
            return bst_maxn(root->l);
    }
    return NULL;
}

//procura recursivamente o menor elemento da arvore/subarvore
bst_n* bst_minn(bst_n* root) {
    if(root) {
        if(!root->r)
            return root;
        else
            return bst_minn(root->r);
    }
    return NULL;
}

//remove o valor passado recursivamente da arvore
bst_n* bst_remn(bst_n* root, int (*comp)( bst_item i1, bst_item i2), bst_item item) {    
    if (root) {
        //checa se o nó atual é o de valor desejado
        int cmp = comp(root->item, item);

        //caso menor, deve estar a direita
        if (cmp < 0)
            root->r = bst_remn(root->r, comp, item);

        //caso maior, deve estar a esquerda
        else if (cmp > 0)
            root->l = bst_remn(root->l, comp, item);

        //caso seja o nó correto
        else {
            //primeiro caso: o nó não tem filhos
            if (!root->l && !root->r) {
                free(root);
                return NULL;
            }
            //segundo caso: o nó tem ambos os filhos
            else if (root->l && root->r) {
                //o nó e o maior elemento da subarvore a direita sao trocados
                bst_n *node = bst_maxn(root->r);
                bst_item auxStr = node->item;
                node->item = root->item;
                root->item = auxStr;
                
                //o nó é removido novamente, em sua nova posicao, onde ira cair no caso 1 ou 3
                root->r = bst_remn(root->r, comp, item);
                return root;
            }
            //terceiro caso: o nó tem apenas um filho
            else {
                bst_n *node = root;

                //o filho entra no lugar do pai e é liberada a memória alocada para o pai
                if (root->l)
                    root = root->l;
                else if (root->r)
                    root = root->r;
                    
                free(node);
                return root;
            }   
        }
    }
    return root;
}

void bst_deln(bst_n* root) {
    if(root) {
        bst_deln(root->l);
        bst_deln(root->r);
        free(root);
    }
}

void bst_initialize(bst *t, int (*comp)(bst_item i1, bst_item i2)) {
    t->compare = comp;
    t->size = 0;
    t->root = NULL;
}

bst_item* bst_get(bst *t, bst_item item) {
    bst_n *n = bst_getn(t->root, t->compare, item);
    if (n)
        return &n->item;
    else 
        return NULL;
}

void bst_put(bst *t, bst_item item) {
    t->root = bst_putn(t->root, t->compare, item);
    t->size++;
}

bst_item* bst_max(bst* t) {
    bst_n *n = bst_maxn(t->root);
    if (n)
        return &n->item;
    else
        return NULL;
}

bst_item* bst_min(bst* t) {
    bst_n *n = bst_minn(t->root);
    if (n)
        return &n->item;
    else
        return NULL;
}

int bst_size(bst* t) {
    return t->size;
}

void bst_rem(bst* t, bst_item item) {    
    t->root = bst_remn(t->root, t->compare, item);
    t->size--;
}

void bst_del(bst* t) {
    bst_deln(t->root);
}

//realiza o processamento do nó atual depois do processamento de suas subarvores
void bst_post_ordern( bst_n *p, void (*process)(bst_item item) ) {
    if(p) {
		bst_post_ordern(p->l, process);
		
		bst_post_ordern(p->r, process);

		process(p->item);
	}
	return;
}

//realiza o processamento do nó atual antes do processamento de suas subarvores
void bst_pre_ordern( bst_n *p, void (*process)(bst_item item) ) {
    if(p) {
		process(p->item);

		bst_pre_ordern(p->l, process);
		
		bst_pre_ordern(p->r, process);
	}
	return;
}

//processa as subárvores à esquerda do nó, então processa o nó e depois as subárvores à direita
void bst_in_ordern( bst_n *p, void (*process)(bst_item item) ) {
	if(p) {
		bst_in_ordern(p->l, process);

		process(p->item);

		bst_in_ordern(p->r, process);
	}
	return;
}

void bst_post_order(bst *t, void (*process)(bst_item item)) {
    bst_post_ordern(t->root, process);
}

void bst_pre_order(bst *t, void (*process)(bst_item item)) {
    bst_pre_ordern(t->root, process);
}

void bst_in_order(bst *t, void (*process)(bst_item item)) {
    bst_in_ordern(t->root, process);
}
