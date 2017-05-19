#include <stdlib.h>

#include "flist/flist.h"


flist_t* flist_new(void){
    return calloc(1, sizeof(flist_t));
}

void flist_free( flist_t *flist ){

    flist_node_t *cur = 0, *tmp = 0;

    if( !flist )
        return;

    for( cur = flist->start; cur; cur = tmp ){
        tmp = cur->next;
        free( cur );
    }

    free( flist );
    return;
}

void flist_insert( flist_t *flist, void *item ){

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

int flist_insert_after( flist_t *flist, void *search_item, void *item ){

    flist_node_t *node = 0, *new_node = 0;

    if( !flist || !flist->start )
        return FLIST_ERR_EMPTY;

    node = flist_search( flist, search_item );

    if( !node )
        return FLIST_ERR_NOTFOUND;

    new_node = malloc( sizeof(flist_node_t) );
    new_node->item = item;

    new_node->prev = node;
    new_node->next = node->next;
    node->next = new_node;

    if( node == flist->end )
        flist->end = new_node;

    return 0;
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

int flist_remove( flist_t *flist, void *item ){

    flist_node_t *node = 0;

    if( !flist || !flist->start ) // No list or empty list
        return FLIST_ERR_EMPTY;

    node = flist_search( flist, item );

    if( !node )
        return FLIST_ERR_NOTFOUND;

    if( node == flist->start )
        flist->start = node->next;

    if( node == flist->end )
        flist->end = node->prev;

    if( node->prev ) // If it is not the first we can update prev->next
        node->prev->next = node->next;

    if( node->next ) // If it is not the last item we can update next->prev
        node->next->prev = node->prev;

    free( node );
    flist->n_nodes--;

    return 0;

}

flist_node_t* flist_search( flist_t *flist, void *item ){

    flist_node_t *cur = 0;

    if( !flist || !flist->start )
        return 0;

    for( cur = flist->start; cur; cur = cur->next ){
        if( cur->item == item )
            return cur;
    }

    return 0;
}

flist_node_t* flist_search_cmp( flist_t *flist, int (*cmp_fn)(flist_node_t *node, void *arg), void *arg ){

    flist_node_t *cur = 0;

    if( !flist || !flist->start || !cmp_fn )
        return 0;

    for( cur = flist->start; cur; cur = cur->next ){
        if( cmp_fn( cur, arg ) == 0 )
            return cur;
    }

    return 0;

}

void flist_iterate( flist_t *flist, int (*cb)(flist_node_t *node, void *arg), void *arg ){

    int r = 0;
    flist_node_t *cur = 0, *next = 0;

    if( !flist || !flist->start || !cb )
        return;

    for( cur = flist->start; cur && r == 0; ){ // Loop until there are items or cb returns != 0
    	next = cur->next;
        r = cb( cur, arg );
        // cur might have been freed after the callback call
        cur = next;
    }

    return;
}
