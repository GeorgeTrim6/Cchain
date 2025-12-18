/**
 * Header file for the system components for the mock block chain project
 * Will contain the information that will be applied to all nodes on the system.
 * That is:
 * - mining difficultly level
 * - List of users
 * - List of miners
 * - mempool of transaction
 */


 typedef struct{
    int difficulty;
    int numUsers;
    int numMiners;
    //User **users = malloc(sizeof(User*)*numUsers);
    //Miner **miners = malloc(sizeof(Miner)*numMiners);
    int numTransactions;
    //Mempool = createMempool 

 } System;