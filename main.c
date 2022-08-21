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
  printf("3 Make a transaction\n");
  printf("4 Exit\n");
}

/**
 * @brief Receive input of user for menu selection
 * 
 * @return int 
 */
int getInput() {
  char *end;
  char buf[20];
  int n;

  do {
      if (!fgets(buf, sizeof buf, stdin))
          break;

      // remove \n
      buf[strlen(buf) - 1] = 0;

      n = strtol(buf, &end, 10);
  } while (end != buf + strlen(buf));

  return n;
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
    
    int option =  getInput();
    
    if (option == 1) {
      displayClients();
    } else if (option == 2) {
      createNewClient();
    } else if (option == 3) {

    } else if (option == 4) {
      return EXIT_SUCCESS;
    }

  }


  return EXIT_SUCCESS;
}