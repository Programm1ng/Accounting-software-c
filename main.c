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
 * @brief Main entry point of the program
 * 
 * @return int 
 */
int main() {
  initClients();
  displayClients();
  return EXIT_SUCCESS;
}