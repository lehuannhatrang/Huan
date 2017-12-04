#include"MenuLib.h"
void MainMenu() {	
	while (true) {
		string ID;
		if (!LoginMenu(ID)) return;
		if (ID == "ADMIN") AdminMenu();
		else if (ID == "Teacher") TeacherMenu();
		else UserMenu(ID);
	}
}

/* Main menu */

void ShowMainMenu() {
	system("cls");
	cout << "ASSIGNMENT SUBMIT\n";
	cout << "************************\n";
	cout << "1. Log in\n2. Sign up\n3. Quit\n";
	cout << "************************\n";
	cout << "Chose an action:\n";
}

bool LoginMenu(string &ID) {
	bool isLogin = false;
	while (!isLogin) {
		system("cls");		
		int n;
		ShowMainMenu();
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

/* ADMIN menu */
void ShowAdminMenu() {
	system("cls");
	cout << "ADMIN MENU\n";
	cout << "************************\n";
	cout << "1. Upload weight file\n2. Upload test cases\n3. Upload Makefile\n4. Exit\n";
	cout << "************************\n";
	cout << "Chose an action:\n";
}

void AdminMenu() {
	while (true) {
		system("cls");
		int n;
		ShowAdminMenu();
		string str;
		getline(cin >> ws, str);
		if (!CheckNumber(str)) continue;
		n = stoi(str, nullptr);
		switch (n) {
		case 1:
			if (!UploadWeight()) cout << "FAILED!!" << endl;
			else cout << "SUCCESS!!" << endl;
			system("pause");
			break;
		case 2:
			if (!UploadTestcases()) cout << "Something Wrong Happen!!" << endl;
			else cout << "SUCCESS!!" << endl;
			system("pause");
			break;
		case 3:
			if (!UploadMakefile()) cout << "FAILED!!" << endl;
			else cout << "SUCCESS!!" << endl;
			system("pause");
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}



/* Teacher menu */
void ShowTeacherMenu() {
	system("cls");
	cout << "TEACHER MENU\n";
	cout << "************************\n";
	cout << "1. See students scores\n2. See the statistics\n3. Exit\n";
	cout << "************************\n";
	cout << "Chose an action:\n";
}

void TeacherMenu() {
	AVLTree<User> *user = LoadAllData();	
	while (true) {
		system("cls");
		int n;
		ShowTeacherMenu();
		string str;
		getline(cin >> ws, str);
		if (!CheckNumber(str)) continue;
		n = stoi(str, nullptr);
		switch (n) {
		case 1:
			FindingUser(user);
			break;
		case 2:
			ViewStatistics(user);
			system("pause");
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

/* User menu */
void ShowUserMenu() {
	system("cls");
	cout << "USER MENU\n";
	cout << "************************\n";
	cout << "1. Submit\n2. See your scores\n3. Exit\n";
	cout << "************************\n";
	cout << "Chose an action:\n";
}

void UserMenu(string ID) {
	system("cls");
	User user = LoadUserData(ID);
	while (true) {
		system("cls");
		int n;
		ShowUserMenu();
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
			user.LoadData();
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