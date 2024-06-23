/*
G1_Kuik Rui Luan
Compiler: Microsoft Visual Studio
*/

// Library Function
#include <iostream>  
#include <cstring>  
#include <cctype>    
#include <string>    
#include <iomanip>   
#include <fstream>  
#include <ctime>     
#include <cstdlib>   

using namespace std;

//Define number of question in get_respd function
#define QUES_NUM 4

// Declare USER structure type that represents all the biodata information of users
struct USER {
	char name[100];
	char phone_num[100];
	char nric[100];
	char age[100];
	char gender[100];
	char race[100];
	char address[100];
	char username[100];
	char password[100];
	char classification[100];
	char first_dose_date[100];
	char first_dose_type[100];
	char sec_dose_date[100];
	char sec_dose_type[100];
	char third_dose_date[100];
	char third_dose_type[100];
};

USER user[500];

//Function Prototypes

//Register function prototypes
void register_main(void);
void registration(void);

//Vaccination Status Function Prototype
void vacStatus(void);
void dose_question(int doseNum);
void register_vac(int doseNum);

//Login Function Prototype
void login(void);
void chk_user(int* index, int i);

//Covid Question Function Prototype
void get_respd(int* ptr_respd1, int* ptr_respd2, int* ptr_respd3, int* ptr_respd4);
void categories(int respd1, int respd2, int respd3, int respd4, int size);

//Update Function Prototype
void update(int index);


// Main menu
int main(void)
{
	bool loop = true;
	do
	{
		system("cls");
		cout << "--------------------------  \n";
		cout << "   COVID-19 MANAGEMENT      \n";
		cout << "--------------------------\n\n";
		cout << "--MAIN MENU-- \n\n";
		cout << "1. LOGIN \n";
		cout << "2. REGISTER \n";
		cout << "3. QUIT \n\n";

		char choice;

		// ask user to select an option from the main menu
		cout << "SELECT AN OPTION: ";
		cin >> choice;

		if (choice == '1')
		{
			// if choice 1 is selected, login function will be called out
			login();
		}

		else if (choice == '2')
		{
			// if choice 2 is selected, register function will be called out
			register_main();
		}

		else if (choice == '3')
		{
			// if choice 3 is selected, system will shut down and the loop will be terminated.
			cout << "System is shutting down...." << endl;
			loop = false;
		}

		else
		{
			// if other than 1,2,3 is entered, system will show invalid option and ask user to select an option again. 
			cout << "\nInvalid Option\n\n" << endl;
		}
	} while (loop);
	return 0;
}

//Register function which asks users to register their biodata, covid, and vaccination information
void register_main(void)
{
	system("cls");
	cout << "=====================================================" << endl;
	cout << "                    Register Here                    " << endl;
	cout << "=====================================================" << endl;
	cout << "\n";
	char choice, proceed;

	cout << "Do you wish to register? [Y]: ";
	cin >> choice;
	//change to uppercase before check the input
	choice = toupper(choice);
	if (choice == 'Y')
	{
		//call registration function asks user to register their personal information 
		system("cls");
		registration();
		cout << "\nPress any key except ENTER to proceed to provide your Covid-19 information ..." << endl;
		cin >> proceed;
		/*
			if users agree to proceed, classify users to different covid - 19 categories by asking some covid - 19 question
			Pre: users need to answer the personal information before answer the covid-19 question
		*/
		if (proceed)
		{
			system("cls");
			int respd1, respd2, respd3, respd4;
			get_respd(&respd1, &respd2, &respd3, &respd4);
			categories(respd1, respd2, respd3, respd4, 0);
			cout << "Press any key except ENTER to proceed to provide your vaccination infomation ..." << endl;
			cin >> proceed;
			/*
				if users agree to proceed, ask users about their vaccination information
				Pre: users need to answer the personal information and covid-19 question before
				provide their vaccination information
			*/
			if (proceed)
			{
				system("cls");
				vacStatus();

				//save all the data in the file after all information is provided
				ofstream out_file("Biodata.txt", ios::app);
				if (!out_file)
					cout << "Error opening output file";
				else
				{
					out_file << user[0].name << "|" << user[0].phone_num << "|" << user[0].nric << "|" << user[0].age << "|"
						<< user[0].gender << "|" << user[0].race << "|" << user[0].address << "|" << user[0].username << "|"
						<< user[0].password << "|" << user[0].classification << "|" << user[0].first_dose_date << "|" << user[0].first_dose_type << "|"
						<< user[0].sec_dose_date << "|" << user[0].sec_dose_type << "|" << user[0].third_dose_date << "|" << user[0].third_dose_type << "\n";
					cout << "\n";
					cout << "Your data is saved. Thanks for registration." << endl;
				}
				out_file.close();
			}
		}
	}
	else
		cout << "Invalid input!" << endl;
	cout << "Press any key except ENTER to proceed to return main menu ..." << endl;
	cin >> proceed;
}

//Register function which asks users to register their biodata information
void registration(void)
{
	cout << "=====================================================" << endl;
	cout << "                    Register Here                    " << endl;
	cout << "=====================================================" << endl;
	cout << "\n";

	//ask the user to enter the phone number
	if (cin.peek() == '\n')
		cin.ignore(256, '\n');
	do
	{
		cout << "\nEnter the phone number: ";
		cin.getline(user[0].phone_num, 100);
		fflush(stdin);

		//check whether it is a number and the length of the phone number must be in 10 or 11
		if (strlen(user[0].phone_num) != 10 && strlen(user[0].phone_num) != 11)
		{
			cout << "Invalid phone number entered." << endl;
		}
	} while (strlen(user[0].phone_num) != 10 && strlen(user[0].phone_num) != 11);

	//ask the user to enter the full name
	bool validName;
	do
	{
		cout << "\nEnter the full name: ";
		cin.getline(user[0].name, 100);
		fflush(stdin);
		validName = true;
		for (int i = 0; i < strlen(user[0].name); i++)
		{
			user[0].name[i] = toupper(user[0].name[i]);
			//check the name entered by the user is valid and not contain number
			if (isdigit(user[0].name[i]))
			{
				validName = false;
				break;
			}
		}
		if (!validName)
		{
			cout << "Invalid name entered." << endl;
		}
	} while (!validName);

	//ask the user to enter username
	do
	{
		cout << "\nEnter the username: ";
		cin.getline(user[0].username, 100);
		fflush(stdin);

		//check the length of the input is not equal to zero to make sure the username is entered
		if (strlen(user[0].username) == 0)
		{
			cout << "Invalid usename entered." << endl;
		}
	} while (strlen(user[0].username) == 0);

	//ask the user to enter nric
	do
	{
		cout << "\nEnter NRIC [xxxxxx-xx-xxxx]: ";
		cin.getline(user[0].nric, 100);
		fflush(stdin);

		//check the length of the nric whether is 14
		if (strlen(user[0].nric) != 14)
		{
			cout << "Invalid NRIC entered." << endl;
		}
	} while (strlen(user[0].nric) != 14);

	//ask the user to enter the age
	bool validAge; 
	do
	{
		cout << "\nEnter the age: ";
		cin.getline(user[0].age, 100);
		fflush(stdin);
		validAge = true;
		//check the age entered is between 0-150
		for (int i = 0; i < strlen(user[0].age); i++)
		{
			//check the name entered by the user is valid and not contain number
			if (isalpha(user[0].age[i]))
			{
				validAge = false;
				break;
			}
		}
		if (!validAge || atoi(user[0].age) < 0 || atoi(user[0].age) > 150)
		{
			cout << "Invalid age entered." << endl;
		}
	} while (!validAge || atoi(user[0].age) < 0 || atoi(user[0].age) > 150); 

	//ask the user to enter the gender
	do
	{
		cout << "\nEnter gender Male[M] Female [F]: ";
		cin.getline(user[0].gender, 100);
		for (int i = 0; user[0].gender[i] != '\0'; i++) {
			user[0].gender[i] = toupper(user[0].gender[i]);
		}
		fflush(stdin);

		//check the gender entered by the user is M or F
		if (strcmp(user[0].gender, "M") != 0 && strcmp(user[0].gender, "F") != 0)
		{
			cout << "Invalid gender entered." << endl;
		}
	} while (strcmp(user[0].gender, "M") != 0 && strcmp(user[0].gender, "F") != 0);

	//ask the user to enter the race
	do
	{
		cout << "\n----------------------------------------------------------------" << endl;
		cout << "| Malay [M]               Chinese [C]               Indian [I] |" << endl;
		cout << "| Bumiputera Sabah [BSH]  Bumiputera Sarawak [BSK]  Others [O] |" << endl;
		cout << "----------------------------------------------------------------" << endl;
		cout << "\nEnter the race: ";
		cin.getline(user[0].race, 100);
		for (int i = 0; user[0].race[i] != '\0'; i++) {
			user[0].race[i] = toupper(user[0].race[i]);
		}
		fflush(stdin);

		//check the race entered is in the options
		if (!(strcmp(user[0].race, "M") == 0 || strcmp(user[0].race, "C") == 0 || strcmp(user[0].race, "I") == 0 || strcmp(user[0].race, "BSH") == 0 || strcmp(user[0].race, "BSK") == 0 || strcmp(user[0].race, "O") == 0))
		{
			cout << "Invalid race entered." << endl;
		}
	} while (!(strcmp(user[0].race, "M") == 0 || strcmp(user[0].race, "C") == 0 || strcmp(user[0].race, "I") == 0 || strcmp(user[0].race, "BSH") == 0 || strcmp(user[0].race, "BSK") == 0 || strcmp(user[0].race, "O") == 0));

	//ask the user to enter home address
	do
	{
		cout << "\nEnter the home address: ";
		cin.getline(user[0].address, 100);
		fflush(stdin);

		//check address entered is not equal to zero
		if (strlen(user[0].address) == 0)
		{
			cout << "Invalid home address entered." << endl;
		}
	} while (strlen(user[0].address) == 0);

	//ask the user to enter password
	do
	{
		cout << "\nEnter the password of at least 8 characters or numbers: ";
		cin.getline(user[0].password, 100);
		fflush(stdin);

		//check the password is in the length of 8
		if (strlen(user[0].password) < 8)
		{
			cout << "Invalid password entered. Please enter at least 8 characters or numbers." << endl;
		}
	} while (strlen(user[0].password) < 8);
}

/*
	Login function which allows users to update covid-19 status or show profile
	Login function which allows admin to view the number of cases in each category
	Pre: users must register their personal information before login
*/
void login(void)
{
	char proceed;
	bool loop = true;
	while (loop)
	{

		char opt;
		int i = 0;
		int index = 0;

		//open biodata text file to view user data
		ifstream in_file("Biodata.txt");
		if (!in_file)
			cout << "Error opening input file";
		//read data from the text file
		else
		{
			while (in_file.getline(user[i].name, 100, '|'))
			{
				in_file.getline(user[i].phone_num, 100, '|');
				in_file.getline(user[i].nric, 100, '|');
				in_file.getline(user[i].age, 100, '|');
				in_file.getline(user[i].gender, 100, '|');
				in_file.getline(user[i].race, 100, '|');
				in_file.getline(user[i].address, 100, '|');
				in_file.getline(user[i].username, 100, '|');
				in_file.getline(user[i].password, 100, '|');
				in_file.getline(user[i].classification, 100, '|');
				in_file.getline(user[i].first_dose_date, 100, '|');
				in_file.getline(user[i].first_dose_type, 100, '|');
				in_file.getline(user[i].sec_dose_date, 100, '|');
				in_file.getline(user[i].sec_dose_type, 100, '|');
				in_file.getline(user[i].third_dose_date, 100, '|');
				in_file.getline(user[i].third_dose_type, 100);
				i++;
			}
		}
		system("cls");
		cout << "-------------------------------------------------\n";
		cout << "                   Log In                        \n";
		cout << "-------------------------------------------------\n";
		cout << "1. Login as admin\n2. Login as user\n0. Exit\n" << endl;
		cout << "Enter option: ";
		cin >> opt;

		//login as admin to view number of cases in each category and view users' profiles
		if (opt == '1')
		{
			char admin[50];
			cout << "Username: ";
			cin >> admin;
			if (strcmp("admin", admin) == 0)
			{
				char adminpass[50];
				cout << "Password: ";
				cin >> adminpass;
				if (strcmp("hereisadmin", adminpass) == 0)
				{
					system("cls");
					char adminopt;
					cout << "Login as admin successfully!" << endl;
					cout << "\n1. Display number of cases in each category" << endl;
					cout << "2. View all users profile" << endl;
					cout << "\nSelect an option: ";
					cin >> adminopt;
					if (adminopt == '1')
					{
						int catA = 0;
						int catB = 0;
						int catC = 0;
						string line;
						ifstream in_file("Biodata.txt");
						if (!in_file)
							cout << "Error opening input file";
						else
						{
							//compute the number of cases in each category
							while (getline(in_file, line)) {
								if ((line.find("CONFIRMED CASE")) != string::npos) {
									catA++;
								}
								else if ((line.find("SUSPECTED CASE")) != string::npos ||
									(line.find("CLOSE CONTACT")) != string::npos ) {
									catB++;
								}
								else if ((line.find("LOW RISK")) != string::npos) {
									catC++;
								}
							}
						}
						in_file.close();
						//display the number of case in each category in table view
						system("cls");
						cout << "-----------------------------------------------------------" << endl;
						cout << "                       Category Table" << endl;
						cout << "-----------------------------------------------------------" << endl;
						cout << "\n\n";
						cout << " _______________________________________________________" << endl;
						cout << "|" << left << setw(10) << "Category|" << setw(25) << "Description" << setw(15) << "| Number of Case    |" << endl;
						cout << "|________|__________________________|___________________|" << endl;
						cout << "|" << setw(8) << " A      |" << setw(26) << "CONFIRMED CASE" << setw(5) << "|\t" << catA << "\t\t|" << endl;
						cout << "|" << setw(8) << " B      |" << setw(26) << "SUSPECTED CASE," << setw(5) << "|\t\t\t|" << endl;
						cout << "|" << setw(8) << "        |" << setw(26) << "CLOSE CONTACT" << setw(5) << "|\t" << catB << "\t\t|" << endl;
						cout << "|" << setw(8) << " C      |" << setw(26) << "LOW RISK" << setw(5) << "|\t" << catC << "\t\t|" << endl;
						cout << "|________|__________________________|___________________|" << endl;

						//display number of case in each category in horizontal bar graph view
						cout << "\n\n\n";
						cout << "------------------------------------------------------" << endl;
						cout << "                Horizontal Bar Graph" << endl;
						cout << "------------------------------------------------------" << endl;
						cout << "\n\n";
						cout << "\nA ";
						for (int row = 0; row < 2; row++)
						{
							for (int i = 0; i < catA; i++)
							{
								cout << "*";
							}
							cout << endl;
							cout << "  ";
						}

						cout << "\nB ";
						for (int row = 0; row < 2; row++)
						{
							for (int i = 0; i < catB; i++)
							{
								cout << "*";
							}
							cout << endl;
							cout << "  ";
						}

						cout << "\nC ";

						for (int row = 0; row < 2; row++)
						{
							for (int i = 0; i < catC; i++)
							{
								cout << "*";
							}
							cout << endl;
							cout << "  ";
						}

						cout << endl;
					}
					else if (adminopt == '2')
					{
						system("cls");
						for (int j = 0; j < i; j++)
						{
							cout << "User " << j + 1 << endl;
							cout << "______________________________________________________________________________________________________" << endl;
							cout << "|" << right << setw(20) << "Name: " << setw(30) << user[j].name << "|" << setw(20) << "Age: " << setw(30) << user[j].age << "|" << endl;
							cout << "|" << setw(20) << "IC: " << setw(30) << user[j].nric << "|" << setw(20) << "Gender: " << setw(30) << user[j].gender << "|" << endl;
							cout << "|" << setw(20) << "Phone Number: " << setw(30) << user[j].phone_num << "|" << setw(20) << "Race: " << setw(30) << user[j].race << "|" << endl;
							cout << "|_____________________________________________________________________________________________________|" << endl;
							cout << "|" << setw(20) << "Address: " << setw(60) << user[j].address << "                     |" << endl;
							cout << "|_____________________________________________________________________________________________________|" << endl;
							cout << "|" << setw(20) << "Status: " << setw(30) << user[j].classification << "|" << setw(51) << "|" << endl;
							cout << "|" << setw(20) << "First Dose Date: " << setw(30) << user[j].first_dose_date << "|" << setw(20) << "First Dose Type: " << setw(30) << user[j].first_dose_type << "|" << endl;
							cout << "|" << setw(20) << "Second Dose Date: " << setw(30) << user[j].sec_dose_date << "|" << setw(20) << "Second Dose Type: " << setw(30) << user[j].sec_dose_type << "|" << endl;
							cout << "|" << setw(20) << "Third Dose Date: " << setw(30) << user[j].third_dose_date << "|" << setw(20) << "Third Dose Type: " << setw(30) << user[j].third_dose_type << "|" << endl;
							cout << "|__________________________________________________|__________________________________________________|" << endl;
						}
					}
					else
					{
						cout << "Invalid input!" << endl;
					}
				}
				else
				{
					cout << "Password incorrect!" << endl;
				}
			}
			else
			{
				cout << "You are not an admin! Please login as user." << endl;
			}
			cout << "\nPress any key except ENTER to proceed to return login menu ..." << endl;
			cin >> proceed;
		}
		//login as user
		else if (opt == '2')
		{
			chk_user(&index, i);
			if (index != 0)
			{
				system("cls");
				char choice1;
				cout << "Login Successful !" << endl;
				cout << "\n1. Update Covid-19 Status " << endl;
				cout << "2. Show profile" << endl;
				cout << "\nSelect an option: ";
				cin >> choice1;
				//update Covid-19 status
				if (choice1 == '1')
				{
					int position = index - 1;
					update(position);
					ofstream out_file("Biodata.txt");
					if (!out_file)
						cout << "Error opening output file";
					else
					{
						for (int j = 0; j < i; j++)
						{
							out_file << user[j].name << "|" << user[j].phone_num << "|" << user[j].nric << "|" << user[j].age << "|"
								<< user[j].gender << "|" << user[j].race << "|" << user[j].address << "|" << user[j].username << "|"
								<< user[j].password << "|" << user[j].classification << "|" << user[j].first_dose_date << "|"
								<< user[j].first_dose_type << "|" << user[j].sec_dose_date << "|" << user[j].sec_dose_type << "|"
								<< user[j].third_dose_date << "|" << user[j].third_dose_type << "\n";
						}
					}
					out_file.close();
				}
				//display user's profile
				else if (choice1 == '2')
				{
					system("cls");
					cout << endl;
					cout << "______________________________________________________________________________________________________" << endl;
					cout << "|" << right << setw(20) << "Name: " << setw(30) << user[index - 1].name << "|" << setw(20) << "Age: " << setw(30) << user[index - 1].age << "|" << endl;
					cout << "|" << setw(20) << "IC: " << setw(30) << user[index - 1].nric << "|" << setw(20) << "Gender: " << setw(30) << user[index - 1].gender << "|" << endl;
					cout << "|" << setw(20) << "Phone Number: " << setw(30) << user[index - 1].phone_num << "|" << setw(20) << "Race: " << setw(30) << user[index - 1].race << "|" << endl;
					cout << "|_____________________________________________________________________________________________________|" << endl;
					cout << "|" << setw(20) << "Address: " << setw(60) << user[index - 1].address << "                     |" << endl;
					cout << "|_____________________________________________________________________________________________________|" << endl;
					cout << "|" << setw(20) << "Status: " << setw(30) << user[index - 1].classification << "|" << setw(51) << "|" << endl;
					cout << "|" << setw(20) << "First Dose Date: " << setw(30) << user[index - 1].first_dose_date << "|" << setw(20) << "First Dose Type: " << setw(30) << user[index - 1].first_dose_type << "|" << endl;
					cout << "|" << setw(20) << "Second Dose Date: " << setw(30) << user[index - 1].sec_dose_date << "|" << setw(20) << "Second Dose Type: " << setw(30) << user[index - 1].sec_dose_type << "|" << endl;
					cout << "|" << setw(20) << "Third Dose Date: " << setw(30) << user[index - 1].third_dose_date << "|" << setw(20) << "Third Dose Type: " << setw(30) << user[index - 1].third_dose_type << "|" << endl;
					cout << "|__________________________________________________|__________________________________________________|" << endl;
					in_file.close();
				}
				else
				{
					cout << "Invalid input!" << endl;
				}
			}
			cout << "\nPress any key except ENTER to return login menu ..." << endl;
			cin >> proceed;
		}
		//return to main menu
		else if (opt == '0')
		{
			loop = false;
		}
		else
		{
			cout << "Invalid input!\n" << endl;
			cout << "\nPress any key except ENTER to proceed to return login menu ..." << endl;
			cin >> proceed;
		}
	}
}

/*
	Ask for users' vaccination information about dose 1, 2 and 3
	If users do not register for vaccination, ask users if the users want to register for receiving vaccination
	Pre: users must register their personal information and answer the Covid-19 question before providing vaccination information
*/
void vacStatus(void)
{
	cout << "-------------------------------------------------\n";
	cout << "              Vaccination Status                 \n";
	cout << "-------------------------------------------------\n";

	int i = 0;
	char regVac, ansdose;
	int doseNum = 1;
	bool loop = true;
	while (loop)
	{
		do
		{
			cout << "Have you registered for vaccination?" << endl;
			cout << "1. Yes\n2. No\n0. Exit" << endl;
			cout << "Enter your answer: ";
			cin >> regVac;

			if (regVac == '0')
				break;
			//enter dose one information
			else if (regVac == '1')
			{
				system("cls");
				cout << "Please key in the information of your dose 1.\n";
				dose_question(doseNum);
				doseNum++;
				cout << "\nHave you taken dose " << doseNum << "? " << endl;
				cout << "1. Yes\n2. No\n";
				cout << "\nEnter your answer: ";
				cin >> ansdose;
			}
			//ask user to register for dose one
			else if (regVac == '2')
			{
				register_vac(doseNum);
			}
			else
				cout << "Invalid input!" << endl;
		} while (regVac != '1' && regVac != '2' && regVac != '0');

		//ask user about dose two information after user has provided dose one information
		if (doseNum == 2)
		{
			do
			{
				//enter dose two information
				if (ansdose == '1')
				{
					system("cls");
					dose_question(doseNum);
					doseNum++;
					cout << "\nHave you taken dose " << doseNum << "? " << endl;
					cout << "1. Yes\n2. No\n";
					cout << "\nEnter your answer: ";
					cin >> ansdose;
				}
				//ask user to register for dose two
				else if (ansdose == '2')
				{
					register_vac(doseNum);
				}
				//ask again the question if the users key in invalid input
				else
				{
					cout << "Invalid input!" << endl;
					cout << "\nHave you taken dose " << doseNum << "? " << endl;
					cout << "1. Yes\n2. No\n" << endl;
					cout << "\nEnter your answer: ";
					cin >> ansdose;
				}
			} while (ansdose != '1' && ansdose != '2');
		}

		//ask user about dose three information after user has provided dose one and two information
		if (doseNum == 3)
		{
			do
			{
				//enter dose three information
				if (ansdose == '1')
				{
					system("cls");
					dose_question(doseNum);
					cout << "\nThank you for protecting yourself and the community from Covid-19!" << endl;
					cout << "Together we stand, together we fight!\n" << endl;
				}
				//ask user to register for dose three
				else if (ansdose == '2')
				{
					register_vac(doseNum);
				}
				//ask again the question if the users key in invalid input
				else
				{
					cout << "Invalid input!" << endl;
					cout << "\nHave you taken dose " << doseNum << "? " << endl;
					cout << "1. Yes\n2. No\n";
					cout << "\nEnter your answer: ";
					cin >> ansdose;
				}
			} while (ansdose != '1' && ansdose != '2');
		}
		loop = false;
	}
}

/*
	Ask for users' either 1, 2 or 3 dose date and vaccine type they have received
	Display the dose question with dose number, doseNum accordingly
*/
void dose_question(int doseNum)
{
	int vac_type, day, month, year;
	cout << "Dose " << doseNum << ": " << endl;
	do {
		cout << "Enter the date of your dose (DD MM YYYY): ";
		cin >> day >> month >> year;
		//validate whether the date entered is in correct format
		if (day > 31 || month > 12 || !(year >= 2020 && year <= 2023)) {
			cout << "Invalid date! Please key in the date in correct format." << endl;
		}
		//assign the day, month and year to 1, 2 or 3 dose date
		else
		{
			if (doseNum == 1)
			{
				string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
				strcpy_s(user[0].first_dose_date, date.c_str());
			}
			else if (doseNum == 2)
			{
				string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
				strcpy_s(user[0].sec_dose_date, date.c_str());
			}
			else
			{
				string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
				strcpy_s(user[0].third_dose_date, date.c_str());
			}
		}
	} while (day > 31 || month > 12 || !(year >= 2020 && year <= 2023));

	string vacTypeLst[4] = { "AstraZenca", "Pfizer", "Sinovac", "Others" };
	do {
		cout << "\nEnter the vaccine type\n<0> AstraZenca\n<1> Pfizer\n<2> Sinovac\n<3> Others\n";
		cout << "Please enter the digit: ";
		cin >> vac_type;
		//validate whether users enter valid vaccine type
		if (vac_type < 0 || vac_type > 3) {
			cout << "Invalid vaccine type! Please key in the digit according to your vaccine type.\n" << endl;
		}
		//assign the vaccine type to 1, 2 or 3 dose type
		else
		{
			if (doseNum == 1)
			{
				const char* vacType = vacTypeLst[vac_type].c_str();
				strcpy_s(user[0].first_dose_type, vacType);
			}
			else if (doseNum == 2)
			{
				const char* vacType = vacTypeLst[vac_type].c_str();
				strcpy_s(user[0].sec_dose_type, vacType);
			}
			else
			{
				const char* vacType = vacTypeLst[vac_type].c_str();
				strcpy_s(user[0].third_dose_type, vacType);
			}
			cout << vacTypeLst[vac_type] << endl;
			cout << "\n";
		}
	} while (vac_type < 0 || vac_type > 3);
}

/*
	Ask users whether the users want to register for 1, 2 or 3 dose
	Display the register vaccine question with dose number, doseNum accordingly
*/
void register_vac(int doseNum)
{
	int reg_ans;
	do
	{
		cout << "\nDo you want to register for dose " << doseNum << "?" << endl;
		cout << "1. Yes\n2. No\n";
		cout << "Enter your answer: ";
		cin >> reg_ans;
		//Display successful registration statements
		if (reg_ans == 1)
		{
			cout << "\nThanks for your registration! We will contact you in a few days for further confirmation." << endl;
		}
		//Display information and importance of vaccination to encourage users to register for vaccination
		else if (reg_ans == 2)
		{
			cout << "\nWhat You Need To Know About COVID-19 Vaccine\n\n";
			cout << "Getting vaccinated is one of the most crucial steps in protecting yourself and\n";
			cout << "your loved ones from COVID-19. It is also to achieve herd immunity for the greater good.\n";
			cout << "Studies have shown that getting vaccinated against COVID-19 can lower your risk of\n";
			cout << "getting and spreading the virus that causes COVID-19. Vaccines also help reduce the risk of\n";
			cout << "severe illnesses and deaths from COVID-19 infections among people who are fully vaccinated.\n\n";
			cout << "Your loved ones need you.\n";
			cout << "Get your COVID-19 vaccine to make sure you can be there for them!\n";
		}
		else
			cout << "Invalid input!\n";
	} while (reg_ans != 1 && reg_ans != 2);
}

/*
	Check whether username is registered before
	If username is valid, validate the password is correctly match with the password registered before
	Allow users to re-enter the password if the users forgot their password
*/
void chk_user(int* index, int i)
{
	char proceed;
	bool loginSuccessful = false;
	while (!loginSuccessful) {
		char username[50];
		cout << "Username: ";
		cin >> username;
		bool usernameFound = false;
		for (int pos = 0; pos < i; pos++) {
			//check whether the username entered is registered in the biodata text file
			if (strcmp(user[pos].username, username) == 0)
			{
				usernameFound = true;
				char password[50];
				cout << "Password: ";
				cin >> password;
				//validate the password entered is matched correctly with username in biodata text file
				if (strcmp(user[pos].password, password) == 0)
				{
					cout << "Login successfully!" << endl;
					loginSuccessful = true;  // exit the loop since login is successful
					*index = pos + 1;
				}
				else
				{
					cout << "\nPassword incorrect!" << endl;
					char forgotpass;
					cout << "\n\nForgot password? [Y]es [N]o : ";
					cin >> forgotpass;

					if (forgotpass == 'y' || forgotpass == 'Y')
					{
						int random_number_entered;
						int random_number = 0;
						//use random number to display recaptcha and ask user to enter the recaptcha to ensure the user is human
						do
						{
							srand(time(NULL));
							random_number = rand() % 1000 + 1;
							cout << random_number << endl;
							cout << "\nEnter the number that show on screen: ";
							cin >> random_number_entered;

							if (random_number_entered != random_number)
								cout << "Please retry...\n";

						} while (random_number != random_number_entered);
						//ask user to enter new password
						cout << "\nNew password: ";
						if (cin.peek() == '\n')
							cin.ignore(256, '\n');
						cin.getline(user[pos].password, 100);

						//update biodata text file
						ofstream out_file("Biodata.txt", ios::out);
						if (!out_file)
							cout << "Error opening output file";
						else
						{
							for (int j = 0; j < i; j++)
							{
								out_file << user[j].name << "|" << user[j].phone_num << "|" << user[j].nric << "|" << user[j].age << "|" << user[j].gender << "|"
									<< user[j].race << "|" << user[j].address << "|" << user[j].username << "|" << user[j].password << "|" << user[j].classification << "|"
									<< user[j].first_dose_date << "|" << user[j].first_dose_type << "|" << user[j].sec_dose_date << "|" << user[j].sec_dose_type << "|"
									<< user[j].third_dose_date << "|" << user[j].third_dose_type << endl;
							}
						}
						out_file.close();

						cout << "Password changed! You may log in again with the new password. \n" << endl;
					}
					else
						cout << "Please login again.\n" << endl;  // exit the loop to login again since username was found, but password was incorrect
				}
			}
		}
		if (!usernameFound) {
			cout << "Username not found! Please return to the main menu to register an account.\n" << endl;
			loginSuccessful = true; // exit the loop since username was not found
		}
	}
}

/*
	Ask users about 4 Covid-19 questions and receive 4 answers from users
	4 responses from users are returned with pass-by-address method using pointers
*/
void get_respd(int* ptr_respd1, int* ptr_respd2, int* ptr_respd3, int* ptr_respd4)
{
	cout << "\n\nPlease answer the following question.\n";
	cout << "YES[1]  NO[2]\n\n";
	cout << "1. Do you have any underlying medical conditions that may increase your risk of severe illness from COVID-19, such as heart disease, diabetes, or lung disease? : ";
	cin >> *ptr_respd1;
	cout << "\n\n2. Have you recently traveled to an area with high COVID-19 transmission rates? : ";
	cin >> *ptr_respd2;
	cout << "\n\n3. Have you been to any COVID-19 cluster related events or areas? : ";
	cin >> *ptr_respd3;
	cout << "\n\n4. Do you live or work in an area where COVID-19 transmission is a high danger, such as a nursing home or healthcare facility? : ";
	cin >> *ptr_respd4;
}

/*
	Calculate the number of 'yes' response and 'no' response from the users in previous get_respd function
	Use switch statements to count the responses
	After the responses are calculated, users need to answer more questions so that the system can classify users to correct categories
	Reminders will be generated to remind users follow SOP
*/
void categories(int respd1, int respd2, int respd3, int respd4, int size)
{
	char proceed;
	int yes = 0;
	int no = 0;
	string classLst[4] = { "CONFIRMED CASE","SUSPECTED CASE","CLOSED CONTACT","LOW RISK" };
	switch (respd1)
	{
	case 1:
		yes++;
		break;
	case 2:
		no++;
		break;
	default:
		cout << "Invalid input.";
		break;
	}
	switch (respd2)
	{
	case 1:
		yes++;
		break;
	case 2:
		no++;
		break;
	default:
		cout << "Invalid input.";
		break;
	}
	switch (respd3)
	{
	case 1:
		yes++;
		break;
	case 2:
		no++;
		break;
	default:
		cout << "Invalid input.";
		break;
	}
	switch (respd4)
	{
	case 1:
		yes++;
		break;
	case 2:
		no++;
		break;
	default:
		cout << "Invalid input.";
		break;
	}

	/*
		Categorise users to category A - Confirmed case or category B - Suspected case / Close contact
		If users have been tested positive, users is categorised to category A and users are asked to quanrantine 7 days
		If users not tested positive but having symptoms or close contact, users are categorised to category B and users are asked to quarantine 3 days
		If users have not been tested positive and do not have any symptom and do not close contact, users are under category B also but users do not need to quarantine
	*/
	if (yes >= 2)
	{
		int respd_catA;
		cout << "You have been assigned to suspected case category, please answer the following question" << endl;
		cout << "\nHave you been tested positive for Covid-19 in the past two days? Yes[1], No[2]" << endl;
		cin >> respd_catA;
		if (respd_catA == 1)
		{
			cout << "\n---------------------------------------------------------------------------------------------------------------------";
			cout << "\nYou are in category A -- CONFIRMED CASE" << endl;
			cout << "\nPlease self-quarantine for 7 days to safeguard others around you and prevent the spread of COVID-19." << endl;
			cout << "\nReminder: Please update your COVID-19 self-test result everyday for the next 7 days." << endl;
			cout << "\n*NOTE* <You might be released earlier if you have tested negative on Day 4.>" << endl;
			const char* classification = classLst[0].c_str();
			strcpy_s(user[size].classification, classification);
		}
		else
		{
			int respd_catB1;
			int respd_catB2;
			cout << "\nHave you had any COVID-19 symptoms in the last 14 days, such as fever, cough, sore throat, bodyache, or shortness of breath?" << endl;
			cout << "YES[1]  NO[2]\n";
			cout << "\nAns: ";
			cin >> respd_catB1;
			if (respd_catB1 == 1)
			{
				cout << "\n---------------------------------------------------------------------------------------------------------------------";
				cout << "\nYou are in category B -- SUSPECTED CASE" << endl;
				cout << "\nPlease self-quarantine for 3 days to safeguard others around you and prevent the spread of COVID-19." << endl;
				cout << "\nReminder: Please update your COVID-19 self-test result on day 1 and day 3." << endl;
				cout << "\n*NOTE* <You may be released from quarantine if your COVID-19 self-test result on day 3 is negative and symptoms have improved.>" << endl;
				cout << "\n*NOTE* <You may consult with a doctor if you continue to have symptoms on day 3 even if the COVID-19 self-test result is negative.>" << endl;
				const char* classification = classLst[1].c_str();
				strcpy_s(user[size].classification, classification);
			}
			else
			{
				cout << "\nDo you staying with roommates or family members who tested positive Covid-19?" << endl;
				cout << "Yes[1]  No[2]\n";
				cout << "\nAns: ";
				cin >> respd_catB2;
				if (respd_catB2 == 1)
				{
					cout << "\n---------------------------------------------------------------------------------------------------------------------";
					cout << "\nYou are suspected to category B -- CLOSE CONTACT" << endl;
					cout << "\nPlease self-quarantine for 3 days to safeguard others around you and prevent the spread of COVID-19." << endl;
					cout << "\nReminder: Please update your COVID-19 self-test result on day 1 and day 3." << endl;
					cout << "\n*NOTE* <You may be released from quarantine if your COVID-19 self-test result on day 3 is negative.>" << endl;
					const char* classification = classLst[2].c_str();
					strcpy_s(user[size].classification, classification);
				}
				else
				{
					cout << "\n---------------------------------------------------------------------------------------------------------------------";
					cout << "\nYou are in category B -- SUSPECTED CASE" << endl;
					cout << "\nReminder: Please update your COVID-19 status weekly." << endl;
					cout << "\n\n!!It is important to take certain precautions to protect yourself from COVID-19." << endl;
					cout << "\nHere are some advices to follow:" << endl;
					cout << "# Wash your hands frequently with soap and water for at least 20 seconds, or use hand sanitizer if you are unable to wash your hands." << endl;
					cout << "# When coughing or sneezing, keep your hands away from your face and cover your mouth and nose with a tissue or your elbow." << endl;
					cout << "# Wear a well-fitting mask in public or among others to help prevent the spread of the virus." << endl;
					cout << "# Follow all standard operating procedure (SOP) established by your local government or health officials." << endl;
					const char* classification = classLst[1].c_str();
					strcpy_s(user[size].classification, classification);
				}
			}
		}
	}
	/*
		Categorise users to category C - Low Risk
		If users have COVID-19 symptoms, users do not need to quarantine and are allowed to work and study as usual if COVID-19 self-test result is negative
		If users do not have COVID-19 symptoms, users do not need to quarantine and are allowed to work and study as usual
	*/
	else
	{
		int respd_catC;
		const char* classification = classLst[3].c_str();
		strcpy_s(user[size].classification, classification);
		cout << "\nHave you had any COVID-19 symptoms in the last 14 days, such as fever, cough, sore throat, bodyache, or shortness of breath? : \n";
		cout << "YES[1]  NO[2]\n";
		cout << "Ans: ";
		cin >> respd_catC;
		if (respd_catC == 1)
		{
			cout << "\n---------------------------------------------------------------------------------------------------------------------";
			cout << "\nYou are in category C -- LOW RISK" << endl;
			cout << "\nReminder: Please update your COVID-19 self-test result for the next 3 days." << endl;
			cout << "\n\n!!It is important to take certain precautions to protect yourself from COVID-19." << endl;
			cout << "\nHere are some advices to follow:" << endl;
			cout << "# Wash your hands frequently with soap and water for at least 20 seconds, or use hand sanitizer if you are unable to wash your hands." << endl;
			cout << "# When coughing or sneezing, keep your hands away from your face and cover your mouth and nose with a tissue or your elbow." << endl;
			cout << "# Wear a well-fitting mask in public or among others to help prevent the spread of the virus." << endl;
			cout << "# Follow all standard operating procedure (SOP) established by your local government or health officials." << endl;
		}
		else
		{
			cout << "\n---------------------------------------------------------------------------------------------------------------------";
			cout << "\nYou are in category C -- LOW RISK" << endl;
			cout << "\n\n!!It is important to take certain precautions to protect yourself from COVID-19." << endl;
			cout << "\nHere are some advices to follow:" << endl;
			cout << "# Wash your hands frequently with soap and water for at least 20 seconds, or use hand sanitizer if you are unable to wash your hands." << endl;
			cout << "# When coughing or sneezing, keep your hands away from your face and cover your mouth and nose with a tissue or your elbow." << endl;
			cout << "# Wear a well-fitting mask in public or among others to help prevent the spread of the virus." << endl;
			cout << "# Follow all standard operating procedure (SOP) established by your local government or health officials." << endl;
		}
	}
}

/*
	Ask users to answer Covid-19 questions and receive responses
	Re-categorise the users to correct Covid-19 case categories
	Pre: users need to login as user before updating their information
*/
void update(int size)
{
	int respd1, respd2, respd3, respd4;
	get_respd(&respd1, &respd2, &respd3, &respd4);
	categories(respd1, respd2, respd3, respd4, size);
	const char* classification = user[size].classification;
	strcpy_s(user[size].classification, classification);
}

