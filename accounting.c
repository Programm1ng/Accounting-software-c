#include "accounting.h"
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

const char *CLIENTS_DIRECTORY = "./clients/";

client_t *firstClient = NULL;
client_t *lastClient = NULL;

void initClients() {

  DIR *d;

  struct dirent *dir;

  d = opendir(CLIENTS_DIRECTORY);

  if (d) {

    while((dir = readdir(d)) != NULL) {

      if (isClientFile(dir->d_name)) {

        char *filePath = getFilePath(dir->d_name);

        char *fileContent = getFileContent(filePath);

        addClient(fileContent);
      }

    }

  }

}

void displayClients() {
  client_t *client = firstClient;

  while (client != NULL) {
    printf("ID: %d\n", client->id);
    printf("Firstname: %s\n", client->firstname);
    printf("Lastname: %s\n", client->lastname);
    printf("Balance: %.2f€\n ", client->balance);
    printf("-------------------------------------------\n");
    client = client->next;
  }
}

static void addClient(char *fileContent) {

  /* The delimeter */
	char delim[] = ";";

  /* Returns a pointer to the character of next token */
	char *ptr = strtok(fileContent, delim);

  // Create new client obj
  client_t * newClient = (client_t *)malloc(sizeof(client_t));

  // Converts char * to integer and get the client id
  newClient->id = atol(ptr);
  ptr = strtok(NULL, delim);
  
  // Get the client firstname
  newClient->firstname = ptr;
  ptr = strtok(NULL, delim);
  
  // Get the client lastname
  newClient->lastname = ptr;
  ptr = strtok(NULL, delim);
  
  /* Get the client balance */
  newClient->balance = atof(ptr);
  ptr = strtok(NULL, delim);

  newClient->next = NULL;

  if (firstClient == NULL) {
    firstClient = newClient;
    lastClient = newClient;
  } else {
    lastClient->next = newClient;
    lastClient = newClient;
  }
}

static char *getFileContent(char *filePath) {

  char *line = (char*) malloc(255 * sizeof(char));

  FILE *fpointer = fopen(filePath, "r");

  fgets(line, 255, fpointer);

  fclose(fpointer);

  return line;
}

static char *getFilePath(char *fileName) {

  /* Our path to the client files */
  const char * path = CLIENTS_DIRECTORY;
  
  /* The length of path and fileName, ( + 1 include the NULL terminator )  */
  int stringLength = strlen(path) + strlen(fileName) + 1;

  /* Create a new char array ( string ) with the size of path and filename */
  char *filePath = (char*) malloc(sizeof(char) * stringLength);

  /* Copy the path into the new created filePath string */
  strcpy(filePath, path);
  
  /* Append now the fileName onto the path which is already in filePath */
  strcat(filePath, fileName);

  /* Return the filePath */
  return filePath;
}

static int isClientFile(char * fileName) {
  
  /* Returns a pointer to the first occurrence of character in the C string dot. */
  char *dot = strrchr(fileName, '.');

  /* If the string is .txt it must be a client file */
  if (dot && !strcmp(dot, ".txt")) 
    return 1;
  else
    return 0;
}