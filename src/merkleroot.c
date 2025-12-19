/**
 * Contains code to create the merkle root hash of transactions
 */

 #include <stdlib.h>
 #include <stdint.h>
 #include <string.h>
 #include "../include/merkleroot.h"
 
 #define MAX_TRANSACTIONS 6



  /**
 * Written by ChatGPT as a way to create a simple hash function for my program.
 */
  uint64_t simple_hash(const void *data, size_t len) {
    uint64_t hash = 14695981039346656037ULL; // FNV offset basis
    const unsigned char *bytes = data;

    for(size_t i = 0; i < len; i++)
        hash = (hash ^ bytes[i]) * 1099511628211ULL; // FNV prime

    return hash;
}


 void create_root(Merkel *merkel, int leftI, int rightI, uint64_t *txHashes ){
    //Base case
    if(leftI == rightI){
        char *data = get_transaction_data(merkel->transactions[leftI]);
        txHashes[leftI] =  simple_hash(data, strlen(data) );
        return;

    }
    //left branch 
    int lL = leftI;
    int lU = ((rightI - leftI) / 2) + leftI;

    //rigth branch 
    int rL = ((rightI - leftI) / 2) + 1 + leftI;
    int rU = rightI;

    //Create branch
    create_root(merkel, lL, lU, txHashes);
    create_root(merkel, rL, rU, txHashes);

    uint64_t x = txHashes[1L];
    uint64_t y = txHashes[rL];

    uint64_t data =  x + y;
    txHashes[lL] = simple_hash(&data, sizeof(data));
    return; 
 }


  Merkel *init_merkel(Transaction **transactions, int numTx){
    Merkel *merkel = malloc(sizeof(Merkel));

    merkel->numTransactions = numTx;
    merkel->transactions = transactions;
    uint64_t *txHashes = malloc(sizeof(uint64_t)*numTx);
    create_root(merkel, 0, merkel->numTransactions - 1, txHashes);
    merkel->root = txHashes[0];

    return merkel;
 }
