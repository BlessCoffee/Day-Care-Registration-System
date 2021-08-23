#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

/*
	Subject: CSEB324 Data Structure & Algorithms
	Project	 : Day Care Registration System 
	Developers : Ajay Samuel Sevaram and AMIERUL REDZUAN BIN MOHD KAMAL
*/

class DayCareSys {

	typedef struct birthdate {
		//A unique datatype that hold month, day, year as intergers

		int day;
		int month;
		int year;
	};

	typedef struct kids {
		/*Holds infomations only for each child*/

		string name;
		birthdate birthday;
		string gender;
		string guardian;
		string contact_no;
		string address;

	};

	typedef struct children {
		/*The tree struture*/

		int data;
		kids info; //Hold info for each child
		children* boy = NULL; //left pointer
		children* girl = NULL; //right pointer
	};

	children* root = NULL; // Declare root pointer as private
	bool root_ismale = false; // check whether root is male or not



	//Displays child info
	void display_Childinfo(children* ptr, int n = NULL) {
		if (n > 0) {
			cout << "Record #" << n << " Details:" << endl;
			cout << setw(20) << left << "Name" << right << ": " << ptr->info.name << endl;
			cout << setw(20) << left << "Date of Birth" << right << ": " << ptr->info.birthday.day << "-" << ptr->info.birthday.month << "-" << ptr->info.birthday.year << endl;
			cout << setw(20) << left << "Gender" << right << ": " << ptr->info.gender << endl;
			cout << setw(20) << left << "Guardian name" << right << ": " << ptr->info.guardian << endl;
			cout << setw(20) << left << "Contact no." << right << ": " << ptr->info.contact_no << endl;
			cout << setw(20) << left << "Address" << right << ": " << ptr->info.address << endl << endl;
		}

		else if (n == -1) {
			cout << "Record Details:" << endl;
			cout << setw(20) << left << "1. Name" << right << ": " << ptr->info.name << endl;
			cout << setw(20) << left << "2. Date of Birth" << right << ": " << ptr->info.birthday.day << "-" << ptr->info.birthday.month << "-" << ptr->info.birthday.year << endl;
			cout << setw(20) << left << "3. Gender" << right << ": " << ptr->info.gender << endl;
			cout << setw(20) << left << "4. Guardian name" << right << ": " << ptr->info.guardian << endl;
			cout << setw(20) << left << "5. Contact no." << right << ": " << ptr->info.contact_no << endl;
			cout << setw(20) << left << "6. Address" << right << ": " << ptr->info.address << endl << endl;
		}

		else {
			cout << "Record Details:" << endl;
			cout << setw(20) << left << "Name" << right << ": " << ptr->info.name << endl;
			cout << setw(20) << left << "Date of Birth" << right << ": " << ptr->info.birthday.day << "-" << ptr->info.birthday.month << "-" << ptr->info.birthday.year << endl;
			cout << setw(20) << left << "Gender" << right << ": " << ptr->info.gender << endl;
			cout << setw(20) << left << "Guardian name" << right << ": " << ptr->info.guardian << endl;
			cout << setw(20) << left << "Contact no." << right << ": " << ptr->info.contact_no << endl;
			cout << setw(20) << left << "Address" << right << ": " << ptr->info.address << endl << endl;
		}

	}

	//Inserts records into the system
	void insertRecord(children* ptr, children* parent) {

		if (root == NULL) {
			root = ptr;
			if (ptr->info.gender == "Male")
				root_ismale = true;
			else
				root_ismale = false;
		}

		else if (ptr->info.gender == "Male") {
			if (parent->boy != NULL)
				insertRecord(ptr, parent->boy);
			else
				parent->boy = ptr;
		}

		else if (ptr->info.gender == "Female") {
			if (parent->girl != NULL)
				insertRecord(ptr, parent->girl);
			else {
				parent->girl = ptr;
			}
		}

	}

	//Delete records from the system
	void delete_Node(children* ptr) {
		children* ptr2 = root;

		if (ptr == root) { //Deletion at root
			if (ptr->boy != NULL) {
				root = ptr2->boy;
				root->girl = ptr2->girl;
				free(ptr2);
				ptr2 = NULL;
				root_ismale = true;
			}
			else if (ptr->girl != NULL) {
				ptr2 = root;
				root = ptr2->girl;
				root->boy = ptr2->boy;
				free(ptr2);
				ptr2 = NULL;
				root_ismale = false;
			}
			else
				root = NULL;
		}

		else if (ptr->info.gender == "Male" && ptr != root) {//Deletion at male side

			if (ptr->boy == NULL) { //if there is no nodes connect to it //prob
				while (ptr2->boy != ptr)
					ptr2 = ptr2->boy;
				free(ptr);
				ptr2->boy = NULL;
			}
			else { //if there is there is nodes connect to it
				while (ptr2->boy != ptr)
					ptr2 = ptr2->boy;
				ptr2->boy = ptr->boy;
				free(ptr);
			}
		}

		else if (ptr->info.gender == "Female" && ptr != root) { //Deletion at female side

			if (ptr->girl == NULL) { //if there is no nodes connect to it
				while (ptr2->girl != ptr)
					ptr2 = ptr2->girl;
				free(ptr);
				ptr2->girl = NULL;
			}
			else { //if there is there is nodes connect to it
				while (ptr2->girl != ptr)
					ptr2 = ptr2->girl;
				ptr2->girl = ptr->girl;
				free(ptr);
			}
		}
	}


public:

	//Gets info from the users and creates a new record
	void register_Record() {
		cin.ignore('1000', '\n');
		system("cls");

		char gender;
		children* ptr = new children; // Create a new element memory space

		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
		cout << setw(40) << ":: REGISTER RECORD ::" << setw(20) << endl;
		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');

		cout << setw(40) << left << " Name" << right << ": ";
		getline(cin, ptr->info.name);

		cout << setw(40) << left << " Date of Birth <Date><Month><Year>" << right << ": ";
		cin >> ptr->info.birthday.day >> ptr->info.birthday.month >> ptr->info.birthday.year;

		cout << setw(40) << left << " Gender <M-Male> or <F-Female>" << right << ": ";
		cin >> gender;

		do {

			if (gender != 'F' && gender != 'f' && gender != 'M' && gender != 'm') {
				cout << setw(40) << left << " Error! Re-enter Gender" << right << ": ";
				cin >> gender;
			}

			switch (gender) {
			case 'F': ptr->info.gender = "Female"; break;
			case 'f': ptr->info.gender = "Female"; break;
			case 'M': ptr->info.gender = "Male"; break;
			case 'm': ptr->info.gender = "Male"; break;
			}
		} while (gender != 'F' && gender != 'f' && gender != 'M' && gender != 'm');
		cin.ignore('1000', '\n');
		cout << endl << "Emergency Contact:" << endl;
		cout << setw(40) << left << "Guardian name" << right << ": ";
		getline(cin, ptr->info.guardian);

		cout << setw(40) << left << "Contact no" << right << ": ";
		getline(cin, ptr->info.contact_no);

		cout << setw(40) << left << "Address" << right << ": ";
		getline(cin, ptr->info.address);

		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
		cout << " Registration Status : Completed" << endl;

		insertRecord(ptr, root);
		cout << endl;
		system("pause");
	}

	//Displays records to the user
	void view_Record() {
		system("cls");
		string choice;
		children* ptr = root;
		int male = 0, female = 0, flag = 0, num = 0;

		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
		cout << setw(40) << ":: DISPLAY RECORD ::" << setw(20) << endl;
		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');


		if (root != NULL) {

			do {

				if (flag == 0) {
					cout << " 1. List of Male children" << endl;
					cout << " 2. List of Female children" << endl;
					cout << " 3. List of All children" << endl;
					cout << " Enter selection: ";
					cin >> choice;

				}
				else {
					cout << "Error! Enter [1,2 or 3] : ";
					cin >> choice;
				}

				if (choice != "1" && choice != "2" && choice != "3")
					num = 0;
				if (choice == "1")
					num = 1;
				if (choice == "2")
					num = 2;
				if (choice == "3")
					num = 3;

				switch (num) {
				case 1:
					cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
					cout << setw(40) << ":: List Of Male Children ::" << setw(20) << endl;
					cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');

					if (root_ismale) {
						male++;
						display_Childinfo(ptr, male);
					}
					else
						female++;

					while (ptr->boy != NULL) {
						male++;
						ptr = ptr->boy;
						display_Childinfo(ptr, male);

					}

					ptr = root;
					while (ptr->girl != NULL) {
						female++;
						ptr = ptr->girl;
					}

					cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
					cout << "End of Record. " << endl;
					cout << "Total no of Male children : " << male << endl;
					cout << "Total no of All children : " << female + male << endl;

					break;

				case 2:
					cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
					cout << setw(40) << ":: List Of Female Children ::" << setw(20) << endl;
					cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');

					if (!root_ismale) {
						female++;
						display_Childinfo(ptr, female);
					}
					else
						male++;

					while (ptr->girl != NULL) {
						female++;
						ptr = ptr->girl;
						display_Childinfo(ptr, female);
					}

					ptr = root;
					while (ptr->boy != NULL) {
						male++;
						ptr = ptr->boy;
					}
					cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
					cout << "End of Record. " << endl;
					cout << "Total no of Female children : " << female << endl;
					cout << "Total no of All children : " << female + male << endl;

					break;

				case 3:

					cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
					cout << setw(40) << ":: List Of Male Children ::" << setw(20) << endl;
					cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');

					if (root_ismale) {
						male++;
						display_Childinfo(ptr, male);
					}


					while (ptr->boy != NULL) {
						male++;
						ptr = ptr->boy;
						display_Childinfo(ptr, male);

					}

					if (male == 0)
						cout << endl << " Display Status: No male records found" << endl << endl;

					cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
					cout << setw(40) << ":: List Of Female Children ::" << setw(20) << endl;
					cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
					ptr = root;

					if (!root_ismale) {
						female++;
						display_Childinfo(ptr, female);
					}


					while (ptr->girl != NULL) {
						female++;
						ptr = ptr->girl;
						display_Childinfo(ptr, female);

					}

					if (female == 0)
						cout << endl << " Display Status: No female records found" << endl << endl;

					cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
					cout << "End of Record. " << endl << endl;
					cout << "Total no of Male children : " << male << endl;
					cout << "Total no of Female children : " << female << endl;
					cout << "Total no of All children : " << female + male << endl;

					break;

				default: flag = 1;
				}

			} while (num != 1 && num != 2 && num != 3);
			cout << endl;
		}
		else
			cout << " Display Status: No record found" << endl << endl << endl << endl;
		system("pause");
	}

	//Search a particular record using it's name to search for it
	void search_Record() {

		cin.ignore('1000', '\n');
		system("cls");

		children* ptr = root;
		string name;
		int flag = 0;

		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
		cout << setw(40) << ":: SEARCH RECORD ::" << setw(20) << endl;
		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');


		if (root != NULL) {
			cout << " Enter Name of Children: ";
			getline(cin, name);
			cout << endl;
			if (ptr->info.name != name) {

				while (ptr->boy != NULL) {
					ptr = ptr->boy;
					if (ptr->info.name == name) {
						display_Childinfo(ptr);
						cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
						cout << " Search Status: Completed";
						flag = 1;
						break;
					}
				}

				ptr = root;

				while (ptr->girl != NULL) {
					ptr = ptr->girl;
					if (ptr->info.name == name) {
						display_Childinfo(ptr);
						cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
						cout << " Search Status: Completed";
						flag = 1;
						break;
					}
				}
			}
			else {
				display_Childinfo(ptr);
				cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
				cout << " Search Status: Completed";
				flag = 1;
			}
		}

		if (root == NULL) {
			cout << " Search Status: No record found" << endl << endl;
		}

		else if (flag != 1) {
			cout << " Search Status: No record found" << endl << endl;
		}
		cout << endl << endl;
		system("pause");
	}

	//Update records of interest using it's name to search for it
	void update_Record() {
		//needs testing
		cin.ignore('1000', '\n');
		system("cls");

		children* ptr = root;
		children* ptr2 = new children();
		string name, input, choice;
		int flag = 0, num = 0, flag2 = 0;
		char i;

		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
		cout << setw(40) << ":: UPDATE RECORD ::" << setw(20) << endl;
		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');


		if (root != NULL) {
			cout << " Enter Name of Children: ";
			getline(cin, name);
			cout << endl;
			if (ptr->info.name != name) {

				while (ptr->boy != NULL) {
					ptr = ptr->boy;
					if (ptr->info.name == name) {
						display_Childinfo(ptr, -1);
						cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
						flag = 1;
						break;
					}
				}

				ptr = root;

				while (ptr->girl != NULL) {
					ptr = ptr->girl;
					if (ptr->info.name == name) {
						display_Childinfo(ptr, -1);
						cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
						flag = 1;
						break;
					}
				}
			}
			else {
				display_Childinfo(ptr, -1);
				flag = 1;
				cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
			}

			if (flag == 1) {

				do {

					if (flag == 1) {
						cout << setw(21) << "Enter no to update" << left << ": ";
						cin >> choice;
						cin.ignore('1000', '\n');
					}

					if (flag == 2) {
						cout << setw(21) << "Error! Re-select no to update" << left << ": ";
						cin >> choice;
						cin.ignore('1000', '\n');
					}

					if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7")
						num = 0;
					if (choice == "1")
						num = 1;
					if (choice == "2")
						num = 2;
					if (choice == "3")
						num = 3;
					if (choice == "4")
						num = 4;
					if (choice == "5")
						num = 5;
					if (choice == "6")
						num = 6;
					if (choice == "7")
						num = 7;

					switch (num) {

					case 1:
						cout << " Enter new name: ";
						getline(cin, ptr->info.name);
						break;

					case 2:
						cout << " Enter new Date of Birth <day> <month> <year>: ";
						cin >> ptr->info.birthday.day >> ptr->info.birthday.month >> ptr->info.birthday.year;
						break;

					case 3:

						do {

							if (flag2 == 0) {

								cout << " Enter new Gender <M-male> <F-female>: ";
								cin >> i;
							}
							else {

								cout << " Error! enter <M-male> <F-female>: ";
								cin >> i;
							}

							switch (i) {
							case 'M': input = "Male"; break;
							case 'm': input = "Male"; break;
							case 'F': input = "Female"; break;
							case 'f': input = "Female"; break;
							default: flag2 = 2;
							}

						} while (i != 'M' && i != 'F' && i != 'f' && i != 'm');

						ptr2->info = ptr->info;
						delete_Node(ptr);
						ptr2->info.gender = input;
						insertRecord(ptr2, root);

						break;

					case 4:
						cout << " Enter new guardian name: ";
						getline(cin, ptr->info.guardian);
						break;

					case 5:
						cout << " Enter new contact no.: ";
						getline(cin, ptr->info.contact_no);
						break;

					case 6:
						cout << " Enter new address: ";
						getline(cin, ptr->info.address);
						break;

					default:
						flag = 2;

					}
				} while (num != 1 && num != 2 && num != 3 && num != 4 && num != 5 && num != 6);

				cout << " Update Status: Completed" << endl;
			}
		}

		if (root == NULL) {
			cout << " Update Status: No record found" << endl;
		}

		else if (flag == 0) {
			cout << " Update Status: No record found" << endl;
		}
		cout << endl << endl << endl;
		system("pause");
	}

	//Deletes record from the system
	void delete_Record() {
		cin.ignore('1000', '\n');
		system("cls");
		char input;
		children* ptr = root, * ptr2 = root;
		string name;
		int flag = 0;

		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
		cout << setw(40) << ":: DELETE RECORD ::" << setw(20) << endl;
		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');


		if (root != NULL) {
			cout << " Enter Name of Children: ";
			getline(cin, name);
			cout << endl;
			if (ptr->info.name != name) {

				while (ptr->boy != NULL) {
					ptr = ptr->boy;
					if (ptr->info.name == name) {
						display_Childinfo(ptr);
						cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
						flag = 1;
						ptr2 = ptr;
						break;
					}
				}
				ptr = root;
				while (ptr->girl != NULL) {
					ptr = ptr->girl;
					if (ptr->info.name == name) {
						display_Childinfo(ptr);
						cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
						ptr2 = ptr;
						flag = 1;
						break;
					}
				}
			}
			else {
				display_Childinfo(ptr);
				cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
				flag = 1;
				ptr2 = ptr;
			}

			if (flag == 1) {
				cout << " Enter 'Y' to delete : ";
				cin >> input;

				if (input == 'Y') {
					delete_Node(ptr2);
					flag = 1;
					cout << endl << " Deletetion Status: Completed" << endl << endl;
				}
				else {
					flag = 1;
					cout << endl << " Deletetion Status: Cancelled" << endl << endl;
				}

			}
		}



		if (flag == 0)
			cout << " Delete Status: No record found" << endl << endl << endl;


		cout << endl;
		system("pause");

	}

	//Saves all records into a text file
	void save_Record() {
		cin.ignore('1000', '\n');
		system("cls");

		int female = 0, male = 0;
		string input = "N";
		children* ptr = root;

		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
		cout << setw(40) << ":: Save Entries ::" << setw(20) << endl;
		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
		if (root != NULL) {
			cout << " If you save the current entries, it will override the previous entry [if there is any]" << endl << endl;
			cout << " are you sure you want to save it [Enter 'Y' to save] : ";
			cin >> input;

			if (input == "Y") {

				ofstream Saved_Child_Records("DayCare_ChildRecords.txt");
				if (Saved_Child_Records.is_open())
				{
					Saved_Child_Records << setw(59) << setfill('-') << "-" << endl << setfill(' ');
					Saved_Child_Records << setw(40) << ":: List Of Male Children ::" << setw(20) << endl;
					Saved_Child_Records << setw(59) << setfill('-') << "-" << endl << setfill(' ');

					if (root_ismale) {
						male++;
						Saved_Child_Records << "Record #" << male << " Details:" << endl;
						Saved_Child_Records << setw(20) << left << "Name" << right << ": " << ptr->info.name << endl;
						Saved_Child_Records << setw(20) << left << "Date of Birth" << right << ": " << ptr->info.birthday.day << "-" << ptr->info.birthday.month << "-" << ptr->info.birthday.year << endl;
						Saved_Child_Records << setw(20) << left << "Gender" << right << ": " << ptr->info.gender << endl;
						Saved_Child_Records << setw(20) << left << "Guardian name" << right << ": " << ptr->info.guardian << endl;
						Saved_Child_Records << setw(20) << left << "Contact no." << right << ": " << ptr->info.contact_no << endl;
						Saved_Child_Records << setw(20) << left << "Address" << right << ": " << ptr->info.address << endl << endl;
					}


					while (ptr->boy != NULL) {
						male++;
						ptr = ptr->boy;
						Saved_Child_Records << "Record #" << male << " Details:" << endl;
						Saved_Child_Records << setw(20) << left << "Name" << right << ": " << ptr->info.name << endl;
						Saved_Child_Records << setw(20) << left << "Date of Birth" << right << ": " << ptr->info.birthday.day << "-" << ptr->info.birthday.month << "-" << ptr->info.birthday.year << endl;
						Saved_Child_Records << setw(20) << left << "Gender" << right << ": " << ptr->info.gender << endl;
						Saved_Child_Records << setw(20) << left << "Guardian name" << right << ": " << ptr->info.guardian << endl;
						Saved_Child_Records << setw(20) << left << "Contact no." << right << ": " << ptr->info.contact_no << endl;
						Saved_Child_Records << setw(20) << left << "Address" << right << ": " << ptr->info.address << endl << endl;

					}

					if (male == 0)
						Saved_Child_Records << endl << " Display Status: No male records found" << endl << endl;

					Saved_Child_Records << setw(59) << setfill('-') << "-" << endl << setfill(' ');
					Saved_Child_Records << setw(40) << ":: List Of Female Children ::" << setw(20) << endl;
					Saved_Child_Records << setw(59) << setfill('-') << "-" << endl << setfill(' ');
					ptr = root;

					if (!root_ismale) {
						female++;
						Saved_Child_Records << "Record #" << female << " Details:" << endl;
						Saved_Child_Records << setw(20) << left << "Name" << right << ": " << ptr->info.name << endl;
						Saved_Child_Records << setw(20) << left << "Date of Birth" << right << ": " << ptr->info.birthday.day << "-" << ptr->info.birthday.month << "-" << ptr->info.birthday.year << endl;
						Saved_Child_Records << setw(20) << left << "Gender" << right << ": " << ptr->info.gender << endl;
						Saved_Child_Records << setw(20) << left << "Guardian name" << right << ": " << ptr->info.guardian << endl;
						Saved_Child_Records << setw(20) << left << "Contact no." << right << ": " << ptr->info.contact_no << endl;
						Saved_Child_Records << setw(20) << left << "Address" << right << ": " << ptr->info.address << endl << endl;
					}


					while (ptr->girl != NULL) {
						female++;
						ptr = ptr->girl;
						Saved_Child_Records << "Record #" << female << " Details:" << endl;
						Saved_Child_Records << setw(20) << left << "Name" << right << ": " << ptr->info.name << endl;
						Saved_Child_Records << setw(20) << left << "Date of Birth" << right << ": " << ptr->info.birthday.day << "-" << ptr->info.birthday.month << "-" << ptr->info.birthday.year << endl;
						Saved_Child_Records << setw(20) << left << "Gender" << right << ": " << ptr->info.gender << endl;
						Saved_Child_Records << setw(20) << left << "Guardian name" << right << ": " << ptr->info.guardian << endl;
						Saved_Child_Records << setw(20) << left << "Contact no." << right << ": " << ptr->info.contact_no << endl;
						Saved_Child_Records << setw(20) << left << "Address" << right << ": " << ptr->info.address << endl << endl;

					}

					if (female == 0)
						Saved_Child_Records << endl << " Display Status: No female records found" << endl << endl;

					Saved_Child_Records << setw(59) << setfill('-') << "-" << endl << setfill(' ');
					Saved_Child_Records << "End of Record. " << endl << endl;
					Saved_Child_Records << "Total no of Male children : " << male << endl;
					Saved_Child_Records << "Total no of Female children : " << female << endl;
					Saved_Child_Records << "Total no of All children : " << female + male << endl;
					Saved_Child_Records.close();

					cout << endl << " The text file named is 'DayCare_ChildRecords.txt'";

					cout << endl << " Saving Status: Completed";
				}

				else {
					cout << "Unable to open file -> Open Somewhere esle. ";
					cout << endl << " Saving Status: Failed" << endl << endl;
				}

			}
			else
				cout << endl << " Saving Status: Saving Declined" << endl << endl;

		}
		else
			cout << " Saving Status: No record found" << endl << endl;

		cout << endl << endl;
		system("pause");
	}

};

int main() {
	DayCareSys DayCareSys;
	string choice = "0";
	int num;

	do {
		system("cls");
		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
		cout << setw(40) << ":: DAY CARE MENU ::" << setw(20) << endl;
		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
		cout << "  1. Search Record" << endl;
		cout << "  2. Register Record" << endl;
		cout << "  3. Update Record" << endl;
		cout << "  4. Delete Record" << endl;
		cout << "  5. Save Entries" << endl;
		cout << "  6. View Record" << endl;
		cout << "  7. Quit" << endl;
		cout << setw(59) << setfill('-') << "-" << endl << setfill(' ');
		cout << " Enter choice: ";
		cin >> choice;

		if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7")
			num = 0;
		if (choice == "1")
			num = 1;
		if (choice == "2")
			num = 2;
		if (choice == "3")
			num = 3;
		if (choice == "4")
			num = 4;
		if (choice == "5")
			num = 5;
		if (choice == "6")
			num = 6;
		if (choice == "7")
			num = 7;


		switch (num) {

		case  1: DayCareSys.search_Record(); break;
		case  2: DayCareSys.register_Record(); break;
		case  3: DayCareSys.update_Record(); break;
		case  4: DayCareSys.delete_Record(); break;
		case  5: DayCareSys.save_Record(); break;
		case  6: DayCareSys.view_Record(); break;
		}

	} while (num != 7);

	cout << endl << " ~~~ Thank you for using the system, Be Blessed ~~~ " << endl << endl;

	return 0;
}
