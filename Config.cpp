#include"Config.h"


bool LoadConfig() {
	

	fstream configfile;
	configfile.open("config.cfg");
	if (!configfile.fail()) {
		string line,temp;
		stringstream ss;

		//Line 1
		getline(configfile, line);
		ss << line;
		ss>> temp >> PROGRAM_FOLDER;

		//Line 2
		getline(configfile, line);
		ss << line;
		ss >> temp >> PROBLEM_NAME;

		//Line 3
		getline(configfile, line);
		ss << line;
		ss >> temp >> TEST_NUMBER;

		//line 4
		getline(configfile, line);
		ss << line;
		ss >> temp >> USER_COMPLINE_FILES_NAMES;

		USER_FOLDER = PROGRAM_FOLDER + "USER\\";
		RESULT_FOLDER = PROGRAM_FOLDER + "ADMIN\\Result\\";
		TESTCASE_FOLDER = PROGRAM_FOLDER + "ADMIN\\Testcases\\";
		MAIN_DIRECT = PROGRAM_FOLDER + "ADMIN\\Compline\\main.cpp";
		ACCOUNT_INFOR_FILE_LOCATION = PROGRAM_FOLDER + "ADMIN\\Accounts\\Accounts.txt";
		configfile.close();
		return true;
	}
	else return false;
}