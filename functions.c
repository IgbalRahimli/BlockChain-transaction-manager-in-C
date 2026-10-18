int getTodayDate(){
	int year, month, day;
	time_t now = time(NULL);
	struct tm *t = localtime(&now); 
	
	year = t->tm_year + 1900;
	month = t->tm_mon + 1;
	day = t->tm_mday;
	return year * 10000 + month * 100 + day;
}


void my_strcpy(char *dest, char *src){
	while(*src){
		*dest = *src;
		src++;
		dest++;
	}
	*dest = 0;
}
unsigned int my_strlen(char *string){
	unsigned int lenght = 0;
	for(int i = 0; *(string + i) != 0; i++)
		lenght++;
	return lenght;
}

int transactionCount(BlockChain bc){
	int count = 0;
	T_Block *temp1 = bc;
	T_Transaction *temp2;
	while(temp1 != NULL){
		temp2 = temp1->listTransaction;
		while(temp2 != NULL){
			count++;
			temp2 = temp2->prev;
		}
		temp1 = temp1->prev;
	}
	return count;
}

T_Block *searchBlockByDate(int date, BlockChain bc){
	while(bc != NULL){
		if(bc->date == date){
			return bc;
		}
		bc = bc->prev;
	}
	return NULL;
}


T_Block *searchBlockById(int id, BlockChain bc){
	while(bc != NULL){
		if(bc->id == id){
			return bc;
		}
		bc = bc->prev;
	}
	return NULL;
}

int presenceStudent(int idStud, BlockChain bc){
	T_Block *temp1 = bc;
	T_Transaction *temp2;
	while(temp1 != NULL){
		temp2 = temp1->listTransaction;
		while(temp2 != NULL){
			if(temp2->idStud == idStud)
				return 1;
			temp2 = temp2->prev;
		}
		temp1 = temp1->prev;
	}
	return 0;
}


void displayBlockChain(BlockChain bc){
	if(bc != NULL){
		printf(" ID         Date\n");
    	printf("----------------\n");
	}

    int year, month, day;
    while(bc != NULL){
        year  = bc->date / 10000;
        month = (bc->date / 100) % 100;
        day   = bc->date % 100;
        printf(" %2d   %d/%d/%d\n", bc->id, day, month, year);

    	bc = bc->prev;
    }
}

void displayBlock(T_Block *block){
	T_Transaction *temp = block->listTransaction;
	if(temp != NULL){
		printf("    ID    Amount   Description\n");
    	printf("-------------------------------------------------------\n");
	}

	while(temp != NULL){
		printf("%6d %9.3f   \"%s\"\n", temp->idStud, temp->amount, temp->descr);
		temp = temp->prev;
	}
}

char displayStudent(int idStud, T_Block *block) {
    int foundAny = 0;
	T_Transaction *temp = block->listTransaction;
	
	while (temp != NULL) {
	    if (temp->idStud == idStud) {
	        printf("Amount: %8.3f | Description: %s\n", temp->amount, temp->descr);
	
	        foundAny = 1;
	    }
	    temp = temp->prev;
	}
	return foundAny;
}

void displayTransaction(int idStud, T_Transaction *transaction){
	printf("%8.3f; %s\n", transaction->amount, transaction->descr);
}

T_Transaction *addTransaction(int idStud, float amount, char *descr, T_Transaction *listTransaction){
	T_Transaction *newTransaction = NULL;
	newTransaction = malloc(sizeof(T_Transaction));
	
	if(newTransaction == NULL){
		printf("malloc failed!");
		return NULL;
	}

	newTransaction->idStud = idStud;
	newTransaction->amount = amount;
	newTransaction->descr = descr;
	newTransaction->prev = listTransaction;
	return newTransaction;
}

BlockChain addBlock(BlockChain bc){
	T_Block *newBlock = NULL;
	newBlock = malloc(sizeof(T_Block));

	if(newBlock == NULL){
		printf("malloc failed!");
		return bc;
	}
	if(bc == NULL){
		newBlock->id = 0;
	} else {
		newBlock->id = bc->id + 1;
	}
	newBlock->date = getTodayDate();

	newBlock->listTransaction = NULL;

	newBlock->prev = bc;
	return newBlock;
}


float totalTransactionStudentBlock(int idStud, T_Block b){
	float total = 0;
	T_Transaction *temp = b.listTransaction;
	while(temp != NULL){
		if(temp->idStud == idStud){
			total += temp->amount;
		}
		temp = temp->prev;
	}
	return total;
}

float balanceStudent(int idStud, BlockChain bc){
	float balance = 0;
	T_Block *temp = bc;
	while(temp != NULL){
		balance += totalTransactionStudentBlock(idStud, *temp);
		temp = temp->prev;
	}
	return balance;
}

void credit(int idStud, float amount, char *descr, BlockChain bc){
	if(amount > 0)
		bc->listTransaction = addTransaction(idStud, amount, descr, bc->listTransaction);
}

int pay(int idStud, float amount, char *descr, BlockChain bc){
	if(balanceStudent(idStud, bc) < amount){
		return -1;
	}
	if(amount <= 0){
		return 0;
	}
	bc->listTransaction = addTransaction(idStud, amount*(-1), descr, bc->listTransaction);
	return 1;
}

void consult(int idStud, BlockChain bc){
	printf("                .....................\n");
 	printf("                | Balance: %8.3f |                \n", balanceStudent(idStud, bc));
	printf("                `````````````````````\n\n");
	printf(" Block Id                      Description    Amount\n");
	printf("----------------------------------------------------\n");

	int count = 0;
	char isEnough = 0;
	T_Block *temp1 = bc;
	T_Transaction *temp2;
	while((temp1 != NULL) && !isEnough){
		temp2 = temp1->listTransaction;
		while((temp2 != NULL) && !isEnough){
			if(temp2->idStud == idStud){
				printf("%9i %32s %9.3f\n", temp1->id,temp2->descr, temp2->amount);
				count++;
			}

			if(count >= 5){
				isEnough = 1;
			}
			temp2 = temp2->prev;
		}
		temp1 = temp1->prev;
	}
}

int transfer(int idSource, int idDestination, float amount, char *descr, BlockChain bc){
	int success = pay(idSource, amount, descr, bc);
	if(success == 1){
		credit(idDestination, amount, descr, bc);
		return 1;
	}
	return success;
}

void destroyChain(BlockChain *bc){
	T_Block *temp0, *temp1 = *bc;
	T_Transaction *temp2, *temp3;
	while(temp1 != NULL){
		temp2 = temp1->listTransaction;
		while(temp2 != NULL){
			temp3 = temp2->prev;
			free(temp2);
			temp2 = temp3;
		}
		temp1->listTransaction = NULL;

		temp0 = temp1->prev;
		free(temp1);
		temp1 = temp0;
	}
	*bc = NULL;
}

void exportChain(BlockChain bc){
	int year, month, day;
	char buffer[256];
	FILE *fptr = NULL;

	int tCount = transactionCount(bc);
	int dates[tCount];
	int idStuds[tCount];
	float amounts[tCount];
	char *descrs[tCount];

	fptr = fopen("blockChain.txt", "w");

	if(fptr == NULL){
		printf("File blockChain.txt cannot be created!\n");
		return;
	}

	int index = 0;
	T_Block *temp1 = bc;
	T_Transaction *temp2;
	while(temp1 != NULL){
		temp2 = temp1->listTransaction;
		while(temp2 != NULL){
			dates[tCount - 1 - index] = temp1->date;
			idStuds[tCount - 1 - index] = temp2->idStud;
			amounts[tCount - 1 - index] = temp2->amount;
			descrs[tCount - 1 - index] = temp2->descr;
			temp2 = temp2->prev;
			index++;
		}
		temp1 = temp1->prev;
	}
	index = 0;
	while(index < tCount){
		year  = dates[index] / 10000;
		month = (dates[index] / 100) % 100;
		day   = dates[index] % 100;

		sprintf(buffer, "%d/%d/%d; %d; %.3f; %s", day, month, year, 
			idStuds[index], amounts[index], descrs[index]);
		
		fprintf(fptr, "%s\n", buffer);

		index++;
	}
	fclose(fptr);
}

void importChain(BlockChain *bc){
	int year, month, day, idStud;
	float amount;
	char buffer[256];
	char descr[256];
	char *descrConst;
	FILE *fptr = NULL;

	destroyChain(bc);

	fptr = fopen("blockChain.txt", "r");

	if(fptr == NULL){
		printf("File blockChain.txt does not exist!\n");
		return;
	}


	int dateInitial = 0, date;
	while(fgets(buffer, 256, fptr)){
		sscanf(buffer, "%d/%d/%d; %d; %f; %[^\n]256s", &day, &month, &year, &idStud, &amount, &descr);
		date = year * 10000 + month * 100 + day;
		if(date != dateInitial){
			*bc = addBlock(*bc);
			(*bc)->date = date;
			dateInitial = date;
		}
		descrConst = NULL;
		descrConst = malloc(sizeof(char) * (my_strlen(descr) + 1));
		my_strcpy(descrConst, descr);
		(*bc)->listTransaction = addTransaction(idStud, amount, descrConst, (*bc)->listTransaction);
	}


	fclose(fptr);
}

float gamble(int idStud, float amount, BlockChain bc){
	int success = pay(idStud, amount, "Bet", bc);
	if(success == 1){
		amount = amount * !(rand() % 3) * (1.5 + (rand() % 50) / 100.0);
		credit(idStud, amount, "Won from gambling", bc);
		return amount;
	}
	if(success == -1)
		return -1;
	return -2;
}

char *rouletteGambleText(float rouletteType){
	int index;
	char *gambleFor1[] = {
		"A Gumball worth 0.3 EATCoin", 
		"A Trial Mix worth 0.4 EATCoin",
		"An Apple worth 0.5 EATCoin",
		"500 mL UFAZ Cola worth 1.8 EATCoin",
		"A Snack bar worth 2.0 EATCoin",
		"French Fries worth 2.2 EATCoin"
	};
	char *gambleFor5[] = {
		"Fresh juice worth 2.5 EATCoin", 
		"Basic Sandwitch worth 2.9 EATCoin",
		"CheeseBurger worth 3.1 EATCoin",
		"Lahmacun Menu worth 8.5 EATCoin",
		"Pumpkin Pie worth 8.8 EATCoin",
		"Doner Menu worth 9.0 EATCoin"
	};
	char *gambleFor10[] = {
		"EXPENSIVE Coffee and CROISSANT worth 7.0 EATCoin",
		"Coban Salad Premium worth 7.5 EATCoin",
		"Rice, Beans and Ayran worth 7.8 EATCoin",
		"Fish and Chips worth 15.0 EATCoin",
		"Big Size Pizza worth 17.5 EATCoin",
		"UFC (UFAZ-KFC) Special Menu worth 20.0 EATCoin"
	};

	
	index = (rand() % 3) + (rand() % 3 + 1) * !(rand() % 3);

	if(rouletteType == 1.0)
		return gambleFor1[index]; 
	else if(rouletteType == 2.0)
		return gambleFor5[index]; 
	else if(rouletteType == 3.0)
		return gambleFor10[index];
	return "None";
}

void rouletteGamble(int idStud, float amount, BlockChain bc){
	char *text = rouletteGambleText(amount);
	if(amount == 1.0)
		amount = 1;
	else if(amount == 2.0)
		amount = 5;
	else if(amount == 3.0)
		amount = 10;
	else {
		printf("Invalid pack :(\n");
		return;
	}

	int success = pay(idStud, amount, "Roulette", bc);
    if(success == 1){
		printf( "  ____                 \n"
				" /\\' .\\    _____     \n"
				"/: \\___\\  / .  /\\   \n"
				"\\' / . / /____/..\\  You won %s!\n"
				" \\/___/  \\'  '\\  /  \n"
				"          \\'__'\\/    \n",  text);
		return;
	}
	printf("Not enough balance for Rouletting :(\n");
}

