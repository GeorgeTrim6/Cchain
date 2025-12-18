/**
 * Implementation file for transactions
 */
#include <stdlib.h>
#include "../include/transaction.h"
#include "../include/user.h"




Transaction *init_transaction(User *payer, User *recipient, int amount){
    if(amount < 0){
        return NULL;
    }

    Transaction *transaction = malloc(sizeof(Transaction));
    if(transaction == NULL){
        fprintf(stderr, "Error allocating memory for transaction\n");
        return NULL;
    }

    //Create new transaction
    transaction->amount = amount;
    transaction->payer = payer;
    transaction->recipient = recipient;
    transaction->time = time(NULL);

    return transaction;
}


char *get_transaction_data(Transaction *tx){
    char *buffer = malloc(sizeof(char)*256);

    if(buffer == NULL){
        printf("Memory allocation for buffer failed\n");
    }

    snprintf(buffer, 256, "%ld|%s|%s|%d", tx->time, get_username(tx->payer), get_username(tx->recipient), tx->amount);    
    return buffer;
}


 bool verify_transaction(Transaction *tx){
    char *data = get_transaction_data(tx);
    uint64_t pk = get_public_key(tx->payer);

    //This will be invalid for some outputs but should be unlikely and doesn't really matter for this project
    if(pk - 10 < 10){
        pk-=10;

    }else{
        pk+=10;
    }

    uint64_t expected = simple_hash(data, strlen(data)) ^ pk;
    return expected == tx->signature;
 }


 void sign_transaction(Transaction *tx, User *user){
    char *data = get_transaction_data(tx);
    tx->signature = create_signature(data, user);
    
 }

 Transaction *copy_transaction(Transaction *tx){
    Transaction *copyTx = malloc(sizeof(Transaction));
    copyTx->amount = tx->amount;
    copyTx->payer = tx->payer;
    copyTx->recipient = tx->recipient;
    copyTx->time = tx->time;
    copyTx->signature = tx->signature;
    return copyTx;
 }
