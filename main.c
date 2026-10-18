#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dsaproject.h"

int startmenu(BlockChain *bc){
	srand(time(NULL));
	printf("\x1B[2J\x1B[H");
    printf("...................................................................\n");
    printf(
		"| Operation Menu:                                                 |\n"
	    "|\t 1. Display the list of blocks in the BlockChain          |\n"
		"|\t 2. Display all transactions in a block                   |\n"
		"|\t 3. Display all transactions for a student on a given day |\n"
    	"|\t 4. Display the history for a student                     |\n"
		"|\t 5. Credit an account                                     |\n"
		"|\t 6. Pay for a meal                                        |\n"
    	"|\t 7. Transfer EATCoins between two students                |\n"
		"|\t 8. Export all transactions to a file                     |\n"
		"|\t 9. Import transactions from a file                       |\n"
    	"|\t10. Gambling (Are you sure?)                              |\n"
    	"|\t11. Roulette of Meals (Really?)                           |\n"
		"|\t12. Exit                                                  |\n");
    printf("```````````````````````````````````````````````````````````````````\n");
    printf("Enter a number to select an operation: ");

	int i, studentID, studentID2, date, blockID, success, select;
    float amount; 
    char *descr, buffer[256];

    fgets(buffer, 256, stdin);  
	select = atoi(buffer);

	printf("\n");

    T_Block *b;

    switch (select)
    {
    case 1: 
        printf("Here is the list of all Blocks:\n");
        displayBlockChain(*bc);  
        break;
    case 2: 
        printf("Enter ID of Block: ");
    	fgets(buffer, 256, stdin);  
		blockID = atoi(buffer);
		b = searchBlockById(blockID, *bc);
		if(b != NULL){
        	displayBlock(b);  
		}
		else {
			printf("Block not found\n");
		}
        break;
	case 3: 
    	printf("Enter ID of Student: ");
    	fgets(buffer, 256, stdin);  
		studentID = atoi(buffer);
		if(!presenceStudent(studentID, *bc)){
			printf("Student ID not found\n");
			break;
		}

        printf("Enter the Date(Ex: '20251122' for 22th November of 2025): ");
    	fgets(buffer, 256, stdin);  
		date = atoi(buffer);

		b = searchBlockByDate(date, *bc);
		if(b != NULL){
			if(!displayStudent(studentID, b)){
				printf("Student ID not found in current block\n");
			}
		}
		else {
			printf("Block not found\n");
		}
        break;
    case 4: 
    	printf("Enter ID of Student: ");
    	fgets(buffer, 256, stdin);  
		studentID = atoi(buffer);
		if(!presenceStudent(studentID, *bc)){
			printf("Student ID not found\n");
			break;
		}

        consult(studentID,*bc);
        break;    
    case 5: 
    	printf("Enter ID of Student: ");
    	fgets(buffer, 256, stdin);  
		studentID = atoi(buffer);


		if(!presenceStudent(studentID, *bc)){
			printf("Student ID not found\n");
			printf("Would you like to add this student? (y/N): ");
    		fgets(buffer, 256, stdin);  
			if((buffer[0] != 'y') && (buffer[0] != 'Y')){
				break;
			}
		}

        printf("Enter amount of EATCoin: ");
    	fgets(buffer, 256, stdin);  
		amount = atof(buffer);
		if(amount <= 0){
			printf("Amount must be more than 0. Reload was not succesful :(\n");
			break;
		}

        credit(studentID, amount, "Account Credited", *bc);  

        printf("Reload was Succesful!\n");
        break;
    case 6:
    	printf("Enter ID of Student: ");
    	fgets(buffer, 256, stdin);  
		studentID = atoi(buffer);
		if(!presenceStudent(studentID, *bc)){
			printf("Student ID not found\n");
			break;
		}

        printf("Enter amount of EATCoin: ");
    	fgets(buffer, 256, stdin);  
		amount = atof(buffer);

        printf("Give a description: ");
    	fgets(buffer, 256, stdin); 

		for(i = 0; (buffer[i] != 0) && (buffer[i] != '\n'); i++);
		buffer[i] = 0;
		descr = malloc(sizeof(char) * (my_strlen(buffer) + 1));
		my_strcpy(descr, buffer);

        success = pay(studentID, amount, descr, *bc);

        if(success == 1){
        	printf("Payment was Succesful! :)\n");
		}
		else if(success == -1){
			printf("Not enough balance. Payment was not succesful :(\n");
		}
        else{
			printf("Amount must be more than 0. Payment was not succesful :(\n");
		}
        break;
		
    case 7:
    	printf("Enter ID of Source: ");
    	fgets(buffer, 256, stdin);  
		studentID = atoi(buffer);
		if(!presenceStudent(studentID, *bc)){
			printf("Student ID not found\n");
			break;
		}

    	printf("Enter ID of Destination: ");
    	fgets(buffer, 256, stdin);  
		studentID2 = atoi(buffer);
		if(!presenceStudent(studentID2, *bc)){
			printf("Student ID not found\n");
			break;
		}

        printf("Enter amount of EATCoin: ");
    	fgets(buffer, 256, stdin);  
		amount = atof(buffer);

        printf("Give a description: ");
    	fgets(buffer, 256, stdin); 

		for(i = 0; (buffer[i] != 0) && (buffer[i] != '\n'); i++);
		buffer[i] = 0;
		descr = malloc(sizeof(char) * (my_strlen(buffer) + 1));
		my_strcpy(descr, buffer);


        success = transfer(studentID, studentID2,amount,descr,*bc);

        if(success == 1){
        	printf("Payment was Succesful! :)\n");
		}
		else if(success == -1){
			printf("Not enough balance. Payment was not succesful :(\n");
		}
        else{
			printf("Amount must be more than 0. Payment was not succesful :(\n");
		}
        break;
    case 8:
        exportChain(*bc);
        printf("Exporting was Succesful! You can check 'blockChain.txt' file.\n");
        break;
    case 9:
        importChain(bc);
        printf("Importing was Succesful!"
				"You can check new Blocks and Transactions with previous operations.\n");
        break;
    case 10:
    	printf("Enter ID of Student: ");
    	fgets(buffer, 256, stdin);  
		studentID = atoi(buffer);
		if(!presenceStudent(studentID, *bc)){
			printf("Student ID not found\n");
			break;
		}

        printf("Enter amount of EATCoin: ");
    	fgets(buffer, 256, stdin);  
		amount = atof(buffer);

		amount = gamble(studentID, amount, *bc);

        if(amount == -1)
			printf("Not enough balance for Gambling :(\n");
		else if(amount == -2)
			printf("Amount must be more than 0. Payment was not succesful :(\n");
		else {
			printf( "  ____                 \n"
					" /\\' .\\    _____     \n"
					"/: \\___\\  / .  /\\   \n"
					"\\' / . / /____/..\\  You won %.3f EATCoin!\n"
					" \\/___/  \\'  '\\  /  \n"
					"          \\'__'\\/    \n",  amount);
		}
        break;
    case 11:
    	printf("Enter ID of Student: ");
    	fgets(buffer, 256, stdin);  
		studentID = atoi(buffer);
		if(!presenceStudent(studentID, *bc)){
			printf("Student ID not found\n");
			break;
		}

		printf(	"..........................................\n"
				"| 1. Play roulette pack 1 ( 1.0 EATCoin) |\n"
				"| 2. Play roulette pack 2 ( 5.0 EATCoin) |\n"
				"| 3. Play roulette pack 3 (10.0 EATCoin) |\n"
				"``````````````````````````````````````````\n");
        printf("Enter: ");
    	fgets(buffer, 256, stdin);  
		amount = atof(buffer);

		rouletteGamble(studentID, amount, *bc);

        break;
        
    case 12:
        printf("Exiting program...\n");
        return 0;
        break;
    
    default:
		printf("Invalid option!\n");
        break;
    }
	printf("\nPress Enter to continue...");
	fgets(buffer, 256, stdin);

	return 1;
}

int main(void){
	BlockChain bc = NULL;

	importChain(&bc);

	if(bc == NULL){
		bc = addBlock(bc);
	}
	else if(bc->date != getTodayDate()){
		bc = addBlock(bc);
	}

	while(startmenu(&bc));

	destroyChain(&bc);
	return 0;
}
