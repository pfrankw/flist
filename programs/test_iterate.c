
#include <stdio.h>
#include <flist/flist.h>

int iterate( flist_node_t *node, void *arg ){

    printf("%s\n", (char*)node->item);
    return 0;
}

int main(){

    int i;
    char *names[] = {
        "Francesco",
        "Giovanni",
        "Alessandra",
        "Salvatore",
        "Giuseppe",
        NULL
    };


    flist_t *flist = flist_new();

    for(i=0; names[i]; i++){
        flist_insert( flist, names[i] );
    }

    flist_iterate( flist, iterate, 0 ); printf("END_ITERATE\n\n");

    i--; flist_remove( flist, names[i] );
    flist_iterate( flist, iterate, 0 ); printf("END_ITERATE\n\n");

    i--; flist_remove( flist, names[i] );
    flist_iterate( flist, iterate, 0 ); printf("END_ITERATE\n\n");

    i--; flist_remove( flist, names[i] );
    flist_iterate( flist, iterate, 0 ); printf("END_ITERATE\n\n");

    i--; flist_remove( flist, names[i] );
    flist_iterate( flist, iterate, 0 ); printf("END_ITERATE\n\n");

    i--; flist_remove( flist, names[i] );
    flist_iterate( flist, iterate, 0 ); printf("END_ITERATE\n\n");

    printf("flist->start = %x, flist->end = %x\n", flist->start, flist->end);

    flist_free( flist );

}
