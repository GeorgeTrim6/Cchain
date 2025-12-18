#include "../include/mempool.h"




Mempool *init_mempool(){
    Mempool *m = malloc(sizeof(Mempool));
    m->transactions =  malloc(sizeof(Transaction*) *INITIAL_CAPACITY);
    m->capacity = INITIAL_CAPACITY;
    m->count = 0;

    return m;
}

void add_transaction(Mempool *m, Transaction *transaction){

    if(m->count == m->capacity){
        m->capacity*=2;
        m->transactions = realloc(m->transactions, sizeof(Transaction *) * m->capacity );

        if(m->transactions == NULL){
            printf("Error reallocating memory for mempool\n");
        }
    }

    m->transactions[m->count++] = transaction;
}
