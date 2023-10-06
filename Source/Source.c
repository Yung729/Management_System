#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#pragma warning(disable:4996)

#define STAFFFILE "staff.bin"
#define LEAVEFILE "leave.bin"
#define DAYDIFFERENT staffLeave.startDay.month * 31 + staffLeave.startDay.day < staffLeave.endDay.month * 31 + staffLeave.endDay.day
#define CALCULATEDAYONE staffLeave.endDay.month * 31 + staffLeave.endDay.day - (staffLeave.startDay.month * 31 + staffLeave.startDay.day) // for calculate first month is big second month is small
#define CALCULATEDAYTWO staffLeave.endDay.month * 30 + staffLeave.endDay.day - (staffLeave.startDay.month * 30 + staffLeave.startDay.day) // for calculate first month is small second month is big
#define MAXSTORAGE 200

// define value for stock module
#define STOCKFILENAME "stockFile.txt"
#define TEMPFILENAME "temp.txt"
#define nameLength 30
#define MAXARGLENGTH 256
#define STOCKSTRUCTELEMENTSNUM 7
#define FOPENTYPE "r+"
#define MAXLINE 200
#define MAXLINELENGTH 64

#pragma region Structure

//Structure - Staff Module (Leong Kah Yung)
typedef struct {
	int day, month, year;
}Date;

typedef struct {
	char staffId[20], name[100], password[50], gender, email[50], address[100], role[10], icNo[30], status[40], contact[120];
	double basicSalary, subSalary;
	Date hireDate;
}Staff;

typedef struct {
	char leaveReason[100], staffId[20], leaveType[20];
	int leaveDay, salaryDeduct;
	Date startDay, endDay;
}Leave;

//Structure - Member Module (Lai Yong Le)
typedef struct
{
	char memberId[20], uplineId[20], name[51], gender, email[51], address[100], icNo[30], contactNo[51], memberType;
	Date joinDate;
}Member;

//struct declaration Fadhil Abbas
typedef struct {
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
}typeDateTime;


typedef struct {
	char orderId[6];
	char itemId[6];
	char memberId[6];
	char staffId[6];

	double price;
	int qty;
	double discount;
	double com;
	double total;

	typeDateTime dateTime;
}typeSales;

//Structure - Stock Module (Tann Jee Schuan)
struct pricing {
	double cost, salePrice;
};

struct stock {
	char itemID[nameLength], supplier[nameLength], name[nameLength];
	long long barcode;
	int quantity;
	struct pricing prices;
};

struct stockArth {
	char itemID[nameLength], supplier[nameLength], name[nameLength];
	long long barcode;
	char quantity[nameLength];
	struct pricing prices;
};


#pragma endregion


#pragma region DeclarationFunction
// design code 

void delay(double number_of_seconds) {
	double milli_seconds = 1000 * number_of_seconds;

	clock_t start_time = clock();

	while (clock() < start_time + milli_seconds);
}

void purple() {
	printf("\033[1;35m");
}
void yellow() {
	printf("\033[0;33m");
}
void green() {
	printf("\033[0;32m");
}
void red() {
	printf("\033[0;31m");
};
void blue() {
	printf("\033[0;34m");
}
void defaultcolor() {
	printf("\033[0m");
};


// main - Leong Kah Yung
void logo();
void screen();
void homeMenu();
void errorMessage(char message[]);
int getInteger(int range);
void getYesNo(char info[], char* input);
void login();
void header(char info[]);
void mainMenu(char loginstatus, char staffId[]);

//staff module - Leong Kah Yung
void staffMenu(char loginstatus, char staffId[]);
void showCurentStaff(char staffId[]);
void staffDisplay(char staffId[]);
void staffDisplayAll();
void staffSearch();
void searchBy(int* choice, void (*function)(char*), int mode);
void staffAdd();
void staffModify(char currentId[]);
void modifyChoice(int choice, Staff* selectedStaff, Staff staffInfo[], int loginIndex, int* autoConfirm, int* block);
void staffDelete(char staffId[]);
void staffReport();
void salaryReport();
void statusReport();
void leaveReport();
void passWordReport();
void eachStatusReport(char staffType[], char status[]);
void leaveApplication(char staffId[]);
void storeToFile(int count, Staff staffInfo[]);
void calculateSubSalary(int inputMonth, int inputYear);
void printOneStaff(Staff staffInfo);
void addStaffData(char* option, int* addCount);
void staffModifyInfo(Staff staffInfo, int mode);
void readSelectStaff(char staffId[], Staff staffInfo[], int* count, int* foundCount, int* found, Staff* selectedStaff);
void readStaff(Staff staffInfo[], int* count, FILE* inputFile);
void readLeave(Leave LeaveInfo[], int* count, FILE* inputFile);
void forgetPass(char staffId[]);

//vallidation - Leong Kah Yung
void getDate(char info[], Date* applyDate, int* dateType);
void getName(char input[]);
void getGender(char* inputGender);
void getIC(char inputIc[]);
void getEmail(char inputEmail[]);
void getRole(char inputRole[]);
void getStatus(char inputStatus[], int mode);
void getSalary(double* inputSalary);
void getPass(char inputPass[]);
void getAddress(char inputAddress[]);
void generateId(char staffId[]);
void getContact(char inputContact[]);
void hidePassword(char inputPassword[]);
void systemDate(Date* currentDate);
void getStaffId(char inputId[]);

//member module - Lai Yong Le
void memberMainPage();
void memberAdd();
void memberSearch();
void memberDelete();
void memberModify();
void memberDisplayAll();
void memberTypeAdv();
void memberMonthlyChange();
void memberComm();

char typeValidation(char oldMemberType, char memberType, char id[]);
char newValidation(char memberType);
int getIntegerFromOne(int range);
void getType(char memberType, char* newMemberType, char id[], int m);
void getMemberId(char memberId[]);
void generateMemberId(char inputId[]);
void getMemberAddress(char inputAddress[]);
void getUplineId(char uplineId[]);

//stock module - Tan Jee Schuan
void stock_management();

void add_product(FILE*);
void search_for_stock(FILE*);
void modify_stock(FILE*);
void display_all_stocks(FILE*);
void generate_low_stock_report(FILE*);
void delete_stock(FILE*);
void validate_sort_stock(FILE*);

void input_new_stock(struct stock*);
int browse_stocks(FILE*);
void modify_stocks_struct(struct stockArth*, char[MAXARGLENGTH]);
void modify_stocks(char[], FILE* filePointer, struct stockArth*);
void stock_argument_generator(char* []);
int search_argument_generator(char* []);
void search_stock(FILE* filePointer, char*);
void random_product_generator(FILE*);
void print_stock_struct(struct stock);
void print_stock_header();
void get_string(char*);
void validate_stock_input(char*, char*, char*);
void delete_record(FILE*);
void zeroise_stock_struct(struct stock*);
void sort_records(FILE*);
int validate_unique_fields(FILE* inputFile);

int alphanumeric_check(char* inputString, int arr_size);
int numeric_check(char* inputString, int arr_size, char mode);
int read_to_stock_struct(struct stock*, FILE*);
int write_struct_to_file(struct stock*, FILE*);

//function declaration FADHIL ABBAS BIN MOHAMAD ZAIN
int mainSales();
void viewSales(typeSales* ptrArrSales);
void searchSales(typeSales* ptrArrSales);
void addSales(typeSales* ptrArrSales);
void modifySales(typeSales* ptrArrSales);
void deleteSales(typeSales* ptrArrSales);
void reportSales(typeSales* ptrArrSales);
int getIndex(int input);
void printHeader();
void printFooter(int a);
int getNum(char str[6]);
void calculateValues(typeSales* buffer);
void color(char color);
int printByOrderId(typeSales* ptrArrSales, char orderId[6]);
void printByArrNum(typeSales* ptrArrSales, int a);
int deleteByOrderId(typeSales* ptrArrSales, char orderId[6]);
void deleteByArrNum(typeSales* ptrArrSales, int a);
double getItemPrice(char itemId[6]);
int getMemberDiscount(char memberId[6]);
char checkStaffId(char staffId[6]);
#pragma endregion


#pragma region MainFunction-Leong Kah Yung

void main() {

	screen();
	homeMenu();
	system("pause");
}

void screen() {
	red();
	printf("\t\t\t\t\t%s\n", "                      _");
	delay(0.2);

	yellow();
	printf("\t\t\t\t\t%s\n", "      _   _ _ __ ___ | |_");
	delay(0.2);

	blue();
	printf("\t\t\t\t\t%s\n", "     | | | | '_ ` _ \\| __|");
	delay(0.2);

	green();
	printf("\t\t\t\t\t%s\n", "     | |_| | | | | | | |_");
	delay(0.2);

	purple();
	printf("\t\t\t\t\t%s\n", "      \\__,_|_| |_| |_|\\__|");

	defaultcolor();
	system("cls");

}

void logo() {

	printf("\t\t\t\t\t%s\n", "                      _");
	yellow();
	printf("\t\t\t\t\t%s\n", "      _   _ _ __ ___ | |_");
	blue();
	printf("\t\t\t\t\t%s\n", "     | | | | '_ ` _ \\| __|");
	green();
	printf("\t\t\t\t\t%s\n", "     | |_| | | | | | | |_");
	purple();
	printf("\t\t\t\t\t%s\n\n", "      \\__,_|_| |_| |_|\\__|");
	defaultcolor();
	printf("========================================================================================================================\n");

}

void header(char info[]) {
	printf("%-45s %s\n", "", info);
	printf("%s\n\n", "========================================================================================================================");
}

void homeMenu() {
	int choice;

	do
	{
		rewind(stdin);
		system("cls");
		logo();
		header("UMT Managment System");
		printf("\t\t\t1. Login  \n\n");
		printf("\t\t\t0. Exit  \n\n");

		choice = getInteger(1);

		switch (choice)
		{
		case 1:
			login();
			break;
		case 0:
			break;
		}

	} while (choice != 0);

}

void login() {

	Staff staffLogin;
	char password[15], staffId[100], loginStatus = 'X', option;

	FILE* loginFile;
	loginFile = fopen(STAFFFILE, "rb");
	if (loginFile == NULL)
	{
		errorMessage("Invalid File , Please Try Again");
		return;
	}
	system("cls");
	logo();
	header("Login System");
	printf("\t\t\tLogin TO account:\n\n");

	getStaffId(staffId);

	printf("\n");
	printf("\t\t\tEnter Password > ");
	hidePassword(password);

	while (fread(&staffLogin, sizeof(Staff), 1, loginFile) != 0) {

		if (strcmp(staffLogin.staffId, staffId) == 0) {
			loginStatus = 'N';
			if (strcmp(staffLogin.password, password) == 0) {

				if (strcmp(staffLogin.status, "Resign") == 0)
					loginStatus = 'R';  //R for resign
				else if (strcmp(staffLogin.role, "ADMIN") == 0)
					loginStatus = 'A';  //A for admin
				else
					loginStatus = 'S'; // S for staff

				break;
			}
		}

	}

	fclose(loginFile);

	switch (loginStatus) //pass in status to validate and login to system
	{
	case 'X':
		errorMessage("Invalid Staff Id");
		system("pause");
		break;
	case 'N':
		errorMessage("Invalid Password.");
		getYesNo("\n\t\t\tRecovery Password (Y/N) > ", &option);

		if (toupper(option) == 'Y')
			forgetPass(staffId);

		system("pause");
		break;
	case 'R':
		errorMessage("This Staff Had Resigned. You May Ask Admin To Active Your Account.");
		loginStatus = 'X';
		system("pause");
		break;
	case 'A':
	case 'S':
		mainMenu(loginStatus, staffId);
		loginStatus = 'X'; //change when logout avoid duplicate login
		break;
	}



}

void mainMenu(char loginstatus, char staffId[]) {
	int choice;

	do
	{
		rewind(stdin);
		system("cls");
		showCurentStaff(staffId);
		logo();
		header("Main Menu");
		printf("\t\t\t1. Staff Menu \n\n");
		printf("\t\t\t2. Member Menu \n\n");
		printf("\t\t\t3. Sales Menu \n\n");
		printf("\t\t\t4. Stock Menu \n\n");
		printf("\t\t\t0. Logout \n\n");

		choice = getInteger(4);

		switch (choice)
		{
		case 1:
			staffMenu(loginstatus, staffId);
			break;
		case 2:
			memberMainPage();
			break;
		case 3:
			mainSales();
			break;
		case 4:
			stock_management();
			break;
		case 0:
			break;
		}


	} while (choice != 0);
}

#pragma endregion


#pragma region mainValidationFunction-Leong Kah Yung

void errorMessage(char message[]) {

	rewind(stdin);
	red();
	printf("\n\t\t\t%s\n", message);
	defaultcolor();
	delay(0.9);
}

int getInteger(int range) {

	int choice, input;
	char checkspace;

	do {
		rewind(stdin);
		printf("\t\t\tEnter your choice > ");
		input = scanf("%d%c", &choice, &checkspace);			 //scanf should return value 2 for integer type;
		if (choice < 0 || choice> range || input != 2 || checkspace != '\n') {
			errorMessage("Invalid Input , Please Try Again");
		}
	} while (choice < 0 || choice> range || input != 2 || checkspace != '\n');

	return choice;
}

void getYesNo(char info[], char* input) {
	int error;
	char checkspace;
	do
	{
		error = 0;
		rewind(stdin);

		printf("%s", info);
		scanf("%c%c", &*input, &checkspace);

		if (toupper(*input) != 'Y' && toupper(*input) != 'N')
		{
			error = 1;
			errorMessage("Invalid Input , Please Try Again");
		}
		else if (checkspace != '\n') {
			error = 1;
			errorMessage("Invalid input, just one character");
		}

	} while (error != 0);
}



#pragma endregion


#pragma region StaffModule-Leong Kah Yung

void showCurentStaff(char staffId[]) {
	Staff staffInfo;
	FILE* showStaff;
	showStaff = fopen(STAFFFILE, "rb");
	if (showStaff == NULL)
	{
		errorMessage("Invalid File , Please Try Again");
		return;
	}
	while (fread(&staffInfo, sizeof(Staff), 1, showStaff) != 0) {

		if (strcmp(staffInfo.staffId, staffId) == 0) {

			printf("%s: %s %s\n", staffInfo.role, staffInfo.staffId, staffInfo.name);
			break;

		}
	}

	fclose(showStaff);
}

void staffMenu(char loginstatus, char staffId[]) {
	int choice;
	do
	{
		system("cls");
		showCurentStaff(staffId);
		logo();
		if (toupper(loginstatus) == 'A')
		{
			header("Admin Management Menu");
			printf("\t\t\t1. Staff Profile\n\n");
			printf("\t\t\t2. All Staff Profile\n\n");
			printf("\t\t\t3. Search Staff Profile\n\n");
			printf("\t\t\t4. Add New Staff\n\n");
			printf("\t\t\t5. Modify Staff\n\n");
			printf("\t\t\t6. Delete Staff Profile\n\n");
			printf("\t\t\t7. Apply Leave\n\n");
			printf("\t\t\t8. Staff Report\n\n");
			printf("\t\t\t0. Back to Mainpage\n\n");

			choice = getInteger(8);

			switch (choice)
			{
			case 1:
				staffDisplay(staffId);
				break;
			case 2:
				staffDisplayAll();
				break;
			case 3:
				staffSearch();
				break;
			case 4:
				staffAdd();
				break;
			case 5:
				staffModify(staffId);
				break;
			case 6:
				staffDelete(staffId);
				break;
			case 7:
				leaveApplication(staffId);
				break;
			case 8:
				staffReport();
				break;
			}
		}
		else
		{
			header("Staff Management Menu");
			printf("\t\t\t1. Staff Profile\n\n");
			printf("\t\t\t2. Apply Leave\n\n");
			printf("\t\t\t0. Back to Mainpage\n\n");

			choice = getInteger(2);

			switch (choice)
			{
			case 1:
				staffDisplay(staffId);
				break;
			case 2:
				leaveApplication(staffId);
				break;

			}
		}


	} while (choice != 0);
}

void staffDisplay(char staffId[]) {

	int choice = 0, autoConfirm, block, loginIndex = 0, count = 0, found = 0, buffer;
	char option;

	Staff staffInfo[MAXSTORAGE];
	Staff selectedStaff;
	FILE* displayStaff;

	do
	{
		count = 0, loginIndex = 0;

		readSelectStaff(staffId, staffInfo, &count, &loginIndex, &buffer, &selectedStaff); //to get staff from staff to array and get selected staff

		printOneStaff(selectedStaff);

		getYesNo("\t\t\tWant to Edit? (Y/N) > ", &option);

		if (toupper(option) == 'Y') {

			do {

				autoConfirm = 0, block = 0, count = 0, loginIndex = 0;  //set count back to 0

				readSelectStaff(staffId, staffInfo, &count, &loginIndex, &buffer, &selectedStaff); // to reset selected staff information

				staffModifyInfo(selectedStaff, 0); //show staff information that able to modify

				choice = getInteger(6);

				modifyChoice(choice, &selectedStaff, staffInfo, loginIndex, &autoConfirm, &block); // the data able to choice to modify

				if (!block) {

					if (autoConfirm == 1) //auto set option to Y or N
						option = 'Y';
					else if (autoConfirm == 2)
						option = 'N';
					else
					{
						printf("\n\n========================================================================================================================\n\n");
						getYesNo("\n\t\t\tConfirm To Edit? (Y/N)            > ", &option);
					}

					// comfirm edit or No edit
					if (toupper(option) == 'Y')
					{

						if (strcmp(selectedStaff.status, "Resign") == 0) //if resign, auto set salary to 0
							selectedStaff.basicSalary = 0.0;

						staffInfo[loginIndex] = selectedStaff; //store back to array
						storeToFile(count, staffInfo); // rewrite and store back to file

						green();
						printf("\n%75s\n", "Staff Data Successfully Edited.");
						defaultcolor();
						printf("\n========================================================================================================================\n\n");
						system("pause");

					}
					else {
						red();
						printf("\n%72s\n", "No Change In Staff Data.");
						defaultcolor();
						printf("\n========================================================================================================================\n\n");
						system("pause");
						option = 'Y'; // change back avoid 0 auto back to staff menu
					}

				}

			} while (choice != 0);
		}

	} while (toupper(option) != 'N');

}

void modifyChoice(int choice, Staff* selectedStaff, Staff staffInfo[], int loginIndex, int* autoConfirm, int* block) {

	char option;
	switch (choice)
	{
	case 1:
		printf("\n\n========================================================================================================================\n\n");
		getName(selectedStaff->name);
		break;
	case 2:
		printf("\n\n========================================================================================================================\n\n");
		getIC(selectedStaff->icNo);
		break;
	case 3:
		printf("\n\n========================================================================================================================\n\n");
		if (selectedStaff->gender == 'M') {

			getYesNo("\n\t\t\tChange To Female? (Y/N)   > ", &option);
			if (toupper(option) == 'Y')
			{
				selectedStaff->gender = 'F';
				*autoConfirm = 1;
			}
			else
				*autoConfirm = 2;
		}
		else {

			getYesNo("\n\t\t\tChange To Male? (Y/N)     > ", &option);
			if (toupper(option) == 'Y')
			{
				selectedStaff->gender = 'M';
				*autoConfirm = 1;
			}
			else
				*autoConfirm = 2;
		}

		break;
	case 4:
		printf("\n\n========================================================================================================================\n\n");
		getContact(selectedStaff->contact);
		break;
	case 5:
		printf("\n\n========================================================================================================================\n\n");
		getEmail(selectedStaff->email);
		break;
	case 6:
		printf("\n\n========================================================================================================================\n\n");
		getAddress(selectedStaff->address);
		break;
	case 7:
		printf("\n\n========================================================================================================================\n\n");
		if (strcmp(selectedStaff->status, "Resign") == 0)
		{
			printf("\n%89s\n\n", "Status Is Resigned, Not Allow To Edit Salary And Position.");
			*block = 1; //block modify if resign
			system("pause");
		}
		else {
			if (strcmp(selectedStaff->role, "ADMIN") == 0)
			{

				getYesNo("\n\t\t\tDemote To Staff? (Y/N)            > ", &option);
				if (toupper(option) == 'Y')
				{
					*autoConfirm = 1;
					strcpy(selectedStaff->role, "STAFF");
					selectedStaff->staffId[0] = 'S';
				}
				else
					*autoConfirm = 2;
			}
			else {

				getYesNo("\n\t\t\tPromote To Admin? (Y/N)     > ", &option);
				if (toupper(option) == 'Y')
				{
					strcpy(selectedStaff->role, "ADMIN");
					selectedStaff->staffId[0] = 'A';
					*autoConfirm = 1;
				}
				else
					*autoConfirm = 2;
			}
		}
		break;
	case 8:
		printf("\n\n========================================================================================================================\n\n");
		if (strcmp(selectedStaff->status, "Resign") == 0)
			getStatus(selectedStaff->status, 1);
		else
			getStatus(selectedStaff->status, 2);
		break;
	case 9:
		printf("\n\n========================================================================================================================\n\n");
		if (strcmp(selectedStaff->status, "Resign") == 0) {
			red();
			printf("\n%89s\n\n", "Status Is Resigned, Not Allow To Edit Salary And Position.");
			defaultcolor();
			system("pause");
			*block = 1; //block to edit
		}
		else
			getSalary(&selectedStaff->basicSalary);
		break;


	case 10:
		printf("\n\n========================================================================================================================\n\n");
		printf("\n\t\t\tEnter Your Password         > ");
		hidePassword(selectedStaff->password);
		printf("\n");
		if (strcmp(staffInfo[loginIndex].password, selectedStaff->password) == 0)
		{
			getPass(selectedStaff->password);
		}
		else
		{
			red();
			printf("\n%79s\n\n", "Incorrect Password! Please Try Again Later.");
			defaultcolor();
			system("pause");
			*block = 1; //block to edit
		}
		break;
	case 0:
		*block = 1;
		break;

	}
}

void staffDisplayAll() {
	system("cls");

	Staff staffInfo;
	FILE* displayStaff;
	displayStaff = fopen(STAFFFILE, "rb");
	if (displayStaff == NULL)
	{
		errorMessage("Invalid File , Please Try Again");
		return;
	}
	else
	{
		logo();
		header("All Staff Record");
		printf(" =====================================================================================================================\n");
		printf("   ID         Name       Gender   Contact Number   Email                 Position   Salary(RM)   Date Join    Status     \n");
		printf(" =====================================================================================================================\n");
		while (fread(&staffInfo, sizeof(Staff), 1, displayStaff) != 0)
		{
			printf("   %-8s   %-10s   %-5c  %-14s   %-20s   %-6s   %10.2f   %02d/%02d/%02d   %s \n", staffInfo.staffId, staffInfo.name, staffInfo.gender, staffInfo.contact, staffInfo.email, staffInfo.role, staffInfo.basicSalary, staffInfo.hireDate.day, staffInfo.hireDate.month, staffInfo.hireDate.year, staffInfo.status);
		}

		printf(" =====================================================================================================================\n");
		printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t< %d Staff Listed >\n\n", ftell(displayStaff) / sizeof(Staff));

		fclose(displayStaff);

		system("pause");
		system("cls");
	}
}

void staffSearch() {

	int choice, count;

	do {
		choice = 0;
		count = 0;
		system("cls");
		logo();
		header("Main Menu");

		printf("\t\t\t\t1. Search by Id\n\n");
		printf("\t\t\t\t2. Search by Name\n\n");
		printf("\t\t\t\t3. Search by IC Number\n\n");
		printf("\t\t\t\t0. Exit to Staff Menu\n\n");
		choice = getInteger(3);

		if (choice == 1)
			searchBy(&choice, getStaffId, 1);
		else if (choice == 2)
			searchBy(&choice, getName, 2);
		else if (choice == 3)
			searchBy(&choice, getIC, 3);


	} while (choice != 0);

}

void searchBy(int* choice, void (*function)(char*), int mode) {

	char userInput[50];
	int found = 0;

	Staff staffInfo;
	FILE* searchStaff;
	searchStaff = fopen(STAFFFILE, "rb");

	if (searchStaff == NULL)
	{
		errorMessage("Invalid File , Please Try Again");
		return;
	}

	system("cls");
	logo();
	header("Search Staff");
	rewind(stdin);
	function(userInput);

	while (fread(&staffInfo, sizeof(Staff), 1, searchStaff) != 0)
	{
		switch (mode)
		{
		case 1:
			if (strcmp(staffInfo.staffId, userInput) == 0) {
				printOneStaff(staffInfo);
				found = 1;
			}
			break;
		case 2:
			if (strcmp(staffInfo.name, userInput) == 0) {
				printOneStaff(staffInfo);
				found = 1;
			}
			break;
		case 3:
			if (strcmp(staffInfo.icNo, userInput) == 0) {
				printOneStaff(staffInfo);
				found = 1;
			}
			break;
		}


	}

	if (found != 1)
	{
		red();
		printf("\n\n\t\t\t\tThis staff not exist in system\n\n");
		defaultcolor();
	}

	printf("\n========================================================================================================================\n");
	printf("\t\t\t\t1. Search Others Staff \t\t 0. Back to Staff Menu \n\n");

	*choice = getInteger(1);

	fclose(searchStaff);


}

void staffAdd() {

	char option;
	int addCount = 0;

	do {
		option = 'N';
		system("cls");
		logo();
		header("Register New Staff");

		red();
		printf("\t\t\tThe Information Needed !\n\n");
		defaultcolor();
		printf("\t\t\t--> Name\n");
		printf("\t\t\t--> Gender\n");
		printf("\t\t\t--> Identity Card No\n");
		printf("\t\t\t--> Contact Number\n");
		printf("\t\t\t--> Email Address\n");
		printf("\t\t\t--> Address\n");
		printf("\t\t\t--> Role (Normal Staff / Admin)\n");
		printf("\t\t\t--> Status\n");
		printf("\t\t\t--> Salary\n");
		printf("\t\t\t--> Create Password\n\n");

		getYesNo("\t\t\tAdd New Staff ? (Y/N) > ", &option);


		if (toupper(option) == 'Y')
			addStaffData(&option, &addCount);

	} while (toupper(option) == 'Y');

}

void addStaffData(char* option, int* addCount) {

	FILE* addStaff;
	addStaff = fopen(STAFFFILE, "ab");

	if (addStaff == NULL) {
		errorMessage("Invalid File , Please Try Again");
		return;
	}

	Staff newStaff = { .staffId = "" };

	getName(newStaff.name);
	getGender(&newStaff.gender);
	getIC(newStaff.icNo);
	getContact(newStaff.contact);
	getEmail(newStaff.email);
	getAddress(newStaff.address);
	getRole(newStaff.role);
	getStatus(newStaff.status, 1);
	getSalary(&newStaff.basicSalary);
	getPass(newStaff.password);
	systemDate(&newStaff.hireDate);

	strncpy(newStaff.staffId, newStaff.role, 1);
	generateId(newStaff.staffId);

	printf("\n\n\n========================================================================================================================\n\n");
	green();
	printf("%68s\n\n", "All Data Entered.");
	defaultcolor();

	system("pause");
	system("cls");

	printOneStaff(newStaff); //display new staff info

	getYesNo("\t\t\tComfirm add New Staff ? (Y/N) > ", &*option);

	if (toupper(*option) == 'Y')
	{
		fwrite(&newStaff, sizeof(Staff), 1, addStaff);
		green();
		printf("\t\t\tStaff Added!\n");
		defaultcolor();
		*addCount += 1;

	}

	getYesNo("\n\t\t\tAdd Another Staff ? (Y/N) > ", &*option);

	if (toupper(*option) == 'N')
	{
		printf("\n========================================================================================================================\n\n");
		printf("%45s< %d Staff Information Added >\n\n", " ", *addCount);
		system("pause");
	}

	fclose(addStaff);
}

void staffModify(char currentId[]) {

	system("cls");
	char staffId[20], staffName[50], option;
	int choice = 0;
	int count = 0, found = 0, error, foundCount = 0, block, autoConfirm;

	Staff staffInfo[MAXSTORAGE];
	Staff selectedStaff;

	logo();
	header("Modify Staff Details");
	printf("\n%92s\n", "Notice: You Must Enter Staff ID To Edit The Selected Staff Data.\n");
	getStaffId(staffId);

	if (strcmp(currentId, staffId) != 0)
	{
		do {
			autoConfirm = 0, block = 0, count = 0, foundCount = 0,found=0;
			readSelectStaff(staffId, staffInfo, &count, &foundCount, &found, &selectedStaff); //to read to array and found the id input match

			if (found)
			{
				system("cls");
				logo();
				header("Modify Staff Details");

				staffModifyInfo(selectedStaff, 1); //show selected staff info

				choice = getInteger(10);

				modifyChoice(choice, &selectedStaff, staffInfo, foundCount, &autoConfirm, &block); //show the info able to modify

				if (!block) {

					if (autoConfirm == 1) //auto set option to Y or N
						option = 'Y';
					else if (autoConfirm == 2)
						option = 'N';
					else
					{
						getYesNo("\n\n\t\t\tConfirm To Edit? (Y/N)            > ", &option);
					}

					// comfirm edit or No edit
					if (toupper(option) == 'Y')
					{

						if (strcmp(selectedStaff.status, "Resign") == 0) //if resign, auto set salary to 0
							selectedStaff.basicSalary = 0.0;

						staffInfo[foundCount] = selectedStaff; //store back to array
						strcpy(staffId, selectedStaff.staffId); // to reset staff Id if the staff id change
						storeToFile(count, staffInfo); // rewrite and store back to file

						green();
						printf("\n%75s\n", "Staff Info Successfully Edited.");
						defaultcolor();
						printf("\n========================================================================================================================\n\n");
						system("pause");
						system("cls");

					}
					else {
						red();
						printf("\n%72s\n", "No Change In Staff Info.");
						defaultcolor();
						printf("\n========================================================================================================================\n\n");
						system("pause");
						system("cls");
					}

				}

			}
			else {
				errorMessage("Invalid Staff Id Because Not Exist In System");
				system("pause");
			}

			

		} while (choice != 0);

	}
	else
	{
		errorMessage("Invalid Staff Id Because Cannot Modify Own Profile");
		system("pause");
	}


}

void staffDelete(char staffId[]) {

	char staffInputId[20];
	char choiceStart, option;
	int count = 0, found = 0, foundIndex = 0;

	Staff staffInfo[MAXSTORAGE];
	Staff bufferStaff;
	FILE* deleteStaff;

	do {
		count = 0, found = 0, foundIndex = 0, option = 'N'; //reset value

		system("cls");
		logo();
		header("Remove Staff");

		getStaffId(staffInputId);

		readSelectStaff(staffInputId, staffInfo, &count, &foundIndex, &found, &bufferStaff); //read to array

		if (found == 1)
		{
			printOneStaff(bufferStaff);

			getYesNo("\n\t\t\tComfirm Delete (Y/N) > ", &option);

			if (toupper(option) == 'Y') {

				deleteStaff = fopen(STAFFFILE, "wb");

				if (deleteStaff == NULL) {
					errorMessage("Invalid File , Please Try Again");
					return;
				}

				for (int i = 0; i < count; i++)
				{
					if (strcmp(staffInputId, staffInfo[i].staffId) == 0)
					{
						if (strcmp(staffInputId, staffId) == 0) {
							fwrite(&staffInfo[i], sizeof(Staff), 1, deleteStaff);
							errorMessage("Cant Delete Own Profile");
						}
						else {
							green();
							printf("\n%51s Had Been Deleted.\n", staffInfo[i].staffId); //if yes, do not write to binary file	
							defaultcolor();
						}
					}
					else
						fwrite(&staffInfo[i], sizeof(Staff), 1, deleteStaff);  //if the staff dun want to delete, write back to the file 	
				}

				fclose(deleteStaff);


			}
			else {
				errorMessage("No Data Deleted");
			}

			getYesNo("\n\t\t\tOthers Delete ? (Y/N) > ", &option);

		}
		else {
			errorMessage("Invalid Staff Id because not exist in system");
			option = 'N';
			system("pause");
		}

	} while (toupper(option) != 'N');
}

void leaveApplication(char staffId[]) {

	int choice, success = 0, startDatetype, endDateType;
	char option;
	Leave staffLeave;
	Date currentDate;
	FILE* leaveFile;
	leaveFile = fopen(LEAVEFILE, "ab");
	
	systemDate(&currentDate);

	if (leaveFile == NULL) {
		errorMessage("Invalid File , Please Try Again");
		return;
	}

	do {
		
		choice = 0, option = 'N', success = 0;

		system("cls");
		logo();
		header("Application Leave Managment System");

		printf("\t\t\t\t1. Unpaid Leave\n\n");
		printf("\t\t\t\t2. Annual Leave\n\n");
		printf("\t\t\t\t0. Back to Staff Menu\n\n");

		choice = getInteger(2);

		if (choice == 1)
		{
			strcpy(staffLeave.leaveType, "Unpaid Leave");
			strcpy(staffLeave.staffId, staffId);
			do
			{
				startDatetype = 0, endDateType = 0;
				system("cls");
				logo();
				header("Application Unpaid Leave System");
				red();
				printf("\t\t\t\tNotice : You Only can apply the leave of this year\n\n");
				defaultcolor();

				getDate("\t\t\t\tEnter the Start date (DD MM YYYY)", &staffLeave.startDay,&startDatetype);
				getDate("\t\t\t\tEnter the End date (DD MM YYYY)", &staffLeave.endDay,&endDateType);

				if (DAYDIFFERENT && staffLeave.startDay.year == currentDate.year && staffLeave.endDay.year == currentDate.year) {

					success = 1;

					rewind(stdin);
					printf("\t\t\t\tEnter the reason > ");
					gets(staffLeave.leaveReason);

					if (startDatetype == 1 && endDateType == 2)
						staffLeave.leaveDay = CALCULATEDAYONE;
					else if (startDatetype == 2 && endDateType == 1)
						staffLeave.leaveDay = CALCULATEDAYTWO;
					else
						staffLeave.leaveDay = CALCULATEDAYONE; // just cincai use one of calculation because is in same month or 7 and 8 month
					
					

					staffLeave.salaryDeduct = staffLeave.leaveDay * 60;

					green();
					printf("\n\t\t\t\tTotal Leave Day : %d\n", staffLeave.leaveDay);
					defaultcolor();

					getYesNo("\n\t\t\tComfirm Apply Leave ? (Y/N) > ", &option);

					if (toupper(option) == 'Y')   //write leave application to file
						fwrite(&staffLeave, sizeof(Leave), 1, leaveFile);

				}
				else
				{
					success = 0;
					errorMessage("End Date Must After Start Day and must in the current year");
				}

			} while (success != 1);
		}
		else if (choice == 2)
		{

			strcpy(staffLeave.leaveType, "Annual Leave");
			strcpy(staffLeave.staffId, staffId);
			strcpy(staffLeave.leaveReason, "Without Reason");
			do
			{
				startDatetype = 0, endDateType = 0;
				system("cls");
				logo();
				header("Application Annual Leave System");
				red();
				printf("\t\t\t\tNotice : You Only can apply the leave of this year\n\n");
				defaultcolor();
				getDate("\t\t\t\tEnter the Start date (DD MM YYYY)", &staffLeave.startDay, &startDatetype);
				getDate("\t\t\t\tEnter the End date (DD MM YYYY)", &staffLeave.endDay, &endDateType);

				if (DAYDIFFERENT && staffLeave.startDay.year == currentDate.year && staffLeave.endDay.year == currentDate.year) {

					success = 1;

					if (startDatetype == 1 && endDateType == 2)
						staffLeave.leaveDay = CALCULATEDAYONE;
					else if (startDatetype == 2 && endDateType == 1)
						staffLeave.leaveDay = CALCULATEDAYTWO;
					else
						staffLeave.leaveDay = CALCULATEDAYONE; // just cincai use one of calculation because is in same month or 7 and 8 month
					

					staffLeave.salaryDeduct = 0;

					green();
					printf("\n\t\t\t\tTotal Leave Day : %d\n", staffLeave.leaveDay);
					defaultcolor();

					getYesNo("\n\t\t\tComfirm Apply Leave ? (Y/N) > ", &option);

					if (toupper(option) == 'Y') //write leave application to file
						fwrite(&staffLeave, sizeof(Leave), 1, leaveFile);

				}
				else
				{
					success = 0;
					errorMessage("End Date Must After Start Day and must in the current year");
				}

			} while (success != 1);
		}


	} while (choice != 0);

	fclose(leaveFile);


}

void calculateSubSalary(int inputMonth, int inputYear) {

	//calculate leave to - from total salary
	Leave staffLeave[MAXSTORAGE];
	Staff staffInfo[MAXSTORAGE];

	int countStaff = 0, countLeave = 0, totalsalaryDeduct;

	readLeave(staffLeave, &countLeave, LEAVEFILE);
	readStaff(staffInfo, &countStaff, STAFFFILE);

	for (int i = 0; i < countStaff; i++)
	{
		totalsalaryDeduct = 0;
		staffInfo[i].subSalary = staffInfo[i].basicSalary;
		for (int j = 0; j < countLeave; j++)
		{
			if (strcmp(staffInfo[i].staffId, staffLeave[j].staffId) == 0)
			{
				if (inputMonth == staffLeave[j].startDay.month && inputYear == staffLeave[j].startDay.year)
				{
					totalsalaryDeduct += staffLeave[j].salaryDeduct;
				}
			}
		}
		staffInfo[i].subSalary = staffInfo[i].basicSalary - totalsalaryDeduct;
	}

	

	storeToFile(countStaff, staffInfo);
}

void staffReport() {
	int choice;
	do
	{
		system("cls");

		logo();
		header("Staff Report");
		printf("\t\t\t\t1. Staff Salary Report\n\n");
		printf("\t\t\t\t2. Status Report\n\n");
		printf("\t\t\t\t3. Leave Application Report\n\n");
		printf("\t\t\t\t4. Staff Password Report\n\n");
		printf("\t\t\t\t0. Back to StaffMenu\n\n");

		choice = getInteger(4);

		switch (choice)
		{
		case 1:
			salaryReport();
			break;
		case 2:
			statusReport();
			break;
		case 3:
			leaveReport();
			break;
		case 4:
			passWordReport();
			break;

		}
	} while (choice != 0);
}

void salaryReport() {
	Staff staffInfo;
	FILE* searchStaff;
	double total = 0, totalFull = 0, totalPart = 0, addition;
	Date currentDate;

	system("cls");
	systemDate(&currentDate);
	logo();
	header("Staff Salary Report");

	calculateSubSalary(currentDate.month, currentDate.year);

	searchStaff = fopen(STAFFFILE, "rb");

	if (searchStaff == NULL)
	{
		errorMessage("Invalid File");
		return;
	}

	printf("Salary Report of %02d-%02d-%02d\n", currentDate.day, currentDate.month, currentDate.year);
	printf(" ---------------------------------------------------------------------------------------------------------------------\n");
	printf("   ID	    Name	Contact Number	Gender	Position    Date Join	    Status	Difference(RM)	Salary(RM)\n");
	printf(" ---------------------------------------------------------------------------------------------------------------------\n");
	while (fread(&staffInfo, sizeof(Staff), 1, searchStaff) != 0)
	{
		if (strcmp(staffInfo.status, "Resign") != 0 && currentDate.month + currentDate.year * 12 - (staffInfo.hireDate.month + staffInfo.hireDate.year * 12) > 0)  // without Resign Staff and without staff just hire current month
		{

			addition = staffInfo.subSalary - staffInfo.basicSalary;

			printf("   %-7s   %-9s	%-16s   %-5c %-7s    %02d/%02d/%02d     %-12s	   %-7.2f	%.2f  \n", staffInfo.staffId, staffInfo.name, staffInfo.contact, staffInfo.gender, staffInfo.role,
				staffInfo.hireDate.day, staffInfo.hireDate.month, staffInfo.hireDate.year, staffInfo.status, addition, staffInfo.subSalary);

			if (strcmp(staffInfo.status, "Part-Time") != 0)
			{
				totalPart += staffInfo.subSalary;
			}
			else if (strcmp(staffInfo.status, "Full-Time") != 0)
			{
				totalFull += staffInfo.subSalary;
			}

			total += staffInfo.subSalary;
		}

	}
	printf(" ---------------------------------------------------------------------------------------------------------------------\n");
	printf("                                                                         Total Part Time Amount : RM %10.2f\n", totalPart);
	printf("                                                                         Total Full Time Amount : RM %10.2f\n", totalFull);
	printf("                                                                            Total Salary Amount : RM %10.2f\n", total);
	fclose(searchStaff);
	system("pause");
}

void statusReport() {

	system("cls");
	logo();
	header("Staff Status Report");

	printf(" ---------------------------------------------------------------------------------------------------------------------\n");
	printf("   ID         Name       Gender   Contact Number     Email                 Position   Salary(RM)   Date Join         \n");


	eachStatusReport("Full Time Staff", "Full-Time");
	eachStatusReport("Part Time Staff", "Part-Time");
	eachStatusReport("Resign Staff", "Resign");

	system("pause");

}

void eachStatusReport(char staffType[], char status[]) {

	int count = 0;

	Staff staffInfo;
	FILE* searchStaff;
	searchStaff = fopen(STAFFFILE, "rb");
	if (searchStaff == NULL)
	{
		errorMessage("Invalid File");
		return;
	}

	printf(" ---------------------------------------------------------------------------------------------------------------------\n");
	color('B');
	printf("%s\n", staffType);
	color('X');
	printf(" ---------------------------------------------------------------------------------------------------------------------\n");

	while (fread(&staffInfo, sizeof(Staff), 1, searchStaff) != 0)
	{
		if (strcmp(staffInfo.status, status) == 0) {
			printf("   %-8s   %-10s   %-7c  %-14s   %-20s   %-8s   %10.2f   %02d/%02d/%02d   \n", staffInfo.staffId, staffInfo.name, staffInfo.gender, staffInfo.contact, staffInfo.email,
				staffInfo.role, staffInfo.basicSalary,
				staffInfo.hireDate.day, staffInfo.hireDate.month, staffInfo.hireDate.year);
			count++;
		}
	}
	printf(" ---------------------------------------------------------------------------------------------------------------------\n");
	color('B');
	printf("											%s Staff: %d\n", staffType, count);
	color('X');

	fclose(searchStaff);
}


void leaveReport() {
	system("cls");

	Leave staffLeave;
	FILE* read;
	read = fopen(LEAVEFILE, "rb");
	if (read == NULL)
	{
		errorMessage("Invalid File");
		return;
	}
	logo();
	header("Staff Leave Report");
	printf(" ---------------------------------------------------------------------------------------------------------------------\n");
	printf("   Type              StaffId	Start Day	End Day		Reason		Total Day Leave   Salary Deduct(RM)  \n");
	printf(" ---------------------------------------------------------------------------------------------------------------------\n");
	while (fread(&staffLeave, sizeof(Leave), 1, read) != 0)
	{
		if (strcmp(staffLeave.leaveType,"Unpaid Leave") == 0)
		{
			printf("   %-17s %-11s %02d/%02d/%02d      %02d/%02d/%02d      %-15s        %d                %d\n", staffLeave.leaveType, staffLeave.staffId, staffLeave.startDay.day, staffLeave.startDay.month,
				staffLeave.startDay.year, staffLeave.endDay.day, staffLeave.endDay.month, staffLeave.endDay.year,
				staffLeave.leaveReason, staffLeave.leaveDay, staffLeave.salaryDeduct);
		}
		
	}

	fclose(read);
	
	read = fopen(LEAVEFILE, "rb");
	if (read == NULL)
	{
		errorMessage("Invalid File");
		return;
	}
	while (fread(&staffLeave, sizeof(Leave), 1, read) != 0)
	{
		if (strcmp(staffLeave.leaveType, "Annual Leave") == 0)
		{
			printf("   %-17s %-11s %02d/%02d/%02d      %02d/%02d/%02d      %-15s        %d                %d\n", staffLeave.leaveType, staffLeave.staffId, staffLeave.startDay.day, staffLeave.startDay.month,
				staffLeave.startDay.year, staffLeave.endDay.day, staffLeave.endDay.month, staffLeave.endDay.year,
				staffLeave.leaveReason, staffLeave.leaveDay, staffLeave.salaryDeduct);
		}

	}
	fclose(read);
	system("pause");
}

void passWordReport() {
	Staff staffInfo;
	FILE* searchStaff;

	system("cls");
	logo();
	header("Staff Password Report");


	searchStaff = fopen(STAFFFILE, "rb");

	if (searchStaff == NULL)
	{
		errorMessage("Invalid File");
		return;
	}

	printf("\t\t\t\t ---------------------------------------------------------\n");
	printf("\t\t\t\t |     ID         Name       Gender	   Password      |\n");
	printf("\t\t\t\t ---------------------------------------------------------\n");
	while (fread(&staffInfo, sizeof(Staff), 1, searchStaff) != 0)
		printf("\t\t\t\t |   %-8s   %-13s  %-10c %-15s|\n", staffInfo.staffId, staffInfo.name, staffInfo.gender, staffInfo.password);
	

	printf("\t\t\t\t ---------------------------------------------------------\n");

	fclose(searchStaff);
	system("pause");
}


void readSelectStaff(char staffId[], Staff staffInfo[], int* count, int* foundCount, int* found, Staff* selectedStaff)
{
	FILE* searchStaff;

	searchStaff = fopen(STAFFFILE, "rb");
	if (searchStaff == NULL)
	{
		errorMessage("Invalid File , Please Try Again");
		return;
	}

	while (*count < MAXSTORAGE && fread(&staffInfo[*count], sizeof(Staff), 1, searchStaff) != 0) {
		if (strcmp(staffId, staffInfo[*count].staffId) == 0)
		{
			*selectedStaff = staffInfo[*count];
			*found = 1;
			*foundCount = *count;
		}
		(*count)++;
	}

	fclose(searchStaff);

}

void readStaff(Staff staffInfo[], int* count, FILE* inputFile) {

	FILE* searchStaff;
	searchStaff = fopen(inputFile, "rb"); //read file

	if (searchStaff == NULL)
	{
		errorMessage("Invalid File , Please Try Again");
		return;
	}

	while (fread(&staffInfo[*count], sizeof(Staff), 1, searchStaff) != 0) //read to array structure
		(*count)++;

	fclose(searchStaff);

}

void readLeave(Leave LeaveInfo[], int* count, FILE* inputFile) {

	FILE* searchLeave;
	searchLeave = fopen(inputFile, "rb"); //read file

	if (searchLeave == NULL)
	{
		errorMessage("Invalid File , Please Try Again");
		return;
	}

	while (fread(&LeaveInfo[*count], sizeof(Leave), 1, searchLeave) != 0) //read to array structure
		(*count)++;

	fclose(searchLeave);

}

void storeToFile(int count, Staff staffInfo[]) {

	FILE* editStaff;
	editStaff = fopen(STAFFFILE, "wb");

	if (editStaff == NULL) {
		errorMessage("Invalid File , Please Try Again");
		return;
	}

	for (int i = 0; i < count; i++) 	//store to binary file
		fwrite(&staffInfo[i], sizeof(Staff), 1, editStaff);

	fclose(editStaff);
}


void printOneStaff(Staff staffInfo) {

	system("cls");
	logo();
	header("Staff Profile");
	printf("\n\t\t\t\t\tName                   : %s\n", staffInfo.name);
	printf("\t\t\t\t\tStaff ID               : %s\n", staffInfo.staffId);
	printf("\t\t\t\t\tStaff IC               : %s\n", staffInfo.icNo);
	printf("\t\t\t\t\tGender                 : ");
	if (toupper(staffInfo.gender) == 'M')
		printf("Male\n");
	else
		printf("Female\n");

	printf("\t\t\t\t\tContact Number         : %s\n", staffInfo.contact);
	printf("\t\t\t\t\tEmail                  : %s\n", staffInfo.email);
	printf("\t\t\t\t\tAddress                : %s\n", staffInfo.address);
	printf("\t\t\t\t\tPosition               : %s\n", staffInfo.role);
	printf("\t\t\t\t\tStatus                 : %s\n", staffInfo.status);
	printf("\t\t\t\t\tSalary (RM)            : %.2lf\n", staffInfo.basicSalary);
	printf("\t\t\t\t\tJoined Date (DD/MM/YY) : %02d/%02d/%02d\n\n", staffInfo.hireDate.day, staffInfo.hireDate.month, staffInfo.hireDate.year);

}

void staffModifyInfo(Staff staffInfo, int mode) {

	system("cls");
	logo();
	header("Staff Profile");
	if (mode == 1)
	{
		printf("%61s %s\n", "Staff ID :", staffInfo.staffId);
		printf("%74s", "Which Data You Want To Edit?");
		printf("\n\n\t\t\t\t\t1. Name                   : %s", staffInfo.name);
		printf("\n\t\t\t\t\t2. Ic no                  : %s", staffInfo.icNo);
		printf("\n\t\t\t\t\t3. Gender                 : %c", staffInfo.gender);
		printf("\n\t\t\t\t\t4. Contact Number         : %s", staffInfo.contact);
		printf("\n\t\t\t\t\t5. Email                  : %s", staffInfo.email);
		printf("\n\t\t\t\t\t6. Address                : %s", staffInfo.address);
		printf("\n\t\t\t\t\t7. Position               : %s", staffInfo.role);
		printf("\n\t\t\t\t\t8. Status                 : %s", staffInfo.status);
		printf("\n\t\t\t\t\t9. Salary (RM)            : %.2lf", staffInfo.basicSalary);
		printf("\n\t\t\t\t\t10. Reset Password");
		printf("\n\t\t\t\t\t0. Return To Staff Profile\n\n");
	}
	else
	{
		printf("%61s %s\n", "Staff ID :", staffInfo.staffId);
		printf("%74s", "Which Data You Want To Edit?");
		printf("\n\n\t\t\t\t\t1. Name                   : %s", staffInfo.name);
		printf("\n\t\t\t\t\t2. Ic no                  : %s", staffInfo.icNo);
		printf("\n\t\t\t\t\t3. Gender                 : %c", staffInfo.gender);
		printf("\n\t\t\t\t\t4. Contact Number         : %s", staffInfo.contact);
		printf("\n\t\t\t\t\t5. Email                  : %s", staffInfo.email);
		printf("\n\t\t\t\t\t6. Address                : %s", staffInfo.address);
		printf("\n\t\t\t\t\t0. Return To Staff Profile\n\n");
	}

}

void forgetPass(char staffId[]) {

	int count = 0, loginIndex = 0, buffer = 0, otp, otpInput, emailChance = 3, otpChance = 3;
	char option;

	Staff staffInfo[MAXSTORAGE];
	Staff selectedStaff;

	readSelectStaff(staffId, staffInfo, &count, &loginIndex, &buffer, &selectedStaff);


	do
	{
		system("cls");
		logo();
		header("Recovery Password");

		red();
		printf("\t\t\t\tNotice : You Only Have %d Chancce To Enter Wrong Email\n\n", emailChance);
		defaultcolor();

		getEmail(selectedStaff.email);
		if (strcmp(selectedStaff.email, staffInfo[loginIndex].email) == 0)
		{
			system("cls");
			emailChance = 0;

			srand(time(0));
			otp = rand() % 9999 + 1000; //random Otp

			printf("+-------------------------------------------------------+\n");
			printf("|   Inbox (10)        |   Sent Items      |   Compose   |\n");
			printf("+-------------------------------------------------------+\n");
			printf("|   To:%-48s |\n", selectedStaff.email);
			printf("|   To:%-48s |\n", "From: Managment System <management@gmail.com>");
			printf("|   Subject: %-42s |\n", "Recovery Password");
			printf("|                                                       |\n");
			printf("|   %-52s|\n", "Hi Your OTP For Verify Your Reset Password Request");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|   OTP : %-46d|\n", otp);
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("|                                                       |\n");
			printf("+------------------------------------------------------+\n");
			system("pause");
			system("cls");


			do
			{
				system("cls");
				logo();
				header("Recovery Password");

				red();
				printf("\t\t\tNotice : You Only Have %d Chancce To Enter Wrong OTP\n\n", otpChance);
				defaultcolor();

				printf("\t\t\tPlease Enter your OTP > ");
				scanf("%d", &otpInput);
				if (otp == otpInput)
				{
					otpChance = 0;
					getPass(selectedStaff.password);

					getYesNo("\n\t\t\tConfirm Reset (Y/N) > ", &option);

					if (toupper(option) == 'Y')
					{
						staffInfo[loginIndex] = selectedStaff; //store back to array

						storeToFile(count, staffInfo); // rewrite and store back to file

						printf("\n%75s\n", "Staff Data Successfully Edited.");

						printf("\n========================================================================================================================\n\n");
						system("pause");
						system("cls");

					}
					else {
						printf("\n%72s\n", "No Change In Staff Data.");
						printf("\n========================================================================================================================\n\n");
						system("pause");
						system("cls");
					}
				}
				else
				{
					errorMessage("Wrong OTP");
					otpChance--;
				}

			} while (otpChance != 0);



		}
		else
		{
			emailChance--;
			if (emailChance != 0)
			{
				errorMessage("Wrong Email Address, Please Enter Again.....");
			}
			else if (emailChance == 0)
			{
				errorMessage("Wrong Email Address");
			}

		}

	} while (emailChance != 0);



}


#pragma endregion


#pragma region StaffValidationFunction -Leong Kah Yung

void getDate(char info[], Date* applyDate,int *dateType) {
	int error;
	Date currentDate;
	//datatype = 1 big month
	//datatype = 2 small month
	do
	{
		systemDate(&currentDate);
		error = 0;
		printf("%s > ", info);
		scanf("%d %d %d", &applyDate->day, &applyDate->month, &applyDate->year);


		if (applyDate->year * 365 + applyDate->month * 31 + applyDate->day < currentDate.year * 365 + currentDate.month * 31 + currentDate.day)
			error = 1;
		else if (applyDate->month > 12 || applyDate->month <= 0)
			error = 2;
		else if (applyDate->month == 1 || applyDate->month == 3 || applyDate->month == 5 || applyDate->month == 7 || applyDate->month == 8 || applyDate->month == 10 || applyDate->month == 12) {
			*dateType = 1;
			if (applyDate->day <= 0 || applyDate->day > 31)
				error = 3;
		}
		else {
			*dateType = 2;
			if (applyDate->day <= 0 || applyDate->day > 30)
				error = 4;
		}


		switch (error)
		{
		case 1:
			errorMessage("Please dont apply the date that passed already");
			break;

		case 2:
			errorMessage("Please enter the month between 1 and 12.");
			break;
		case 3:
			errorMessage("Please enter correct day for (January, March, May, July, August, October, and December)");
			break;
		case 4:
			errorMessage("Please enter correct day for (Feb, Apr, Jun, Sep, and Nov) ");
			break;

		}

	} while (error != 0);
}

void generateId(char inputId[]) {

	char newnum[5];
	char lastid[10];
	int lastnum;

	FILE* countId;
	Staff staffData;
	countId = fopen(STAFFFILE, "rb");

	if (countId == NULL)
	{
		errorMessage("Invalid File , Please Try Again");
		return;
	}
	else
	{
		while (fread(&staffData, sizeof(Staff), 1, countId) != 0)
		{
			strcpy(lastid, &staffData.staffId[1]);
		}

		lastnum = atoi(lastid); //convert to integer

		itoa(lastnum + 1, newnum, 10); // convert to string 

		if (strlen(newnum) == 2)
		{
			strcat(inputId, "00");
			strcat(inputId, newnum);
		}
		else if (strlen(newnum) == 3)
		{
			strcat(inputId, "0");
			strcat(inputId, newnum);
		}
		else if (strlen(newnum) == 4)
		{
			strcat(inputId, newnum);
		}
		else
		{
			strcat(inputId, "000");
			strcat(inputId, newnum);
		}
	}

	fclose(countId);
}

void getStaffId(char inputId[]) {
	int error;
	do
	{
		error = 0;
		rewind(stdin);
		printf("\t\t\tEnter Staff Id > ");
		gets(inputId);


		for (int i = 1; i < strlen(inputId); i++)
		{
			if (!isspace(inputId[i]) && !isdigit(inputId[i]))
				error = 1;
		}

		if (strlen(inputId) == 0)
			error = 2;
		else if (inputId[0] != 'A' && inputId[0] != 'S')
			error = 3;

		switch (error)
		{
		case 1:
			errorMessage("Please do not enter simbol or alphabet at id numeric code A\"0001\"");
			break;

		case 2:
			errorMessage("Please do not leave it at blank.");
			break;
		case 3:
			errorMessage("Must start with A or S.");
			break;

		}

	} while (error != 0);
}

void getName(char inputName[]) {
	int error;
	do
	{
		error = 0;
		rewind(stdin);
		printf("\t\t\tEnter Name > ");
		gets(inputName);


		if (strlen(inputName) == 0)
			error = 2;

		for (int i = 0; i < strlen(inputName); i++)
		{

			if (strlen(inputName) > 100) { //for valid name should not over 100 word		
				error = 1;
				break;
			}
			else if (isspace(inputName[0]))
				error = 3;
			else if (!isspace(inputName[i]) && !isalpha(inputName[i]))
				error = 4;

		}


		switch (error)
		{
		case 1:
			errorMessage("Please do not enter an unreasonably long name.");
			break;
		case 2:
			errorMessage("Please do not leave it at blank.");
			break;
		case 3:
			errorMessage("Please do not start with space.");
			break;
		case 4:
			errorMessage("Please do not enter simbol or number.");
			break;
		}

	} while (error != 0);
}

void getGender(char* inputGender) {

	int error;
	char checkspace;
	do
	{
		error = 0;
		rewind(stdin);
		printf("\t\t\tEnter Gender (M/F) > ");
		scanf("%c%c", &*inputGender, &checkspace);

		*inputGender = toupper(*inputGender);

		if (toupper(*inputGender) != 'M' && toupper(*inputGender) != 'F')
		{
			error = 1;
			errorMessage("Input Must M(Male) or F (Female)");
		}
		else if (checkspace != '\n') {
			error = 1;
			errorMessage("Invalid input, just one character");
		}


	} while (error != 0);
}

void getIC(char inputIc[]) {
	int error;
	int day, month, year;
	char buffer[10];
	do
	{
		error = 0;
		rewind(stdin);
		printf("\t\t\tEnter Identify Card Number (without '-') > ");
		gets(inputIc);

		year = atoi(strncpy(buffer, inputIc, 2)); //check month from Ic 1,2 digits
		month = atoi(strncpy(buffer, inputIc + 2, 2)); 	//check month from Ic 3,4 digits
		day = atoi(strncpy(buffer, inputIc + 4, 2)); 	//check day from Ic 5,6 digits

		if (strlen(inputIc) == 0)
			error = 3;
		else if (strlen(inputIc) != 12)  //for valid ic must 12 number
			error = 1;
		else if (year < 0 || year > 99)
			error = 4;
		else if (month <= 0 || month > 12)
			error = 5;
		else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
			if (day <= 0 || day > 31)
				error = 6;
		}
		else
			if (day <= 0 || day > 30)
				error = 6;


		for (int i = 0; i < strlen(inputIc); i++)
		{
			if (!isspace(inputIc[i]) && !isdigit(inputIc[i]))  // only include digit only
				error = 2;
		}


		switch (error)
		{
		case 1:
			errorMessage("Ic number must 12 numbers");
			break;
		case 2:
			errorMessage("Ic number only can enter by digits");
			break;
		case 3:
			errorMessage("Ic number cannot be blank");
			break;
		case 4:
			errorMessage("Invalid year of birth in IC number");
			break;
		case 5:
			errorMessage("Invalid month of birth in IC number");
			break;
		case 6:
			errorMessage("Invalid day of birth in IC number");
			break;
		}

	} while (error != 0);
}

void getContact(char inputContact[]) {

	int error;

	do
	{
		error = 0;
		printf("\n\t\t\tEnter Contact Number (Example : 0123456789)      > ");
		rewind(stdin);
		gets(inputContact);

		for (int i = 0; i < strlen(inputContact); i++)
		{
			if (!isdigit(inputContact[i]))
				error = 1;
		}

		if (inputContact[0] != '0' || inputContact[1] != '1')
			error = 2;
		else if (inputContact[2] == '1' || inputContact[2] == '5') { //check for 011- or 015-
			if (strlen(inputContact) != 11)
				error = 3;

		}
		else if (strlen(inputContact) != 10)
			error = 4;


		switch (error)
		{
		case 1:
			errorMessage("Please Enter Numbers Only.");
			break;
		case 2:
			errorMessage("Please Start With 01- (Example : 0121234567)");
			break;
		case 3:
			errorMessage("For 011 and 015, Phone Number Must Contain 11 Numbers.");
			break;
		case 4:
			errorMessage("Phone Number Must Contain 10 Numbers.");
			break;
		}

	} while (error != 0);

}

void getEmail(char inputEmail[]) {
	int error;
	int countAliance, countDot, locateAliance, locateDot;

	do
	{
		error = 0;
		countAliance = 0;
		countDot = 0;
		rewind(stdin);
		printf("\t\t\tEnter Email  > ");
		gets(inputEmail);

		for (int i = 0; i < strlen(inputEmail); i++)
		{
			if (inputEmail[i] == '@')
			{
				countAliance++;
				locateAliance = i;
			}
			else if (inputEmail[i] == '.') {
				countDot++;
				locateDot = i;
			}
		}

		if (!(isalpha(inputEmail[0])))
			error = 1;
		else if (countAliance == 0 || countDot == 0)
			error = 2; //need @ and .
		else if (inputEmail[locateAliance + 1] == '.') //if the dot is behind the @
			error = 3;
		else {
			for (int i = locateAliance + 1; i < locateDot; i++) //check the letter between @ and . must not be any simbol
			{
				if (!isalpha(inputEmail[i]))
					error = 4;
			}
			for (int i = locateDot + 1; i < strlen(inputEmail); i++) //check the letter after . must not be any simbol
			{
				if (!isalpha(inputEmail[i]))
					error = 5;
				else if (inputEmail[i] == '\0')
					error = 6;
			}

		}

		switch (error)
		{
		case 1:
			errorMessage("First Letter Should start with alphabet (Example : abc123@mail.com)");
			break;
		case 2:
			errorMessage("Please Enter Email In (abc123@mail.com) format.");
			break;
		case 3:
			errorMessage("Domain Name Should Be Entered. (Example : abc123@mail.com)");
			break;
		case 4:
			errorMessage("Domain Name Should Be Enter By Numbers or Alphabets. (Example : abc123@mail.com)");
			break;
		case 5:
			errorMessage("Domain Should Be Enter By Alphabets. (Example : .com, .org, .my)");
			break;
		case 6:
			errorMessage("Please Enter The Domain. (Example : .com, .org, .my)");
			break;
		}

	} while (error != 0);

}

void getRole(char inputRole[]) {

	int choice, error;

	do {
		error = 0;
		rewind(stdin);
		printf("\t\t\tChoose A Position: 1) Admin      2) Staff\n");
		choice = getIntegerFromOne(2);

		switch (choice)
		{
		case 1:
			strcpy(inputRole, "ADMIN");
			break;
		case 2:
			strcpy(inputRole, "STAFF");
			break;
		default:
			errorMessage("Please Enter The Correct Code.");
			error = 1;
		}

	} while (error != 0);
}

void getStatus(char inputStatus[], int mode) {
	int error, choice;

	/*mode 1 = create new status or (Resign -> Full/Part Time)
	  mode 2 = edit status     (Full time -> Part time/Resign)
							  (Part time-> Full time / Resign)*/

	do
	{
		error = 0;
		printf("\n\t\t\tChoose A Status             ");
		if (mode == 1)
		{
			printf("\n\t\t\t 1) Full-Time  2) Part-Time \n");
			rewind(stdin);
			choice = getIntegerFromOne(2);
			switch (choice)
			{
			case 1:
				strcpy(inputStatus, "Full-Time");
				break;
			case 2:
				strcpy(inputStatus, "Part-Time");
				break;
			default:
				error = 1;
			}
		}

		if (mode == 2) {

			if (strcmp(inputStatus, "Full-Time") == 0)
			{
				printf("\n\t\t\t 1) Part-Time     2) Resign\n");
				rewind(stdin);
				choice = getIntegerFromOne(2);
				switch (choice)
				{
				case 1:
					strcpy(inputStatus, "Part-Time");
					break;
				case 2:
					strcpy(inputStatus, "Resign");
					break;
				default:
					error = 1;
				}
			}
			else
			{
				printf("\n\t\t\t 1) Full-Time     2) Resign\n");
				rewind(stdin);
				choice = getIntegerFromOne(2);

				switch (choice)
				{
				case 1:
					strcpy(inputStatus, "Full-Time");
					break;
				case 2:
					strcpy(inputStatus, "Resign");
					break;
				default:
					error = 1;
				}
			}
		}

	} while (error != 0);
}

void getSalary(double* inputSalary) {
	int error = 0;

	do
	{
		error = 0;
		printf("\t\t\tEnter Salary                > ");
		rewind(stdin);

		scanf("%lf", &*inputSalary);

		if (*inputSalary <= 0) {
			error = 1;
			errorMessage("Please Insert A Valid Amount");
		}
		else if (*inputSalary >=1000000)
		{
			error = 1;
			errorMessage("Salary exceed 1000k too high for a month salary");
		}
	} while (error != 0);

}

void hidePassword(char inputPassword[]) {

	int i = 0;
	char charBuffer;

	rewind(stdin);
	while ((charBuffer = getch())) { //get password without printing it on console

		if (charBuffer == 13) //when press enter, stop loop
			break;
		else if (charBuffer == 8) //when backspace, delete character
		{
			if (i > 0)
			{
				i--;
				inputPassword[i] = '\0';
				printf("\b \b");
			}
		}
		else	//store into password variable and print asterisk
		{
			inputPassword[i] = charBuffer;
			i++;
			printf("*");
		}
	}
	inputPassword[i] = '\0';
}

void getPass(char inputPass[]) {
	int error, digit, lower, upper, chance;
	char passCheck[50];

	do {
		do
		{
			error = 0;
			digit = 0;
			lower = 0;
			upper = 0;

			printf("\n\t\t\tCreate New Password\n");
			blue();
			printf("\t\t\tCondition :\n ");
			defaultcolor();
			printf("\t\t\tAt least 8 character \n ");
			printf("\t\t\tAt least 1 digit \n ");
			printf("\t\t\tAt least 1 uppercase \n ");
			printf("\t\t\tAt least 1 lowercase \n ");
			printf("\t\t\tEnter Password > ");

			rewind(stdin); // prevent error if user enter character
			hidePassword(inputPass);

			for (int i = 0; i < strlen(inputPass); i++)
			{
				if (isdigit(inputPass[i]))
					digit++;
				else if (islower(inputPass[i]))
					lower++;
				else if (isupper(inputPass[i]))
					upper++;
			}

			if (strlen(inputPass) < 8 || strlen(inputPass) > 12)
				error = 4;
			else if (digit == 0)
				error = 1;
			else if (lower == 0)
				error = 2;
			else if (upper == 0)
				error = 3;

			switch (error)
			{
			case 1:
				errorMessage("Password at least need one digit.");
				break;
			case 2:
				errorMessage("Password at least need one lowercase.");
				break;
			case 3:
				errorMessage("Password at least need one uppercase");
				break;
			case 4:
				errorMessage("Password at least 8 character and less than 12 character");
				break;
			}
		} while (error != 0);

		printf("\n\n\t\t\tComfirm Password            > ");
		hidePassword(passCheck);
		chance = 4;
		while (strcmp(passCheck, inputPass) != 0)
		{
			chance--;
			if (chance == 0)
			{
				printf("\n\t\t\tPlease Enter A New Password Again.\n");
				break;
			}
			else
			{
				printf("\n\t\t\tPlease Try Again (%d)        > ", chance);
				hidePassword(passCheck);
			}

		}

	} while (chance == 0);
}

void getAddress(char inputAddress[]) {
	int error = 0;

	do
	{
		error = 0;
		rewind(stdin);
		printf("\t\t\tEnter staff Address > ");
		gets(inputAddress);


		if (strlen(inputAddress) == 0) {
			error = 1;
			errorMessage("Should be fill in the address");
		}

		for (int i = 0; i < strlen(inputAddress); i++)
		{
			if (!isspace(inputAddress[i]) && !isdigit(inputAddress[i]) && !isalpha(inputAddress[i])) {
				error = 1;
				errorMessage("Address cannot have simbol");
			}
		}

	} while (error != 0);
}

void systemDate(Date* currentDate) {
	//get the current date
	time_t t;
	t = time(NULL);
	struct tm tm = *localtime(&t);
	
	currentDate->day = tm.tm_mday;
	currentDate->month = tm.tm_mon + 1;
	currentDate->year = tm.tm_year + 1900;
}



#pragma endregion


#pragma region memberModule-Lai Yong Le

void memberMainPage() {

	int select, changeMemNum, i;

	Member totalMember[100];
	FILE* total;
	do {
		i = 0;
		total = fopen("member.bin", "rb");

		while (fread(&totalMember[i], sizeof(Member), 1, total) != 0)
			i++;

		fclose(total);

		select = 0;
		system("cls");
		logo();
		header("Member Main Page");
		printf("%37s %d\n\n", "Total Number of Member: ", i);
		printf("\t\t\t%s\n\n", "1. Add New Member");
		printf("\t\t\t%s\n\n", "2. Search Member Information");
		printf("\t\t\t%s\n\n", "3. Modify Member Information");
		printf("\t\t\t%s\n\n", "4. Delete Member Information");
		printf("\t\t\t%s\n\n", "5. Display All Member Information");
		printf("\t\t\t%s\n\n", "6. View Member Type Benefits");
		printf("\t\t\t%s\n\n", "7. Monthly Member Change");
		printf("\t\t\t%s\n\n", "8. Upline member commission");
		printf("\t\t\t%s\n", "0. Back to Main Menu");

		rewind(stdin);
		printf("\n\n\t\t\tPlease make your selection (0 - 8 only):\n\n ");
		select = getInteger(8);

		switch (select)
		{
		case 1:
			memberAdd();
			break;
		case 2:
			memberSearch();
			break;
		case 3:
			memberModify();
			break;
		case 4:
			memberDelete();
			break;
		case 5:
			memberDisplayAll();
			break;
		case 6:
			memberTypeAdv();
			break;

		case 7:
			memberMonthlyChange();
			break;
		case 8:
			memberComm();
			break;

		case 0:
			break;

		default:
			errorMessage("Invalid Selection! Only 0 - 8 are available");
		}

	} while (select != 0);
}

void memberAdd() {
	Member newMember;
	char choice, yesNo;
	int count = 0;
	FILE* add;

	do {
		choice = 'N';
		add = fopen("member.bin", "ab");
		system("cls");
		logo();
		header("Add New Member");
		red();
		printf("The Information Needed !\n");
		defaultcolor();
		printf("--> Name\n");
		printf("--> Gender\n");
		printf("--> Identity Card No\n");
		printf("--> Contact Number\n");
		printf("--> Email Address\n");
		printf("--> Address\n");
		printf("--> Member Type\n");
		printf("--> Upline ID(optional)\n");

		getYesNo("\nAdd New Member ? (Y/N) > ", &choice);


		if (add == NULL) {
			errorMessage("Invalid File");
			return;
		}
		else if (toupper(choice) == 'Y')
		{
			Member newMember = { .memberId = "" };
			getName(newMember.name);
			getGender(&newMember.gender);
			getIC(newMember.icNo);
			getContact(newMember.contactNo);
			getEmail(newMember.email);
			getMemberAddress(newMember.address);
			getType(newMember.memberType, &newMember.memberType, "", 1);
			getYesNo("\t\t\tDoes this member have upline?(Y/N) > ", &yesNo);
			if (toupper(yesNo) == 'Y')
				getUplineId(newMember.uplineId);
			else
				strcpy(newMember.uplineId, "None");
			systemDate(&newMember.joinDate);

			newMember.memberId[0] = 'M';
			generateMemberId(newMember.memberId);


			printf("\n\n\n========================================================================================================================\n\n");
			printf("%68s\n\n", "All Data Entered.");
			system("pause");
			system("cls");

			printf("\n\t\t\t\t\tName                   : %s\n", newMember.name);
			printf("\t\t\t\t\tMember ID              : %s\n", newMember.memberId);
			printf("\t\t\t\t\tMember IC              : %s\n", newMember.icNo);
			printf("\t\t\t\t\tGender                 : ");
			if (toupper(newMember.gender) == 'M')
				printf("Male\n");
			else
				printf("Female\n");

			printf("\t\t\t\t\tContact Number         : %s\n", newMember.contactNo);
			printf("\t\t\t\t\tEmail                  : %s\n", newMember.email);
			printf("\t\t\t\t\tMember Type            : ");
			if (toupper(newMember.memberType == 'N'))
				printf("Normal\n");
			else if (toupper(newMember.memberType == 'G'))
				printf("Gold\n");
			else if (toupper(newMember.memberType == 'P'))
				printf("Platinum\n");
			else
				printf("Diamond\n");
			printf("\t\t\t\t\tUpline Id              : %s\n", newMember.uplineId);
			printf("\t\t\t\t\tJoined Date (DD/MM/YY) : %02d/%02d/%02d\n", newMember.joinDate.day, newMember.joinDate.month, newMember.joinDate.year);
			printf("========================================================================================================================\n\n");

			getYesNo("Confirm add New Member ? (Y/N) > ", &choice);

			if (toupper(choice) == 'Y')
			{
				fwrite(&newMember, sizeof(newMember), 1, add);
				green();
				printf("Member Added!\n");
				defaultcolor();
				count++;

			}

			getYesNo("Add Another Member ? (Y/N) > ", &choice);

			if (toupper(choice) == 'N')
			{
				printf("\n========================================================================================================================\n\n");
				printf("%45s< %d Member Information Added >\n\n", " ", count);
				system("pause");
			}

		}
		fclose(add);
	} while (toupper(choice) == 'Y');



}

void memberSearch() {
	system("cls");
	int choice;
	char valid, memberName[100], memberId[31];
	Member srcMember;
	FILE* searchMember;

	do {
		searchMember = fopen("member.bin", "rb");
		system("cls");
		logo();
		header("Search Member");
		valid = 'R';
		printf("\t\t\t1. Search by Id\n\n");
		printf("\t\t\t2. Search by Name\n\n");
		printf("\t\t\t0.Exit to Member Menu\n\n");
		choice = getInteger(2);

		if (searchMember == NULL) {
			errorMessage("Invalid File");
			return;
		}

		if (choice == 1)
		{
			rewind(stdin);
			printf("\n%s\n\n", " Search ");
			getMemberId(memberId);

			while (fread(&srcMember, sizeof(Member), 1, searchMember) != 0)
			{
				if (strcmp(srcMember.memberId, memberId) == 0) {
					system("cls");
					logo();
					header("Search Member");
					printf("\n\t\t\t\t\tMember ID              : %s\n", srcMember.memberId);
					printf("\t\t\t\t\tName                   : %s\n", srcMember.name);
					printf("\t\t\t\t\tMember IC              : %s\n", srcMember.icNo);
					printf("\t\t\t\t\tGender                 : ");
					if (toupper(srcMember.gender) == 'M')
						printf("Male\n");
					else
						printf("Female\n");
					printf("\t\t\t\t\tContact Number         : %s\n", srcMember.contactNo);
					printf("\t\t\t\t\tMember Type            : ");
					if (toupper(srcMember.memberType == 'N'))
						printf("Normal\n");
					else if (toupper(srcMember.memberType == 'G'))
						printf("Gold\n");
					else if (toupper(srcMember.memberType == 'P'))
						printf("Platinum\n");
					else
						printf("Diamond\n");
					printf("\t\t\t\t\tUpline Id              : %s\n", srcMember.uplineId);
					printf("\t\t\t\t\tEmail                  : %s\n", srcMember.email);
					printf("\t\t\t\t\tAddress                : %s\n", srcMember.address);
					printf("\t\t\t\t\tJoined Date (DD/MM/YY) : %02d/%02d/%02d\n", srcMember.joinDate.day, srcMember.joinDate.month, srcMember.joinDate.year);

					valid = 'Y';
				}

			}
		}
		else if (choice == 2)
		{
			rewind(stdin);
			printf("\n%s\n\n", " Search ");
			getName(memberName);

			while (fread(&srcMember, sizeof(Member), 1, searchMember) != 0)
			{
				if (strcmp(srcMember.name, memberName) == 0)
				{
					system("cls");
					logo();
					header("Search Member");
					printf("\n\t\t\t\t\tMember ID              : %s\n", srcMember.memberId);
					printf("\t\t\t\t\tName                   : %s\n", srcMember.name);
					printf("\t\t\t\t\tMember IC              : %s\n", srcMember.icNo);
					printf("\t\t\t\t\tGender                 : ");
					if (toupper(srcMember.gender) == 'M')
						printf("Male\n");
					else
						printf("Female\n");
					printf("\t\t\t\t\tContact Number         : %s\n", srcMember.contactNo);
					printf("\t\t\t\t\tMember Type            : ");
					if (toupper(srcMember.memberType == 'N'))
						printf("Normal\n");
					else if (toupper(srcMember.memberType == 'G'))
						printf("Gold\n");
					else if (toupper(srcMember.memberType == 'P'))
						printf("Platinum\n");
					else
						printf("Diamond\n");
					printf("\t\t\t\t\tEmail                  : %s\n", srcMember.email);
					printf("\t\t\t\t\tAddress                : %s\n", srcMember.address);
					printf("\t\t\t\t\tUpline ID              : %s\n", srcMember.uplineId);
					printf("\t\t\t\t\tJoined Date (DD/MM/YY) : %02d/%02d/%02d\n", srcMember.joinDate.day, srcMember.joinDate.month, srcMember.joinDate.year);

					valid = 'Y';
				}
			}
		}
		else
		{
			purple();
			printf("\n\t\t\tRedirecting to the Member Main Page");
			delay(0.4);
			printf(".");
			delay(0.4);
			printf(".");
			delay(0.4);
			printf(".");
			defaultcolor();
			delay(1.2);
			valid = 'O';
		}

		if (valid == 'R')
			errorMessage("Invalid Member");

		if (choice != 0) {
			printf("\n\n\t\t\t1. Search Others Member \t\t 0. Back to Member Menu \n\n");
			choice = getInteger(1);
			if (choice == 1)
				valid = 'N';
		}
		fclose(searchMember);
	} while (valid == 'N');

}

void memberDelete() {
	Member dltMember[100];
	FILE* findMember;
	FILE* deleteMember;
	char memberId[31];
	char memberInput[30];
	int i, count = 0, found;
	char option, choice;


	do {
		system("cls");
		logo();
		header("Delete Member");
		i = 0;
		found = 0;
		count = 0;
		option = 'N';
		findMember = fopen("member.bin", "rb");
		if (findMember == NULL)
		{
			errorMessage("Invalid File");
			return;
		}
		while (fread(&dltMember[count], sizeof(Member), 1, findMember) != 0) //read to array structure
			count++;

		fclose(findMember);

		getMemberId(memberInput);

		for (int i = 0; i < count; i++)
		{
			if (strcmp(memberInput, dltMember[i].memberId) == 0)
			{
				printf("\n\t\t\t\t\tMember ID              : %s\n", dltMember[i].memberId);
				printf("\t\t\t\t\tName                   : %s\n", dltMember[i].name);
				printf("\t\t\t\t\tMember IC              : %s\n", dltMember[i].icNo);
				printf("\t\t\t\t\tGender                 : ");
				if (toupper(dltMember[i].gender) == 'M')
					printf("Male\n");
				else
					printf("Female\n");
				printf("\t\t\t\t\tContact Number         : %s\n", dltMember[i].contactNo);
				printf("\t\t\t\t\tEmail                  : %s\n", dltMember[i].email);
				printf("\t\t\t\t\tAddress                : %s\n", dltMember[i].address);
				printf("\t\t\t\t\tMember Type            : ");
				if (toupper(dltMember[i].memberType == 'N'))
					printf("Normal\n");
				else if (toupper(dltMember[i].memberType == 'G'))
					printf("Gold\n");
				else if (toupper(dltMember[i].memberType == 'P'))
					printf("Platinum\n");
				else
					printf("Diamond\n");
				printf("\t\t\t\t\tJoined Date (DD/MM/YY) : %02d/%02d/%02d\n", dltMember[i].joinDate.day, dltMember[i].joinDate.month, dltMember[i].joinDate.year);

				found = 1;
			}
		}

		if (found == 1)
		{
			getYesNo("Confirm Delete (Y/N) > ", &choice);

			if (toupper(choice) == 'Y') {

				deleteMember = fopen("member.bin", "wb");
				if (deleteMember == NULL) {
					errorMessage("Invalid File");
					system("pause");
					return;
				}

				for (int i = 0; i < count; i++)
				{
					if (strcmp(memberInput, dltMember[i].memberId) == 0)
					{
						if (toupper(choice) == 'Y') {
							green();
							printf("\n%51s Had Been Deleted.\n", dltMember[i].memberId); //if yes, do not write to binary file
							defaultcolor();
						}
						else {
							fwrite(&dltMember[i], sizeof(Member), 1, deleteMember); //if the member dun want to delete, write back to the file 		
						}
					}
					else
						fwrite(&dltMember[i], sizeof(Member), 1, deleteMember);
				}
				fclose(deleteMember);


			}

			getYesNo("Others Delete ? (Y/N) > ", &option);

			if (toupper(option) == 'N')
			{
				printf("Will Automatic return back to Member Menu\n\n\n");
				system("pause");
			}

		}
		else {
			errorMessage("Invalid Id because not exist in system");
			option = 'N';
			system("pause");
		}

	} while (toupper(option) != 'N');
}

void memberModify() {
	system("cls");
	logo();
	header("Edit Member Detail");
	char memberInput[31], memberName[100];
	int choice = 0;
	int count = 0, found = 0, j = 0;

	Member memberInfo[100];
	Member tempMember;
	FILE* findMember;
	FILE* modifyMember;

	int error, block, autoConfirm;
	char option;

	findMember = fopen("member.bin", "rb");
	if (findMember == NULL)
	{
		errorMessage("Invalid File");
		return;
	}
	while (fread(&memberInfo[count], sizeof(Member), 1, findMember) != 0) //read to array structure
		count++;

	fclose(findMember);

	printf("\n\n%92s\n", "Notice: You Must Enter Member ID To Modify The Selected Member Data.");
	getMemberId(memberInput);


	do {
		found = 0;
		j = 0;
		choice = 0;
		option = 'N';
		system("cls");

		for (int i = 0; i < count; i++)
		{
			if (strcmp(memberInput, memberInfo[i].memberId) == 0)
			{
				tempMember = memberInfo[i];
				found = 1;
				j = i;
				break;
			}
		}

		if (strcmp(memberInput, memberInfo[j].memberId) == 0)
		{

			system("cls");
			logo();
			header("Edit Member Detail");
			printf("%61s %s\n", "Member ID :", memberInfo[j].memberId);
			printf("%74s", "Which Data You Want To Edit?");
			printf("\n\n\t\t\t\t\t1. Name                   : %s", tempMember.name);
			printf("\n\t\t\t\t\t2. Ic no                  : %s", tempMember.icNo);
			printf("\n\t\t\t\t\t3. Gender                 : ");
			if (tempMember.gender == 'M')
				printf("Male\n");
			else
				printf("Female\n");
			printf("\t\t\t\t\t4. Contact Number         : %s", tempMember.contactNo);
			printf("\n\t\t\t\t\t5. Email                  : %s", tempMember.email);
			printf("\n\t\t\t\t\t6. Address                : %s", tempMember.address);
			printf("\n\t\t\t\t\t7. Member Type            : ");
			if (tempMember.memberType == 'N')
				printf("Normal\n");
			else if (tempMember.memberType == 'G')
				printf("Gold\n");
			else if (tempMember.memberType == 'P')
				printf("Platinum\n");
			else
				printf("Diamond\n");
			printf("\t\t\t\t\t0. Return To Member Menu\n");
			choice = getInteger(7);


			if (found == 1) {
				autoConfirm = 0;
				block = 0;

				switch (choice)
				{
				case 1:
					printf("\n\n========================================================================================================================\n\n");
					getName(tempMember.name);
					break;
				case 2:
					printf("\n\n========================================================================================================================\n\n");
					getIC(tempMember.icNo);
					break;
				case 3:
					printf("\n\n========================================================================================================================\n\n");
					if (tempMember.gender == 'M') {

						getYesNo("\n\t\t\tChange To Female? (Y/N)   > ", &option);
						if (toupper(option) == 'Y')
						{
							tempMember.gender = 'F';
							autoConfirm = 1;
						}
						else
							autoConfirm = 2;
					}
					else {

						getYesNo("\n\t\t\tChange To Male? (Y/N)     > ", &option);
						if (toupper(option) == 'Y')
						{
							tempMember.gender = 'M';
							autoConfirm = 1;
						}
						else
							autoConfirm = 2;
					}

					break;
				case 4:
					printf("\n\n========================================================================================================================\n\n");
					getContact(tempMember.contactNo);
					break;
				case 5:
					printf("\n\n========================================================================================================================\n\n");
					getEmail(tempMember.email);
					break;
				case 6:
					printf("\n\n========================================================================================================================\n\n");
					getAddress(tempMember.address);
					break;
				case 7:
					printf("\n\n========================================================================================================================\n\n");
					getType(tempMember.memberType, &tempMember.memberType, memberInfo[j].memberId, 2);
					break;
				case 0:
					block = 1;
					option = 'N';
					break;

				}


				if (block == 0) {

					if (autoConfirm == 1) //auto set option to Y or N
						option = 'Y';
					else if (autoConfirm == 2)
						option = 'N';
					else
					{
						printf("\n\n========================================================================================================================\n\n");
						getYesNo("\n\t\t\tConfirm To Edit? (Y/N)            > ", &option);
					}

					// confirm edit or No edit
					if (toupper(option) == 'Y')
					{
						modifyMember = fopen("member.bin", "wb");
						if (modifyMember == NULL)
						{
							errorMessage("Invalid File");
						}
						else {

							memberInfo[j] = tempMember; //store back to array

							for (int i = 0; i < count; i++) {	//store to binary file
								fwrite(&memberInfo[i], sizeof(Member), 1, modifyMember);
							}

							fclose(modifyMember);
							printf("\n%75s\n", "Member Data Successfully Edited.");

							printf("\n========================================================================================================================\n\n");
							system("cls");
						}
					}
					else {
						printf("\n%72s\n", "No Change In Member Data.");
						printf("\n========================================================================================================================\n\n");

					}

				}
			}

		}
		else {
			errorMessage("Invalid Id because not exist in system");
			system("pause");
		}

	} while (choice != 0);

}

void memberDisplayAll() {
	Member displayAll;

	system("cls");
	logo();

	int count = 0;
	Member memberInfo;
	FILE* displayMember;
	displayMember = fopen("member.bin", "rb");
	if (displayMember == NULL)
	{
		errorMessage("Invalid File");
		return;
	}
	else
	{
		header("All Member Data");
		printf(" =======================================================================================================================\n");
		printf("  Member ID   Name        Gender     Contact Number    Email                   Member Type    Upline ID    Join Date         \n");
		printf(" =======================================================================================================================\n");
		while (fread(&memberInfo, sizeof(Member), 1, displayMember) != 0)
		{
			count++;
			printf("  %-9s   %-12s", memberInfo.memberId, memberInfo.name);
			if (memberInfo.gender == 'M')
				printf("%-10s", "Male");
			else
				printf("%-10s", "Female");
			printf(" %-15s   %-24s", memberInfo.contactNo, memberInfo.email);
			if (memberInfo.memberType == 'N')
				printf("%-15s", "Normal");
			else if (memberInfo.memberType == 'G')
				printf("%-15s", "Gold");
			else if (memberInfo.memberType == 'P')
				printf("%-15s", "Platinum");
			else
				printf("%-15s", "Diamond");
			printf("%-13s", memberInfo.uplineId);
			printf("%02d/%02d/%02d\n", memberInfo.joinDate.day, memberInfo.joinDate.month, memberInfo.joinDate.year);
		}

		fclose(displayMember);
		printf(" =====================================================================================================================\n");
		printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t< %d Member Listed >\n\n", count);
		system("pause");

	}
}

void memberTypeAdv() {

	Member memberInfo[100];
	Member tempMember;
	FILE* adv;
	FILE* changeType;

	int i, k, found = 0;
	char memberId[30];
	char choice, yesNo, valid;


	do {
		i = 0;
		k = 0;
		found = 0;
		system("cls");
		logo();
		header("Member Type Change");
		printf("\n%75s\n", "Notice: You Must Enter Member ID To Make Changes");
		printf("================================================================================================\n\n");

		printf("%75s\n", "============================================");
		printf("%44s %30s\n", "Type", "Discount per payment");
		printf("%75s\n", "============================================");
		printf("%38s %10s %15d%% %s\n ", "||", "N (Normal)", 0, "||");
		printf("%37s %8s %17d%% %s\n ", "||", "G (Gold)", 2, "||");
		printf("%37s %10s %13d%% %s\n ", "||", "P (Platinum)", 5, "||");
		printf("%37s %11s %14d%% %s\n ", "||", "D (Diamond)", 9, "||");
		printf("%74s\n\n", "============================================");

		getYesNo("Would you like to make changes on your member type? (Y/N) --> Back to member menu) > ", &choice);
		printf("\n");
		rewind(stdin);
		yesNo = 'N';
		choice = toupper(choice);

		if (choice == 'Y') {
			do {
				adv = fopen("member.bin", "rb");
				if (adv == NULL) {
					errorMessage("Invalid File");
					return;
				}
				valid = 'Y';
				getMemberId(memberId);
				while (fread(&memberInfo[k], sizeof(Member), 1, adv) != 0)
					k++;
				fclose(adv);
				for (i = 0; i < k; i++)
				{
					if (strcmp(memberId, memberInfo[i].memberId) == 0) {
						tempMember = memberInfo[i];
						found = 1;
						break;
					}
				}
				changeType = fopen("member.bin", "wb");
				if (found == 1) {
					
					getType(tempMember.memberType, &tempMember.memberType, tempMember.memberId, 2);
					memberInfo[i] = tempMember;
					for (i = 0; i < k; i++)
						fwrite(&memberInfo[i], sizeof(Member), 1, changeType);
					getYesNo("\n\n\t\t\tDo you like to make changes on other member? (Y/N) > ", &yesNo);

				}
				else
				{
					errorMessage("Invalid Member");
					valid = 'N';
				}
				fclose(changeType);
			} while (valid == 'N');
		}
	} while (toupper(yesNo) == 'Y');
}

void memberComm() {

	system("cls");
	logo();
	header("Upline Member Commission");
	Member memberInfo[MAXSTORAGE];
	Date currentDate;


	systemDate(&currentDate);
	int countSales = 0, countMember = 0;
	double totalComm;

	FILE* findMember;
	findMember = fopen("member.bin", "rb");
	if (findMember == NULL)
	{
		errorMessage("Invalid File");
		return;
	}
	while (fread(&memberInfo[countMember], sizeof(Member), 1, findMember) != 0) //read to array structure
		countMember++;

	fclose(findMember);

	FILE* readSales;
	readSales = fopen("fileSales.txt", "r");
	if (readSales == NULL)
	{
		errorMessage("Invalid File");
		return;
	}

	typeSales SalesInfo[MAXSTORAGE];
	while (!feof(readSales)) {
		fscanf(readSales, "%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d,%d,%d,%lf,%d,%lf,%lf,%lf\n",
			&SalesInfo[countSales].orderId,
			&SalesInfo[countSales].itemId,
			&SalesInfo[countSales].memberId,
			&SalesInfo[countSales].staffId,
			&SalesInfo[countSales].dateTime.year,
			&SalesInfo[countSales].dateTime.mon,
			&SalesInfo[countSales].dateTime.day,
			&SalesInfo[countSales].dateTime.hour,
			&SalesInfo[countSales].dateTime.min,
			&SalesInfo[countSales].dateTime.sec,
			&SalesInfo[countSales].price,
			&SalesInfo[countSales].qty,
			&SalesInfo[countSales].discount,
			&SalesInfo[countSales].com,
			&SalesInfo[countSales].total);

		countSales++;
	}

	fclose(readSales);

	char isEmpty = 'Y';
	printf("\t\t\t\t======================================================\n");
	printf("\t\t\t\t| Upline Member       Downline Member     Commission |\n");
	printf("\t\t\t\t======================================================\n");
	for (int i = 0; i < countMember; i++) {

		totalComm = 0;

		if (strcmp(memberInfo[i].uplineId, "None") == 0)
			continue;

		else {
			for (int j = 0; j < countSales; j++) {

				if (strcmp(memberInfo[i].memberId, SalesInfo[j].memberId) == 0 &&
					currentDate.month == SalesInfo[j].dateTime.mon &&
					currentDate.year == SalesInfo[j].dateTime.year)
					totalComm += SalesInfo[j].com;
			}

			if (totalComm > 0) {
				printf("\t\t\t\t| %s               %s               RM %7.2f |\n", memberInfo[i].uplineId, memberInfo[i].memberId, totalComm);
				isEmpty = 'N';
			}

		}
	}
	if (isEmpty == 'Y') {
		printf("\t\t\t\t| No comission data!                                 |\n");
	}
	printf("\t\t\t\t======================================================\n");
	printf("\t\t\t\t");
	system("pause");
}

void memberMonthlyChange() {
	Member monthlyMember;
	char valid, choice, charMonth[5], charLastMonth[5];
	int month, lastMonth, year;
	int lastYear, diff, normal1, normal2, gold1, gold2, plat1, plat2, dia1, dia2, normal, gold, platinum, diamond;
	int count1 = 0, count2 = 0;

	double changes = 0;

	FILE* check;
	do
	{

		count1 = 0;
		count2 = 0;
		normal1 = 0;
		normal2 = 0;
		gold1 = 0;
		gold2 = 0;
		plat1 = 0;
		plat2 = 0;
		dia1 = 0;
		dia2 = 0;
		normal = 0;
		gold = 0;
		platinum = 0;
		diamond = 0;
		valid = 'N';
		choice = 'N';
		check = fopen("member.bin", "rb");

		if (check == NULL)
		{
			errorMessage("Invalid File");
			return;
		}

		system("cls");
		logo();
		header("Member Monthly Change");
		rewind(stdin);

		printf("%15s\n", "Notice : You can only view record year after 2022");
		printf("================================================================================================\n\n");
		printf("\n\t\tEnter Month (Only number is allowed eg. 1=Jan, 2=Feb, ..., 12=Dec) \n\n");
		month = getIntegerFromOne(12);
		do {
			printf("\n\t\tEnter Full Year (starting from 2022 only)\n\n");
			year = getInteger(2023);
			if (year < 2022) {
				errorMessage("Invalid Input");
				delay(0.5);
				valid = 'N';
			}
			else
			{
				valid = 'Y';
			}
		} while (valid == 'N');



		switch (month)
		{
		case 1:
			strcpy(charMonth, "JAN");
			strcpy(charLastMonth, "DEC");
			break;
		case 2:
			strcpy(charMonth, "FEB");
			strcpy(charLastMonth, "JAN");
			break;
		case 3:
			strcpy(charMonth, "MAR");
			strcpy(charLastMonth, "FEB");
			break;
		case 4:
			strcpy(charMonth, "APR");
			strcpy(charLastMonth, "MAR");
			break;
		case 5:
			strcpy(charMonth, "MAY");
			strcpy(charLastMonth, "APR");
			break;
		case 6:
			strcpy(charMonth, "JUN");
			strcpy(charLastMonth, "MAY");
			break;
		case 7:
			strcpy(charMonth, "JUL");
			strcpy(charLastMonth, "JUN");
			break;
		case 8:
			strcpy(charMonth, "AUG");
			strcpy(charLastMonth, "JUL");
			break;
		case 9:
			strcpy(charMonth, "SEP");
			strcpy(charLastMonth, "AUG");
			break;
		case 10:
			strcpy(charMonth, "OCT");
			strcpy(charLastMonth, "SEP");
			break;
		case 11:
			strcpy(charMonth, "NOV");
			strcpy(charLastMonth, "OCT");
			break;
		case 12:
			strcpy(charMonth, "DEC");
			strcpy(charLastMonth, "NOV");
			break;
		}

		if (month == 1)
		{
			lastMonth = 12;
			lastYear = year - 1;
		}
		else {
			lastMonth = month - 1;
			lastYear = year;
		}

		while (fread(&monthlyMember, sizeof(Member), 1, check))
		{
			if (year == monthlyMember.joinDate.year)
			{
				if (month == monthlyMember.joinDate.month) {
					count1++;
					if (monthlyMember.memberType == 'N')
						normal1++;
					else if (monthlyMember.memberType == 'G')
						gold1++;
					else if (monthlyMember.memberType == 'P')
						plat1++;
					else
						dia1++;
				}
			}
			if (lastYear == monthlyMember.joinDate.year) {
				if (lastMonth == monthlyMember.joinDate.month) {
					count2++;
					if (monthlyMember.memberType == 'N')
						normal2++;
					else if (monthlyMember.memberType == 'G')
						gold2++;
					else if (monthlyMember.memberType == 'P')
						plat2++;
					else
						dia2++;
				}
			}
		}

		normal = normal1 - normal2;
		gold = gold1 - gold2;
		platinum = plat1 - plat2;
		diamond = dia1 - dia2;

		diff = count1 - count2;
		if (count2 > 0)
			changes = diff / (double)count2; // changes of the input year based on the previous month

		system("cls");
		printf("\n\n");
		printf("\t\t%s %d compared to last month (%s %d)\n\n", charMonth, year, charLastMonth, lastYear);
		printf("\t\t");
		if (count1 == 0 && count2 == 0) {
			printf("\n\t\t\t\t%s\n", "==============================================");
			printf("\n\t\t\t\t\t%s\n", "NO RECORD FOR THESE TWO MONTHS");
			printf("\n\t\t\t\t%s\n", "==============================================");
		}
		else
		{
			if (count2 != 0) {
				if (diff > 0)
					printf("( Difference:  + %d member(s) (+ %.2f%%) )\n", diff, changes * 100);
				else
					printf("( Difference:   %d member(s) (%.2f%%) )\n", diff, changes * 100);
			}
			else //another output as denominator cannot be zero
			{
				if (diff > 0)
					printf("( Difference:  + %d member(s) )\n", diff);
				else
					printf("( Difference:   %d member(s) )\n", diff);
			}
			printf("\n\n\n");
			printf("%55s %s %d", "MEMBER OF", charMonth, year);
			printf("\n\t\t\t\t%s\n", "==============================================");
			printf("%34s %s %s\n", "||", "NORMAL * * GOLD * * PLATINUM * * DIAMOND", "||");
			printf("\t\t\t\t%s\n", "==============================================");
			printf("%34s %s +%d %7s +%d %7s +%d %8s +%d  %4s          \n", "||", "", normal1, "", gold1, "", plat1, "", dia1, "||");
			printf("\t\t\t\t%s\n", "==============================================");
			printf("\t\t\t\t%s %d\n", "TOTAL MEMBER(S): ", count1);
		}

		getYesNo("\nWould you like to have a look on another record?(Y/N) > ", &choice);

		choice = toupper(choice);
	} while (choice == 'Y');
}

// member validation and some validation from staff module do together by teamwork
void getType(char memberType, char* newMemberType, char id[], int m) {
	Member memberInfo;
	char valid, lastType, newType, checkspace;
	int choice = 0;
	lastType = memberType;
	do {
		valid = 'Y';
		rewind(stdin);
		printf("\t\t\tEnter Member Type To Be Chosen ( N(Normal)/G(Gold)/P(Platinum)/D(Diamond) ) > ");	
		scanf("%c%c", &*newMemberType, &checkspace);

		*newMemberType = toupper(*newMemberType);
		newType = *newMemberType;
		if (checkspace != '\n') {
			errorMessage("Invalid input, just one character");
			valid = 'N';
		}
		else {
			if (m == 1)
				valid = newValidation(newType);
			else {
				valid = newValidation(newType);
				if (newType == 'N' || newType == 'G' || newType == 'P' || newType == 'D')
					valid = typeValidation(lastType, newType, id);
			}
		}
	} while (valid == 'N');

}

void getMemberAddress(char inputAddress[]) {
	int error = 0;

	do
	{
		error = 0;
		rewind(stdin);
		printf("\t\t\tEnter Member Address > ");
		gets(inputAddress);

		if (strlen(inputAddress) == 0) {
			error = 1;
			red();
			printf("\t\t\tShould be fill in the address\n");
			defaultcolor();
		}


	} while (error != 0);
}

void getMemberId(char memberId[]) {
	int error;
	do
	{
		error = 0;
		rewind(stdin);
		printf("\t\t\tEnter Member Id > ");
		gets(memberId);
		
		for (int i = 1; i < strlen(memberId); i++)
		{
			if (!isspace(memberId[i]) && !isdigit(memberId[i]))
				error = 1;
		}


		if (strlen(memberId) == 0)
			error = 2;
		else if (memberId[0] != 'M')
			error = 3;

		switch (error)
		{
		case 1:
			red();
			printf("\t\t\tPlease do not enter simbol or alphabet at id numeric code M\"0001\" .\n");
			defaultcolor();
			break;

		case 2:
			red();
			printf("\t\t\tPlease do not leave it at blank.\n");
			defaultcolor();
			break;
		case 3:
			red();
			printf("\t\t\tMust start with M.\n");
			defaultcolor();
			break;

		}

	} while (error != 0);
}

void generateMemberId(char inputId[]) {

	char newnum[7];
	char lastid[10];
	int lastnum;

	FILE* countId;
	Member memberData;
	countId = fopen("member.bin", "rb");

	if (countId == NULL)
	{
		errorMessage("File");
		return;
	}
	else
	{
		while (fread(&memberData, sizeof(Member), 1, countId) != 0)
		{
			strcpy(lastid, &memberData.memberId[1]);
		}

		lastnum = atoi(lastid); //convert to integer

		itoa(lastnum + 1, newnum, 10); // convert to string 

		if (strlen(newnum) == 2)
		{
			strcat(inputId, "00");
			strcat(inputId, newnum);
		}
		else if (strlen(newnum) == 3)
		{
			strcat(inputId, "0");
			strcat(inputId, newnum);
		}
		else if (strlen(newnum) == 4)
		{
			strcat(inputId, newnum);
		}
		else
		{
			strcat(inputId, "000");
			strcat(inputId, newnum);
		}
	}

	fclose(countId);
}

int getIntegerFromOne(int range) {

	int choice, input;
	char checkspace;

	do {
		rewind(stdin);
		printf("\t\t\tEnter your choice > ");
		input = scanf("%d%c", &choice, &checkspace);			 //scanf should return value 2 for integer type;
		if (choice <= 0 || choice > range || input != 2 || checkspace != '\n') {
			errorMessage("Invalid Input");
		}
	} while (choice <= 0 || choice > range || input != 2 || checkspace != '\n');

	return choice;
}

char typeValidation(char oldMemberType, char memberType, char id[]) {

	memberType = toupper(memberType);
	oldMemberType = toupper(oldMemberType);

	if (oldMemberType == 'N')
	{
		printf("\t\t\tYou are a Normal member.\n");
		delay(0.2);
		blue();
		printf("\t\t\tVerifying");
		delay(0.6);
		printf(".");
		delay(0.6);
		printf(".");
		delay(0.6);
		printf(".\n");
		defaultcolor();
		printf("\t\t\t");
		if (memberType == 'G') {
			green();
			printf("Congratulation! You %s are now a Gold member! ", id);
			defaultcolor();
		}
		else if (memberType == 'P')
		{
			green();
			printf("Congratulation! You %s are now a Platinum member! ", id);
			defaultcolor();
		}
		else if (memberType == 'D')
		{
			green();
			printf("Congratulation! You %s are now a Diamond member! ", id);
			defaultcolor();
		}
		else
		{
			errorMessage("Invalid Choice! You are already a Normal member");
			return 'N';
		}

	}
	else if (oldMemberType == 'G')
	{
		printf("\t\t\tYou are a Gold member.\n");
		delay(0.2);
		blue();
		printf("\t\t\tVerifying");
		delay(0.6);
		printf(".");
		delay(0.6);
		printf(".");
		delay(0.6);
		printf(".\n");
		defaultcolor();
		printf("\t\t\t");
		if (memberType == 'P')
		{
			green();
			printf("Congratulation! You %s are now a Platinum member! ", id);
			defaultcolor();
		}
		else if (memberType == 'D')
		{
			green();
			printf("Congratulation! You %s are now a Diamond member! ", id);
			defaultcolor();
		}
		else if (memberType == 'N') {
			green();
			printf("Congratulation! You %s are now a Normal member! ", id);
			defaultcolor();
		}
		else
		{
			errorMessage("Invalid Choice! You are already a Gold member");
			return 'N';
		}


	}
	else if (oldMemberType == 'P')
	{
		printf("\t\t\tYou are a Platinum member.\n");
		delay(0.2);
		blue();
		printf("\t\t\tVerifying");
		delay(0.6);
		printf(".");
		delay(0.6);
		printf(".");
		delay(0.6);
		printf(".\n");
		defaultcolor();
		printf("\t\t\t");
		if (memberType == 'G')
		{
			green();
			printf("Congratulation! You %s are now a Gold member! ", id);
			defaultcolor();
		}
		else if (memberType == 'D')
		{
			green();
			printf("Congratulation! You %s are now a Diamond member! ", id);
			defaultcolor();
		}
		else if (memberType == 'N') {
			green();
			printf("Congratulation! You %s are now a Normal member! ", id);
			defaultcolor();
		}
		else
		{
			errorMessage("Invalid Choice! You are already a Platinum member");
			return 'N';
		}
	}
	else if (oldMemberType == 'D')
	{
		printf("\t\t\tYou are a Diamond member.\n");
		delay(0.2);
		blue();
		printf("\t\t\tVerifying");
		delay(0.6);
		printf(".");
		delay(0.6);
		printf(".");
		delay(0.6);
		printf(".\n");
		defaultcolor();
		printf("\t\t\t");
		if (memberType == 'G')
		{
			green();
			printf("Congratulation! You %s are now a Gold member! ", id);
			defaultcolor();
		}
		else if (memberType == 'P')
		{
			green();
			printf("Congratulation! You %s are now a Platinum member! ", id);
			defaultcolor();

		}
		else if (memberType == 'N') {
			green();
			printf("Congratulation! You %s are now a Normal member! ", id);
			defaultcolor();
		}
		else
		{
			errorMessage("Invalid Choice! You are already a Diamond member");
			return 'N';
		}

	}
	else {
		errorMessage("Invalid Input");
		return 'N';
	}

}

char newValidation(char memberType) {

	memberType = toupper(memberType);

	if (!isalpha(memberType) && !isdigit(memberType))
	{
		errorMessage("Invalid Character! No Special Character Is Allowed");
		return 'N';
	}
	else if (!(memberType >= 'A' && memberType <= 'Z')) {
		errorMessage("Invalid Digit! No Digit Is Allowed");
		return 'N';
	}
	else if (memberType != 'N' && memberType != 'G' && memberType != 'P' && memberType != 'D') {
		errorMessage("Invalid Type! Only N,G,P and D Are Allowed");
		return 'N';
	}
	else
		return 'Y';
}

void getUplineId(char uplineId[]) {
	int error;
	FILE* findUplineId;
	Member findMember;

	do
	{
		error = 4;
		rewind(stdin);
		printf("\t\t\tEnter Upline Id > ");
		gets(uplineId);
		printf("\t\t\t");

		findUplineId = fopen("member.bin", "rb");

		if (findUplineId == NULL) {
			errorMessage("Invalid File! ");
			return;
		}

		for (int i = 1; i < strlen(uplineId); i++)
		{
			if (!isspace(uplineId[i]) && !isdigit(uplineId[i]))
				error = 1;
		}

		if (strlen(uplineId) == 0)
			error = 2;
		else if (uplineId[0] != 'M')
			error = 3;

		while (fread(&findMember, sizeof(Member), 1, findUplineId) != 0) {
			if (strcmp(uplineId, findMember.memberId) == 0) {
				error = 0;
			}
		}
		fclose(findUplineId);

		switch (error)
		{
		case 1:
			red();
			printf("Please do not enter simbol or alphabet at id numeric code M\"0001\" .\n");
			defaultcolor();
			break;

		case 2:
			red();
			printf("Please do not leave it at blank.\n");
			defaultcolor();
			break;
		case 3:
			red();
			printf("Must start with M.\n");
			defaultcolor();
			break;
		case 4:
			red();
			printf("The member ID is not in the system.\n");
			defaultcolor();
			break;
		}

	} while (error != 0);

}

#pragma endregion


#pragma region salesModule-Fadhil

//main function for sales module
int mainSales() {

	FILE* fileSales = NULL;
	typeSales arrSales[100] = { NULL };
	getIndex(-99);
	getIndex(0);
	int index = 0;

	//fileSales open and load
	fileSales = fopen("filesales.txt", "r");

	//if file doesnt exist, create new
	if (fileSales == NULL) {
		system("cls");
		logo();
		header("\n\t\t\tSales Management System\n\n");
		printf("\t\t\tSales module file did not exist.\n\n");
		printf("\t\t\tA new module file will be created. ");
		system("pause");

		fileSales = fopen("filesales.txt", "w");

		//if couldnt create new, return
		if (fileSales == NULL) {
			system("cls");
			logo();
			header("\t\t\tSales Management System\n\n");
			printf("\t\t\tModule file creation is unsuccessful.\n\n");
			printf("\t\t\tSales module will be unusable. ");
			system("pause");
			return -1;
		}
	}
	else {

		while (!feof(fileSales)) {
			if (fscanf(fileSales, "%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d,%d,%d,%lf,%d,%lf,%lf,%lf\n",
				&arrSales[index].orderId,
				&arrSales[index].itemId,
				&arrSales[index].memberId,
				&arrSales[index].staffId,
				&arrSales[index].dateTime.year,
				&arrSales[index].dateTime.mon,
				&arrSales[index].dateTime.day,
				&arrSales[index].dateTime.hour,
				&arrSales[index].dateTime.min,
				&arrSales[index].dateTime.sec,
				&arrSales[index].price,
				&arrSales[index].qty,
				&arrSales[index].discount,
				&arrSales[index].com,
				&arrSales[index].total) == 15);

			index++;
		}

		if (strcmp(arrSales[0].orderId, "") == 0)
			index = 0;

		getIndex(index);
	}
	fclose(fileSales);

	//menu selection
	char sel = '0';
	system("cls");
	do {
		if (sel != 'X') {
			logo();
			header("Sales Management System");
			printf("\t\t\tView      [V]\n\n");
			printf("\t\t\tSearch    [S]\n\n");
			printf("\t\t\tAdd       [A]\n\n");
			printf("\t\t\tModify    [M]\n\n");
			printf("\t\t\tDelete    [D]\n\n");
			printf("\t\t\tReport    [R]\n\n");
			printf("\t\t\tExit      [E]\n\n");
		}

		//select module
		printf("\t\t\tPlease select : ");
		rewind(stdin);
		sel = getchar();
		sel = toupper(sel);

		switch (sel) {
		case 'V':
			system("cls");
			logo();
			header("View Sales");
			viewSales(&arrSales);
			printf("\n");
			system("pause");
			system("cls");
			break;
		case 'S':
			system("cls");
			logo();
			header("Search Sales");
			searchSales(&arrSales);
			printf("\n");
			system("pause");
			system("cls");
			break;
		case 'A':
			system("cls");
			logo();
			header("Add Sales");
			addSales(&arrSales);
			printf("\n");
			system("pause");
			system("cls");
			break;
		case 'M':
			system("cls");
			logo();
			header("Modify Sales");
			modifySales(&arrSales);
			printf("\n");
			system("pause");
			system("cls");
			break;
		case 'D':
			system("cls");
			logo();
			header("Delete Sales");
			deleteSales(&arrSales);
			printf("\n");
			system("pause");
			system("cls");
			break;
		case 'R':
			system("cls");
			logo();
			header("Report Sales");
			reportSales(&arrSales);
			printf("\n");
			system("pause");
			system("cls");
			break;
		case 'E':
			break;
		default:
			color('R');
			printf("\t\t\tInvalid. ");
			system("pause");
			color('X');
			printf("\n");
			sel = 'X';
		}
	} while (sel != 'E');

	fileSales = fopen("filesales.txt", "w");
	for (int a = 0; a < getIndex(0); a++) {
		fprintf(fileSales, "%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%lf,%d,%lf,%lf,%lf\n",
			arrSales[a].orderId,
			arrSales[a].itemId,
			arrSales[a].memberId,
			arrSales[a].staffId,
			arrSales[a].dateTime.year,
			arrSales[a].dateTime.mon,
			arrSales[a].dateTime.day,
			arrSales[a].dateTime.hour,
			arrSales[a].dateTime.min,
			arrSales[a].dateTime.sec,
			arrSales[a].price,
			arrSales[a].qty,
			arrSales[a].discount,
			arrSales[a].com,
			arrSales[a].total);
	}
	fclose(fileSales);

	return 0;
}

//view sales function
void viewSales(typeSales* ptrArrSales) {

	printf("Sales Information Module > View Sales\n");
	printf("\n");

	if (getIndex(0) > 0) {
		color('B');
		printHeader();
		for (int a = 0; a < getIndex(0); a++) {
			printByArrNum(ptrArrSales, a);
		}
		printFooter(getIndex(0));
		color('X');
	}
	else {
		color('R');
		printf("Sales data empty!\n");
		color('X');
	}
}

//search sales function
void searchSales(typeSales* ptrArrSales) {

	char rep = 'Y';
	do {
		printf("Enter order ID  : ");
		char orderId[6];
		rewind(stdin);
		scanf("%[^\n]", &orderId);

		//check if orderId exist
		int found = 0;
		color('B');
		found = printByOrderId(ptrArrSales, orderId);
		color('X');

		if (found == 0) {
			color('R');
			printf("No sales found! Continue search? [Y/N] : ");
			color('X');
		}
		else {
			printf("Continue search? [Y/N] : ");
		}

		rewind(stdin);
		rep = getchar();
		rep = toupper(rep);

	} while (rep == 'Y');
}

//point of sale system to add new sales
void addSales(typeSales* ptrArrSales) {

	typeSales buffer = { "\0","\0","\0","\0",0,0,0,0,0,{0,0,0,0,0,0} };

	//get current date and time
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	buffer.dateTime.year = tm.tm_year + 1900;
	buffer.dateTime.mon = tm.tm_mon + 1;
	buffer.dateTime.day = tm.tm_mday;
	buffer.dateTime.hour = tm.tm_hour;
	buffer.dateTime.min = tm.tm_min;
	buffer.dateTime.sec = tm.tm_sec;

	printf("Date : %04d-%02d-%02d | Time : %02d:%02d:%02d\n",
		buffer.dateTime.year,
		buffer.dateTime.mon,
		buffer.dateTime.day,
		buffer.dateTime.hour,
		buffer.dateTime.min,
		buffer.dateTime.sec);

	//check memberId and get discount
	int memberDiscount;
	do {
		printf("Enter member ID          : ");
		rewind(stdin);
		scanf("%[^\n]", &buffer.memberId);

		memberDiscount = getMemberDiscount(buffer.memberId);
		if (memberDiscount == -1) {
			color('R');
			printf("Invalid. ");
			color('X');
		}
		else if (memberDiscount == -2) {
			color('R');
			printf("File error!\n");
			system("pause");
			color('X');
			return;
		}
	} while (memberDiscount == -1);

	//check staffId
	char valid;
	do {
		printf("Enter staff ID           : ");
		rewind(stdin);
		scanf("%[^\n]", &buffer.staffId);

		valid = checkStaffId(buffer.staffId);
		if (valid == 'N') {
			color('R');
			printf("Invalid. ");
			color('X');
		}
		else if (valid == 'F') {
			color('R');
			printf("File error!\n");
			system("pause");
			color('X');
			return;
		}
	} while (valid == 'N');

	//get current orderId from last orderId in array
	sprintf(buffer.orderId, "P%04d", getNum(ptrArrSales[getIndex(0) - 1].orderId) + 1);
	printf("Order ID                 : %s\n", buffer.orderId);

	int startArr = getIndex(0);
	int currentArr = getIndex(0);
	int duplicateArr;

	double total = 0;
	double discount = 0;
	double grandTotal = 0;
	double commission = 0;

	char cont = 'Y';
	do {
		//check itemId and get price
		printf("\n");
		do {
			printf("Enter item ID [E to exit]: ");
			rewind(stdin);
			scanf("%[^\n]", &buffer.itemId);

			//check to exit
			if (strcmp(buffer.itemId, "E") == 0) {
				cont = 'N';
				break;
			}

			buffer.price = getItemPrice(buffer.itemId);
			if (buffer.price == -1) {
				color('R');
				printf("Invalid. ");
				color('X');
			}
			else if (buffer.price == -2) {
				color('R');
				printf("File error!\n");
				system("pause");
				color('X');
				return;
			}
		} while (buffer.price == -1);

		//exit item choose
		if (cont == 'N')
			break;

		//check qty
		do {
			printf("Enter item quantity      : ");
			buffer.qty = 0;
			rewind(stdin);
			scanf("%d", &buffer.qty);

			if (buffer.qty > 0)
				break;
			else {
				color('R');
				printf("Invalid. ");
				color('X');
				continue;
			}
		} while (1);

		//check duplicate itemId and combine
		duplicateArr = -1;
		for (int a = startArr; a < currentArr; a++) {
			if (strcmp(ptrArrSales[a].orderId, buffer.orderId) == 0 &&
				strcmp(ptrArrSales[a].itemId, buffer.itemId) == 0)
				duplicateArr = a;
		}

		//duplicate values sum
		if (duplicateArr != -1) {
			buffer.qty += ptrArrSales[duplicateArr].qty;
		}

		//calculate values
		calculateValues(&buffer);

		//assign values
		ptrArrSales[currentArr] = buffer;
		getIndex(1);

		//resolve duplicate
		if (duplicateArr != -1) {
			deleteByArrNum(ptrArrSales, duplicateArr);
			currentArr--;
		}

		currentArr++;
	} while (cont == 'Y');

	//message if exit
	if (currentArr - startArr == 0) {
		color('R');
		printf("No sales added!\n");
		color('X');
	}

	else {
		//sale summary calculation
		for (int a = startArr; a < currentArr; a++)
			total += (ptrArrSales[a].price * ptrArrSales[a].qty);
		discount += total * (memberDiscount / 100);
		grandTotal = total - discount;
		commission = grandTotal * 0.05;

		//sale summary
		color('B');
		printByOrderId(ptrArrSales, buffer.orderId);
		printf("| Total         : %10.2lf                                                                                          |\n", total);
		printf("| Discount      : %10.2lf                                                                                          |\n", discount);
		printf("| Grand Total   : %10.2lf                                                                                          |\n", grandTotal);
		printf("| Commission    : %10.2lf for member %s                                                                         |\n", commission, buffer.memberId);
		printf("|---------------------------------------------------------------------------------------------------------------------|\n");
		color('X');
	}
}

//change data for existing sales
void modifySales(typeSales* ptrArrSales) {

	typeSales buffer;
	int modArrFirst = -1;
	int modArr = -1;
	int modArrLast = -1;

	//get orderId from user
	int found = 0;
	do {
		printf("Enter order ID : ");
		rewind(stdin);
		scanf("%[^\n]", &buffer.orderId);

		color('B');
		found = printByOrderId(ptrArrSales, buffer.orderId);
		color('X');

		if (found == 0) {
			color('R');
			printf("Invalid. ");
			color('X');
		}

	} while (found == 0);

	//if only ene orderId, get array number
	if (found == 1) {

		for (int a = 0; a < getIndex(0); a++) {

			if (strcmp(ptrArrSales[a].orderId, buffer.orderId) == 0)
				modArrFirst = modArr = modArrLast = a;
		}
	}

	//if more than one orderId, clarify with user for which itemId, get array number
	if (found > 1) {
		do {
			printf("Specify item ID : ");
			rewind(stdin);
			scanf("%[^\n]", &buffer.itemId);

			for (int a = 0; a < getIndex(0); a++) {

				//get all array position for the orderId for easier data manipulation
				if (strcmp(ptrArrSales[a].orderId, buffer.orderId) == 0 && modArrFirst == -1)
					modArrFirst = a;

				if (strcmp(ptrArrSales[a].orderId, buffer.orderId) == 0
					&& strcmp(ptrArrSales[a].itemId, buffer.itemId) == 0)
					modArr = a;

				if (strcmp(ptrArrSales[a].orderId, buffer.orderId) == 0)
					modArrLast = a;
			}

			if (modArr == -1) {
				color('R');
				printf("Invalid. ");
				color('X');
			}

		} while (modArr == -1);
	}

	char sel = 'R';
	do {
		printf("\n");
		printf("Modify order data\n");
		printf("Item ID      [I]\n");
		printf("Member ID    [M]\n");
		printf("Staff ID     [S]\n");
		printf("Quantity     [Q]\n");
		printf("Date         [D]\n");
		printf("Time         [T]\n");
		printf("Please select : ");

		//select data mofify
		rewind(stdin);
		sel = getchar();
		sel = toupper(sel);
		printf("\n");

		char rep = 'Y';
		switch (sel) {
			//item
		case 'I':
			do {
				printf("Enter new item ID : ");
				rewind(stdin);
				scanf("%[^\n]", &buffer.itemId);

				if (strcmp(buffer.itemId, ptrArrSales[modArr].itemId) == 0) {
					color('R');
					printf("New value same as old!\n");
					color('X');
				}
				else if (getItemPrice(buffer.itemId) == -1) {
					color('R');
					printf("Invalid. ");
					color('X');
				}
				else if (getItemPrice(buffer.itemId) == -2) {
					color('R');
					printf("File error!\n");
					system("pause");
					color('X');
					return;
				}
				else {
					rep = 'N';

					int arrDuplicate = -1;
					for (int a = modArrFirst; a <= modArrLast; a++) {
						if (strcmp(buffer.itemId, ptrArrSales[a].itemId) == 0 && a != modArr)
							arrDuplicate = a;
					}

					//if no duplicate
					if (arrDuplicate == -1) {
						strcpy(ptrArrSales[modArr].itemId, buffer.itemId);
					}
					//if duplicate
					else {
						strcpy(ptrArrSales[modArr].itemId, buffer.itemId);
						ptrArrSales[modArr].qty += ptrArrSales[arrDuplicate].qty;
						deleteByArrNum(ptrArrSales, arrDuplicate);
					}

					//calculate new values
					typeSales buffer2 = ptrArrSales[modArr];
					calculateValues(&buffer2);
					ptrArrSales[modArr] = buffer2;
				}
			} while (rep == 'Y');
			break;

		case 'M':
			//member
			do {
				printf("Enter new member ID : ");
				rewind(stdin);
				scanf("%[^\n]", &buffer.memberId);

				if (strcmp(buffer.memberId, ptrArrSales[modArr].memberId) == 0) {
					color('R');
					printf("New value same as old!\n");
					color('X');
				}
				else if (getMemberDiscount(buffer.memberId) == -1) {
					color('R');
					printf("Invalid. ");
					color('X');
				}
				else if (getMemberDiscount(buffer.memberId) == -2) {
					color('R');
					printf("File error!\n");
					system("pause");
					color('X');
					return;
				}
				else {
					rep = 'N';

					for (int a = modArrFirst; a <= modArrLast; a++)
						strcpy(ptrArrSales[a].memberId, buffer.memberId);
				}

			} while (rep == 'Y');
			break;

		case 'S':
			//staff
			do {
				printf("Enter new staff ID : ");
				rewind(stdin);
				scanf("%[^\n]", &buffer.staffId);

				if (strcmp(buffer.staffId, ptrArrSales[modArr].staffId) == 0) {
					color('R');
					printf("New value same as old!\n");
					color('X');
				}
				else if (checkStaffId(buffer.staffId) == 'N') {
					color('R');
					printf("Invalid. ");
					color('X');
				}
				else if (checkStaffId(buffer.staffId) == 'F') {
					color('R');
					printf("File error!\n");
					system("pause");
					color('X');
					return;
				}
				else {
					rep = 'N';
					for (int a = modArrFirst; a <= modArrLast; a++)
						strcpy(ptrArrSales[a].staffId, buffer.staffId);
				}
			} while (rep == 'Y');
			break;

		case 'Q':
			//qty
			do {
				printf("Enter new item quantity	: ");
				rewind(stdin);
				scanf("%d", &buffer.qty);

				if (buffer.qty > 0) {
					rep = 'N';
					ptrArrSales[modArr].qty = buffer.qty;
				}
				else {
					color('R');
					printf("Invalid. ");
					color('X');
				}

			} while (rep == 'Y');
			break;

		case 'D':
			//date
			do {
				printf("Enter new date [yyyy/mm/dd] : ");
				rewind(stdin);
				scanf("%d/%d/%d", &buffer.dateTime.year, &buffer.dateTime.mon, &buffer.dateTime.day);

				if (buffer.dateTime.year > 0
					&& buffer.dateTime.mon >= 1
					&& buffer.dateTime.mon <= 12
					&& buffer.dateTime.day >= 1
					&& buffer.dateTime.day <= 31) {
					rep = 'N';
					for (int a = modArrFirst; a <= modArrLast; a++) {
						ptrArrSales[a].dateTime.year = buffer.dateTime.year;
						ptrArrSales[a].dateTime.mon = buffer.dateTime.mon;
						ptrArrSales[a].dateTime.day = buffer.dateTime.day;
					}
				}
				else {
					color('R');
					printf("Invalid. ");
					color('X');
				}

			} while (rep == 'Y');
			break;

		case 'T':
			//time
			do {
				printf("Enter new time [hh:mm:ss] : ");
				rewind(stdin);
				scanf("%d:%d:%d", &buffer.dateTime.hour, &buffer.dateTime.min, &buffer.dateTime.sec);

				if (buffer.dateTime.hour >= 0
					&& buffer.dateTime.hour < 24
					&& buffer.dateTime.min >= 0
					&& buffer.dateTime.min < 60
					&& buffer.dateTime.sec >= 0
					&& buffer.dateTime.sec < 60) {
					rep = 'N';
					for (int a = modArrFirst; a <= modArrLast; a++) {
						ptrArrSales[a].dateTime.hour = buffer.dateTime.hour;
						ptrArrSales[a].dateTime.min = buffer.dateTime.min;
						ptrArrSales[a].dateTime.sec = buffer.dateTime.sec;
					}
				}
				else {
					color('R');
					printf("Invalid. ");
					color('X');
				}

			} while (rep == 'Y');
			break;

		default:
			color('R');
			printf("Invalid. ");
			color('X');
			sel = 'R';
		}
	} while (sel == 'R');

	color('B');
	printByOrderId(ptrArrSales, buffer.orderId);
	color('X');
}

//delete sales function
void deleteSales(typeSales* ptrArrSales) {

	char sel = 'N';
	do {
		printf("Enter order ID : ");
		char orderId[6];
		rewind(stdin);
		scanf("%[^\n]", &orderId);

		//check if orderId exist
		int found = 0;
		color('B');
		found = printByOrderId(ptrArrSales, orderId);
		color('X');

		if (found == 0) {
			color('R');
			printf("No sales found! Continue search to delete? [Y/N] : ");
			color('X');
		}
		else {
			//delete order
			deleteByOrderId(ptrArrSales, orderId);
			printf("The above sales record have been deleted!");
			sel = 'N';
		}

		rewind(stdin);
		sel = getchar();
		sel = toupper(sel);

	} while (sel == 'Y');
}

//generate report for sales
void reportSales(typeSales* ptrArrSales) {

	typeDateTime sel;
	int count = 0;

	//get date from user
	char rep = 'Y';
	do {
		printf("Enter date to report [yyyy/mm/dd] : ");
		rewind(stdin);
		scanf("%d/%d/%d", &sel.year, &sel.mon, &sel.day);

		if (sel.year > 0
			&& sel.mon >= 1
			&& sel.mon <= 12
			&& sel.day >= 1
			&& sel.day <= 31)
			rep = 'N';
		else {
			color('R');
			printf("Invalid. ");
			color('X');
		}

	} while (rep == 'Y');

	//print out all sales that match date
	double total = 0;
	char header = 'N';
	color('B');
	int a;
	for (a = 0; a < getIndex(0); a++) {
		if (ptrArrSales[a].dateTime.year == sel.year && ptrArrSales[a].dateTime.mon == sel.mon && ptrArrSales[a].dateTime.day == sel.day) {

			if (header == 'N') {
				printHeader();
				header = 'Y';
			}
			printByArrNum(ptrArrSales, a);
			total += ptrArrSales[a].total;
			count++;
		}
	}
	color('X');

	//print out total
	if (header == 'Y') {
		color('B');
		printFooter(count);
		printf("| Total         : %10.2lf                                                                                          |\n", total);
		printf("|---------------------------------------------------------------------------------------------------------------------|\n");
		color('X');
	}
	else {
		color('B');
		printf("Sales data empty!\n");
		color('X');
	}
}

//get current index num for struct array by pass 0, if pass any other number, will add or substract
int getIndex(int input) {

	static index = 0;

	if (input == -99)
		index = 0;
	else
		index += input;

	return index;
}

//print out table header
void printHeader() {
	printf("|--------|--------|--------|--------|------------|----------|------------|-----|------------|------------|------------|\n");
	printf("| Order  | Item   | Member | Staff  | Date       | Time     | Price      | Qty | Discount   | Commission | Total      |\n");
	printf("|--------|--------|--------|--------|------------|----------|------------|-----|------------|------------|------------|\n");
}

//print out table footer
void printFooter(int a) {

	printf("|---------------------------------------------------------------------------------------------------------------------|\n");
	printf("| Total records : %7d                                                                                             |\n", a);
	printf("|---------------------------------------------------------------------------------------------------------------------|\n");
}

//change string to num to return latest id number
int getNum(char str[6]) {

	int num = 0;

	//convert string to number by removing letters leaving only numbers
	for (int a = 0; str[a] != '\0'; a++) {
		if (str[a] >= 48 && str[a] <= 57)
			num = num * 10 + (str[a] - 48);
	}

	return num;
}

//assign new price, recalculate discount, total and commission
void calculateValues(typeSales* buffer) {

	int memberDiscount = getMemberDiscount(buffer->memberId);

	buffer->price = getItemPrice(buffer->itemId);
	buffer->discount = (buffer->price * buffer->qty) * (memberDiscount / 100);
	buffer->total = (buffer->price * buffer->qty) - buffer->discount;
	buffer->com = ((buffer->price * buffer->qty) - buffer->discount) * 0.05;
}

//color print function
void color(char color) {

	switch (color) {
	case 'R':
		printf("\033[1;31m");
		break;
	case 'G':
		printf("\033[1;32m");
		break;
	case 'Y':
		printf("\033[0;33m");
		break;
	case 'B':
		printf("\033[1;34m");
		break;
	case 'P':
		printf("\033[1;35m");
		break;
	default:
		printf("\033[0m");
	}
}

//print all sales with matching orderId, with header and footer, return number of arrays printed
int printByOrderId(typeSales* ptrArrSales, char orderId[6]) {

	int found = 0;
	char header = 'N';

	printf("\n");
	for (int a = 0; a < getIndex(0); a++) {
		if (strcmp(ptrArrSales[a].orderId, orderId) == 0) {
			found++;

			//print header condition and avoid double print header
			if (found == 1 && header == 'N') {
				printHeader();
				header = 'Y';
			}
			printByArrNum(ptrArrSales, a);
		}
	}
	if (header == 'Y') {
		printFooter(found);
	}
	return found;
}

//print the row of sale of specific row
void printByArrNum(typeSales* ptrArrSales, int a) {

	printf("| %6s | %6s | %6s | %6s | %04d/%02d/%02d | %02d:%02d:%02d | %10.2lf | %3d | %10.2lf | %10.2lf | %10.2lf |\n",
		ptrArrSales[a].orderId,
		ptrArrSales[a].itemId,
		ptrArrSales[a].memberId,
		ptrArrSales[a].staffId,

		ptrArrSales[a].dateTime.year,
		ptrArrSales[a].dateTime.mon,
		ptrArrSales[a].dateTime.day,
		ptrArrSales[a].dateTime.hour,
		ptrArrSales[a].dateTime.min,
		ptrArrSales[a].dateTime.sec,

		ptrArrSales[a].price,
		ptrArrSales[a].qty,
		ptrArrSales[a].discount,
		ptrArrSales[a].com,
		ptrArrSales[a].total);
}

//delete all array where orderId matched the passed value, return number of deleted rows
int deleteByOrderId(typeSales* ptrArrSales, char orderId[6]) {

	int del = 0;

	for (int a = 0; a < getIndex(0); a++) {

		if (strcmp(ptrArrSales[a].orderId, orderId) == 0) {

			deleteByArrNum(ptrArrSales, a);
			a--;
			del++;
		}
	}
	return del;
}

//delete the row of sale of specific row
void deleteByArrNum(typeSales* ptrArrSales, int a) {

	for (int b = a; b < getIndex(0); b++)
		ptrArrSales[b] = ptrArrSales[b + 1];

	getIndex(-1);
}

//get item price from itemID, return -2 if file error, -1 if item didnt exist
double getItemPrice(char itemId[6]) {

	FILE* fileItem = NULL;
	struct stock buffer;
	double price = -1;

	fileItem = fopen("stockFile.txt", "r");
	if (fileItem == NULL)
		price = -2;
	else {
		while (!feof(fileItem)) {
			fscanf(fileItem, "%[^,],%lld,%[^,],%[^,],%d,%lf,%lf\n",
				&buffer.itemID,
				&buffer.barcode,
				&buffer.supplier,
				&buffer.name,
				&buffer.quantity,
				&buffer.prices.cost,
				&buffer.prices.salePrice);

			if (strcmp(buffer.itemID, itemId) == 0) {
				price = buffer.prices.salePrice;
				break;
			}
			else {
				price = -1;
			}
		}
	}
	return price;
}

//get discount percentage from memberId, return -2 if file error, -1 if member didnt exist
int getMemberDiscount(char memberId[6]) {

	int discountPerctage = -1;
	FILE* fileMember = NULL;
	Member buffer;

	fileMember = fopen("member.bin", "rb");
	if (fileMember == NULL)
		discountPerctage = -2;
	else {
		int a = 0;
		while (fread(&buffer, sizeof(Member), 1, fileMember) == 1) {

			if (strcmp(buffer.memberId, memberId) == 0) {

				switch (buffer.memberType) {
				case 'N':
					discountPerctage = 0;
					break;
				case 'G':
					discountPerctage = 2;
					break;
				case 'P':
					discountPerctage = 5;
					break;
				case 'D':
					discountPerctage = 9;
					break;
				default:
					discountPerctage = 0;
				}
				break;
			}
			else
				discountPerctage = -1;
			a++;
		}
	}
	fclose(fileMember);

	return discountPerctage;
}

//check staffId exist or not, return F if file error, N if member didnt exist, Y if exist
char checkStaffId(char staffId[6]) {

	char valid = 'N';
	FILE* fileStaff = NULL;
	Staff buffer;

	fileStaff = fopen("staff.bin", "rb");
	if (fileStaff == NULL)
		valid = 'F';
	else {
		int a = 0;
		while (fread(&buffer, sizeof(Staff), 1, fileStaff) == 1) {

			if (strcmp(buffer.staffId, staffId) == 0) {
				valid = 'Y';
				break;
			}
			a++;
		}
	}
	fclose(fileStaff);

	return valid;
}

#pragma endregion


#pragma region stockModule- Tan Jee Schuan
void stock_management()
{
	int inputInt;

	FILE* fp;
	fp = fopen(STOCKFILENAME, "r"); //find out if file exists
	if (fp == NULL)
	{
		printf("Stock file not found, creating file");
		fp = fopen(STOCKFILENAME, "w");

		if (fp == NULL)
		{
			printf("Cannot open file");
			exit(-1);
		}
	}
	else
	{
		fclose(fp);
		fp = fopen(STOCKFILENAME, FOPENTYPE);
	}

	do
	{
		system("cls");
		logo();
		header("Stock Managment System");
		fseek(fp, 0, SEEK_SET);

		inputInt = 0;

		printf("\t\t\t1. Add Product\n\n");
		printf("\t\t\t2. Search Product\n\n");
		printf("\t\t\t3. Modify Stocks\n\n");
		printf("\t\t\t4. Display All Stocks\n\n");
		printf("\t\t\t5. Generate Low Stock Report\n\n");
		printf("\t\t\t6. Delete Record\n\n");
		printf("\t\t\t7. Validate And Sort Records\n\n");
		printf("\t\t\t99. Exit\n");

		printf("\nEnter Selection: ");

		rewind(stdin);
		scanf("%d", &inputInt);

		switch (inputInt)
		{

		case 1:
			add_product(fp);
			break;

		case 2:
			search_for_stock(fp);
			break;

		case 3:
			modify_stock(fp);
			break;

		case 4:
			display_all_stocks(fp);
			break;

		case 5:
			generate_low_stock_report(fp);
			break;

		case 6:
			delete_stock(fp);
			break;

		case 7:
			validate_sort_stock(fp);
			break;

		case 99:
			return 0;
			break;

		default:
			system("cls");
			printf("Invalid Selection!\n\n");
			_sleep(1000);
			system("cls");
			break;
		}
	} while (inputInt != 99);

	fclose(fp);
}

void add_product(FILE* filePointer)
{
	struct stock inputStockStruct = { 0 };

	input_new_stock(&inputStockStruct);


	print_stock_header();
	print_stock_struct(inputStockStruct);

	write_struct_to_file(&inputStockStruct, filePointer);
	fclose(filePointer);
	filePointer = fopen(STOCKFILENAME, FOPENTYPE);

	printf("\n\nRecord added\n\n");
	system("pause");
	system("cls");
}

void search_for_stock(FILE* inputFile)
{
	char searchStr[MAXARGLENGTH] = { '\0' };

	system("cls");
	logo();
	header("Search Stock Info");
	if (search_argument_generator(&searchStr) == 0)
		search_stock(inputFile, searchStr);
}

void modify_stock(FILE* inputFile)
{
	struct stockArth fileStocks = { '\0' };
	char stockModArgs[MAXARGLENGTH] = { '\0' };
	system("cls");
	logo();
	header("Modify Stock Info");
	if (browse_stocks(inputFile) == 0) //modifies fp to struct location
	{
		stock_argument_generator(&stockModArgs);
		modify_stocks_struct(&fileStocks, stockModArgs);

		modify_stocks(STOCKFILENAME, inputFile, &fileStocks); //appends modified record at end of file
		delete_record(inputFile); //deletes old record

		sort_records(inputFile);

		system("pause");
		system("cls");
	}
	else
	{
		printf("\nEnd of records.\n\n");
		system("pause");
		system("cls");
	}
}

void display_all_stocks(FILE* filePointer)
{
	system("cls");
	logo();
	header("Display Stock Info");
	struct stock bufferStucture = { 0 };
	int count = 0;

	print_stock_header();

	while (read_to_stock_struct(&bufferStucture, filePointer) != 0)
	{
		print_stock_struct(bufferStucture);
		printf("\n");
		zeroise_stock_struct(&bufferStucture);
		count++;
	}

	printf("\nTotal: %d record(s)\n\n\n", count);
	system("pause");
	system("cls");

	return 0;
}

void generate_low_stock_report(FILE* filePointer)
{
	system("cls");
	logo();
	header("Low Stock Report ");
	char searchStr[] = "quantity <20";
	search_stock(filePointer, searchStr);
}

void delete_stock(FILE* filePointer)
{
	system("cls");
	logo();
	header("Delete Stock Info ");
	printf("Select Record to Delete: ");

	if (browse_stocks(filePointer) == 0)
	{
		delete_record(filePointer);
		printf("Record deleted\n\n");
	}

	else
		printf("End of records.");

	system("pause");
	system("cls");
}

void validate_sort_stock(FILE* filePointer)
{
	system("cls");
	logo();
	header("Validate Stock Info ");
	sort_records(filePointer);
	validate_unique_fields(filePointer);
	system("cls");
	printf("File validated and sorted\n\n");
	system("pause");
	system("cls");
}

void input_new_stock(struct stock* inputStockStruct)
{
	char bufferString[nameLength];
	int bufferInt, temp = 0;
	double bufferDouble;
	long bufferLong;

	system("cls");
	logo();
	header("Add Stock Info");
	do
	{
		if (temp == 1)
			printf("\nitemID too short (at least 5 characters)\n");
		validate_stock_input(&bufferString, "ItemID", "a");
		temp = 1;
	} while (strlen(bufferString) < 5);
	temp = 0;
	strcpy(inputStockStruct->itemID, bufferString);


	print_stock_header();
	print_stock_struct(*inputStockStruct);
	printf("\n");
	do
	{
		if (temp == 1)
			printf("\Barcode too short (at least 6 digits)\n");
		validate_stock_input(&bufferString, "Barcode", "i");
		temp = 1;
	} while (strlen(bufferString) < 6);
	temp = 0;
	bufferLong = atol(bufferString);
	inputStockStruct->barcode = bufferLong;

	system("cls");
	print_stock_header();
	print_stock_struct(*inputStockStruct);
	printf("\n");
	validate_stock_input(&bufferString, "Product Name", "n");
	strcpy(inputStockStruct->name, bufferString);

	system("cls");
	print_stock_header();
	print_stock_struct(*inputStockStruct);
	printf("\n");
	do
	{
		if (temp == 1)
			printf("\Supplier name too short (at least 3 character)\n");
		validate_stock_input(&bufferString, "Supplier", "n");
		temp = 1;
	} while (strlen(bufferString) < 3);
	temp = 0;
	strcpy(inputStockStruct->supplier, bufferString);

	system("cls");
	print_stock_header();
	print_stock_struct(*inputStockStruct);
	printf("\n");
	validate_stock_input(&bufferString, "Quantity", "i");
	bufferInt = atoi(bufferString);
	inputStockStruct->quantity = bufferInt;

	system("cls");
	print_stock_header();
	print_stock_struct(*inputStockStruct);
	printf("\n");
	validate_stock_input(&bufferString, "Cost", "d");
	bufferDouble = atof(bufferString);
	inputStockStruct->prices.cost = bufferDouble;

	system("cls");
	print_stock_header();
	print_stock_struct(*inputStockStruct);
	printf("\n");
	validate_stock_input(&bufferString, "Sale Price", "d");
	bufferDouble = atof(bufferString);
	inputStockStruct->prices.salePrice = bufferDouble;
}

int browse_stocks(FILE* filePointer) //modifies inputed pointer to selected structure in file
{
	struct stock bufferStucture = { 0 };

	long fileSize;
	int structNum = 1, displayNum, structureSelection, charNumToTarget = 0, displayedNum = 0;
	int tens = 0, ones = 0;

	while (read_to_stock_struct(&bufferStucture, filePointer) != 0)
	{
		structNum++;
	}

	fseek(filePointer, 0, SEEK_SET);
	structNum -= 1;
	//splits number into tens and ones
	tens = structNum / 10;
	ones = structNum % 10;

	for (int i = 0; i < tens + 1; i++)
	{
		if (i == tens && ones == 0)
			break;

		int lineLength[10] = { 0 };

		printf("\n\n%-5s %-15s %-15s %-30s %-15s %-10s %-10s %-10s \n", "No", "ItemID", "Barcode", "Name", "Supplier", "Quantity", "Cost", "Price");
		printf("------------------------------------------------------------------------------------------------------------");

		if (i == tens)
			displayNum = ones;
		else
			displayNum = 10;


		for (int j = 0; j < displayNum; j++) //goes though file
		{
			lineLength[j] = read_to_stock_struct(&bufferStucture, filePointer) + 2; //newline char isnt counted
			printf("\n%-5d ", j + 1);
			print_stock_struct(bufferStucture);
		}

		displayedNum += displayNum;

		printf("\n\n%d out of %d displayed. 11 for next page. 1-10 for selection. 99 to exit: ", displayedNum, structNum);

		rewind(stdin);
		int tempFlag = 0;
		do
		{
			if (tempFlag == 1)
				printf("\nEnter valid number: ");

			scanf("%d", &structureSelection);
			rewind(stdin);

			if (structureSelection > 0 && structureSelection < 11)
			{
				for (int k = 9; k > structureSelection - 2; k--)
				{
					charNumToTarget += lineLength[k];
				}
				fseek(filePointer, -charNumToTarget, SEEK_CUR); //moves filePointer back by character number
				return 0;
			}
			else if (structureSelection == 99)
			{
				return 1;
			}
			else if (structureSelection == 11)
			{
				break;
			}
			else
			{
				tempFlag = 1;
			}
		} while (structureSelection < 1 || structureSelection > 10);

	}

	return 1;
}

void modify_stocks_struct(struct stockArth* modifiedStockStruct, char args[MAXARGLENGTH]) //only modifies selects fields, rest are ignored; EXAMPLE: --barcode 1234 only modifies the barcode
{
	char splitArgs[STOCKSTRUCTELEMENTSNUM][MAXARGLENGTH] = { '\0' };
	char finalArgs[STOCKSTRUCTELEMENTSNUM][2][MAXARGLENGTH] = { '\0' };
	int x = 0;

	//split string based on '--' delimiter
	for (int i = 0; i < MAXARGLENGTH; i++)
	{
		int y = 0;
		if (args[i] == '-' && args[i + 1] == '-') //if finds '--' in string
		{
			for (int j = i + 2; j < MAXARGLENGTH; j++)
			{
				if (args[j + 1] == '-' && args[j + 2] == '-') //prevent from reading whitespace at start of '--'
				{
					i = j - 1;
					break;
				}
				splitArgs[x][y] = args[j];
				y++;
			}
			x++;
		}
	}

	//split string based on ' ' delimiter
	int found = 0;
	for (int x = 0; x < STOCKSTRUCTELEMENTSNUM; x++)
	{
		found = 0;
		int i = 0, j = 0;
		for (int y = 0; y < MAXARGLENGTH; y++)
		{
			if (splitArgs[x][y] == ' ' && found == 0)
			{
				i++;
				j = 0;
				found = 1;
			}

			else
			{
				finalArgs[x][i][j] = splitArgs[x][y];
				j++;
			}
		}
	}

	for (int x = 0; x < STOCKSTRUCTELEMENTSNUM; x++)
	{
		if (strcmp(finalArgs[x][0], "itemid") == 0)
		{
			if (finalArgs[x][1][0] != '\0')
				strcpy(modifiedStockStruct->itemID, finalArgs[x][1]);
		}
		else if (strcmp(finalArgs[x][0], "barcode") == 0)
		{
			if (finalArgs[x][1][0] != '\0')
				modifiedStockStruct->barcode = atol(finalArgs[x][1]);
		}
		else if (strcmp(finalArgs[x][0], "supplier") == 0)
		{
			if (finalArgs[x][1][0] != '\0')
				strcpy(modifiedStockStruct->supplier, finalArgs[x][1]);
		}
		else if (strcmp(finalArgs[x][0], "name") == 0)
		{
			if (finalArgs[x][1][0] != '\0')
				strcpy(modifiedStockStruct->name, finalArgs[x][1]);
		}
		else if (strcmp(finalArgs[x][0], "quantity") == 0)
		{
			if (finalArgs[x][1][0] != '\0')
				strcpy(modifiedStockStruct->quantity, finalArgs[x][1]);
		}
		else if (strcmp(finalArgs[x][0], "cost") == 0)
		{
			modifiedStockStruct->prices.cost = atof(finalArgs[x][1]);
		}
		else if (strcmp(finalArgs[x][0], "saleprice") == 0)
		{
			modifiedStockStruct->prices.salePrice = atof(finalArgs[x][1]);
		}
	}
}

//Does not move file pointer
void modify_stocks(char fileNameToWriteTo[], FILE* filePointer, struct stockArth* modifiedStockStruct) //In Quantity, +, -performs arthimatic on current stock quantity, unsigned means direct change;
{
	struct stock finalStruct = { '\0' };
	int stockQuantity, inputQuantity;
	char bufferStr[MAXARGLENGTH] = { '\0' };

	strcpy(bufferStr, modifiedStockStruct->quantity);
	inputQuantity = atoi(bufferStr);
	fseek(filePointer, -(read_to_stock_struct(&finalStruct, filePointer) + 2), SEEK_CUR);

	if (strchr(bufferStr, '-') != NULL || strchr(bufferStr, '+') != NULL)
		stockQuantity = finalStruct.quantity + inputQuantity;
	else
		stockQuantity = inputQuantity;

	if (modifiedStockStruct->itemID[0] != '\0')
		strcpy(finalStruct.itemID, modifiedStockStruct->itemID);
	if (modifiedStockStruct->supplier[0] != '\0')
		strcpy(finalStruct.supplier, modifiedStockStruct->supplier);
	if (modifiedStockStruct->name[0] != '\0')
		strcpy(finalStruct.name, modifiedStockStruct->name);
	if (modifiedStockStruct->barcode != '\0')
		finalStruct.barcode = modifiedStockStruct->barcode;
	if (modifiedStockStruct->quantity != '\0')
		finalStruct.quantity = stockQuantity;
	if (modifiedStockStruct->prices.cost != '\0')
		finalStruct.prices.cost = modifiedStockStruct->prices.cost;
	if (modifiedStockStruct->prices.salePrice != '\0')
		finalStruct.prices.salePrice = modifiedStockStruct->prices.salePrice;

	FILE* fp = fopen(fileNameToWriteTo, FOPENTYPE); //opens file again to prevent moving original file pointer
	if (fp == NULL)
	{
		printf("Cannot open file");
		exit(-1);
	}
	write_struct_to_file(&finalStruct, fp);
	fclose(fp);
}

void stock_argument_generator(char* str[])
{
	char tempStr[MAXARGLENGTH] = { '\0' };
	char bufferString[nameLength] = { '\0' };

	validate_stock_input(&bufferString, "ItemID", "a");
	if (bufferString[0] != '\0')
	{
		strcat(tempStr, " --itemid ");
		strcat(tempStr, bufferString);
	}

	validate_stock_input(&bufferString, "Barcode", "i");
	if (bufferString[0] != '\0')
	{
		strcat(tempStr, " --barcode ");
		strcat(tempStr, bufferString);
	}

	validate_stock_input(&bufferString, "Product Name", "n");
	if (bufferString[0] != '\0')
	{
		strcat(tempStr, " --name ");
		strcat(tempStr, bufferString);
	}

	validate_stock_input(&bufferString, "Supplier", "n");
	if (bufferString[0] != '\0')
	{
		strcat(tempStr, " --supplier ");
		strcat(tempStr, bufferString);
	}

	validate_stock_input(&bufferString, "Quantity (+ , - to add or subtract)", "s");
	if (bufferString[0] != '\0')
	{
		strcat(tempStr, " --quantity ");
		strcat(tempStr, bufferString);
	}

	validate_stock_input(&bufferString, "Cost", "d");
	if (bufferString[0] != '\0')
	{
		strcat(tempStr, " --cost ");
		strcat(tempStr, bufferString);
	}

	validate_stock_input(&bufferString, "Sale Price", "d");
	if (bufferString[0] != '\0')
	{
		strcat(tempStr, " --saleprice ");
		strcat(tempStr, bufferString);
	}

	strcpy(str, tempStr);
}

int search_argument_generator(char* str[])
{
	int inputNum;
	char tempStr[MAXARGLENGTH] = { '\0' };

	do
	{
		printf("\nWhat to search in?\n");
		printf("1. ItemID\n");
		printf("2. Barcode\n");
		printf("3. Supplier\n");
		printf("4. Name\n");
		printf("5. Custom Command\n");
		printf("99. Exit\n\n");

		scanf("%d", &inputNum);
		rewind(stdin);

		switch (inputNum)
		{
		case 1:
			printf("\nEnter ItemID to search: ");

			get_string(&tempStr);

			strcat(str, "itemid ");
			strcat(str, tempStr);
			break;

		case 2:
			printf("\nEnter Barcode to search: ");

			get_string(&tempStr);

			strcat(str, "barcode ");
			strcat(str, tempStr);
			break;

		case 3:
			printf("\nEnter Supplier to search: ");

			get_string(&tempStr);

			strcat(str, "supplier ");
			strcat(str, tempStr);
			break;

		case 4:
			printf("\nEnter Name to search: ");

			get_string(&tempStr);

			strcat(str, "name ");
			strcat(str, tempStr);
			break;

		case 5:
			printf("\nEnter custom command: ");
			get_string(&tempStr);
			strcpy(str, tempStr);
			break;

		case 99:
			return 1;

		default:
			printf("Invalid Selection");
		}

	} while (inputNum <= 0 || inputNum > 5);

	return 0;
}

void search_stock(FILE* filePointer, char* inputStr) //eg. itemid A12345
{
	struct stock bufferStock = { '\0' };
	char structVars[STOCKSTRUCTELEMENTSNUM][MAXARGLENGTH] = { "itemid","barcode","supplier","name","quantity","cost","saleprice" };
	char targetField[MAXARGLENGTH] = { '\0' }, fieldValue[MAXARGLENGTH] = { '\0' };
	int structElementNum = -1, foundRecords = 0;

	//targetField = strtok(inputStr, " "); //split into command and argument
	//fieldValue = strtok(NULL, " ");

	int found = 0;
	for (int x = 0; x < MAXARGLENGTH; x++)
	{
		if (found == 0)
		{
			for (int y = 0; y < MAXARGLENGTH; y++)
			{
				if (inputStr[x] != ' ')
				{
					targetField[y] = inputStr[x];
					x++;
				}
				else
				{
					found = 1;
				}
			}
		}

		else if (found == 1)
			for (int y = 0; y < MAXARGLENGTH; y++)
			{
				fieldValue[y] = inputStr[x];
				x++;
			}
	}

	for (int i = 0; i < STOCKSTRUCTELEMENTSNUM; i++)
	{
		if (strcmp(structVars[i], targetField) == 0)
			structElementNum = i;
	}

	print_stock_header();

	while (read_to_stock_struct(&bufferStock, filePointer) != 0)
	{
		if (strstr(fieldValue, "<") == NULL && strstr(fieldValue, ">") == NULL)
		{
			switch (structElementNum)
			{
			case 0:
				if (strcmp(bufferStock.itemID, fieldValue) == 0)
				{
					print_stock_struct(bufferStock);
					printf("\n");
					foundRecords++;
				}
				break;
			case 1:
				if (bufferStock.barcode == atol(fieldValue))
				{
					print_stock_struct(bufferStock);
					printf("\n");
					foundRecords++;
				}
				break;
			case 2:
				if (strcmp(bufferStock.supplier, fieldValue) == 0)
				{
					print_stock_struct(bufferStock);
					printf("\n");
					foundRecords++;
				}
				break;
			case 3:
				if (strcmp(bufferStock.name, fieldValue) == 0)
				{
					print_stock_struct(bufferStock);
					printf("\n");
					foundRecords++;
				}
				break;
			case 4:
				if (bufferStock.quantity == atoi(fieldValue))
				{
					print_stock_struct(bufferStock);
					printf("\n");
					foundRecords++;
				}
				break;
			case 5:
				if (bufferStock.prices.cost == atof(fieldValue))
				{
					print_stock_struct(bufferStock);
					printf("\n");
					foundRecords++;
				}
				break;
			case 6:
				if (bufferStock.prices.salePrice == atof(fieldValue))
				{
					print_stock_struct(bufferStock);
					printf("\n");
					foundRecords++;
				}
				break;
			default:
				printf("Search function invalid parameters");
				break;
			}
		}

		else
		{
			char tempFieldValue[MAXARGLENGTH] = { '\0' };
			strcpy(tempFieldValue, fieldValue);
			for (int i = 0; i < MAXARGLENGTH - 1; i++)
			{
				tempFieldValue[i] = tempFieldValue[i + 1];
			}

			if (strstr(fieldValue, "<") != NULL)
			{
				if (bufferStock.quantity < atoi(tempFieldValue))
				{
					print_stock_struct(bufferStock);
					printf("\n");
					foundRecords++;
				}
			}
			else if (strstr(fieldValue, ">") != NULL)
			{
				if (bufferStock.quantity > atoi(tempFieldValue))
				{
					print_stock_struct(bufferStock);
					printf("\n");
					foundRecords++;
				}
			}
		}
	}

	if (foundRecords == 0)
		printf("\nNo record found!\n");
	else
		printf("\n%d record(s) found that fit the criteria (%s %s)\n\n\n", foundRecords, targetField, fieldValue);

	system("pause");
	system("cls");
}

void validate_stock_input(char* outputStr, char* printStr, char* inputChar) // modes: a is alphanumeric, i is integer, d is decimal, s is signed, n is no check
{
	char bufferString[MAXARGLENGTH] = { '\0' };
	int tempFlag = 0;
	do
	{
		if (tempFlag == 0)
			printf("\nEnter %s: ", printStr);
		else if (tempFlag == -1)
			printf("\nEnter a %s: ", printStr);
		else
			printf("\nEnter valid %s: ", printStr);

		get_string(&bufferString);

		tempFlag = -1;
		if (bufferString[0] != '\0')
		{
			if (inputChar[0] == 'a')
				tempFlag = alphanumeric_check(bufferString, nameLength);
			else if (inputChar[0] == 'i')
				tempFlag = numeric_check(bufferString, nameLength, 'i');
			else if (inputChar[0] == 'd')
				tempFlag = numeric_check(bufferString, nameLength, 'd');
			else if (inputChar[0] == 's')
				tempFlag = numeric_check(bufferString, nameLength, 's');
			else if (inputChar[0] == 'n')
				tempFlag = 0;
		}
	} while (tempFlag != 0);

	strcpy(outputStr, bufferString);
}

void delete_record(FILE* inputFile)
{
	//deletes old record
	char oldStr[MAXARGLENGTH] = { '\0' };
	char tempStr[MAXARGLENGTH] = { '\0' };

	fscanf(inputFile, "%[^\n]\n", &oldStr);

	FILE* tempFilePointer = fopen(TEMPFILENAME, "w+");
	if (tempFilePointer == NULL)
	{
		printf("Cannot open file");
		exit(-1);
	}

	fseek(inputFile, 0, SEEK_SET);
	while (fscanf(inputFile, "%[^\n]\n", &tempStr) != EOF) //writes all records except for one selected record
	{
		if (strcmp(tempStr, oldStr) != 0)
		{
			fprintf(tempFilePointer, "%s\n", tempStr);
		}

	}

	fclose(inputFile);

	inputFile = fopen(STOCKFILENAME, "w"); //rewrite inputFile
	fseek(tempFilePointer, 0, SEEK_SET);
	while (fscanf(tempFilePointer, "%[^\n]\n", &tempStr) != EOF)
	{
		if (strcmp(tempStr, oldStr) != 0)
		{
			fprintf(inputFile, "%s\n", tempStr);
		}
	}
	fclose(inputFile);
	inputFile = fopen(STOCKFILENAME, FOPENTYPE);
}

void sort_records(FILE* inputFile)
{
	struct stock bufferStruct = { '\0' };
	char temp[MAXARGLENGTH] = { '\0' };
	char itemIDArr[MAXARGLENGTH][nameLength] = { '\0' };

	int count = 0, index[MAXARGLENGTH] = { 0 }, min;

	FILE* tempFilePointer = fopen(TEMPFILENAME, "w+");
	if (tempFilePointer == NULL)
	{
		printf("Cannot open file");
		exit(-1);
	}

	fseek(inputFile, 0, SEEK_SET);
	while (read_to_stock_struct(&bufferStruct, inputFile) != 0) //loads itemID into Array, gets number of lines
	{
		strcpy(itemIDArr[count], bufferStruct.itemID);
		count++;
	}
	fseek(inputFile, 0, SEEK_SET);

	for (int i = 0; i < count; i++) //assigns numbers to index array
	{
		index[i] = i;
	}

	//sorting
	for (int i = 0; i < count - 1; i++)
	{
		min = i; //puts index number of smallest string as i

		for (int j = i + 1; j < count; j++) //starts from one element up from i to process unsorted strings, finds strings smaller than of which with min
		{
			if (strcmp(itemIDArr[index[min]], itemIDArr[index[j]]) > 0) //compares the smallest string with the next strings
				min = j; //if smaller string is found, min is changed into index number of smaller string
		}

		//if new min is found, the old min change places with new min
		if (min != i)
		{
			int temp = index[min];
			index[min] = index[i];
			index[i] = temp;
		}
	}

	//write to temp file
	fseek(inputFile, 0, SEEK_SET);
	for (int k = 0; k < count; k++)
	{
		fseek(inputFile, 0, SEEK_SET);

		while (1)
		{
			read_to_stock_struct(&bufferStruct, inputFile);
			if (strcmp(bufferStruct.itemID, itemIDArr[index[k]]) == 0)
			{
				write_struct_to_file(&bufferStruct, tempFilePointer);
				break;
			}
		}
	}

	//rewrite to main file
	fclose(inputFile);
	inputFile = fopen(STOCKFILENAME, "w");
	if (inputFile == NULL)
	{
		printf("Cannot open file");
		exit(-1);
	}

	fseek(tempFilePointer, 0, SEEK_SET);
	while (read_to_stock_struct(&bufferStruct, tempFilePointer) != 0)
	{
		write_struct_to_file(&bufferStruct, inputFile);
	}

	fclose(inputFile);
	fclose(tempFilePointer);

	inputFile = fopen(STOCKFILENAME, FOPENTYPE);
	if (inputFile == NULL)
	{
		printf("Cannot open file");
		exit(-1);
	}
}

int validate_unique_fields(FILE* inputFile)
{
	fseek(inputFile, 0, SEEK_SET);

	FILE* file2;
	file2 = fopen(TEMPFILENAME, "w+");

	char itemIDArr[MAXARGLENGTH][nameLength] = { '\0' };
	struct stock bufferStock1;
	struct stock bufferStock2;

	int count = 0;
	while (read_to_stock_struct(&bufferStock1, inputFile) != 0) //loads itemid into array, gets number of lines
	{
		strcpy(itemIDArr[count], bufferStock1.itemID);
		count++;
	}

	int found = 0, i = 0;
	fseek(inputFile, 0, SEEK_SET);
	while (read_to_stock_struct(&bufferStock1, inputFile) != 0)
	{
		found = 0;
		for (size_t x = i + 1; x < MAXARGLENGTH; x++)
		{
			if (strcmp(itemIDArr[x], bufferStock1.itemID) == 0)
			{
				found = 1;
			}
		}

		if (found != 1)
			write_struct_to_file(&bufferStock1, file2);

		i++;
	}

	char str[MAXARGLENGTH] = { '\0' };

	fclose(inputFile);
	fclose(file2);

	inputFile = fopen(STOCKFILENAME, "w"); //rewrite inputFile
	file2 = fopen(TEMPFILENAME, "r");

	fseek(inputFile, 0, SEEK_SET);

	while (fscanf(file2, "%[^\n]\n", &str) != EOF)
	{
		fprintf(inputFile, "%s\n", str);
	}

	fclose(inputFile);
	fclose(file2);

	inputFile = fopen(STOCKFILENAME, FOPENTYPE);
}

int alphanumeric_check(char* inputString, int arr_size)
{
	for (int i = 0; i < arr_size; i++)
	{
		char bufferChar = inputString[i];

		if (bufferChar == '\n')
			bufferChar = '\0';

		if (bufferChar == '\0') //detects end of string
			return 0; //returns 0 if no special character found

		if (isalnum(bufferChar) == 0)
			return 1; //returns 1 if special character found
	}
	return 1; //return 1 if string is not \0 terminated
}

int numeric_check(char* inputString, int arr_size, char mode) //modes: i is integer, d is decimal, s is signed
{
	{
		for (int i = 0; i < arr_size; i++)
		{
			char bufferChar = inputString[i];

			if (mode == 'i')
			{
				if (bufferChar == '\0') //detects end of string
					return 0; //returns 0 if no special character found

				if (isdigit(bufferChar) == 0)
					return 1; //returns 1 if non-digit found
			}

			else if (mode == 'd')
			{
				if (bufferChar == '\0') //detects end of string
					return 0; //returns 0 if no special character found

				else if (isdigit(bufferChar) == 0 && bufferChar != '.')
					return 1; //returns 1 if non-digit found
			}

			else if (mode == 's')
			{
				if (bufferChar == '\0') //detects end of string
					return 0; //returns 0 if no special character found

				else if (isdigit(bufferChar) == 0 && bufferChar != '_')
					if (bufferChar != '+' && bufferChar != '-')
						return 1; //returns 1 if non-digit found
			}

			else
				return -1;
		}

		return 1; //return 1 if string is not \0 terminated
	}
}

void zeroise_stock_struct(struct stock* inputStock)
{
	strcpy(inputStock->itemID, "\0");

	inputStock->barcode = 0;

	strcpy(inputStock->supplier, "\0");

	strcpy(inputStock->name, "\0");

	inputStock->quantity = 0;

	inputStock->prices.cost = 0;

	inputStock->prices.salePrice = 0;;
}

void get_string(char* targetStr)
{
	rewind(stdin);
	targetStr[0] = '\0'; //reset string
	fgets(targetStr, nameLength, stdin);
	targetStr[strcspn(targetStr, "\n")] = '\0'; //replaces \n with \0
}

void print_stock_struct(struct stock inputStock)
{
	printf("%-15s %-15lld %-30s %-15s %-10d %-10.2lf %-10.2lf", inputStock.itemID, inputStock.barcode, inputStock.name, inputStock.supplier, inputStock.quantity, inputStock.prices.cost, inputStock.prices.salePrice);
}

void print_stock_header()
{
	system("cls");
	logo();
	header("Add Stock Info");
	printf("\n\n%-15s %-15s %-30s %-15s %-10s %-10s %-10s \n", "ItemID", "Barcode", "Name", "Supplier", "Quantity", "Cost", "Price");
	printf("------------------------------------------------------------------------------------------------------------\n");
}

int read_to_stock_struct(struct stock* inputStruct, FILE* filePointer) //reads file into struct stock, returns the length of line read
{
	char bufferStr[MAXARGLENGTH] = { '\0' };

	if (fscanf(filePointer, "%[^\n]\n", &bufferStr) != EOF)
	{
		int lineLength = strlen(bufferStr);
		sscanf(bufferStr, "%[^,],%lld,%[^,],%[^,],%d,%lf,%lf\n", &inputStruct->itemID, &inputStruct->barcode, &inputStruct->supplier, &inputStruct->name, &inputStruct->quantity, &inputStruct->prices.cost, &inputStruct->prices.salePrice);
		return lineLength;
	}
	else
	{
		return 0;
	}
}

int write_struct_to_file(struct stock* inputStruct, FILE* filePointer)
{
	fseek(filePointer, 0, SEEK_END);
	fprintf(filePointer, "%s,%lld,%s,%s,%d,%.2lf,%.2lf\n", inputStruct->itemID, inputStruct->barcode, inputStruct->supplier, inputStruct->name, inputStruct->quantity, inputStruct->prices.cost, inputStruct->prices.salePrice);
}

#pragma endregion


