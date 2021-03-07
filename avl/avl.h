#ifndef AVL_H
#define AVL_H

typedef int avl_item;

typedef struct node_ {
	int data;
	char bal; //we only need 2 bits
	struct node_ *right, *left;
} avl_n;

typedef struct {
	avl_n *root;
    int size;
    int (*cmp)( avl_item i1, avl_item i2); //comparison function
} avl;

/* example comparison function:
int cmp(int a, int b) {
    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}
*/

// public functions

/*! Initialization function for the AVL Tree. This function must be called before using the tree.
    @param t adress of the tree allocated by the user
    @param cmp comparison function to be used in the tree
*/
void avl_initialize( avl* t, int (*cmp)( avl_item i1, avl_item i2) );

/*! Deletes the tree and frees allocated memory. This function must be callet before closing the program.
    @param t adress of the tree allocated by the user
*/
void avl_destroy( avl* t );

/*! Inserts an item in the tree. If the item is already in the tree, does nothing.
    @param t adress of the tree allocated by the user
    @param item item to be inserted in the tree
*/
void avl_insert( avl* t, avl_item data );

/*! Searches for the ceiling of the passed value in the tree
    @param t adress of the tree allocated by the user
	@param data item to find the ceiling of
	@param data_ceil this pointer will be assigned the ceiling, if found
    @return 1 if the ceiling exists, 0 if it doesn`t
*/
int avl_ceil( avl* t, avl_item data, avl_item *data_ceil ); // Se o teto existir, retorna 1 e em data_ceil o teto de data. Caso contrário, retorna 0 (falso).

/*! Searches for the floor of the passed value in the tree
    @param t adress of the tree allocated by the user
	@param data item to find the floor of
	@param data_floor this pointer will be assigned the floor, if found
    @return 1 if the floor exists, 0 if it doesn`t
*/
int avl_floor( avl* t, avl_item data, avl_item *data_floor ); // Se o piso existir, retorna 1 e em data_floor o piso de data. Caso contrário, retorna 0 (falso).

#endif