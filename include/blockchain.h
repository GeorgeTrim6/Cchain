/**
 * Modeled as a linked list of blocks
 */

 #include "block.h"


typedef struct Node{
    Block *data;
    struct Node *next;
    struct Node *prev;

 }Node;


 typedef struct Blockchain
 {
    Node *front;
    Node *back;
    int size;
    
 } Blockchain;


 /**
  * Initialize blockchain state
  */
 Blockchain *init_blockchain();