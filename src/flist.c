#include <stdlib.h>

#include "flist/flist.h"


flist_t* flist_new(){
    return calloc(1, sizeof(flist_t));
}

void flist_free( flist_t *flist ){

    flist_node_t *cur = 0, *tmp = 0;

    if( !flist )
        return;

    for(cur = flist->start; cur; cur = tmp){
        tmp = cur->next;
        free( cur );
    }

    free( flist );
    return;
}

void flist_add( flist_t *flist, void *item ){

    flist_node_t *new_node = 0;

    if( !flist )
        return;

    new_node = malloc( sizeof(flist_node_t) );
    new_node->item = item;

    if( !flist->start ){ // Empty
        new_node->prev = 0;
        new_node->next = 0;
        flist->start = flist->end = new_node;
        flist->n_nodes++;
        return;
    }

    new_node->next = 0;
    new_node->prev = flist->end;
    flist->end->next = new_node;
    flist->end = new_node;
    flist->n_nodes++;
    return;
}

void flist_push( flist_t *flist, void *item ){

    flist_node_t *new_node = 0;

    if( !flist )
        return;

    new_node = malloc( sizeof(flist_node_t) );
    new_node->item = item;

    if( !flist->start ){ // Empty
        new_node->prev = 0;
        new_node->next = 0;
        flist->start = flist->end = new_node;
        flist->n_nodes++;
        return;
    }

    new_node->prev = 0;
    new_node->next = flist->start;
    flist->start->prev = new_node;
    flist->start = new_node;
    flist->n_nodes++;

    return;
}

int flist_pop( flist_t *flist, void **item ){

    flist_node_t *next = 0;

    if( !flist || !flist->start ) // No list or empty list
        return FLIST_ERR_EMPTY;

    *item = flist->start->item;
    next = flist->start->next;
    free( flist->start );
    flist->start = next;

    if( !flist->start ){ // If it was the only present node
        flist->end = 0;
    } else {
        flist->start->prev = 0;
    }

    flist->n_nodes--;

    return 0;

}

int flist_del( flist_t *flist, void *item ){

    flist_node_t *cur = 0;

    if( !flist || !flist->start ) // No list or empty list
        return FLIST_ERR_EMPTY;

    for(cur = flist->start; cur; cur = cur->next ){

        if( cur->item == item ){

            if( cur == flist->start ){
                flist->start = cur->next;
            }

            if( cur == flist->end ){
                flist->end = cur->prev;
            }

            if( cur->prev ) // If it is not the first we can update prev->next
                cur->prev->next = cur->next;

            if( cur->next ) // If it is not the last item we can update next->prev
                cur->next->prev = cur->prev;

            free( cur );
            flist->n_nodes--;

            return 0;
        }
    }

    return FLIST_ERR_NOTFOUND;
}

void flist_iterate( flist_t *flist, int (*cb)(flist_node_t *node, void *arg), void *arg ){

    int r = 0;
    flist_node_t *cur = 0;

    if( !flist || !flist->start || !cb )
        return;

    for(cur = flist->start; cur && r == 0; cur = cur->next ){ // Loop until there are items or cb returns != 0
        r = cb( cur, arg );
    }

    return;
}
