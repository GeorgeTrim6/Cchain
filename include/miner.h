/**
 * Header file for the miner. Miner should have all the capabilities of a user with the additional
 * ability to create new valid blocks. 
 */
#include <stdlib.h>
#include "user.h"

 typedef struct Miner Miner;


 Miner *init_miner(char *username, int balance);

/**
 * Gets the username associated with the miner
 */
 char *get_miner_username(Miner *miner);


/**
 * Gets the user struct associated with the miner
 */
 User *get_miner_user(Miner *miner);
