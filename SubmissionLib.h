#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<string>
#include<Windows.h>
#include<iomanip>
#include<fstream>
#include"XMLProcess.h"
#include"tinyxml.h"
#include<stdlib.h>
#include<time.h>
#include<boost\filesystem.hpp>
#define PROGRAM_FOLDER "D:\\ASSIGNMENT\\"
#define USER_FOLDER "D:\\ASSIGNMENT\\USER\\"
#define MAIN_DIRECT "D:\\ASSIGNMENT\\ADMIN\\Compline\\main.cpp"
#define RESULT_FOLDER "D:\\ASSIGNMENT\\ADMIN\\Result"
#define TESTCASE_FOLDER "D:\\ASSIGNMENT\\ADMIN\\Testcases\\"
#define PROBLEM_NAME "Calculate"
#define USER_COMPLINE_FILES_NAMES "CalculateLib.cpp"
#define NUMBER_OF_FILE_SUB 2
#define TEST_NUMBER 5

using namespace std;
using namespace boost::filesystem;


class Submission {
private:
	float score;
	struct tm Time_Submission;
	string ID;
	int pos;
public:
	Submission();
	Submission(string ID);
	void setTime();
	tm getTime();
	void setSubmitTime(const tm & submitTime);
	void setpos(int pos);
	void setScore(float score);
	float getScore();
	
	bool LoadData(int a);
	bool SaveData(int pos);
	void Print();
	bool Compare(string MSSV, int SubCount, int stt);
	void SaveScore(string MSSV, int SubCount);

	// Copy data form filePath to newfolder and compile it using Command Line
	bool CompileAndRun(string Direct, int count);
	// This functions support compiling
	bool Compile(string NewFolder, int count);
};

struct SubmissionNode {
	Submission data;
	SubmissionNode *next;
	SubmissionNode(Submission submit);
};

class SubmissionLinkedList {
private:
	SubmissionNode *head;
public:
	SubmissionLinkedList();
	SubmissionNode* getHead();
	void addSubmit(Submission submit);
	bool LoadData(int submitCount,string ID);
	
};

char* string2char(string str);
