/**
 * Implementation file for miner.
 */
#include "../include/miner.h"


 struct Miner{
    User *user;

 };


 Miner *init_miner(char *username, int balance){
    User *user = init_user(username, balance);

    Miner *miner = malloc(sizeof(Miner));

    if(miner == NULL){
        fprintf(stderr, "Error allocating memory for the miner\n");
        return NULL;
    }

    miner->user = user;
    return miner;
 }


 char *get_miner_username(Miner *miner){
    return get_username(miner->user);
 }

 User *get_miner_user(Miner *miner){
    return miner->user;
 }

 