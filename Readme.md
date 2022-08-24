# Accounting Software in C

I made this project just for learning more about the **Programming Language C**.
<br><br>
The program will display a menu to let the user choose between different actions.

1. Show all clients
2. Create client
3. Show transaction of a client
4. Make a transaction
5. Exit
   <br>

### **Show all clients**

Prints all existing clients into the terminal
<br>

### **Create client**

Allows the user to create a new client
<br>

### **Show transaction of a client**

The user has to enter an id of a client, then all transactions of this client will be printed out into the terminal
<br>

### **Make a transaction**

The user has to enter the ID of the client who should pay, the client who should receive the payment and the amount which should be transferred
<br><br>

## **How does it work**?

The clients are getting saved into a text file, the name of the text file is ID.txt for each client. For example 0.txt or 1.txt.
<br>

### The structure of a client string in a client file

`ID;firstname;lastname;balance;`
<br>
<br>
When a transaction gets created, this transaction will be also saved into the client text file.
The transaction string includes following informations:

1. The type of transaction ( 0 = outcome / paid, 1 = income / received )
2. The ID of the receiver / payer
3. The amount of money
   <br><br>

The transaction string gets append to the end of the client informations and if there is already an other transaction or multiple other transactions the new transaction gets just append to the end of the last transaction in the file.
<br>

### Example of a transaction string

`type/otherClientId/amount;`
<br>

### Example of a client file with 2 transactions

`0/Max/Mustermann/1000.00;0/1/20.00;1/1/50.00;`
<br>

1. ID -> 0
2. Firstname -> Max
3. Lastname -> Mustermann
4. Balance -> 1000.00
5. Transaction<br>
   5.1 Type of transaction -> 0 ( this client paid money )<br>
   5.1 The ID of the client who received the payment -> 1<br>
   5.3 Amount -> 20.00
6. Transaction<br>
   5.1 Type of transaction -> 1 ( this client received money )<br>
   5.1 The ID of the client who payed -> 1<br>
   5.3 Amount -> 50.00
