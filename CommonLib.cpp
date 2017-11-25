#include"CommonLib.h"

string encrypt(std::string msg, std::string key)
{
	// Make sure the key is at least as long as the message
	std::string tmp(key);
	while (key.size() < msg.size())
		key += tmp;

	// And now for the encryption part
	for (std::string::size_type i = 0; i < msg.size(); ++i) {
		msg[i] += key[i];
		
	}
	return msg;
}
string decrypt(std::string msg, std::string key)
{

	std::string tmp(key);
	while (key.size() < msg.size())
		key += tmp;

	// And now for the encryption part
	for (std::string::size_type i = 0; i < msg.size(); ++i) {
		msg[i] -= key[i];

	}
	return msg;
}

void UserMenu() {
	bool isLogin = false;
	while (!isLogin) {
		system("cls");
		int n;
		cout << "Choose action :\n1.Login\n2.Sign in\n3.Exit\nYour option: ";
		cin >> n;
		switch (n)
		{
		case 1:
			isLogin=Login();
			system("pause");
			break;
		case 2:
			CreateAccount();
			system("pause");
			break;
		case 3:
			return;
		default:
			break;
		}
	}
	system("cls");

	while (true) {
		system("cls");
		int n;
		cout << "Choose action :\n1.Submit\n2.See your scores\n3.Exit\nYour option: ";
		cin >> n;
		switch (n) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

bool Login() {	
	string ID, Password;
	cout << "Login :" << endl;
	cout << setw(10) << "MSSV:";
	getline(cin >> ws, ID);
	cout << setw(10) << "Password:";
	getline(cin >> ws, Password);

	fstream AccountInfor;
	AccountInfor.open(ACCOUNT_INFOR_FILE_LOCATION,ios::in);
	if (AccountInfor.is_open()) {

		while (!AccountInfor.eof()) {
			string str, ACID, ACPW;
			stringstream ss;
			getline(AccountInfor, str);
			str = decrypt(str, ENCRYPT_KEY);
			ss << str;
			ss >> ACID >> ACPW;
			if (ID == ACID&&Password == ACPW) {
				AccountInfor.close();
				cout << "Correct!!" << endl;
				return true;
			}
		}
		cout << "Incorrect!!" << endl;
		AccountInfor.close();
		return false;
	}
	else {
		cout << "Cannot open Accounts file" << endl;
		return false;
	}
	
}

bool CreateAccount() {
	string ID, password;
	cout << "Join in :" << endl;
	cout << setw(10) << "MSSV:";
	getline(cin >> ws, ID);
	cout << setw(10) << "Password:";
	getline(cin >> ws, password);
	fstream AccountInfor;
	AccountInfor.open(ACCOUNT_INFOR_FILE_LOCATION,ios::in);
	if (AccountInfor.is_open()) {

		//check if the account already existed
		while (!AccountInfor.eof()) {
			string str, ACID, ACPW;
			stringstream ss;
			getline(AccountInfor, str);
			str = decrypt(str, ENCRYPT_KEY);
			ss << str;
			ss >> ACID >> ACPW;
			if (ID == ACID) {
				AccountInfor.close();
				cout << "This account is already existed!!" << endl;
				return false;
			}
		}
	}
	else {
		cout << "Failed to open Accounts file!" << endl;
		return false;
	}
		AccountInfor.close();
		AccountInfor.open(ACCOUNT_INFOR_FILE_LOCATION, ios::out | ios::in | ios::app);
		//If not, create new account
		if (AccountInfor.is_open()) {
			string code = encrypt(ID + " " + password, ENCRYPT_KEY);
			AccountInfor << code << endl;
			AccountInfor.close();
			User user("ID");
			user.CreateNewUserFolder();
			return true;
		}
		else {
			cout << "Failed to open Accounts file!" << endl;
			return false;
		}
}

User LoadUserData(string ID) {
	User myAccount(ID);
	return myAccount;
}

