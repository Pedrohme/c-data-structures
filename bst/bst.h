#ifndef BST_H
#define BST_H

//tipo de dado armazenado na arvore
typedef int bst_item;

typedef struct bst_nodes {
    struct bst_nodes* l;
    struct bst_nodes* r;
    bst_item item;
} bst_n;

typedef struct bst_struct {
    bst_n *root;
    int quantidade;
    int (*compare)( bst_item i1, bst_item i2); //função de comparação
} bst;

/* ex função de comparação :
int cmp(int a, int b) {
    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}
*/

/*! Função para inicializar uma arvore binaria de busca. É obrigatório chamar esta função antes do início da utilização da arvore.
    @param t endereço da arvore alocada pelo usuario
    @param comp função de comparação a ser utilizada pela árvore
*/
void bst_initialize(bst *t, int (*comp)(bst_item i1, bst_item i2));

/*! Busca o item passado na árvore
    @param t endereço da fila alocada pelo usuário
    @param item item a ser buscado
    @return endereço do item buscado caso encontrado. Caso não encontrado, retorna NULL
*/
bst_item* bst_get(bst *t, bst_item item);

/*! Insere um item na árvore. Itens repetidos não serão inseridos.
    @param t endereço da fila alocada pelo usuário
    @param item item a ser inserido
*/
void bst_put(bst *t, bst_item item);

/*! Busca o item de maior valor na árvore
    @param t endereço da fila alocada pelo usuário
    @return endereço do item. Caso a árvore esteja vazia, retorna NULL
*/
bst_item* bst_max(bst* t);

/*! Busca o item de menor valor na árvore
    @param t endereço da fila alocada pelo usuário
    @return endereço do item. Caso a árvore esteja vazia, retorna NULL
*/
bst_item* bst_min(bst* t);

/*! Remove um item da árvore. Itens repetidos não serão inseridos.
    @param t endereço da fila alocada pelo usuário
    @param item item a ser removido
*/
void bst_rem(bst* t, bst_item item);

/*! Apaga a árvore e libera a memória alocada. Essa função deve sempre ser chamada antes de finalizar o programa.
    @param t endereço da fila alocada pelo usuário
*/
void bst_del(bst* t);

#endif