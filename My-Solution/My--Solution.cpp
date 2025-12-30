
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.text";

struct sClientInfo
{
	string AccountNumber;
	string PIN;
	string Name;
	string PhoneNumber;
	double AccountBalance;
	bool MarkForDelete = false;
};

enum enMainMenueOptions {
	eClientsList = 1, eAddNewClient = 2, eDeleteClient = 3,
	eUpdataClient = 4, eFindClient = 5, eTransactions = 6, eExit = 7
};

enum enTransactionsMenueOption { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenue = 4 };

void ShowMainMenueScreen();
void ShowTransactionsMenueScreen();
void SaveClientsDataToFile(string FileName, vector<sClientInfo>& vClients);
void SaveClientDataToFile(string FileName, string stDataLine);

vector<string> SplitvString(string St1, string delim)
{
	vector <string> vString;
	short Pos = 0;
	string sWord = "";
	while ((Pos = St1.find(delim)) != string::npos)
	{
		sWord = St1.substr(0, Pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		St1.erase(0, Pos + delim.length());
	}
	if (St1 != "")
	{
		vString.push_back(St1);
	}
	return vString;
}

sClientInfo ConvertLineToRecord(string strClientInfoLine, string Seperator = "#//#")
{
	sClientInfo Client;
	vector<string>vClientData;

	vClientData = SplitvString(strClientInfoLine, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PIN = vClientData[1];
	Client.Name = vClientData[2];
	Client.PhoneNumber = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

short ReadMainMenueOption()
{
	short Number = 0;

	do {

		cout << "\nChoose What do you want to do ?[1 To 7]?";
		cin >> Number;

	} while (Number < 1 || Number>7);

	return Number;
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter an account number ?";
	cin >> AccountNumber;

	return AccountNumber;
}

bool ClientExistsByAccountNumber(string AccountNumber)
{
	fstream MyFile;

	MyFile.open(ClientsFileName, ios::in);

	if (MyFile.is_open())
	{
		string DataLine = "";
		sClientInfo Client;

		while (getline(MyFile, DataLine))
		{
			Client = ConvertLineToRecord(DataLine);

			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}

		}
		MyFile.close();
	}
	return false;
}

void PrintClientRecord(sClientInfo Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PIN;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.PhoneNumber;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}

sClientInfo ReadNewClientInfo()
{
	sClientInfo ClientInfo;

	cout << "\nEnter an account number? ";
	getline(cin >> ws, ClientInfo.AccountNumber);

	while (ClientExistsByAccountNumber(ClientInfo.AccountNumber))
	{
		cout << "\nClient With [" << ClientInfo.AccountNumber << "] already exists,Enter another Account Number?";
		getline(cin, ClientInfo.AccountNumber);
	}


	cout << "\nEnter PinCode? ";
	getline(cin >> ws, ClientInfo.PIN);

	cout << "\nEnter Name? ";
	getline(cin, ClientInfo.Name);

	cout << "\nEnter Phone? ";
	getline(cin, ClientInfo.PhoneNumber);

	cout << "\nEnter AccountBalance? ";
	cin >> ClientInfo.AccountBalance;

	return ClientInfo;
}

string ConvertRecordToLine(sClientInfo& ClientInfo, string Dilem = "#//#")
{
	string Text = "";

	Text += ClientInfo.AccountNumber + Dilem;
	Text += ClientInfo.PIN + Dilem;
	Text += ClientInfo.Name + Dilem;
	Text += ClientInfo.PhoneNumber + Dilem;
	Text += to_string(ClientInfo.AccountBalance);

	return Text;
}


void SaveClientDataToFile(string FileName, string stDataLine)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;

		MyFile.close();
	}

}

void AddNewClient()
{

	sClientInfo Client;

	Client = ReadNewClientInfo();
	SaveClientDataToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddNewClients()
{
	char AddMore = 'y';
	do
	{


		cout << "\nAdding New Client:\n";

		AddNewClient();

		cout << "\nClient added successfully,do you want to add more clients (Y or N) ?";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');


}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClientInfo>& vClients)
{
	for (sClientInfo& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

void ShowAddNewClientsScreen()
{
	cout << "_______________________________________\n";
	cout << "\tAdding New Clients Screen\n";
	cout << "_______________________________________\n";

	AddNewClients();

}

bool FindClientAccountNumber(string AccountNumber, vector<sClientInfo>& vClients, sClientInfo& Client)
{

	for (sClientInfo& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}

	return false;
}

vector<sClientInfo> LoadClientsDataFromFile(string FileName)
{


	vector<sClientInfo> vClients;

	fstream MyFile;

	MyFile.open(FileName, ios::in);


	if (MyFile.is_open())
	{
		string Line = "";
		sClientInfo Client;

		while (getline(MyFile, Line))
		{

			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}

	return vClients;
}

void PrintClientCard(sClientInfo& ClientInfo)
{
	cout << "\nThe following are the client details:\n\n";

	cout << setw(17) << "AccountNumber   : " << ClientInfo.AccountNumber << endl;
	cout << setw(17) << "pin Code        : " << ClientInfo.PIN << endl;
	cout << setw(17) << "Name            : " << ClientInfo.Name << endl;
	cout << setw(17) << "Phone           : " << ClientInfo.PhoneNumber << endl;
	cout << setw(17) << "Account Balance : " << ClientInfo.AccountBalance << endl;

}

void SaveClientsDataToFile(string FileName, vector<sClientInfo>& vClients)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (sClientInfo& C : vClients)
		{
			string DataLine = "";
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}

		MyFile.close();
	}

}

void ShowAllClientsScreen()
{

	vector<sClientInfo> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n\n";
	cout << "----------------------------------------------------------------------------------------------------------------\n\n";
	cout << "| " << left << setw(15) << "Account Number ";
	cout << "| " << left << setw(10) << "Pin Code ";
	cout << "| " << left << setw(40) << "Client Name ";
	cout << "| " << left << setw(12) << "Phone ";
	cout << "| " << left << setw(8) << "Account Balance ";
	cout << "\n\n----------------------------------------------------------------------------------------------------------------\n\n";


	if (vClients.size() == 0)
	{
		cout << "\n\nNo Available In The System !\n";
	}

	for (sClientInfo& Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}

	cout << "\n\n----------------------------------------------------------------------------------------------------------------\n\n";



}

void GoBackToMainMenue()
{
	cout << "\n\nPress Any Key To Go Back To Main Menue ...!";
	system("pause>0");
	ShowMainMenueScreen();
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClientInfo>& vClients)
{

	sClientInfo Client;
	char Answer = 'n';

	if (FindClientAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);


		cout << "\nAre you sure that you want to delete this Client\n";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);

			vClients = LoadClientsDataFromFile(ClientsFileName);

			cout << "\nClient deleted Successfully\n";

			return true;
		}
		else
		{
			cout << "\nClient was not deleted.\n";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not found !\n\n";
	}
	return false;
}

sClientInfo ChangeClientRecord(string AccountNumber)
{
	sClientInfo ClientInfo;

	ClientInfo.AccountNumber = AccountNumber;

	cout << "\nEnter PinCode?";
	getline(cin >> ws, ClientInfo.PIN);

	cout << "\nEnter Name?";
	getline(cin, ClientInfo.Name);

	cout << "\nEnter Phone?";
	getline(cin, ClientInfo.PhoneNumber);

	cout << "\nEnter AccountBalance?";
	cin >> ClientInfo.AccountBalance;


	return ClientInfo;

}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClientInfo>& vClients)
{


	sClientInfo Client;
	char Answer = 'n';

	if (FindClientAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\nAre you sure that you want to update this Client? (Y or N)?";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			for (sClientInfo& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\nClient Updated Successfully\n";
			return true;
		}
		else
		{
			cout << "\nClient was not Updated.\n";
			return false;
		}

	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not found !\n\n";
		return false;
	}


}

void ShowFindClientScreen()
{
	cout << "---------------------------------\n";
	cout << "\tFind Client Screen\n";
	cout << "---------------------------------\n";

	vector<sClientInfo> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	sClientInfo Client;

	if (FindClientAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient With Account Number[" << AccountNumber << "] is Not found!" << endl;
	}

}

void ShowDeleteClientScreen()
{
	cout << "------------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "------------------------------------\n";

	vector<sClientInfo>vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void GoBackToTransactionMenue()
{
	cout << "\nPress Any Key To Go Back To Transaction Menue ...";
	system("pause>0");
	ShowTransactionsMenueScreen();
}

float ReadWithdrawAmount()
{
	float Amount = 0.0;

	cout << "\nPlease enter withdraw amount ?";
	cin >> Amount;

	return Amount;
}

void ShowUpdateClientInfoScreen()
{
	cout << "--------------------------------------\n";
	cout << "\tUpdate Client Info Screen\n";
	cout << "--------------------------------------\n";

	vector<sClientInfo> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	UpdateClientByAccountNumber(AccountNumber, vClients);

}

bool DepositBalanceToClinetByAccountNumber(string AccountNumber, double Amount, vector<sClientInfo>& vClient)
{


	char Answer = 'n';

	cout << "\nAre you sure that you want to perform this transaction? y/n ?";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y')
	{

		for (sClientInfo& C : vClient)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance = C.AccountBalance + Amount;
				SaveClientsDataToFile(ClientsFileName, vClient);
				cout << "\nDone Successfully New Balance = " << C.AccountBalance << endl;
				return true;
			}
		}

	}

	return false;

}

void ShowTransactionDepositScreen()
{
	cout << "-----------------------------------------\n";
	cout << "\tDeposit Screen\n";
	cout << "-----------------------------------------\n";

	vector<sClientInfo>vClient = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	sClientInfo Client;

	while (!FindClientAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		cout << "\nPlease enter an account number ?";
		AccountNumber = ReadClientAccountNumber();
	}


	PrintClientCard(Client);

	double Amount = 0.0;
	cout << "\nPlease enter deposit amount ?";
	cin >> Amount;



	DepositBalanceToClinetByAccountNumber(AccountNumber, Amount, vClient);

}

double TotalBalances(vector<sClientInfo>& vClient)
{
	double TotalBalances = 0.0;

	for (sClientInfo Client : vClient)
	{
		TotalBalances = TotalBalances + Client.AccountBalance;
	}

	return TotalBalances;
}

void PrintClientRecordBalanceLine(sClientInfo& Client)
{
	cout << "| " << left << setw(20) << Client.AccountNumber;
	cout << "| " << left << setw(35) << Client.Name;
	cout << "| " << left << setw(40) << Client.AccountBalance;

}

void ShowTotalBalances()
{
	vector<sClientInfo> vClient = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tBalances List (" << vClient.size() << ") Client(s).\n";

	cout << "----------------------------------------------------------------------------------------------------------------------\n\n";
	cout << "| " << left << setw(20) << "Account Number ";
	cout << "| " << left << setw(35) << "Client Name ";
	cout << "| " << left << setw(40) << "Account Balance ";
	cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";


	if (vClient.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In The System!";
	}
	else
	{

		for (sClientInfo& Client : vClient)
		{
			PrintClientRecordBalanceLine(Client);
			cout << endl;
		}

		cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";

		cout << "\t\t\t\t\t\tTotal Balances = " << TotalBalances(vClient) << endl;
	}

}

void ShowTransactionsWithdrawScreen()
{
	cout << "-------------------------------------\n";
	cout << "\tWithdraw Screen\n";
	cout << "-------------------------------------\n";

	vector<sClientInfo>vClient = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	sClientInfo Client;

	while (!FindClientAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		cout << "\nPlease enter an account number ?";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0.0;
	cout << "\nPlease enter deposit amount ?";
	cin >> Amount;


	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance,you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter another amount ?";
		cin >> Amount;
	}


	DepositBalanceToClinetByAccountNumber(AccountNumber, Amount * -1, vClient);


}

void ShowExitScreen()
{
	cout << "------------------------------\n";
	cout << "\tProgram Ends\n";
	cout << "------------------------------\n";
}

void PerformTransactionsMenueOption(enTransactionsMenueOption TransactionsMenueOption)
{

	switch (TransactionsMenueOption)
	{
	case enTransactionsMenueOption::eDeposit:
		system("cls");
		ShowTransactionDepositScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionsMenueOption::eWithdraw:
		system("cls");
		ShowTransactionsWithdrawScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionsMenueOption::eTotalBalances:
		system("cls");
		ShowTotalBalances();
		GoBackToTransactionMenue();
		break;

	case enTransactionsMenueOption::eMainMenue:

		ShowMainMenueScreen();

	}


}

short ReadTransactionsMenueOption()
{
	short Choice = 0;

	do
	{
		cout << "\nChoose What do you want to do?[1 To 4]?";
		cin >> Choice;

	} while (Choice < 1 || Choice > 4);

	return Choice;
}

void ShowTransactionsMenueScreen()
{
	system("cls");
	cout << "==========================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "==========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "==========================================\n";


	PerformTransactionsMenueOption((enTransactionsMenueOption)ReadTransactionsMenueOption());
}

void PerformMainMenueOption(enMainMenueOptions MainMenueOptions)
{

	switch (MainMenueOptions)
	{
	case enMainMenueOptions::eClientsList:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eUpdataClient:
		system("cls");
		ShowUpdateClientInfoScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eTransactions:
		system("cls");
		ShowTransactionsMenueScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eExit:
		system("cls");
		ShowExitScreen();
		break;
	}

}

void ShowMainMenueScreen()
{
	system("cls");
	cout << "=============================================\n";
	cout << "\t\tMain Menue Screen.\n";
	cout << "=============================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Updata Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit\n";
	cout << "=============================================\n";

	PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}


int main()
{

	ShowMainMenueScreen();


	return 0;
}

