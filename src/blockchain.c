/**
 * Implementation file for blockchain
 */

#include "../include/blockchain.h"

 Blockchain *init_blockchain(){
    Blockchain *bc = malloc(sizeof(Blockchain));
    bc->size = 0;
    return bc;
 }