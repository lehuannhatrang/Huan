#pragma once
#include<string>
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<time.h>
#define PROGRAM_FOLDER "D:\\ASSIGNMENT\\"
#define MAIN_DIRECT "D:\\ASSIGNMENT\\ADMIN\\Compline\\main.cpp"
#define PROBLEM_NAME "Calculate"
#define USER_COMPLINE_FILES_NAMES "CalculateLib.cpp"
#define NUMBER_OF_FILE_SUB 2
using namespace std;

class Submission {
private:
	float score;
	struct tm Time_Submission;
	string ID;
public:
	Submission(string ID);
	bool ComplineAndRun(string Direct[], int count);
	//void setTime();
};
