#include "accounting.h"
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "colors.h"

const char *CLIENTS_DIRECTORY = "./clients/";

Client *firstClient = NULL;
Client *lastClient = NULL;

void initClients() {

  // Declare a variable to hold a stream to a directory
  DIR *d;
  struct dirent *dir;
  d = opendir(CLIENTS_DIRECTORY);

  if (d) {

    while((dir = readdir(d)) != NULL) {

      if (isClientFile(dir->d_name)) {
        char *filePath = getFilePath(dir->d_name);
        char *fileContent = getFileContent(filePath);
        Client *client = getClientFromFile(fileContent);
        addClientToLinkedList(client);
        free(filePath);
        free(fileContent);
      }
    }
  }
}

void displayClients() {
  
  Client *client = firstClient;

  if (client == NULL) {
    printf("No clients yet\n");
    return;
  }

  printf("################################################\n");

  while (client != NULL) {
    
    displayClient(client);

    if (client->next != NULL) {
      printf("-------------------------------------------\n");
    }
    client = client->next;
  }

  printf("################################################\n");
}

static void displayClient(Client *client) {
  printf("ID: %d\n", client->id);
  printf("Firstname: %s\n", client->firstname);
  printf("Lastname: %s\n", client->lastname);
  
  // If the balance is negative, print balance in red, else in green
  if(client->balance >= 0) {
    printf("%s", KGRN);
  } else {
    printf("%s", KRED);
  }
  printf("Balance: %.2f€\n", client->balance);
  
  // Reset console color to normal
  printf("%s", KNRM);
}

void createNewClient() {

  Client *client = (Client*)malloc(sizeof(Client));

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
  scanf("%lf", &client->balance);
  
  char *fileName = createFileName(client->id);

  char *filePath = getFilePath(fileName);

  writeClientToFile(filePath, client);

  addClientToLinkedList(client);

  free(fileName);

  free(filePath);

  printf("%sCreated new client %s %s%s\n", KGRN, client->firstname, client->lastname, KNRM);
}

static int getNewClientId() {

  int newId = 0;
  
  Client *client = firstClient;

  while(client != NULL) {
    
    if (client->id >= newId) {
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

static Client *getClientFromFile(char *fileContent) {

  /* The delimeter */
	char delim[] = ";/";

  // If a token is found, a pointer to the beginning of the token. Otherwise, a null pointer.
	char *ptr = strtok(fileContent, delim);

  // Create new client obj
  Client * newClient = (Client *)malloc(sizeof(Client));

  // Converts char * to integer and get the client id
  newClient->id = atol(ptr);
  ptr = strtok(NULL, delim);
  
  // Get the client firstname
  strcpy(newClient->firstname, ptr);
  ptr = strtok(NULL, delim);
  
  // Get the client lastname
  strcpy(newClient->lastname, ptr);
  ptr = strtok(NULL, delim);
  
  // Get the client balance
  newClient->balance = atof(ptr);
  ptr = strtok(NULL, delim);

  newClient->ta = newTransactionsArray();

  // Check for transactions
  while(ptr != NULL) {

    Transaction *transaction = newTransaction();

    // The type of the transaction
    transaction->type = atoi(ptr);

    ptr = strtok(NULL, delim);

    // The Client ID of the other client of the transaction
    transaction->otherClientId = atoi(ptr);

    ptr = strtok(NULL, delim);

    // The Amount of the transaction
    transaction->amount = atof(ptr);

    ptr = strtok(NULL, delim);

    // Add transaction to the transactions array of the client
    insertTransaction(newClient->ta, transaction);
  }

  newClient->next = NULL;

  return newClient;
}

static void addClientToLinkedList(Client *client) {
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

static void writeClientToFile(char *filePath, Client *client) {
  
  FILE *fpointer = fopen(filePath, "w");

  fprintf(fpointer, "%d;%s;%s;%.2f;", client->id, client->firstname, client->lastname, client->balance);

  fclose(fpointer);
}

void displayTransactions() {

  int clientId;
  printf("Please enter the id of the client\n");
  scanf("%d", &clientId);
  
  Client *selectedClient = getClientById(clientId);

  if (selectedClient == NULL) return;
  
  size_t size = selectedClient->ta->size;

  printf("\n");
  printf("---------------------------------------------\n");
  
  printf("%s %s - Transactions\n\n", selectedClient->firstname, selectedClient->lastname);
  
  for (int i = 0; i < size; i++) {
    
    Transaction *transaction = &selectedClient->ta->transactions[i];

    displayTransaction(transaction);
  }

  printf("---------------------------------------------\n");
}

static void displayTransaction(Transaction *transaction) {
  // Income
  if (transaction->type == 0) {
    printf("%s", KGRN);
    printf("Received +%.2lf€ ", transaction->amount);
  } 
  // Outcome
  else {
    printf("%s", KRED);
    printf("Paid -%.2lf€ ", transaction->amount);
  }

  // Reset terminal text color to default
  printf("%s", KNRM);

  Client *otherClient = getClientById(transaction->otherClientId);

  if (transaction->type == 0) {
    printf("from ");
  } else {
    printf("to ");
  }
  if (otherClient != NULL) { 
    printf("%s %s\n", otherClient->firstname, otherClient->lastname);
  } else {
    printf("%s\n", "Unknown");
  }
}

static Client* getClientById(int clientId) {
  
  Client *client = firstClient;

  if (client == NULL) {
    return NULL;
  }

  while (client != NULL) {
    if (client->id == clientId) return client;
    client = client->next;
  }

  return NULL;
}

int makeTransaction() {

  int fromClientId, toClientId = 0;
  printf("Pay from client id:\n");
  scanf("%d", &fromClientId);
  
  printf("Pay to client id:\n");
  scanf("%d", &toClientId);
  
  double amount = -1;
  printf("Please enter the amount of money you want to send\n");
  scanf("%lf", &amount);

  if (fromClientId == toClientId) {
    printf("%sA client cannot pay himself%s\n", KRED, KNRM);
    return 1;
  }

  if (amount <= 0) {
    printf("%sThe amount must be greater than zero%s\n", KRED, KNRM);
    return 1;
  }
  
  Client *fromClient = getClientById(fromClientId);
  
  Client *toClient = getClientById(toClientId);

  if (fromClient == NULL) {
    printf("%sClient who shall pay does not exist%s\n", KRED, KNRM);
    return 1;
  }

  if (toClient == NULL) {
    printf("%sClient who shall receive the payment does not exist%s\n", KRED, KNRM);
    return 1;
  }

  if (fromClient->balance - amount < 0) {
    printf("%sClient who shall pay does not have enough money\n%s", KRED, KNRM);
    return 1;
  }

  fromClient->balance -= amount;
  toClient->balance += amount;

  printf("Make payment from %s %s to %s %s\n", fromClient->firstname, fromClient->lastname, toClient->firstname, toClient->lastname);

  // Make new transaction object for sender
  Transaction *transactionSender = newTransaction();
  transactionSender->type = 1;
  transactionSender->otherClientId = toClientId;
  transactionSender->amount = amount;

  insertTransaction(fromClient->ta, transactionSender);

  // Make new transaction object for receiver
  Transaction *transactionReceiver = newTransaction();
  transactionReceiver->type = 0;
  transactionReceiver->otherClientId = fromClientId;
  transactionReceiver->amount = amount;

  insertTransaction(toClient->ta, transactionReceiver);

  updateClientFile(fromClient);
  updateClientFile(toClient);

  return 0;
}

static void saveTransactionToFile(Client *client, Transaction *transaction) {

  char *fileName = createFileName(client->id);

  char *filePath = getFilePath(fileName);

  FILE *fpointer = fopen(filePath, "a");

  fprintf(fpointer, "%d/%d/%.2lf;", transaction->type, transaction->otherClientId, transaction->amount);

  fclose(fpointer);
}

static void updateClientFile(Client *client) {

  char *fileName = createFileName(client->id);

  char *filePath = getFilePath(fileName);

  remove(filePath);

  writeClientToFile(filePath, client);

  if (client->ta != NULL) {
    for(int i = 0; i < client->ta->size; i++) {
      saveTransactionToFile(client, &client->ta->transactions[i]);
    }
  }

  free(fileName);

  free(filePath);
}