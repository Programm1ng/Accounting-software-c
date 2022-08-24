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
  printf("\n");
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
  
  // Loads clients and transactions into the program
  initClients();
  
  while(1) {

    // Display the menu so the user can choose an action
    displayMenu();

    // Declare a int variable to save the user input
    int option;

    // Get the user input
    scanf("%d", &option);
    
    // Check which action the user has choosen
    if (option == 1) {
      displayClients();
    } else if (option == 2) {
      createNewClient();
    } else if (option == 3) {
      int clientId = 0;
      displayTransactions();
    } else if (option == 4) {
      makeTransaction();
    } else {
      return EXIT_SUCCESS;
    }

  }
}