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
  return transaction;
}

void insertTransaction(TransactionsArray *ta, Transaction *transaction) {
  ta->size += 1;
  ta->transactions = realloc(ta->transactions, ta->size * sizeof(Transaction));
  ta->transactions[ta->size-1] = *transaction;
}

void freeTransactionsArray(TransactionsArray *ta) {
  free(ta->transactions);
  ta->transactions = NULL;
  ta->size = 0;
}