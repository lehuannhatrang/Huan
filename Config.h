#ifndef CONFIG_H
#define CONFIG_H
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
using namespace std;

string PROGRAM_FOLDER;		//
string USER_FOLDER;			//
string MAIN_DIRECT;			//
string RESULT_FOLDER;		//
string TESTCASE_FOLDER;		//
string PROBLEM_NAME;		//
string USER_COMPLINE_FILES_NAMES;//
string ACCOUNT_INFOR_FILE_LOCATION;	//
int TEST_NUMBER;



bool LoadConfig();
#endif