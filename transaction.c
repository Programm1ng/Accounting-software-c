#include "transaction.h"
#include <stdlib.h>

TransactionsArray *newTransactionsArray() {
  TransactionsArray *ta = (TransactionsArray *)malloc(sizeof(TransactionsArray));
  ta->transactions = NULL;
  ta->size = 0;
  return ta;
}

Transaction *newTransaction() {
  Transaction *transaction = malloc(sizeof(Transaction));
  transaction->day = 0;
  transaction->month = 0;
  transaction->year = 0;
  return transaction;
}

void insertTransaction(TransactionsArray *ta, Transaction *transaction) {
  ta->transactions = realloc(ta->transactions, ta->size * sizeof(Transaction));
  ta->transactions[ta->size] = *transaction;
  ta->size += 1;
}

void freeTransactionsArray(TransactionsArray *ta) {
  free(ta->transactions);
  ta->transactions = NULL;
  ta->size = 0;
}