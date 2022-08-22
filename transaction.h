#include <stdio.h>

#ifndef TRANSACTION_HEADER
#define TRANSACTION_HEADER

/**
 * @brief Stores information about one transaction
 * 
 */
typedef struct {
  int type;
  int otherClientId;
  int day;
  int month;
  int year;
  float amount;
} Transaction;

/**
 * @brief Stores multiple transactions
 * 
 */
typedef struct {
  Transaction * transactions;
  size_t size;
} TransactionsArray;

/**
 * @brief Creates a new TransactionsArray obj
 * 
 * @return TransactionsArray* 
 */
TransactionsArray *newTransactionsArray();

/**
 * @brief Creates a new Transaction obj from the Transaction struct
 * 
 * @return Transaction* 
 */
Transaction *newTransaction();

/**
 * @brief Inserts a transaction into the given TransactionsArray
 * 
 * @param ta 
 * @param t 
 */
void insertTransaction(TransactionsArray *ta, Transaction *t);

/**
 * @brief Deallocates the memory from the TransactionsArray
 * 
 * @param ta 
 */
void freeTransactionsArray(TransactionsArray *ta);

#endif