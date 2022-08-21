/**
 * @file client_t.h
 * @author Programm1ng
 * @brief Holds the structure for a client
 * @version 0.1
 * @date 2022-08-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CLIENT_HEADER
#define CLIENT_HEADER

typedef struct client {
  int id;
  char firstname[50];
  char lastname[50];
  float balance;
  struct client * next;
} client_t;

#endif