/**
 * @author George Trimbath
 * Main execution point for mimicking blockchain functionality
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../include/miner.h"
#include "../include/user.h"
#include "../include/transaction.h"
#include "../include/mempool.h"
#define INPUT_MAX 30

/**
 * Struct for storing the list of users on the network
 */
typedef struct{
    User **users;
    int userCount;
    int capacity;

}Users;

/**
 * Struct for storing the list of miners on the network
 */
typedef struct{
    Miner **miners;
    int minerCount;
    int capacity;

}Miners;


/**
 * Helper function for getting input from a user for each command.
 */
char *getUserInput(){
    char *userInput = malloc(sizeof(char)*INPUT_MAX);
    
    //Read in user input
    if(fgets(userInput, INPUT_MAX, stdin) != NULL){
        return userInput;
    } else{
        fprintf(stderr, "Error getting user input");
        exit(EXIT_FAILURE);
    }
}

/**
 * Function that ensures program is terminated properly
 */
void executeTerminate(Miners *minerList, Users *userList ){
    printf("Termination will now be executed\n");

    for(int i = 0; i < minerList->minerCount; i++){
        free(minerList->miners[i]);
    }
    free(minerList->miners);

    for(int i = 0; i < userList->userCount; i++){
        free(userList->users[i]);
    }

    free(userList->users);

    printf("Termination complete\n");
}

/**
 * This will make a user as inactive so a user can no longer make or receive transactions. 
 * There data however will remain.
 */
void deleteUser(char *userInput){
    char *username = malloc(sizeof(char)*INPUT_MAX);
    if(sscanf(userInput, "%s\n", username) == 1 && strncmp(username, userInput, strlen(userInput) - 1) == 0){
        printf("User named %s successfully deleted\n", username);
    } else{
        fprintf(stderr, "USAGE username\n");
    }
}

/**
 * Returns a user that matches the provided username
 */
User *getUser(Miners *minerList, Users *userList, char *username){
    for(int i = 0; i < userList->userCount; i++){
        if(strcmp(get_username(userList->users[i]), username) == 0){
            return userList->users[i];
        }

    }

    for(int i = 0; i < minerList->minerCount; i++){
        if(strcmp(get_miner_username(minerList->miners[i]), username) == 0){
            return get_miner_user(minerList->miners[i]);
        }

    }

    return NULL; 
}


/**
 * Creates a new user or miner to add to the list of active users and miners.
 */
void createUser(char *userInput, Users *userList, Miners *minersList){
    char *username = malloc(sizeof(char)*INPUT_MAX);
    size_t strLength = strlen(userInput);
    size_t substring = 6;

    //Create a new miner
    if(sscanf(userInput, "%s miner\n", username) == 1 && strcmp(userInput + strLength - substring, "miner\n") == 0){

        //Check to see if user added is a duplicate
        User *dupUser = getUser(minersList, userList, username);
        
        if(dupUser != NULL){
            printf("Miner with this username already exists\n");
            return;
        }
        Miner *newMiner = init_miner(username, 0);

        if(minersList->minerCount == minersList->capacity){
            minersList->capacity*=2;

            minersList->miners = realloc(minersList->miners, sizeof(Miner*)* minersList->capacity);

            if(minersList->miners == NULL){
                fprintf(stderr, "Memory reallocation for miner list failed.");
            }
        }


        minersList->miners[minersList->minerCount++] = newMiner; 
        printf("Miner named %s successfully created\n", username);

    //Create a new user
    }else if(sscanf(userInput, "%s\n", username) == 1 && strncmp(username, userInput, strlen(userInput) - 1) == 0){

        //Check to see if user added is a duplicate
        User *dupUser = getUser(minersList, userList, username);
        
        if(dupUser != NULL){
            printf("User with this username already exists\n");
            return;
        }

        User *newUser = init_user(username, 0);

        //Increase capacity of user list if necessary
        if(userList->userCount == userList->capacity){
                    userList->capacity*=2;
                    userList->users = realloc(userList->users, sizeof(User*)*userList->capacity);

                    if(userList->users == NULL){
                        fprintf(stderr, "Memory reallocation for user list failed.");
                    }
        }

        userList->users[userList->userCount++] = newUser;
        printf("User named %s successfully created\n", username);

    //User input error
    } else{
        fprintf(stderr, "USAGE: username miner or username\n");
    }
}

/**
 * User makes a manual transaction, to pay another user.
 * Will need to create a struct called transaction to store.
 */
Transaction *makeTransaction(char *transaction, Miners *minerList, Users *userList){
    char *payer = malloc(sizeof(char)*INPUT_MAX);
    char *receipent = malloc(sizeof(char)*INPUT_MAX);
    int amount = 0;

    //Initialize and have user validate transaction
    if(sscanf(transaction, "%s %s %d", payer, receipent, &amount) == 3){
        printf("%s paid %s, %d coins\n", payer, receipent, amount);
        User *pUser = getUser(minerList, userList, payer);
        User *rUser = getUser(minerList, userList, receipent);

        if(pUser == NULL || rUser == NULL){
            fprintf(stderr, "Invalid transaction user did not exist\n");
        }

        Transaction *newTransaction = init_transaction(pUser, rUser, amount);
        sign_transaction(newTransaction, newTransaction->payer);

        //Payer can now add transaction to mempool if its valid
        if(verify_transaction(newTransaction)){
            Mempool *m = get_mempool(newTransaction->payer);
            add_transaction(m, newTransaction);
            return newTransaction;
        }

    } else{
        fprintf(stderr, "USAGE: Payer receipent amount\n");

    }
    return NULL;

}

/**
 * Method used to update the difficulty of hashing
 * number indicates number of leading zeros in hash before the hash is considered valid
 */
void updateDifficulty(char *difficulty){
    int diff = 0;
    if(sscanf(difficulty, "%d\n", &diff)){
        //Add code here to update system diffculty
        printf("Diffculty successfully updated to %d\n", diff);
    } else{
          fprintf(stderr, "USAGE: integer\n");
    }
}

/**
 * Simple method to distribute a transaction to the mempool on nodes in the rest of the system.
 * Need a way to copy transactions as don't want the same tx to be shared across all mempools
 */
void broadCastTransaction(Transaction *tx, Users *userList, Miners *minerList){
    //Add to the mempool for every node except the payers as it will already be there
    for(int i = 0; i < userList->userCount; i++){
        if(strcmp(get_username(userList->users[i]), get_username( tx->payer )) != 0 ){
            Mempool *m = get_mempool(userList->users[i]);
            Transaction *copyTx = copy_transaction(tx);
            add_transaction(m, copyTx);
        } 
    }

    for(int i = 0; i < minerList->minerCount; i++){
        if(strcmp(get_miner_username(minerList->miners[i]), get_username( tx->payer )) != 0 ){
            Mempool *m = get_mempool(get_miner_user(minerList->miners[i]));
            Transaction *copyTx = copy_transaction(tx);
            add_transaction(m, copyTx);
        } 
    }
}


 int main(int argc, char* argv[]){
    //open or create file
    FILE *fp = fopen("../files/keys.txt", "w");
    if(fp){
        fclose(fp);
    } else{
        printf("Error opening file at program start-up");
    }

    //For pseudo-random cryptography functions.
    srand(time(NULL));

    //Initialize miner and user lists
    Users userList;
    userList.capacity = 10;
    userList.userCount = 0;
    userList.users = malloc(sizeof(User*) * userList.capacity);

    Miners minerList;
    minerList.capacity = 10;
    minerList.minerCount = 0;
    minerList.miners = malloc(sizeof(Miner*) * minerList.capacity);


    while(true){
        printf("cmd>");

        char *userInput = malloc(sizeof(char)*INPUT_MAX);

        if(fgets(userInput, INPUT_MAX, stdin) != NULL){
            //Exit program
            if(strcmp(userInput, "Terminate\n") == 0){
                executeTerminate(&minerList, &userList);
                break;

            //Deletes a user/miner
            } else if(strcmp(userInput, "Delete\n") == 0){
                printf("Delete>");
                char *userID = getUserInput();
                deleteUser(userID);

            //Creates a new user/miner
            } else if(strcmp(userInput, "Create\n") == 0){
                printf("Create>");
                char *userID = getUserInput();
                createUser(userID, &userList, &minerList);
            
            // Creates a new transaction
            } else if(strcmp(userInput, "Transaction\n") == 0){
                printf("Transaction>");
                char *transactionStr = getUserInput();
                Transaction *transaction = makeTransaction(transactionStr, &minerList, &userList);
                if(transaction){
                    printf("New transaction created!\n");
                    broadCastTransaction(transaction, &userList, &minerList);
                }

            //Allows update of the hashing difficulty
            }else if(strcmp(userInput, "Difficulty\n") == 0){
                printf("Difficulty>");
                char *difficulty = getUserInput();
                updateDifficulty(difficulty);
                
            }else{
                printf("Invalid command: Commands are Terminate, Delete, Create, Transaction, Difficulty\n");
            }
        }
    }


    printf("Good bye!\n");
    return EXIT_SUCCESS;
 }