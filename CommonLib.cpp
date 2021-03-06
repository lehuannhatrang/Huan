#include"CommonLib.h"

/* Use key to encrypt the account infor */
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

/* Use key to decrypt the account infor */
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

/* Login Function */
bool Login(string &name) {
	string ID, Password;
	cout << "Login :" << endl;
	cout << setw(10) << "MSSV:";
	getline(cin >> ws, ID);
	cout << setw(10) << "Password:";
	getline(cin >> ws, Password);

	std::fstream AccountInfor;
	AccountInfor.open(ACCOUNT_INFOR_FILE_LOCATION,ios::in);		//open file to read
	if (AccountInfor.is_open()) {
		//read all the file 
		while (!AccountInfor.eof()) {
			string str, ACID, ACPW;
			stringstream ss;
			getline(AccountInfor, str);
			str = decrypt(str, ENCRYPT_KEY);	//decript the infor
			ss << str;
			ss >> ACID >> ACPW;
			if (ID == ACID&&Password == ACPW) {
				AccountInfor.close();			//close the accounts infor file
				cout << "Correct!!" << endl;	
				name = ID;						//get name
				return true;
			}
		}
		cout << "Incorrect!!" << endl;			//dont find the correct infor -> exit
		AccountInfor.close();					
		name = "";
		return false;
	}
	else {
		cout << "Cannot open Accounts file" << endl;	
		return false;
	}
	
}

/* Function to create new account*/
bool CreateAccount() {
	string ID, password;
	int MSSV;

	cout << "Join in :" << endl;

	cout << setw(10) << "MSSV:";
	getline(cin >> ws, ID);
	if (!CheckID(ID)) return false;			//Check if it is an ID

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
			AccountInfor  << code << endl;
			AccountInfor.close();			//close the account infor file
			User user(ID);					
			user.CreateNewUserFolder();		//create new folder for this account
			user.SaveData();				//save this account data
			return true;
		}
		else {
			cout << "Failed to open Accounts file to write!" << endl;
			return false;
		}
}

/* Load the user data */
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
	if (ID == "ADMIN"||ID=="Teacher") return true;
	if (CheckNumber(ID)&&ID.length()>5) return true;
	cout << "It's not a student's ID" << endl;
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
			if (str == "") continue;
			str = decrypt(str, ENCRYPT_KEY);			
			ss << str;
			ss >> ID >> temp;
			if (ID == "ADMIN"||ID=="Teacher") continue;
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

bool FindingUser(AVLTree<User> *data) {
	while (true) {
		string ID;
		cout << "\nMSSV : ";
		getline(cin >> ws, ID);
		if (!CheckNumber(ID)||ID=="x") return 0;
		node<User> *user=new node<User>();
		if (!data->AVLSearch(user, stoi(ID, nullptr))) {
			cout << "Not Found!!" << endl;
			continue;
		}
		user->data.PrintScores();
	}

}

void ViewStatistics(AVLTree<User> *data)
{
	if (data->root == NULL) return;
	data->root->data.PrintScores();
	AVLTree<User> *temp=new AVLTree<User>() ;
	node<User> *pwalk = data->root;
	temp->root = data->root->left;
	ViewStatistics(temp);
	temp->root = pwalk->right;
	ViewStatistics(temp);
}

/* Upload weight file function */

bool UploadWeight() {
	string WeightfileDir;
	cout << "Type new Weight-file directory :";
	getline(cin >> ws, WeightfileDir);
	if (exists(WeightfileDir)) {
		copy_file(WeightfileDir.c_str(), (string(RESULT_FOLDER) + "\\weight.txt").c_str(),copy_option::overwrite_if_exists);
		return true;
	}
	else return false;
}

/* Upload Test cases function*/

bool UploadTestcases() {
	for (int i = 0; i < TEST_NUMBER; i++) {
		string direct;
		cout << "Type testcase" << i + 1 << " direction : ";
		getline(cin >> ws, direct);
		if (exists(direct)) {
			copy_file(direct.c_str(), (string(TESTCASE_FOLDER) + "testcase" + to_string(i + 1) + ".txt"), copy_option::overwrite_if_exists);
		}
		else return false;
	}
	return true;

}

bool UploadMakefile() {
	string MakefileDir;
	cout << "Type new Make-file directory :";
	getline(cin >> ws, MakefileDir);
	if (exists(MakefileDir)) {
		copy_file(MakefileDir.c_str(), MAKEFILE_DIRECTORY, copy_option::overwrite_if_exists);
		return true;
	}
	else return false;

}