/**
 * @file main2.c
 * @author Programm1ng
 * @brief A simple c accounting software for training my c skills
 * @version 0.1
 * @date 2022-08-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "accounting.h"

/**
 * @brief Show menu to let the user choose an action
 * 
 */
void displayMenu() {
  printf("Please choose an action by typing in the number and press enter\n");
  printf("1 Show clients\n");
  printf("2 Create client\n");
  printf("3 Show transactions of a client\n");
  printf("4 Make a transaction\n");
  printf("5 Exit\n");
}

/**
 * @brief Main entry point of the program
 * 
 * @return int 
 */
int main() {
  
  initClients();
  
  while(1) {

    displayMenu();
    int option;
    scanf("%d", &option);
    
    if (option == 1) {
      displayClients();
    } else if (option == 2) {
      createNewClient();
    } else if (option == 3) {
      int clientId = 0;
      printf("Please enter the id of the client\n");
      scanf("%d", &clientId);
      displayTransactions(clientId);
    } else if (option == 4) {
      int fromClientId, toClientId = 0;
      printf("Pay from client id:\n");
      scanf("%d", &fromClientId);
      
      printf("Pay to client id:\n");
      scanf("%d", &toClientId);
      
      double amount = -1;
      printf("Please enter the amount of money you want to send\n");
      scanf("%lf", &amount);

      makeTransaction(fromClientId, toClientId, amount);

    } else {
      return EXIT_SUCCESS;
    }

  }
}