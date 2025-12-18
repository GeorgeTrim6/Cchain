/**
 * Header file for users
 */
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>


 typedef struct User User;

 typedef struct Mempool Mempool;

/**
 * Create the user struct with default data.
 * Create the users private and public key pair
 */
 User *init_user(char *username, int balance);

/**
 * Gets the user's name
 */
 char *get_username(User *user);

/**
 * Written by ChatGPT as a way to create a simple hash function for my program.
 */
 uint64_t simple_hash(const void *data, size_t len);

/**
 * Gets the users public key for verifying transactions
 */
 uint64_t get_public_key(User *user);

/**
 * Used to get the user to authenicate a transaction by providing their signature
 */
 uint64_t create_signature(char *data, User *user);


 /**
  * Gets the users mempool
  */
Mempool *get_mempool(User *user);


