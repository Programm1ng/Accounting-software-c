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

#include "client_t.h"

extern const char *CLIENTS_DIRECTORY;

/**
 * @brief Load all clients from files
 * 
 * @return client_t* 
 */
void initClients();

/**
 * @brief Display all loaded clients on the console
 * 
 */
void displayClients();

/**
 * @brief Given the content of a client file creates a new client_t object
 * 
 * @param fileContent 
 */
static client_t *getClientFromFile(char* fileContent);

/**
 * @brief Adds a client object to the linked list of clients
 * 
 * @param client 
 */
static void addClientToLinkedList(client_t *client);

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
static void writeClientToFile(char *filePath, client_t *client);