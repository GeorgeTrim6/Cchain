/**
 * Implementation file for user.c
 */
#include "../include/user.h"
#include "../include/mempool.h"

#define MAX_LENGTH 64

 struct User{
    char *username;
    int accountBalance;
    uint64_t publicKey;
    Mempool *mempool;

 };

 /*** ------------------------ Private helper functions ------------------------------- */

/**
 * Generates a secret private key for our user.
 */
uint64_t generate_secret_key() {
    return ((uint64_t)rand() << 32) | rand();
}

/**
 * Crazy secure public key creation method to make a public and private key pair
 * that can be used to validate transactions.
 */
uint64_t create_public_key(uint64_t sk){
    if(sk <= 10){
        return sk + 10;
    }
    return sk - 10;

}


/**
 * Gets the secret key thats been saved in the file keys.txt
 */
 uint64_t get_secret_key(char *username){
    uint64_t hashedUsername = simple_hash(username, strlen(username));

    FILE *fp = fopen("../files/keys.txt", "r");

    if(fp == NULL){
        printf("Error opening file\n");
    }

    char buffer[256];

    while(fgets(buffer, MAX_LENGTH, fp) != NULL){
        //Get first string of characters before space
        uint64_t name;
        uint64_t key; 
        if(sscanf(buffer, "%" SCNu64", %" SCNu64, &name, &key) == 2){
            if(name == hashedUsername){
                return key;
            }

        }else{
            printf("Failure parsing keys.txt");
        }
    }

    return 0;
 }

/**
 * Saves the secret key along with the associated users hashed username.
 */
  void save_key(uint64_t key, char *username){
    uint64_t hashedUsername = simple_hash(username, strlen(username)); 
    FILE *fp = fopen("../files/keys.txt", "a");

    if(fp != NULL){
        fprintf(fp, "%" PRIu64 ", %" PRIu64 "\n", hashedUsername, key);
        fclose(fp);

    } else{
        fprintf(stderr, "Error writing key to file\n");
    }

 }

  /*** ------------------------ --------------------------------- ------------------------------- */


 uint64_t get_public_key(User *user){
    return user->publicKey;

 }

  User *init_user(char *username, int balance){
    User *newUser = malloc(sizeof(User));

    if(newUser == NULL){
        fprintf(stderr, "Memory allocation failed for user failed\n");
        return NULL;
    }

    uint64_t sk = generate_secret_key();
    save_key(sk, username);
    uint64_t pk = create_public_key(sk);

    newUser->accountBalance = balance;
    newUser->username = username;
    newUser->publicKey = pk;
    newUser->mempool = init_mempool();

    return newUser;
 }

  uint64_t create_signature(char *data, User *user){
    // Get the secret key
    uint64_t sk = get_secret_key(user->username);

    if(sk == 0){
        printf("Error getting user's secret key\n");
        exit(EXIT_FAILURE);
    }


    return simple_hash(data, strlen(data)) ^ sk;
 }



char *get_username(User *user){
    return user->username;
 }

 uint64_t simple_hash(const void *data, size_t len) {
    uint64_t hash = 14695981039346656037ULL; // FNV offset basis
    const unsigned char *bytes = data;

    for(size_t i = 0; i < len; i++)
        hash = (hash ^ bytes[i]) * 1099511628211ULL; // FNV prime

    return hash;
}


Mempool *get_mempool(User *user){
    return user->mempool;
}



