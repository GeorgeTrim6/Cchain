/**
 * Header file: For block.c 
 */

 #include "transaction.h"

 #define MAX_NUM_TRANSACTIONS 5

  typedef struct Header{
    int nonce;
    int64_t merkleroot;
    int difficulty;
    int64_t prevBlockHash;
    time_t date;

 }Header;


 typedef struct Block{
    Header *header;
    Transaction **transactions;
    int numTransactions;
    int64_t hash;

 }Block;

 /**
  * Initializes state for a new block
  */
Block *init_block(int difficulty, int64_t prevBlockHash);

 /**
  * Adds a new transaction to the block.
  */
 bool block_add_transaction(Block *b, Transaction *tx);

/**
 * The transaction for the miner when a block is successfully mined.
 */
 bool block_add_miner_transaction(Block *b, User *user);