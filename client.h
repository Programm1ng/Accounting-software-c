/**
 * @file client.h
 * @author Programm1ng
 * @brief Holds the structure for a client
 * @version 0.1
 * @date 2022-08-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "transaction.h"

#ifndef CLIENT_HEADER
#define CLIENT_HEADER

typedef struct Client {
  int id;
  char firstname[50];
  char lastname[50];
  float balance;
  TransactionsArray *ta;
  struct Client * next;
} Client;

#endif