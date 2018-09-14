//Include Statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Structure Template
typedef struct customer_Info{
	char name[101];
	int checkingID;
	float checkingTotal;
	int savingsID;
	float savingsTotal;
	bool delete;
}account; 

//Function Prototyping
void createAccount(void);
void deleteAccount(void);
void deposit(void);
void withdraw(void);
void transfer(void);
void view(void);
void clear(void);

//Global Variable
int numRecords = 0; 

//***** MAIN FUNCTION *****
int main(void){
	printf("\n\n***** Welcome to the Banking Program! *****");
	
	int userInput = 0; 
	
	//The Menu
	do
	{
		printf("\n\n=== Main Menu ===");
		printf("\n\t1) Create an Account");
		printf("\n\t2) Delete an Account");
		printf("\n\t3) Deposit Funds");
		printf("\n\t4) Withdraw Funds");
		printf("\n\t5) Transfer Funds");
		printf("\n\t6) View Account Information");
		printf("\n\t7) Quit\n\n\t***  ");
		scanf("%i", &userInput);
		clear();
		
		switch (userInput)
		{
			case 1:
				//Create an Account
				system("cls");
				createAccount();
				break;
			case 2:
				//Delete an Account
				system("cls");
				deleteAccount();
				break;
			case 3:
				//Deposit Funds
				system("cls");
				//deposit();
				break;
			case 4:
				//Withdraw Funds
				system("cls");
				//withdraw();
				break;
			case 5:
				//Transfer Funds
				system("cls");
				//transfer();
				break;
			case 6:
				//View Account Information  
				system("cls");
				//view();	
				break;
			case 7:
				break;
			default:
				printf("\n\n***** Please Enter a Valid Menu Option *****");
				break;
		}				
	}while(userInput != 7);
	
	//Erase the file 
	FILE *filePointer = fopen("accounts.dat", "w");
	fclose(filePointer);
	printf("\n\n***** Exiting the Banking Program *****\n\n\n");
	
	return 0; 
}


//***** CREATE ACCOUNT *****
void createAccount(void){
	FILE *filePointer = fopen("accounts.dat", "ab+");
	account *recordPointer = malloc(sizeof(account));

	int tempHolder=0, checker=0; 
	
	//*** NAME ***
	printf("\n\n*** Please Enter the Customer's Name (Max 100 Characters)\n\t- ");
	scanf("%100[^\n]", recordPointer->name);
	clear();
	
	//*** CHECKING ACCOUNT NUMBER ***
	printf("\n*** Please Enter the Customer's Unique Checking Account Number\n\t- ");
	scanf("%i", &tempHolder);
	clear();
	while(fread(recordPointer, sizeof(account), 1, filePointer) == 1){
		if(tempHolder == recordPointer->checkingID){
			checker = 2; 
			break;
		}
		else{
			checker = 1;
		}
	}
	if(checker == 1){
		recordPointer->checkingID = tempHolder; 
	}
	else if(checker == 2){
		printf("\n\n\t***** ERROR: Duplicate Checking Account Number Found *****");
		return;
	}
	tempHolder = 0; 
	checker = 0; 
	fseek(filePointer, 0, SEEK_SET);
	
	//*** CHECKING ACCOUNT BALANCE ***
	printf("\n*** Please Enter the Customer's Checking Account Balance\n\t- $ ");
	scanf("%f", &tempHolder);
	clear();
	if(tempHolder < 0){
		printf("\n\n***** You can't have a negative balance! *****");
		return; 
	}
	else{
		recordPointer->checkingTotal = tempHolder; 
	}
	tempHolder = 0; 
	
	//*** SAVINGS ACCOUNT NUMBER ***
	printf("\n*** Please Enter the Customer's Unique Savings Account Number\n\t- ");
	scanf("%i", &tempHolder);
	clear();
	while(fread(recordPointer, sizeof(account), 1, filePointer) == 1){
		if(tempHolder == recordPointer->savingsID){
			checker = 2; 
			break;
		}
		else{
			checker = 1;
		}
	}
	if(checker == 1){
		recordPointer->savingsID = tempHolder; 
	}
	else if(checker == 2){
		printf("\n\n\t***** ERROR: Duplicate Savings Account Number Found *****");
		return;
	}
	tempHolder=0, checker=0; 
	fseek(filePointer, 0, SEEK_SET);
	
	//*** SAVINGS ACCOUNT BALANCE ***
	printf("\n*** Please Enter the Customer's Savings Account Balance\n\t- $ ");
	scanf("%f", &tempHolder);
	clear();
	if(tempHolder < 0){
		printf("\n\n***** You can't have a negative balance! *****");
		return; 
	}
	else{
		recordPointer->savingsTotal = tempHolder; 
	}
	tempHolder = 0; 
	
	//*** CONFIRMATION ***
	printf("\n***** Account Added Successfully! *****");
	numRecords++;
	
	//*** ADD INFORMATION TO TEXT FILE ***
	fwrite(recordPointer, sizeof(account), 1, filePointer);
	
	//*** CLEANUP ***
	tempHolder = 0;
	checker = 0;
	free(recordPointer);
	fclose(filePointer);
}



//***** DELETE ACCOUNT *****
void deleteAccount(void){
	if(numRecords >= 1){
		FILE *filePointer = fopen("accounts.dat", "ab+");
		FILE *tempFile = fopen("temporary.dat", "ab+");
		account *recordPointer = malloc(sizeof(account));
		
		int userInput=0, tempHolder=0;
		recordPointer->delete = false; 
		
		//*** MENU ***
		while(userInput != 3){
			printf("\n\n--- Search for Record By ---");
			printf("\n\t1) Checking Account Number");
			printf("\n\t2) Savings Account Number");
			printf("\n\t3) Quit\n\t***  ");
			scanf("%i", &userInput);
			clear();
			
			//*** CHECKING ACCOUNT NUMBER ***
			if(userInput == 1){
				printf("\n*** Please Enter the Customer's Checking Account Number:\n\t-  ");
				scanf("%i", &tempHolder);
				clear();
				
				while(fread(recordPointer, sizeof(account), 1, filePointer) == 1){
					if(tempHolder == recordPointer->checkingID){
						recordPointer->delete = true;
						printf("\n***** Found Record! *****");
						break;
					}
					else{
						fwrite(recordPointer, sizeof(account), 1, tempFile);
						printf("\n***** NO Record! *****");
					}
				}
				fseek(filePointer, 0, SEEK_SET);
			}
			
			//*** SAVINGS ACCOUNT NUMBER ***
			else if(userInput == 2){
				printf("\n*** Please Enter the Customer's Savings Account Number:\n\t-  ");
				scanf("%i", &tempHolder);
				clear();
				
				while(fread(recordPointer, sizeof(account), 1, filePointer) == 1){
					if(tempHolder == recordPointer->savingsID){
						recordPointer->delete = true;
						printf("\n***** Found Record! *****");
					}
					else{
						fwrite(recordPointer, sizeof(account), 1, tempFile);
					}
				}
				fseek(filePointer, 0, SEEK_SET);
			}	
			
			else if(userInput!=1 && userInput!=2 && userInput!=3){
				printf("\n\n===== Please Enter a Valid Menu Option =====");
			}
		}
		
		if(recordPointer->delete == true){
			printf("\n\n***** Record Deleted *****");
			remove("accounts.dat");
			rename("tempfile.dat", "accounts.dat");
			recordPointer->delete = false; 
			numRecords--;
			return; 
		}
		else{
			printf("\n\n===== Record Not Found! =====");
			recordPointer->delete = false;
		}
		
		//*** CLEANUP ***
		recordPointer->delete = false; 
		fseek(filePointer, 0, SEEK_SET);
		free(recordPointer);
		fclose(filePointer);
	}
	else{
		printf("\n\n===== No Records to Delete =====");
	}
	printf("\n*** Exiting Delete Function***");
}

//***** CLEAR FUNCTION *****
void clear(void){
	while(getchar() != '\n');
}
