#include"MenuLib.h"
void MainMenu() {	
	while (true) {
		string ID;
		if (!LoginMenu(ID)) return;
		if (ID == "ADMIN") AdminMenu();
		else UserMenu(ID);
	}
}

bool LoginMenu(string &ID) {
	bool isLogin = false;
	while (!isLogin) {
		system("cls");		
		int n;
		cout << "Choose action :\n1.Login\n2.Sign up\n3.Exit\nYour option: ";
		string str;
		getline(cin >> ws, str);
		if (!CheckNumber(str)) continue;
		n = stoi(str, nullptr);
		switch (n)
		{
		case 1:
			isLogin = Login(ID);
			system("pause");
			break;
		case 2:
			CreateAccount();
			system("pause");
			break;
		case 3:
			return false;
		default:
			break;
		}
	}
	return true;
}

void AdminMenu() {
	AVLTree<User> *user = LoadAllData();	
	while (true) {
		system("cls");
		int n;
		cout << "Choose action :\n1.Update new default file\n2.See students scores\n3.See the statistics\n4.Exit\nYour option: ";
		string str;
		getline(cin >> ws, str);
		if (!CheckNumber(str)) continue;
		n = stoi(str, nullptr);
		switch (n) {
		case 1:
			break;
		case 2:
			FindingUser();
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

void UserMenu(string ID) {
	system("cls");
	User user = LoadUserData(ID);
	while (true) {
		system("cls");
		int n;
		cout << "Choose action :\n1.Submit\n2.See your scores\n3.Exit\nYour option: ";
		string str;
		getline(cin >> ws, str);
		if (!CheckNumber(str)) continue;
		n = stoi(str, nullptr);
		switch (n) {
		case 1:
			if (user.Submit()) cout << "SUCCESS!!" << endl;
			else cout << "SUBMIT FAILED!!" << endl;
			system("pause");
			break;
		case 2:
			user.PrintScores();
			system("pause");
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}