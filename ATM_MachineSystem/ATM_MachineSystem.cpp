#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include<iomanip>
using namespace std;

const string File_Name = "Clients.txt";

struct  stClient_Info
{
	string Full_Name;
	string AccountNumber;
	string PinCode;
	int Balance;
};

vector <string> Split_String(string S1, string Delimiter = " || ")
{
	string delim = Delimiter;
	short pos = 0;
	string sWord;
	vector <string> V1;

	while ((pos = S1.find(delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			V1.push_back(sWord);
		}
		S1.erase(0, pos + delim.length());

	}
	if (S1 != "")
	{
		V1.push_back(S1);
	}
	return V1;

}

string Client_In_Line(stClient_Info Client_Info, string Separator = " || ")
{
	return Client_Info.Full_Name + Separator + Client_Info.AccountNumber + Separator + Client_Info.PinCode + Separator + to_string(Client_Info.Balance);
}

stClient_Info Line_To_Client(string S1, string Separator = " || ")
{
	stClient_Info Client_Info;
	vector <string> V1 = Split_String(S1, Separator);
	Client_Info.Full_Name = V1[0];
	Client_Info.AccountNumber = V1[1];
	Client_Info.PinCode = V1[2];
	Client_Info.Balance = stoi(V1[3]);

	return Client_Info;
}

void Save_File_InVECT(string File_Name, vector <string>& VClients)

{
	fstream File;
	File.open(File_Name, ios::in);

	if (File.is_open())
	{
		string Line;

		while (getline(File, Line))
		{
			VClients.push_back(Line);
		}

		File.close();
	}
}
void Save_Vect_In_File(vector <string> V1, string File_Name = "Clients.txt")
{
	ofstream File;
	File.open(File_Name, ios::trunc);
	File.close();

	File.open(File_Name, ios::out | ios::app);

	if (File.is_open())
	{
		for (string& K : V1)
		{
			File << K << endl;
		}
		File.close();
	}

}

void Show_Clients_Data(stClient_Info Client_Info , string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client;
	Save_File_InVECT(File_Name, V1);

	for (string& Line : V1)
	{
		Client = Line_To_Client(Line);
		if (Client.AccountNumber == Client_Info.AccountNumber)
		{
			cout << "\n_______________________________________________________";
			cout << "_____________________________________________\n" << endl;
			cout << "| " << left << setw(15) << "Account Number";
			cout << "| " << left << setw(10) << "Pin Code";
			cout << "| " << left << setw(40) << "Client Name";
			cout << "| " << left << setw(12) << "Balance";
			cout << "\n_______________________________________________________";
			cout << "_____________________________________________\n" << endl;
			cout << "| " << setw(15) << left << Client.AccountNumber;
			cout << "| " << setw(10) << left << Client.PinCode;
			cout << "| " << setw(40) << left << Client.Full_Name;
			cout << "| " << setw(12) << left << Client.Balance;
			cout << "\n_______________________________________________________";
			cout << "_____________________________________________\n" << endl;
		}
	}
	

}

bool Verify_AccNum(string AccountNum, string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client;
	Save_File_InVECT(File_Name, V1);

	for (string& Line : V1)
	{
		Client = Line_To_Client(Line);
		if (Client.AccountNumber == AccountNum)
		{
			return true;
		}
	}
	return false;
}


bool Verify_Pin(string Acc_Num, string Pin, string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client;
	Save_File_InVECT(File_Name, V1);

	for (string& Line : V1)
	{
		Client = Line_To_Client(Line);
		if (Client.AccountNumber == Acc_Num)
		{
			if (Client.PinCode == Pin)
			{
				return true;
			}
		}
	}
	return false;
}

stClient_Info GetClientByAccAndPin(string Account_Number, string Pin, string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client;
	Save_File_InVECT(File_Name, V1);

	for (string& Line : V1)
	{
		Client = Line_To_Client(Line);
		if (Client.AccountNumber == Account_Number)
		{
			if (Client.PinCode == Pin)
			{
				return Client;
			}
		}
	}
	return Client;
}
 
void Deposit(string AccountNumber, string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client_Info;
	string New;
	char Answer;
	bool yes = true;
	Save_File_InVECT(File_Name, V1);
	bool Found = false;
	for (int i = 0; i < V1.size(); i++)
	{
		Client_Info = Line_To_Client(V1[i]);

		if (Client_Info.AccountNumber == AccountNumber)
		{
			Found = true;

			cout << "\nPlease Enter The Amount You Want To Deposit In This Account  : \n";
			int Amount_To_Add;
			cin >> Amount_To_Add;


			do
			{
				cout << "\nDo You Confirm Deposit In This Account  Y/N \n";
				cin >> Answer;
				cout << endl << endl;

			} while (Answer != 'y' && Answer != 'Y' && Answer != 'n' && Answer != 'N');

			if (tolower(Answer) == 'n')
			{
				Client_Info.Balance = Client_Info.Balance - Amount_To_Add;
				yes = false;
			}

			Client_Info.Balance += Amount_To_Add;
			New = Client_In_Line(Client_Info);
			V1[i] = New;

			Save_Vect_In_File(V1);
			if (yes)
			{
				cout << "\n=========================================\n";
				cout << "|       Amount Successfully Added       |\n";
				cout << "=========================================\n";
			}
			else
			{
				cout << "\n================================================\n";
				cout << "|       Transaction Failed To Take Place       |\n";
				cout << "================================================\n";
			}
			break;
		}
	}
}

void NormalWithdraw(string Acc_Num, string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client_Info;
	string New;
	char Answer;
	bool yes = true;
	bool Can = false;
	Save_File_InVECT(File_Name, V1);
	bool Found = false;
	for (int i = 0; i < V1.size(); i++)
	{
		Client_Info = Line_To_Client(V1[i]);

		if (Client_Info.AccountNumber == Acc_Num)
		{
			Found = true;

			cout << "\n========================================================================";
			cout << "\n|   Please Enter The Amount You Want To Withdraw From This Account  :  |";
			cout << "\n========================================================================\n";
			cout << "|             Note : The Amount Must Be Able To Divide By 50            |\n";
			cout << "========================================================================\n";
			int Amount_To_Sub;
			cin >> Amount_To_Sub;
			cout << endl;

			while (Amount_To_Sub % 50 != 0)
			{
				cout << "\n==============================================================================\n";
				cout << "|             Note : The Amount You Entered Can't Be Divided By 50            |\n";
				cout << "==============================================================================\n";

				cout << " Re Enter The Amount  : ";
				cin >> Amount_To_Sub;
				cout << endl;

			}


			do
			{
				cout << "\nDo You Confirm Withdraw From This Account  Y/N  : ";
				cin >> Answer;
				cout << endl << endl;

			} while (Answer != 'y' && Answer != 'Y' && Answer != 'n' && Answer != 'N');

			if (tolower(Answer) == 'n')
			{
				yes = false;
			}
			else
			{

				if (Client_Info.Balance >= Amount_To_Sub)
				{
					Can = true;
					Client_Info.Balance = Client_Info.Balance - Amount_To_Sub;
					New = Client_In_Line(Client_Info);
					V1[i] = New;
				}
				else
				{
					cout << "\n=====================================================================================\n";
					cout << "|       You Can't Take That Amount From This Account As It Exceeds Its Balance      |\n";
					cout << "=====================================================================================\n";
				}
			}

			Save_Vect_In_File(V1);
			if (Can || yes == false)
			{
				if (yes)
				{
					cout << "\n=========================================\n";
					cout << "|       Amount Successfully Taken       |\n";
					cout << "=========================================\n";
				}
				else
				{
					cout << "\n================================================\n";
					cout << "|       Transaction Failed To Take Place       |\n";
					cout << "================================================\n";
				}
				break;
			}
		}
	}

}
void QuickWithdraw(string Acc_Num, int Amount_To_Sub , string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client_Info;
	string New;
	char Answer;
	bool yes = true;
	bool Can = false;
	Save_File_InVECT(File_Name, V1);
	bool Found = false;
	for (int i = 0; i < V1.size(); i++)
	{
		Client_Info = Line_To_Client(V1[i]);

		if (Client_Info.AccountNumber == Acc_Num)
		{
			Found = true;

			do
			{
				cout << "\nDo You Confirm Withdraw From This Account  Y/N  : ";
				cin >> Answer;
				cout << endl << endl;

			} while (Answer != 'y' && Answer != 'Y' && Answer != 'n' && Answer != 'N');

			if (tolower(Answer) == 'n')
			{
				yes = false;
			}
			else
			{

				if (Client_Info.Balance >= Amount_To_Sub)
				{
					Can = true;
					Client_Info.Balance = Client_Info.Balance - Amount_To_Sub;
					New = Client_In_Line(Client_Info);
					V1[i] = New;
				}
				else
				{
					cout << "\n=====================================================================================\n";
					cout << "|       You Can't Take That Amount From This Account As It Exceeds Its Balance      |\n";
					cout << "=====================================================================================\n";
				}
			}

			Save_Vect_In_File(V1);
			if (Can || yes == false)
			{
				if (yes)
				{
					cout << "\n=========================================\n";
					cout << "|       Amount Successfully Taken       |\n";
					cout << "=========================================\n";
				}
				else
				{
					cout << "\n================================================\n";
					cout << "|       Transaction Failed To Take Place       |\n";
					cout << "================================================\n";
				}
				break;
			}
		}
	}

}

void ShowAtmMenu()
{
	cout << "\n=========================================\n";
	cout << "|        ALGERIAN NATIONAL BANK         |\n";
	cout << "|               ATM MACHINE             |\n";
	cout << "=========================================\n";
	cout << "|  1. Quick Withdraw                    |\n";
	cout << "|  2. Normal Withdraw                   |\n";
	cout << "|  3. Deposit                           |\n";
	cout << "|  4. Veify Informations                |\n";
	cout << "|  5. Logout                            |\n";
	cout << "|  6. Exit                              |\n";
	cout << "=========================================\n";
	cout << ">> Please enter your choice (1-6) : ";
}

void ShowQuichWithdrawScreen()
{
	cout << "\n====================================================================================\n";
	cout << "|                                ALGERIAN NATIONAL BANK                            |\n";
	cout << "|                                       ATM MACHINE                                |\n";
	cout << "====================================================================================\n";
	cout << "|  Choose One Of The Below Amounts To Withdraw From your Account     :             |\n";
	cout << "|                                                                                  |\n";
	cout << "|  [1] = 50    [2] = 100    [3] = 200    [4] = 400    [5] = 600    [6] = 800       |\n";
	cout << "|  [7] = 1000               [8] = 2000                [9] = Exit ..                |\n";
	cout << "====================================================================================\n";
	cout << ">> Please enter your choice (1-9) : ";
}

stClient_Info LoginMenu()
{
	bool Done = false;
	stClient_Info Client;
	while (Done == false)
	{
		system("cls");
		cout << "\n==============================================\n";
		cout << "|           ALGERIAN NATIONAL BANK           |\n";
		cout << "|                  ATM MACHINE               |\n";
		cout << "==============================================\n";
		cout << "|  Login The Client Account ...             |\n";
		cout << "==============================================\n";
		string Acount_Number, PinCode;
		cout << " Enter Your Account Number : ";
		getline(cin >> ws, Acount_Number);
		cout << endl;

		if (Verify_AccNum(Acount_Number) == true)
		{
			cout << " Enter The PinCode  : ";
			getline(cin >> ws, PinCode);
			cout << endl;
			int Try = 3;

			while (Verify_Pin(Acount_Number, PinCode) == false)
			{
				if (Try == 0)
				{
					cout << " You Ran Out Of Chances To Enter Pin Code , Returning To Login Menu ..." << endl;
					cout << "\n>> Press Enter to return to the Login menu...";
					system("pause>0");
					break;
				}
				cout << " The Pin Code Is Wrong , Please Try Another One  : ";
				getline(cin >> ws, PinCode);
				cout << endl;
				Try--;
			}

			if (Verify_Pin(Acount_Number, PinCode) == true)
			{
				Done = true;
				Client = GetClientByAccAndPin(Acount_Number, PinCode);
			}

		}
		else
		{
			cout << " There Is No Account With This Number , Returning To Login Menu ..." << endl;
			cout << "\n>> Press Enter to return to the Login menu...";
			system("pause>0");

		}
	}

	return Client;

}

void Precise_AmountToSub(int Choice , int &Amount_To_Sub)
{
	switch (Choice)
	{
	case 1:
		Amount_To_Sub = 50;
		break;
	case 2:
		Amount_To_Sub = 100;
		break;
	case 3:
		Amount_To_Sub = 200;
		break;
	case 4:
		Amount_To_Sub = 400;
		break;
	case 5:
		Amount_To_Sub = 600;
		break;
	case 6:
		Amount_To_Sub = 800;
		break;
	case 7:
		Amount_To_Sub = 1000;
		break;
	case 8:
		Amount_To_Sub = 2000;
		break;
	}
}

int main()
{
	stClient_Info Client;

	bool Logout = true;
	int Choice = 0;
	do
	{
		if (Logout)
		{
			Client = LoginMenu();
		}

		Logout = false;

		system("cls");
		ShowAtmMenu();
		cin >> Choice;

		switch (Choice)
		{
		case 1:
		{
			bool Done = false;
			do
			{
				system("cls");
				ShowQuichWithdrawScreen();
				cin >> Choice;
				int Amount_To_Sub = 0;
				if (Choice > 0 && Choice <= 9)
				{
					if (Choice == 9)
					{
						Done = true;
						break;
					}
					else
					{
						Precise_AmountToSub(Choice, Amount_To_Sub);
						QuickWithdraw(Client.AccountNumber, Amount_To_Sub);
						Done = true;
					}
				}
				else
				{
					cout << " Invalid Choice , Choose One Of The Options  1-9 " << endl;
					break;
				}
			} while (Done != true);
			break;
		}
		case 2:
			system("cls");
			cout << "\n==============================================\n";
			cout << "|           ALGERIAN NATIONAL BANK           |\n";
			cout << "|                  ATM MACHINE               |\n";
			cout << "==============================================\n";
			cout << "|  Normal Withdrawing Screen ...             |\n";
			cout << "==============================================\n";

			NormalWithdraw(Client.AccountNumber);

			break;

		case 3:
			system("cls");
			cout << "\n==============================================\n";
			cout << "|           ALGERIAN NATIONAL BANK           |\n";
			cout << "|                  ATM MACHINE               |\n";
			cout << "==============================================\n";
			cout << "|  Depositing Screen ...                     |\n";
			cout << "==============================================\n";

			Deposit(Client.AccountNumber);

			break;
		case 4:
			system("cls");
			cout << "\n==============================================\n";
			cout << "|           ALGERIAN NATIONAL BANK           |\n";
			cout << "|                  ATM MACHINE               |\n";
			cout << "==============================================\n";
			cout << "|  Client Informations Screen ...            |\n";
			cout << "==============================================\n";

			Show_Clients_Data(Client);

			break;

		case 5:
			system("cls");
			cout << "\n==============================================\n";
			cout << "|           ALGERIAN NATIONAL BANK           |\n";
			cout << "|                  ATM MACHINE               |\n";
			cout << "==============================================\n";
			cout << "|  Logout Screen ...                         |\n";
			cout << "==============================================\n";
			Logout = true;

			cout << "\n>> Press Enter To Return To The Login Screen...";
			system("pause>0");
			break;

		case 6 :
			system("cls");
			cout << "\n==============================================\n";
			cout << "|           ALGERIAN NATIONAL BANK           |\n";
			cout << "|                  ATM MACHINE               |\n";
			cout << "==============================================\n";
			cout << "|  Exiting Program ...                       |\n";
			cout << "==============================================\n";

			break;


		default:
			cout << "\n===================================================\n";
			cout << "|              ALGERIAN NATIONAL BANK             |\n";
			cout << "|                     ATM MACHINE                 |\n";
			cout << "===================================================\n";
			cout << "[!] Invalid choice. Please select between 1 and 6.\n";
			cout << "===================================================\n";
			
		}

		if (Choice != 6 && Choice != 5)
		{
			cout << "\n>> Press Enter To Return To The ATM Menu...";
			system("pause>0");
		}

	} while (Choice != 6);



}