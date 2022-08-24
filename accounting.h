/**
 * @file accounting.h
 * @author Programm1ng
 * @brief Bundles all the functionality for the accounting software
 * @version 0.1
 * @date 2022-08-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <time.h>
#include "client.h"
#include "transaction.h"

extern const char *CLIENTS_DIRECTORY;

/**
 * @brief Load all clients from files
 * 
 * @return Client* 
 */
void initClients();

/**
 * @brief Display all loaded clients on the console
 * 
 */
void displayClients();

/**
 * @brief Prints a given client on the terminal
 * 
 * @param *client
 */
static void displayClient(Client *client);

/**
 * @brief Given the content of a client file creates a new Client object
 * 
 * @param fileContent 
 */
static Client *getClientFromFile(char* fileContent);

/**
 * @brief Adds a client object to the linked list of clients
 * 
 * @param client 
 */
static void addClientToLinkedList(Client *client);

/**
 * @brief Loads the content of a client file
 * 
 * @param filePath 
 * @return char* content of client file
 */
static char *getFileContent(char *filePath);

/**
 * @brief Uses the CLIENT_DIRECTORY constants and the file name given as parameter and creates the file path
 * 
 * @param fileName 
 * @return char* 
 */
static char *getFilePath(char *fileName);

/**
 * @brief Checks if a given file is a client text file
 * 
 * @param fileName 
 * @return int 1 if it is a client file, 0 if not
 */
static int isClientFile(char * fileName);


/**
 * @brief Given a client obj and creates a file name for that client
 * 
 * @param int 
 * @return char* the filename
 */
static char *createFileName(int clientId);

/**
 * @brief Creates a new client
 * 
 */
void createNewClient();

/**
 * @brief Get a new id for a new client
 * 
 * @return int 
 */
static int getNewClientId();

/**
 * @brief Saves a client object into a client text file
 * 
 * @param filePath 
 * @param client 
 */
static void writeClientToFile(char *filePath, Client *client);

/**
 * @brief Prints all transactions of a client on the terminal
 * 
 * @param client 
 */
void displayTransactions(int clientId);

/**
 * @brief Prints a transaction on the terminal
 * 
 * @param transaction 
 */
static void displayTransaction(Transaction *transaction);

/**
 * @brief Get a Client obj by its ID
 * 
 * @param clientId 
 * @return Client* 
 */
static Client *getClientById(int clientId);

/**
 * @brief Makes a transaction from a client to another client, returns 0 if successful otherwise returns 1
 * 
 * @param fromClientId 
 * @param toClientId 
 * @param amount 
 * @return int
 */
int makeTransaction(int fromClientId, int toClientId, double amount);

/**
 * @brief Saves a transaction to a client file
 * 
 * @param client 
 * @param transaction 
 */
static void saveTransactionToFile(Client *client, Transaction *transaction);

/**
 * @brief Update a client file
 * 
 */
static void updateClientFile(Client *client);