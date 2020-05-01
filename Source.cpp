#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <string.h>

typedef struct node
{
	//Data
	int stockNum;
	char stockName[30];
	char stockSupName[30];
	int stockSupNum;
	int reOrder;
	int numOfUnits;
	float costUnit;
	int date;
	int month;
	int year;
	int chemStore;
	int dept;
	int reOrderMonth;
	int authorise;
	//Next
	struct node* NEXT;
}stock;

//Struct For Log In Details
typedef struct userDetails {
	char userName[30];
	char password[30];
	struct userDetails* NEXT;

}login;

//function
void user(struct userDetails** top);
void addNewStock(struct node** top);
void addStockItem(struct node* top);
void displayAll(struct node* top);
void displaySome(struct node* top);
void updateStock(struct node* top);
void deleteFirst(struct node** top);
void deleteStock(struct node* top);
void generateStat(struct node* top);
void printTofile(struct node* top);
void printFromfile(struct node** top);
void monetary(struct node* top);
void printToFileEnd(struct node* top);

//public variables for Generate stat
float belowf = 0;
float belowTwiceF = 0;
float aboveF = 0;
float belowM = 0;
float belowTwiceM = 0;
float aboveM = 0;

void main()
{
	struct node* headPtr = NULL;
	struct userDetails* logiN = NULL;
	int result;
	int option,choice;

	//Log in Function
	user(&logiN);

	//call print from file
	printFromfile(&headPtr);

	//Menu
	printf("=========Stock Control International Ltd=========\n");
	printf("Enter 1 to Add a stock item\n");
	printf("Enter 2 to display all stock item\n");
	printf("Enter 3 to display specific item details to screen\n");
	printf("Enter 4 to update a stock item details\n");
	printf("Enter 5 to delete a stock item\n");
	printf("Enter 6 to generate statistics based on department\n");
	printf("Enter 7 to print all stock items to file the program\n");
	printf("Enter 8 to list all the stock items in order of their total monetary value\n");
	printf("Enter 9 to save items details to the file\n");
	printf("Enter -1 to exit the program\n");
	scanf("%d", &option);
	printf("=================================================\n");

	//while loop for option
	while (option != -1)
	{
		if (option == 1)
		{
			//start
			if (headPtr == NULL)
			{
				addNewStock(&headPtr);
			}
			else
			{
				//end
				addStockItem(headPtr);
			}
		}
		else if (option == 2)
		{
			displayAll(headPtr);
		}
		else if (option == 3)
		{
			displaySome(headPtr);
		}
		else if (option == 4)
		{
			updateStock(headPtr);
		}
		else if (option == 5)
		{
			if (headPtr == NULL)
			{
				printf("Sorry Nothing is in the list - Please try again\n");
			}
			else
			{
				printf("Which stock items that you want to delete? first item or Other item?\n");
				printf("Enter 1 to delete the first Item:\n");
				printf("Enter 2 to delete other Items:\n");
				scanf("%d", &choice);
				if (choice == 1)
				{
					deleteFirst(&headPtr);
				}
				else if (choice == 2)
				{
				//	headPtr->stockNum = choice;
					deleteStock(headPtr);
				}
			}//else
		}
		else if (option == 6)
		{
			generateStat(headPtr);
		}
		else if (option == 7)
		{
			printTofile(headPtr);
		}
		else if (option == 8)
		{
			monetary(headPtr);
		}
		else if (option == 9)
		{
			printToFileEnd(headPtr);
		}

		//Menu
		printf("=========Stock Control International Ltd=========\n");
		printf("Enter 1 to Add a stock item\n");
		printf("Enter 2 to display all stock item\n");
		printf("Enter 3 to display specific item details to screen\n");
		printf("Enter 4 to update a stock item details\n");
		printf("Enter 5 to delete a stock item\n");
		printf("Enter 6 to generate statistics based  on department\n");
		printf("Enter 7 to print all stock items to file the program\n");
		printf("Enter 8 to list all the stock items in order of their total monetary value:\n");
		printf("Enter 9 to save items details to the file\n");
		printf("Enter -1 to exit the program\n");
		scanf("%d", &option);
		printf("=================================================\n");

	}//while

	getch();
}//end Main

void user(struct userDetails** top)
{
	struct userDetails* newNode;
	FILE*details;

	//File Handling
	details = fopen("user.txt", "r");

	int validate = 0;
	char userName1[30];
	char password[30];
	int i = 0;
	char ch;

	printf("Please enter Username\n");
	scanf("%s", userName1);
	printf("Please enter Password\n");
	//scanf("%s", password);
	for (i= 0;i < 7; i++)
	{
		ch = getch();	//get the first character entered for password
		password[i] = ch;	//insert it into the password array
		ch = '*';	//change the value of ch to '*'
		printf("%c", ch);	//print ch which now contains '*' to the screen
	}
	password[i - 1] = '\0';

	//Read in data from txt file
	if (details == NULL) {
		printf("Sorry The File Could Not Be Opened\n");
	}
	else 
	{
		while (!feof(details))
		{
			newNode = (struct userDetails*)malloc(sizeof(struct userDetails));
			fscanf(details, "%s %s \n", newNode->userName, newNode->password);

			//String compare for password and username
			if (strcmp(newNode->userName, userName1) == 0) 
			{
				if (strcmp(newNode->password, password) == 0) 
				{
				//	printf("Log In Successful\n");
					validate++;
				}
			}
			*top = newNode;
			newNode->NEXT = *top;
		}//while
	}//else
	
	fclose(details);

	i = 0;
	if (validate > 0) {
		printf("\nLog In Successful\n");
		return;
	}
	else if (validate <= 0) {
		printf("\nUsername or Password is Incorrect - Please try again\n");
		user(top);
	//	return;
	}

}//end function 

void printFromfile(struct node** top)
{
	//struct node* temp;
	//openfile
	FILE*rfile;

	//read from file
	rfile = fopen("stock.txt", "r");
	
	//if
	if (rfile == NULL)
	{
		printf("Sorry nothing was added to the list\n");
	}
	else if (rfile != NULL)
	{
		while (!feof(rfile))
		{
			struct node*newNode = (struct node*)malloc(sizeof(struct node));

			//read from file
			fscanf(rfile, " %d %s %s %d %d %d %f %d %d %d %d %d %d %d ",
				&newNode->stockNum, newNode->stockName, newNode->stockSupName
				, &newNode->stockSupNum, &newNode->reOrder, &newNode->numOfUnits
				, &newNode->costUnit, &newNode->date, &newNode->month, &newNode->year
				, &newNode->chemStore, &newNode->dept, &newNode->reOrderMonth
				, &newNode->authorise);

			newNode->NEXT = *top;
			*top = newNode;
		}//while

		printf("Successfully added file to the list\n");
		fclose(rfile);
	}//else
}//end fuction

void addNewStock(struct node** top)
{
	//variables
	int d, m, y;
	//declare dynamic array
	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	//adding data
	printf("Please enter Stock Item Number: \n");
	scanf("%d", &newNode->stockNum);
	printf("Please enter Stock Item Name: \n");
	scanf("%s", newNode->stockName);
	printf("Please enter Stock Item Suppiler Name: \n");
	scanf("%s", newNode->stockSupName);
	printf("Please enter Stock Item Suppiler Contact Number: \n");
	scanf("%d", &newNode->stockSupNum);
	printf("Please enter Re-order Threshold Limit: \n");
	scanf("%d", &newNode->reOrder);
	printf("Please enter Number of Units: \n");
	scanf("%d", &newNode->numOfUnits);
	printf("Please enter Cost per Units: \n");
	scanf("%f", &newNode->costUnit);

	//Date validation
	do
	{
		printf("Please enter Last Order Date(DD/MM/YYYY): \n");
		scanf("%d %d %d", &d, &m, &y);
	} while ((d < 1 || d > 31) || (m < 1 || m > 12) || (y > 2020 || y < 2000));

	//store d/m/y value into data
	newNode->date = d;
	newNode->month = m;
	newNode->year = y;

	// hazadous chemical store validation
	do
	{
		printf("Does this item need to be stored in a hazardous chemical store?\n");
		printf("type (1) for YES / (2) for NO\n");
		scanf("%d", &newNode->chemStore);
	} while (newNode->chemStore < 1 || newNode->chemStore>2);

	//department Validation
	do
	{
		printf("Which Department does his stock item belong to?\n");
		printf("For Office type '1' / For Maintenance type '2'\n");
		scanf("%d", &newNode->dept);
	} while (newNode->dept < 1 || newNode->dept > 2);

	//month validation
	do
	{
		printf("which of the following months do items need to re-order? \n");
		printf("No Specified Month type '1' / Feb type '2' / Aug type '3' \n");
		scanf("%d", &newNode->reOrderMonth);
	} while (newNode->reOrderMonth < 1 || newNode->reOrderMonth > 3);

	//Authorise the purchase Validation
	do
	{
		printf("Which of the following people need to authorise the purchase?\n");
		printf("Managing Director type '1'\n");
		printf("Financial Controller type '2'\n");
		printf("Department Manager type '3'\n");
		scanf("%d", &newNode->authorise);
	} while (newNode->authorise < 1 || newNode->authorise >  3);

	newNode->NEXT = *top;
	*top = newNode;

}//end function

void addStockItem(struct node* top)
{
	//variables
	int d, m, y;
	int id = 0;
	int option, choice;
	struct node* temp = top;
	struct node* temporary = top;
	//declare dynamic array
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	
	//check if unique
	printf("Please enter Stock Item Number: \n");
	scanf("%d", &id);

	while (temporary != NULL)
	{
		if (temporary->stockNum != id)
		{
			temporary = temporary->NEXT;
			//temp = temp->NEXT;			
		}//if
		else
		{
			//choices 
			do {
				printf("It is already entered - Do you want to update details or exit?\n");
				printf("Enter 1 to update the stock item's details:\n");
				printf("Enter 2 to exit to Menu\n");
				scanf("%d", &option);
			} while(option < 1 || option > 2);

			if (option == 1)
			{
				updateStock(temp);
				return;

			}//if
			else if (option == 2)
			{
				return;
			}
		}//else
	}//while

	//adding value
	newNode->stockNum = id;
	printf("Please enter Stock Item Name: \n");
	scanf("%s", newNode->stockName);
	printf("Please enter Stock Item Suppiler Name: \n");
	scanf("%s", newNode->stockSupName);
	printf("Please enter Stock Item Suppiler Contact Number: \n");
	scanf("%d", &newNode->stockSupNum);
	printf("Please enter Re-order Threshold Limit: \n");
	scanf("%d", &newNode->reOrder);
	printf("Please enter Number of Units: \n");
	scanf("%d", &newNode->numOfUnits);
	printf("Please enter Cost per Units: \n");
	scanf("%f", &newNode->costUnit);

	//Date validation
	do
	{
		printf("Please enter Last Order Date(DD/MM/YYYY): \n");
		scanf("%d %d %d", &d, &m, &y);
	} while ((d < 1 || d > 31) || (m < 1 || m > 12) || (y > 2020 || y < 2000));

	//store d/m/y value into data
	newNode->date = d;
	newNode->month = m;
	newNode->year = y;

	// hazadous chemical store validation
	do
	{
		printf("Does this item need to be stored in a hazardous chemical store?\n");
		printf("type (1) for YES / (2) for NO\n");
		scanf("%d", &newNode->chemStore);
	} while (newNode->chemStore < 1 || newNode->chemStore > 2);

	//department Validation
	do
	{
		printf("Which Department does his stock item belong to?\n");
		printf("For Office type '1' / For Maintenance type '2'\n");
		scanf("%d", &newNode->dept);
	} while (newNode->dept < 1 || newNode->dept > 2);

	//month validation
	do
	{
		printf("which of the following months do items need to re-order? \n");
		printf("No Specified Month type '1' / Feb type '2' / Aug type '3' \n");
		scanf("%d", &newNode->reOrderMonth);
	} while (newNode->reOrderMonth < 1 || newNode->reOrderMonth > 3);

	//Authorise the purchase Validation
	do
	{
		printf("Which of the following people need to authorise the purchase?\n");
		printf("Managing Director type '1'\n");
		printf("Financial Controller type '2'\n");
		printf("Department Manager type '3'\n");
		scanf("%d", &newNode->authorise);
	} while (newNode->authorise < 1 || newNode->authorise > 3);

	while (temp->NEXT != NULL)
	{
		temp = temp->NEXT;
	}//while

	newNode->NEXT = NULL;
	temp->NEXT = newNode;

}//end Add Stock Item

void displayAll(struct node* top)
{
	int i = 0;
	struct node* temp = top;
	//temp = top;

	while (temp != NULL)
	{
		i++;
		//output all details
		printf("%d. Item No. is: %d\n", i, temp->stockNum);
		printf("Item Name is: %s\n", temp->stockName);
		printf("Item Supplier Name is: %s\n", temp->stockSupName);
		printf("Item Suppiler Contact Number is: %d\n", temp->stockSupNum);
		printf("Re-order Threshold Limit is: %d\n", temp->reOrder);
		printf("Number of Units is: %d\n", temp->numOfUnits);
		printf("Cost per Units is: %.2f\n", temp->costUnit);
		printf("Last Order Date is: %d /%d /%d\n", temp->date, temp->month, temp->year);

		//if/else for outputing Question/Answers
		//hazardous chemical store
		if (temp->chemStore == 1)
		{
			printf("Does this item need to be stored in a hazardous chemical store? YES\n");
		}
		else if (temp->chemStore == 2)
		{
			printf("Does this item need to be stored in a hazardous chemical store? NO\n");
		}

		//Department
		if (temp->dept == 1)
		{
			printf("Which Department does this stock item belong to? OFFICE\n");
		}
		else if (temp->dept == 2)
		{
			printf("Which Department does this stock item belong to? MAINTENANCE\n");
		}

		//Re order
		if (temp->reOrderMonth == 1)
		{
			printf("Which of the following months do items need to re-order? NO SPECIFIED MONTH\n");
		}
		else if (temp->reOrderMonth == 2)
		{
			printf("Which of the following months do items need to re-order? FEBRUARY\n");
		}
		else if (temp->reOrderMonth == 3)
		{
			printf("Which of the following months do items need to re-order? AUGUST\n");
		}

		//authorise
		if (temp->authorise == 1)
		{
			printf("Which of the following people need to authorise the purshase? MANAGING DIRECTOR\n");
		}
		else if (temp->authorise == 2)
		{
			printf("Which of the following people need to authorise the purshase? FINANCIAL CONTROLLER\n");
		}
		else if (temp->authorise == 3)
		{
			printf("Which of the following people need to authorise the purshase? DEPARTMENT MANAGER\n");
		}
	//	printf("Total Monetary Value for this item is: %.2f\n", temp->mValue);
		printf("==================================================================================================\n");

		temp = temp->NEXT;

	}//while
}//end function

void displaySome(struct node* top)
{
	//variables
	struct node* temp = top;
	int answer;
	int number;
	char name[30];

	//validation for choices
	do
	{
		printf("\nPlease enter 1 for Stock Item Number\n"); 
		printf("       Enter 2 for Stock Item Name to SEARCH\n");
		scanf("%d",&answer);

	} while(answer < 1 || answer > 2);

	//condition for answer 1
	if (answer == 1)
	{

		//Stock number validation
		do
		{
			printf("Please enter the Stock Item number that you want to search\n");
			scanf("%d", &number);
		} while (number < 0);

		while (temp->stockNum != number)
		{
			temp = temp->NEXT;
			if (temp == NULL)
			{
				printf("Invalid stock Item");
				return;
			}
		}// end while	
		
		//if stock number equal to number that input
		if (number == temp->stockNum)
		{
			//output all details
			printf("Item No. is: %d\n", temp->stockNum);
			printf("Item Name is: %s\n", temp->stockName);
			printf("Item Supplier Name is: %s\n", temp->stockSupName);
			printf("Item Suppiler Contact Number is: %d\n", temp->stockSupNum);
			printf("Re-order Threshold Limit is: %d\n", temp->reOrder);
			printf("Number of Units is: %d\n", temp->numOfUnits);
			printf("Cost per Units is: %.2f\n", temp->costUnit);
			printf("Last Order Date is: %d /%d /%d\n", temp->date, temp->month, temp->year);

			//if/else for outputing Question/Answers
			//hazardous chemical store
			if (temp->chemStore == 1)
			{
				printf("Does this item need to be stored in a hazardous chemical store? YES\n");
			}
			else if (temp->chemStore == 2)
			{
				printf("Does this item need to be stored in a hazardous chemical store? NO\n");
			}

			//Department
			if (temp->dept == 1)
			{
				printf("Which Department does this stock item belong to? OFFICE\n");
			}
			else if (temp->dept == 2)
			{
				printf("Which Department does this stock item belong to? MAINTENANCE\n");
			}

			//Re order
			if (temp->reOrderMonth == 1)
			{
				printf("Which of the following months do items need to re-order? NO SPECIFIED MONTH\n");
			}
			else if (temp->reOrderMonth == 2)
			{
				printf("Which of the following months do items need to re-order? FEBRUARY\n");
			}
			else if (temp->reOrderMonth == 3)
			{
				printf("Which of the following months do items need to re-order? AUGUST\n");
			}

			//authorise
			if (temp->authorise == 1)
			{
				printf("Which of the following people need to authorise the purshase? MANAGING DIRECTOR\n");
			}
			else if (temp->authorise == 2)
			{
				printf("Which of the following people need to authorise the purshase? FINANCIAL CONTROLLER\n");
			}
			else if (temp->authorise == 3)
			{
				printf("Which of the following people need to authorise the purshase? DEPARTMENT MANAGER\n");
			}
			temp = temp->NEXT;
		}//if

	}//end if first answer
	else if (answer == 2)
	{
		//ask for stock item name
		printf("Please enter the Stock Item name that you want to search\n");
		scanf("%s", name);

		while (strcmp(name, temp->stockName) != 0)
		{
			temp = temp->NEXT;

			if (temp == NULL)
			{
				printf("Invalid stock name");
				return;
			}

		}//end while

		//if stock name equal to Name that input
		if (strcmp(name, temp->stockName) == 0)
		{
			//output all details
			printf("Item No. is: %d\n", temp->stockNum);
			printf("Item Name is: %s\n", temp->stockName);
			printf("Item Supplier Name is: %s\n", temp->stockSupName);
			printf("Item Suppiler Contact Number is: %d\n", temp->stockSupNum);
			printf("Re-order Threshold Limit is: %d\n", temp->reOrder);
			printf("Number of Units is: %d\n", temp->numOfUnits);
			printf("Cost per Units is: %.2f\n", temp->costUnit);
			printf("Last Order Date is: %d /%d /%d\n", temp->date, temp->month, temp->year);

			//if/else for outputing Question/Answers
			//hazardous chemical store
			if (temp->chemStore == 1)
			{
				printf("Does this item need to be stored in a hazardous chemical store? YES\n");
			}
			else if (temp->chemStore == 2)
			{
				printf("Does this item need to be stored in a hazardous chemical store? NO\n");
			}

			//Department
			if (temp->dept == 1)
			{
				printf("Which Department does this stock item belong to? OFFICE\n");
			}
			else if (temp->dept == 2)
			{
				printf("Which Department does this stock item belong to? MAINTENANCE\n");
			}

			//Re order
			if (temp->reOrderMonth == 1)
			{
				printf("Which of the following months do items need to re-order? NO SPECIFIED MONTH\n");
			}
			else if (temp->reOrderMonth == 2)
			{
				printf("Which of the following months do items need to re-order? FEBRUARY\n");
			}
			else if (temp->reOrderMonth == 3)
			{
				printf("Which of the following months do items need to re-order? AUGUST\n");
			}

			//authorise
			if (temp->authorise == 1)
			{
				printf("Which of the following people need to authorise the purshase? MANAGING DIRECTOR\n");
			}
			else if (temp->authorise == 2)
			{
				printf("Which of the following people need to authorise the purshase? FINANCIAL CONTROLLER\n");
			}
			else if (temp->authorise == 3)
			{
				printf("Which of the following people need to authorise the purshase? DEPARTMENT MANAGER\n");
			}
		}//if

	}//end else if for 2 answer
}//end function

void updateStock(struct node* top)
{
	//variables
	struct node* temp = top;
	int answer;
	int newPhone;
	char newName[30];
	int newReorder;
	int number;
	char name[30]; 
	temp = top;

	//validation for choices
	do
	{
		printf("\nPlease enter 1 for Stock Item Number\n");
		printf(" OR Enter 2 for Stock Item Name to Search\n");
		scanf("%d", &answer);

	} while (answer < 1 || answer > 2);

	//condition for answer 1
	if (answer == 1)
	{
		//Stock number validation
		do
		{
			printf("Please enter the Stock Item number that you want to Update\n");
			scanf("%d", &number);
		} while (number < 0);

		while (temp->stockNum != number)
		{
			temp = temp->NEXT;
			if (temp == NULL)
			{
				printf("Invalid stock Item");
				return;
			}
		}// end while	

		//if stock number equal to number that input
		if (temp->stockNum == number)
		{
			//ask for new information and add new data
			printf("Please enter new Stock Item Supplier Name:\n");
			scanf("%s", temp->stockSupName);
			printf("Please enter new Stock Item Supplier Contact Number:\n");
			scanf("%d", &temp->stockSupNum);
			printf("Please enter new RE-Order Threshold Limit:\n");
			scanf("%d", &temp->reOrder);

			//display new items details
			printf("New stock Item Suppiler Name: %s\n", temp->stockSupName);
			printf("New stock Item Suppiler Contact No.: %d\n", temp->stockSupNum);
			printf("New Re-order Threshole limit: %d\n", temp->reOrder);
		}

	}//end if first answer
	else if (answer == 2)
	{
		//ask for stock item name
		printf("Please enter the Stock Item name that you want to Update\n");
		scanf("%s", name);

		while (strcmp(name, temp->stockName) != 0)
		{
			temp = temp->NEXT;

			if (temp == NULL)
			{
				printf("Invalid stock name");
				return;
			}

		}//end while

		//if stock name equal to Name that input
		if (strcmp(name, temp->stockName) == 0)
		{
			//ask for new information and add new data
			printf("Please enter new Stock Item Supplier Name:\n");
			scanf("%s", temp->stockSupName);
			printf("Please enter new Stock Item Supplier Contact Number:\n");
			scanf("%d", &temp->stockSupNum);
			printf("Please enter new RE-Order Threshold Limit:\n");
			scanf("%d", &temp->reOrder);

			//display new items details
			printf("New stock Item Suppiler Name: %s\n", temp->stockSupName);
			printf("New stock Item Suppiler Contact No.: %d\n", temp->stockSupNum);
			printf("New Re-order Threshole limit: %d\n", temp->reOrder);
		}

	}//end else if for 2 answer
}//end function

void deleteFirst(struct node** top)
{
	struct node* temp;

	temp = *top;

	//Moving the head pointer to the second node
	*top = temp->NEXT;

	//clear memory of the frist node
	free(temp);
	printf("The item has been deleted\n");
}//end function

void deleteStock(struct node* top)
{
	//tempory var
	struct node* temp = top;
	struct node* prevTemp;

	//varriables
	int number;

	//ask for item number
	do {
		printf("Please enter the Stock Item number that you want to Delete\n");
		scanf("%d", &number);
	} while (number < 2);

	while (temp->stockNum != number)
	{
		prevTemp = temp;
		temp = temp->NEXT;

		if(temp == NULL)
		{
			printf("Your number is wrong! please try agian\n");
			return;
		}

	}//end while

	if (temp->stockNum == number)
	{
		prevTemp->NEXT = temp->NEXT;
		free(temp);
		printf("The item has been deleted\n");
	}//if

}//end function

void generateStat(struct node* top)
{
	//variables
	struct node* temp = top;
	int countbelow = 0;
	int countBeTwice = 0;
	int countAbove = 0;
	int countbelow1 = 0;
	int countBeTwice1 = 0;
	int countAbove1 = 0;
	int totOff = 0;
	int totMain = 0;

	//condition for department
	if (temp->dept == 1)
	{
		if (temp->numOfUnits < temp->reOrder)
			countbelow++;
		else if (temp->numOfUnits > temp->reOrder && temp->numOfUnits < (temp->reOrder * 2))
			countBeTwice++;
		else if (temp->numOfUnits > temp->reOrder)
			countAbove++;

		//calculation
		totOff = countAbove + countBeTwice + countbelow;
		belowf = 100 * (countbelow / totOff);
		belowTwiceF = 100 * (countBeTwice / totOff);
		aboveF = 100 * (countAbove / totOff);

	}//if
	else if(temp->dept == 2)
	{
		if (temp->numOfUnits < temp->reOrder)
			countbelow1++;
		else if (temp->numOfUnits > temp->reOrder && temp->numOfUnits < (temp->reOrder * 2))
			countBeTwice1++;
		else if (temp->numOfUnits > temp->reOrder)
			countAbove1++;

		//calculation
		totMain = countbelow1 + countBeTwice1 + countAbove1;
		belowM = 100 * (countbelow1 / totMain);
		belowTwiceM = 100 * (countBeTwice1 / totMain);
		aboveM = 100 * (countAbove1 / totMain);
	}//else if

	//output
	printf("\n=============================OFFICE DEPARTMENT===========================\n");
	printf("%.2f percent of Stock items below the re-order threshold limit\n", belowf);
	printf("%.2f percent of Stock items below twice the re-order threshold limit\n", belowTwiceF);
	printf("%.2f percent of Stock items above twice the re-order threshold limit\n", aboveF);
	printf("\n===========================MAINTENANCE DEPARTMENT========================\n");
	printf("%.2f percent of Stock items below the re-order threshold limit\n", belowM);
	printf("%.2f percent of Stock items below twice the re-order threshold limit\n", belowTwiceM);
	printf("%.2f percent of Stock items above twice the re-order threshold limit\n\n", aboveM);

}//end function

void printTofile(struct node* top)
{
	struct node* temp = top;
		//open the file
	FILE*file;

	file = fopen("Report.txt", "w");

	while (temp != NULL)
	{
		fprintf(file, "Item No. is: %d\n", temp->stockNum);
		fprintf(file, "Item Name is: %s\n", temp->stockName);
		fprintf(file, "Item Supplier Name is: %s\n", temp->stockSupName);
		fprintf(file, "Re-order Threshold Limit is: %d\n", temp->reOrder);
		fprintf(file, "Number of Units is: %d\n", temp->numOfUnits);
		fprintf(file, "Cost per Units is: %.2f\n", temp->costUnit);
		fprintf(file, "Last Order Date is: %d /%d /%d\n", temp->date, temp->month, temp->year);

		//if/else for outputing Question/Answers
			//hazardous chemical store
		if (temp->chemStore == 1)
		{
			fprintf(file, "Does this item need to be stored in a hazardous chemical store? YES\n");
		}
		else if (temp->chemStore == 2)
		{
			fprintf(file, "Does this item need to be stored in a hazardous chemical store? NO\n");
		}

		//Department
		if (temp->dept == 1)
		{
			fprintf(file, "Which Department does this stock item belong to? OFFICE\n");
		}
		else if (temp->dept == 2)
		{
			fprintf(file, "Which Department does this stock item belong to? MAINTENANCE\n");
		}

		//Re order
		if (temp->reOrderMonth == 1)
		{
			fprintf(file, "Which of the following months do items need to re-order? NO SPECIFIED MONTH\n");
		}
		else if (temp->reOrderMonth == 2)
		{
			fprintf(file, "Which of the following months do items need to re-order? FEBRUARY\n");
		}
		else if (temp->reOrderMonth == 3)
		{
			fprintf(file, "Which of the following months do items need to re-order? AUGUST\n");
		}

		//authorise
		if (temp->authorise == 1)
		{
			fprintf(file, "Which of the following people need to authorise the purshase? MANAGING DIRECTOR\n");
		}
		else if (temp->authorise == 2)
		{
			fprintf(file, "Which of the following people need to authorise the purshase? FINANCIAL CONTROLLER\n");
		}
		else if (temp->authorise == 3)
		{
			fprintf(file, "Which of the following people need to authorise the purshase? DEPARTMENT MANAGER\n");
		}
		fprintf(file, "===========================================================================================\n");

		temp = temp->NEXT;
	}//while

	//output
	fprintf(file, "\n=============================OFFICE DEPARTMENT===========================\n");
	fprintf(file, "%.2f percent of Stock items below the re-order threshold limit\n", belowf);
	fprintf(file, "%.2f percent of Stock items below twice the re-order threshold limit\n", belowTwiceF);
	fprintf(file, "%.2f percent of Stock items above twice the re-order threshold limit\n", aboveF);
	fprintf(file, "\n===========================MAINTENANCE DEPARTMENT========================\n");
	fprintf(file, "%.2f percent of Stock items below the re-order threshold limit\n", belowM);
	fprintf(file, "%.2f percent of Stock items below twice the re-order threshold limit\n", belowTwiceM);
	fprintf(file, "%.2f percent of Stock items above twice the re-order threshold limit\n\n", aboveM);

	//close file
	fclose(file);
	printf("Successfully print to the file.\n");
}//end function

void monetary(struct node* top)
{
	struct node* temp = top;
	float value;
	int i = 0;

	while (temp != NULL)
	{
		i++;

		//calc
		value = temp->numOfUnits * temp->costUnit;

		//output
		printf("%d. Item No. is: %d\n", i, temp->stockNum);
		printf("Item Name is: %s\n", temp->stockName);
		printf("Number of Units is: %d\n", temp->numOfUnits);
		printf("Cost per Units is: %.2f\n", temp->costUnit);
		printf("Total Monetary Value for this item is: %.2f\n", value);
		printf("================================================\n");

		temp = temp->NEXT;
	}//while
}//end function

void printToFileEnd(struct node* top)
{
	FILE*file;
	struct node* temp = top;

	file = fopen("stock.txt", "w");

	if (file == NULL)
	{
		printf("Can not open the file");
	}//if
	else
	{
		while (temp != NULL)
		{
			fprintf(file, "%d %s %s %d %d %d %f %d %d %d %d %d %d %d\n",
				temp->stockNum, temp->stockName, temp->stockSupName
				, temp->stockSupNum, temp->reOrder, temp->numOfUnits
				, temp->costUnit, temp->date, temp->month, temp->year
				, temp->chemStore, temp->dept, temp->reOrderMonth
				, temp->authorise);

			temp = temp->NEXT;
		}//while

		fclose(file);
		printf("SAVE!\n");
		return;
	}//else
}//end function