/**
 * Header file for transactions
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>


typedef struct User User;
typedef struct Mempool Mempool;
/**
 * Will store data associated with a transaction
 */
/* Named struct — NOT anonymous */
typedef struct Transaction {
    User *payer;
    User *recipient;
    int amount;
    time_t time;
    uint64_t signature;
} Transaction;



 /**
  * Initialization function for transaction
  * Returns a pointer to the struct
  */
 Transaction *init_transaction(User *payer, User *receipent, int amount);


 /**
  * Used to return the state of a transaction as a string besides for the signature field.
  */
 char *get_transaction_data(Transaction *tx);


 /**
 * Sign the transaction to verify that it is accurate.
 */
void sign_transaction(Transaction *tx, User *user);

/**
 * Function to verify if the transaction is valid aka hash to the expected value 
 * based on the payer's private key
 */
bool verify_transaction(Transaction *tx);


/**
 * Creates and returns a deep copy of a transaction
 */
Transaction *copy_transaction(Transaction *tx);

#endif