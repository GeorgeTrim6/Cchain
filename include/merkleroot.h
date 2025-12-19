/**
 * Header file for merkleroot
 */

 #include "transaction.h"


  typedef struct Merkel{
    uint64_t root;
    Transaction **transactions;
    int numTransactions;
 }Merkel;


/**
 * Creates the new merkel structure
 */
 Merkel *init_merkel(Transaction **transactions, int numTx);


 /**
  * Returns true if expected matches actual root
  */
 bool validate_root(Merkel merkel);