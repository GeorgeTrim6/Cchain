/**
 * Implementation file for a block created by a miner on the systems.
 * Blocks can only be created by miners but can be validated by users.
 */
#include <inttypes.h>
#include "../include/block.h"



Block *init_block(int difficulty, int64_t prevBlockHash){
    Block *b = malloc(sizeof(Block));

    //Initialize header state
    Header *h = malloc(sizeof(Header));
    h->difficulty = difficulty;
    h->prevBlockHash = prevBlockHash;
    h->nonce = 0;
    h->date = time(NULL);

    b->header = h;
    b->numTransactions = 0;
    b->hash = 0;
    b->transactions = malloc(sizeof(Transaction *) * MAX_NUM_TRANSACTIONS + 1);

    return b;
}


bool block_add_transaction(Block *b, Transaction *tx){
    //Add block 
    if(b->numTransactions < MAX_NUM_TRANSACTIONS){
        b->transactions[b->numTransactions++] = tx;
        return true;
    }
    return false;
}

bool block_add_miner_transaction(Block *b, User *user);



