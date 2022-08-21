#include "accounting.h"
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
        client_t *client = getClientFromFile(fileContent);
        addClientToLinkedList(client);
      }
    }
  }
}

void displayClients() {
  client_t *client = firstClient;

  if (client == NULL) {
    printf("No clients yet");
    return;
  }

  while (client != NULL) {
    printf("ID: %d\n", client->id);
    printf("Firstname: %s\n", client->firstname);
    printf("Lastname: %s\n", client->lastname);
    printf("Balance: %.2f€\n", client->balance);
    printf("-------------------------------------------\n\n");
    client = client->next;
  }
}

void createNewClient() {

  client_t *client = (client_t*)malloc(sizeof(client_t));

  client->id = getNewClientId();
  
  char firstname[50];
  printf("Please enter the firstname\n");
  scanf("%s", firstname);
  strcpy(client->firstname, firstname);

  char lastname[50];
  printf("Please enter the lastname\n");
  scanf("%s", lastname);
  strcpy(client->lastname, lastname);

  printf("Please enter the balance\n");
  scanf("%f", &client->balance);
  
  char *fileName = createFileName(client->id);

  char *filePath = getFilePath(fileName);

  free(fileName);

  writeClientToFile(filePath, client);
}

static int getNewClientId() {

  int newId = 0;
  
  client_t *client = firstClient;

  while(client != NULL) {
    
    if (client->id > newId) {
      newId = client->id + 1;
    }

    client = client->next;
  }

  return newId;
}

static char *createFileName(int clientId) {

  char *str = (char*)malloc(30 * sizeof(char));

  sprintf(str, "%d", clientId);

  strcat(str, ".txt\0");

  return str;
}

static client_t *getClientFromFile(char *fileContent) {

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
  strcpy(newClient->firstname, ptr);
  ptr = strtok(NULL, delim);
  
  // Get the client lastname
  strcpy(newClient->lastname, ptr);
  ptr = strtok(NULL, delim);
  
  /* Get the client balance */
  newClient->balance = atof(ptr);
  ptr = strtok(NULL, delim);

  newClient->next = NULL;

  return newClient;
}

static void addClientToLinkedList(client_t *client) {
  if (firstClient == NULL) {
    firstClient = client;
    lastClient = client;
  } else {
    lastClient->next = client;
    lastClient = client;
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

static void writeClientToFile(char *filePath, client_t *client) {
  
  FILE *fpointer = fopen(filePath, "w");

  fprintf(fpointer, "%d;%s;%s;%.2f", client->id, client->firstname, client->lastname, client->balance);

  fclose(fpointer);
}