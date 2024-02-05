#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <ctime>
#include <conio.h>
#define size 20
using namespace std;
struct Time
{
	int day, month, year, min, sec, hour;
};
struct cust {
	string username, password;
	float balance = 0.0;
	float withdep[size] = {};//the trans.of withdarw and deposit
	int withdepnum = 0;//number of trans.
	string word[size] = {};//withdraw or deposit word (w or d)
	Time time[size];
};

void mainmenu(cust user[size], int &usernum, int &userfound);
void login(cust user[size], int &usernum, int &userfound);
void signup(cust user[size], int &usernum, int &userfound);
void actionmenu(cust user[size], int &usernum, int &userfound);
void withdraw(cust user[size], int &usernum, int &userfound);
void deposit(cust user[size], int &usernum, int &userfound);
void display(cust user[size], int &usernum, int &userfound);
void adminmenu(cust user[size], int &usernum, int &userfound);
void searchforuser(cust user[size], int &usernum, int &userfound);
void displaytransactions(cust user[size], int &usernum, int &userfound);
void displaytime(cust user[size], int &usernum, int &userfound);

int main()
{

	cust user[size];
	int usernum = 0;//number of users
	int userfound = 0;

	ifstream read("atmsave.txt");
	if (read.is_open()) {
		while (read >> usernum >> user[usernum].withdepnum >> user[usernum].username >> user[usernum].password >> user[usernum].balance)
		{
			for (int i = user[usernum].withdepnum - 1; i >= 0; i--)
			{
				read >> user[usernum].withdep[i] >> user[usernum].word[i] >> user[usernum].time[i].hour >> user[usernum].time[i].min >> user[usernum].time[i].sec >> user[usernum].time[i].day >> user[usernum].time[i].month >> user[usernum].time[i].year;
			}
			usernum += 1;
		}
	}
	else
	{
		cout << "Error in file.";
		Sleep(500);
	}
	mainmenu(user, usernum, userfound);
	system("pause");
	return 0;

}

void mainmenu(cust user[size], int &usernum, int &userfound)
{


	ofstream file;
	while (1)
	{

		int userPick;

		system("color F0");
		for (int i = 0; i < 10; i++)
		{
			cout << ".";
			Sleep(100);
		}
		system("cls");

		cout << "-------------------------------------------\n";
		cout << "        ATM MainMenu\n";
		cout << "-------------------------------------------\n" << endl;
		cout << "Please select an option from the menu below: \n";
		cout << "1. Login\n";
		cout << "2. Create a New Account\n";
		cout << "3. Quit\n" << endl;
		cout << "Please select your choice: ";
		cin >> userPick;
		switch (userPick)
		{
		case 1:
			system("cls");
			login(user, usernum, userfound);
			break;
		case 2:
			system("cls");
			signup(user, usernum, userfound);
			break;
		case 3:
			file.open("atmsave.txt", ios::app || ios::ate);
			for (int i = 0; i < usernum; i++)
			{

				file << i << "\t" << user[i].withdepnum << "\t" << user[i].username << "\t" << user[i].password << "\t" << user[i].balance << "\t";

				for (int j = user[i].withdepnum - 1; j >= 0; j--)
				{
					file << user[i].withdep[j] << "\t" << user[i].word[j] << "\t" << user[i].time[j].hour << "\t" << user[i].time[j].min << "\t" << user[i].time[j].sec << "\t" << user[i].time[j].day << "\t" << user[i].time[j].month << "\t" << user[i].time[j].year << "\t";
				}
				file << endl;
			}
			file.close();
			exit(0);
			break;
		default:
			cout << "Wrong choice\n";
			break;
		}

	}

}
void signup(cust user[size], int &usernum, int &userfound)
{
	for (int i = 0; i < 10; i++)
	{
		cout << ".";
		Sleep(100);
	}
	system("cls");
	system("color F1");
	cout << "-------------------------------------------\n";
	cout << "             Create an Account\n";
	cout << "-------------------------------------------\n" << endl;
	cout << "Enter the user name of your choice: ";
	cin >> user[usernum].username;
	cout << "Enter a password of your choice: ";
	cin >> user[usernum].password;
	cout << "Enter An Initial Amount : ";
	cin >> user[usernum].balance;
	for (int i = 0; i < usernum; i++)
	{
		if (user[usernum].username == user[i].username)
		{
			cout << endl << "This username is already taken" << endl;
			cout << "Press any key to continue..";
			_getch();
			system("cls");
			signup(user, usernum, userfound);
		}
	}
	cout << "\nINFO: Your account has been created successfully!\n";
	cout << endl;
	Sleep(600);
	system("cls");
	usernum++;
	mainmenu(user, usernum, userfound);
}
void login(cust user[size], int &usernum, int &userfound)
{

	string un, pw;

	for (int i = 0; i < 10; i++)
	{
		cout << ".";
		Sleep(100);
	}
	system("cls");
	system("color F2");
	cout << "-------------------------------------------\n";
	cout << "             Log into your Account\n";
	cout << "-------------------------------------------\n" << endl;
	cout << "Enter Username: ";
	cin >> un;
	cout << "Enter Password: ";
	cin >> pw;

	if (usernum == 0)
	{
		cout << "\n*Please Signup first*\n";
	}
	for (int i = 0; i < usernum; i++)
	{
		if (un == user[i].username && pw == user[i].password)
		{
			userfound = i;
			cout << "\nLogin Successful!" << endl;
			Sleep(500);
			system("cls");
			actionmenu(user, usernum, userfound);
		}
		else if ((un == "admin" || un == "Admin") && (pw == "admin" || pw == "Admin"))
		{
			cout << "\nLogin Successful!" << endl;
			system("cls");
			adminmenu(user, usernum, userfound);
		}

		else if (i == usernum - 1)
		{

			cout << "\n";
			cout << "ERROR: Incorrect Username!\n";
			cout << "OR ";
			cout << "Incorrect Password!\n";
			cout << "\n";

		}

	}
	Sleep(1200);
	system("cls");
	mainmenu(user, usernum, userfound);
}
void actionmenu(cust user[size], int &usernum, int &userfound)
{
	int choice;

	for (int i = 0; i < 10; i++)
	{
		cout << ".";
		Sleep(100);
	}
	system("cls");
	system("color F3");
	cout << "-------------------------------------------\n";
	cout << "                 Action Menu\n";
	cout << "-------------------------------------------\n" << endl;
	cout << "1. Deposit Money\n";
	cout << "2. Withdraw Money\n";
	cout << "3. Request Balance\n";
	cout << "4. View Last 5 Transactions\n";
	cout << "5. Return to MainMenu\n";
	cout << "Enter your choice: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		system("cls");
		deposit(user, usernum, userfound);
		actionmenu(user, usernum, userfound);
		break;
	case 2:
		system("cls");
		withdraw(user, usernum, userfound);
		actionmenu(user, usernum, userfound);
		break;
	case 3:
		system("cls");
		for (int i = 0; i < 10; i++)
		{
			cout << ".";
			Sleep(100);
		}
		system("cls");
		system("color F3");
		cout << "\nYour balance for your account is: $" << user[userfound].balance;
		cout << endl;
		cout << "Press any key to continue..";
		_getch();
		system("cls");
		actionmenu(user, usernum, userfound);
		break;
	case 4:
		system("cls");
		display(user, usernum, userfound);
		actionmenu(user, usernum, userfound);
		break;
	case 5:
		system("cls");
		mainmenu(user, usernum, userfound);
		break;
	default:
		cout << "Invalid choice";
		Sleep(500);
		system("cls");
		actionmenu(user, usernum, userfound);
		break;
	}



}
void withdraw(cust user[size], int &usernum, int &userfound)
{
	float withdrawamount;
	for (int i = 0; i < 10; i++)
	{
		cout << ".";
		Sleep(100);
	}
	system("cls");
	system("color F4");
	cout << "Enter the amount of money to withdraw: $";
	cin >> withdrawamount;
	if (withdrawamount < 0)
	{
		cout << "\n          *ERROR* - Withdraw amount.\n";
		Sleep(100);
		actionmenu(user, usernum, userfound);
	}

	while (user[userfound].balance < 0.00)
	{
		system("cls");
		for (int i = 0; i < 10; i++)
		{
			cout << ".";
			Sleep(100);
		}
		system("cls");
		cout << "\n          *ERROR* - Withdraw amount.\n";
		cout << "You do not have enough dollars to withdraw that amount.\n";
		cout << endl;
		user[userfound].balance += withdrawamount;
		cout << "Your Balance is $ " << user[userfound].balance << endl;
		cout << "Press any key to continue..";
		_getch();
		system("cls");
		actionmenu(user, usernum, userfound);
	}

	time_t now;
	struct tm nowlocal;
	now = time(NULL);
	nowlocal = *localtime(&now);
	user[userfound].time[user[userfound].withdepnum].day = nowlocal.tm_mday;
	user[userfound].time[user[userfound].withdepnum].month = nowlocal.tm_mon + 1;
	user[userfound].time[user[userfound].withdepnum].year = nowlocal.tm_year + 1900;
	user[userfound].time[user[userfound].withdepnum].hour = nowlocal.tm_hour;
	user[userfound].time[user[userfound].withdepnum].min = nowlocal.tm_min;
	user[userfound].time[user[userfound].withdepnum].sec = nowlocal.tm_sec;

	user[userfound].balance -= withdrawamount;
	user[userfound].withdep[user[userfound].withdepnum] = withdrawamount;
	user[userfound].word[user[userfound].withdepnum] = "w";
	user[userfound].withdepnum++;
	Sleep(1000);
	system("cls");
	actionmenu(user, usernum, userfound);
}
void deposit(cust user[size], int &usernum, int &userfound)
{
	float depositamount;
	for (int i = 0; i < 10; i++)
	{
		cout << ".";
		Sleep(100);
	}
	system("cls");
	system("color F5");
	cout << "Enter the amount of money to deposit: $";
	cin >> depositamount;
	if (depositamount < 0)
	{
		system("cls");
		for (int i = 0; i < 10; i++)
		{
			cout << ".";
			Sleep(100);
		}
		system("cls");
		cout << "ERROR : Invalid Amount\n";
		Sleep(2000);
		deposit(user, usernum, userfound);
	}

	time_t now;
	struct tm nowlocal;
	now = time(NULL);
	nowlocal = *localtime(&now);
	user[userfound].time[user[userfound].withdepnum].day = nowlocal.tm_mday;
	user[userfound].time[user[userfound].withdepnum].month = nowlocal.tm_mon + 1;
	user[userfound].time[user[userfound].withdepnum].year = nowlocal.tm_year + 1900;
	user[userfound].time[user[userfound].withdepnum].hour = nowlocal.tm_hour;
	user[userfound].time[user[userfound].withdepnum].min = nowlocal.tm_min;
	user[userfound].time[user[userfound].withdepnum].sec = nowlocal.tm_sec;
	user[userfound].balance += depositamount;
	user[userfound].withdep[user[userfound].withdepnum] = depositamount;
	user[userfound].word[user[userfound].withdepnum] = "d";
	user[userfound].withdepnum++;
	system("cls");
	actionmenu(user, usernum, userfound);
}
void display(cust user[size], int &usernum, int &userfound)
{
	int num = user[userfound].withdepnum - 1;
	int number = 1;
	for (int i = 0; i < 10; i++)
	{
		cout << ".";
		Sleep(100);
	}
	system("cls");
	system("color F6");
	cout << "THE last 5 Trans.\n" << endl;
	while (number <= 5)
	{

		cout << number << ")" << user[userfound].word[num] << "- " << user[userfound].withdep[num] << " " << user[userfound].time[num].hour << ":" << user[userfound].time[num].min << ":" << user[userfound].time[num].sec << endl;
		num--;
		number++;
		if (num < 0)
		{
			break;
		}
	}
	cout << "press any key to continue..";
	_getch();
	system("cls");
	actionmenu(user, usernum, userfound);
}
void adminmenu(cust user[size], int &usernum, int &userfound)
{
	system("cls");
	system("color F6");
	for (int i = 0; i < 10; i++)
	{
		cout << ".";
		Sleep(100);
	}
	system("cls");
	int userpick;

	cout << "-------------------------------------------\n";
	cout << "                ADMIN Menu\n";
	cout << "-------------------------------------------\n" << endl;

	cout << "1- Search For User.\n";
	cout << "2- Display Transactions Of The Day.\n";
	cout << "3- Return To MainMenu.\n";
	cout << "Enter your choice: ";
	cin >> userpick;

	switch (userpick)
	{
	case 1:
		searchforuser(user, usernum, userfound);
		break;
	case 2:
		displaytime(user, usernum, userfound);
		break;

	case 3:
		mainmenu(user, usernum, userfound);
		break;

	default:
		cout << "ERROR: Please enter a valid option from the menu!";
		Sleep(1000);
		adminmenu(user, usernum, userfound);
	}
	adminmenu(user, usernum, userfound);
}
void searchforuser(cust user[size], int &usernum, int &userfound)
{
	system("cls");
	system("color F3");
	for (int i = 0; i < 10; i++)
	{
		cout << ".";
		Sleep(100);
	}
	system("cls");
	string us;
	cout << "Enter the username you want to search for : ";
	cin >> us;
	for (int i = 0; i < usernum; i++)
	{
		if (us == user[i].username)
		{
			userfound = i;
			displaytransactions(user, usernum, userfound);
		}
		else if (i == usernum - 1)
		{
			cout << us << " is not available here,you can come again." << endl;
			Sleep(1000);
			adminmenu(user, usernum, userfound);
		}

	}
	adminmenu(user, usernum, userfound);
}
void displaytransactions(cust user[size], int &usernum, int &userfound)
{

	int n = 1;
	int num = user[userfound].withdepnum - 1;
	cout << "The transactions of this user : " << endl;
	while (num >= 0)
	{
		cout << n << ") " << user[userfound].word[num] << "- " << user[userfound].withdep[num] << " " << user[userfound].time[num].hour << ":" << user[userfound].time[num].min << ":" << user[userfound].time[num].sec << endl;
		num--;
		n++;
	}
	cout << "Press any key to continue..";
	_getch();
	adminmenu(user, usernum, userfound);
}
void displaytime(cust user[size], int &usernum, int &userfound)
{
	system("cls");
	system("color F5");
	for (int i = 0; i < 10; i++)
	{
		cout << ".";
		Sleep(100);
	}
	system("cls");
	int d, m, y;//cin>>day>>month>>year(to compare);
	int counter = 1;
	int n = 1;
	cout << "Enter the date you want to search for : ";
	cin >> d >> m >> y;
	for (int i = 0; i < usernum; i++)
	{
		for (int j = user[i].withdepnum - 1; j >= 0; j--)
		{
			if (d == user[i].time[j].day && m == user[i].time[j].month && y == user[i].time[j].year)
			{
				cout << n << ")" << user[i].word[j] << "- " << user[i].withdep[j] << "->" << user[i].username << " " << user[i].time[j].hour << ":" << user[i].time[j].min << ":" << user[i].time[j].sec << endl;
				counter = 0;
				n++;
			}
		}
	}
	cout << "Press any key to continue..";
	_getch();
	if (counter == 1)
	{
		cout << "There is no transactions in this day .";
		Sleep(500);
		adminmenu(user, usernum, userfound);
	}
}