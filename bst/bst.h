/* BINARY SEARCH TREE */

#ifndef BST_H
#define BST_H

//Data type stored in the tree
typedef int bst_item;

typedef struct bst_nodes {
    struct bst_nodes* l;
    struct bst_nodes* r;
    bst_item item;
} bst_n;

typedef struct bst_struct {
    bst_n *root;
    int size;
    int (*compare)( bst_item i1, bst_item i2); //comparison function
} bst;

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

/*! Initialization function for the Binary Search Tree. This function must be called before using the tree.
    @param t adress of the tree allocated by the user
    @param comp comparison function to be used in the tree
*/
void bst_initialize(bst *t, int (*comp)(bst_item i1, bst_item i2));

/*! Searches for the passed item in the tree
    @param t adress of the tree allocated by the user
    @param item item to be searched for
    @return the item's adress if found. If the item isn't n the tree, returns a NULL pointer
*/
bst_item* bst_get(bst *t, bst_item item);

/*! Inserts an item in the tree. If the item is already in the tree, does nothing.
    @param t adress of the tree allocated by the user
    @param item item to be inserted in the tree
*/
void bst_put(bst *t, bst_item item);

/*! Searches for the item of maximum value in the tree
    @param t adress of the tree allocated by the user
    @return the item`s adress. If the tree is empty, returns a NULL pointer
*/
bst_item* bst_max(bst* t);

/*! Searches for the item of minimum value in the tree
    @param t adress of the tree allocated by the user
    @return the item`s adress. If the tree is empty, returns a NULL pointer
*/
bst_item* bst_min(bst* t);

/*! Size function
    @return number of items stores in the tree
*/
int bst_size(bst* t);

/*! Removes an item from the tree. If the item isn`t in the tree, does nothing.
    @param t adress of the tree allocated by the user
    @param item item to be removed
*/
void bst_rem(bst* t, bst_item item);

/*! Deletes the tree and frees allocated memory. This function must be callet before closing the program.
    @param t adress of the tree allocated by the user
*/
void bst_del(bst* t);


/* tree traversal functions
    example processing function:

    void print(int item) {
	    printf(" %d", item);
    }

*/

/*! Performs the Post-order traversal of the tree
    @param t adress of the tree allocated by the user
    @param process processing function to be used
*/
void bst_post_order(bst *t, void (*process)(bst_item item));

/*! Performs the Pre-order traversal of the tree
    @param t adress of the tree allocated by the user
    @param process processing function to be used
*/
void bst_pre_order(bst *t, void (*process)(bst_item item));

/*! Performs the In-order traversal of the tree
    @param t adress of the tree allocated by the user
    @param process processing function to be used
*/
void bst_in_order(bst *t, void (*process)(bst_item item));

#endif