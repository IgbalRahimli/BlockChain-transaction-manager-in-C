typedef struct t_Transaction {
	int idStud;
	float amount;
	char *descr;
	struct t_Transaction *prev;
} T_Transaction;

typedef struct t_Block {
	int id;
	int date;
	T_Transaction *listTransaction;
	struct t_Block *prev;
} T_Block;

typedef T_Block *BlockChain;

// helpers
int getTodayDate();

void my_strcpy(char *dest, char *src);

unsigned int my_strlen(char *string);

// counter
int transactionCount(BlockChain bc);

// searchers
T_Block *searchBlockByDate(int date, BlockChain bc);

T_Block *searchBlockById(int id, BlockChain bc);

int presenceStudent(int idStud, BlockChain bc);

// displayers

void displayBlockChain(BlockChain bc);

void displayBlock(T_Block *block);

char displayStudent(int idStud, T_Block *block);

void displayTransaction(int idStud, T_Transaction *transaction);

// requested functions
T_Transaction *addTransaction(int idStud, float amount, char *descr, T_Transaction *listTransaction);

BlockChain addBlock(BlockChain bc); 

float totalTransactionStudentBlock(int idStud, T_Block b);

float balanceStudent(int idStud, BlockChain bc);

void credit(int idStud, float amount, char *descr, BlockChain bc);

int pay(int idStud, float amount, char *descr, BlockChain bc);

void consult(int idStud, BlockChain bc);

int transfer(int idSource, int idDestination, float amount, char *descr, BlockChain bc);



// file management
void destroyChain(BlockChain *bc);

void exportChain(BlockChain bc);

void importChain(BlockChain *bc);


// extra functions
float gamble(int idStud, float amount, BlockChain bc);

void rouletteGamble(int idStud, float amount, BlockChain bc);

#include "dsaproject.c"
