#ifndef FLIST_H
#define FLIST_H

#include <stdlib.h>

#include "flist/err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct flist_node_t {

    void    *item;
    struct flist_node_t *prev;
    struct flist_node_t *next;

} flist_node_t;


typedef struct {

    size_t n_nodes;
    flist_node_t *start;
    flist_node_t *end;

} flist_t;


flist_t* flist_new();
void flist_free( flist_t *flist );

void flist_add( flist_t *flist, void *item );
void flist_push( flist_t *flist, void *item );

int flist_pop( flist_t *flist, void **item );
int flist_del( flist_t *flist, void *item );

void flist_iterate( flist_t *flist, int (*cb)(flist_node_t *node, void *arg), void *arg );

#ifdef __cplusplus
}
#endif


#endif
