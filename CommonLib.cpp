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

bool Login(string &name) {
	string ID, Password;
	cout << "Login :" << endl;
	cout << setw(10) << "MSSV:";
	getline(cin >> ws, ID);
	cout << setw(10) << "Password:";
	getline(cin >> ws, Password);

	std::fstream AccountInfor;
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
				name = ID;
				return true;
			}
		}
		cout << "Incorrect!!" << endl;
		AccountInfor.close();
		name = "";
		return false;
	}
	else {
		cout << "Cannot open Accounts file" << endl;
		return false;
	}
	
}

bool CreateAccount() {
	string ID, password;
	int MSSV;

	cout << "Join in :" << endl;

	cout << setw(10) << "MSSV:";
	getline(cin >> ws, ID);
	if (!CheckID(ID)) return false;

	cout << setw(10) << "Password:";
	getline(cin >> ws, password);


	std::fstream AccountInfor;
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
		cout << "Failed to open Accounts file to ckeck!" << endl;
		return false;
	}
		AccountInfor.close();

		//If not, create new account
		AccountInfor.open(ACCOUNT_INFOR_FILE_LOCATION, ios::out | ios::in | ios::app);
		if (AccountInfor.is_open()) {
			string code = encrypt(ID + " " + password, ENCRYPT_KEY);
			AccountInfor << code << endl;
			AccountInfor.close();
			User user(ID);
			user.CreateNewUserFolder();
			user.SaveData();
			return true;
		}
		else {
			cout << "Failed to open Accounts file to write!" << endl;
			return false;
		}
}

User LoadUserData(string ID) {
	User myAccount(ID);
	myAccount.LoadData();
	return myAccount;
}

bool CheckNumber(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i]<'0' || str[i]>'9') return false;
	}
	return true;
}

bool CheckID(string ID) {
	if (ID == "ADMIN") return true;
	if (CheckNumber(ID)) return true;
	return false;
}

AVLTree<User>* LoadAllData() {
	AVLTree<User> *root=new AVLTree<User>();
	string ID;
	bool taller = true;
	std::fstream AccountInfor;
	AccountInfor.open(ACCOUNT_INFOR_FILE_LOCATION, ios::in);
	if (AccountInfor.is_open()) {
		while (!AccountInfor.eof()) {
			string str, temp;
			stringstream ss;
			getline(AccountInfor, str);
			str = decrypt(str, ENCRYPT_KEY);
			ss << str;
			ss >> ID >> temp;
			if (ID == "ADMIN") continue;
			User user = LoadUserData(ID);
			node<User> *usernode = new node<User>(user, stoi(user.get_ID(), nullptr));
			root->AVLInsert(usernode, taller);
		}
		AccountInfor.close();
	}
	else {
		cout << "Failed to load all users data !!" << endl;
		return false;
	}

	
	return root;
}

bool FindingUser() {
	AVLTree<User> *data = LoadAllData();
	while (true) {
		string ID;
		cout << "\nMSSV : ";
		getline(cin >> ws, ID);
		if (!CheckNumber(ID)||ID=="3") return 0;
		node<User> *user=new node<User>();
		if (!data->AVLSearch(user, stoi(ID, nullptr))) {
			cout << "Not Found!!" << endl;
			continue;
		}
		user->data.PrintScores();
	}

}