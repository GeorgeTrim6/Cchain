/**
 * Mempool: each user has their own mempool which is used to store transactions
 * that the user views as valid.
 */

#include <stdlib.h>
#include "transaction.h"

#define INITIAL_CAPACITY 10


// typedef struct Transaction Transaction;

/**
 * Mempool will store an array of transactions that have been validated
 */
typedef struct Mempool {
    Transaction **transactions;
    int count;
    int capacity;
} Mempool;


/**
 * Create the initial mempool
 */
Mempool *init_mempool();


/**
 * Adds a new valid transaction to the users mempool
 */
void add_transaction(Mempool *m, Transaction *transaction);



