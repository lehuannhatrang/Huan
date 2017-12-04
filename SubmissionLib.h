
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef SUBMISSION_H
#define	 SUBMISSION_H

#include<Windows.h>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
#include<sstream>
#include<boost\filesystem.hpp>
#include"XMLProcess.h"
#include"tinyxml.h"


#define PROGRAM_FOLDER "D:\\ASSIGNMENT\\"
#define USER_FOLDER "D:\\ASSIGNMENT\\USER\\"
#define MAIN_DIRECT "D:\\ASSIGNMENT\\ADMIN\\Compline\\main.cpp"
#define RESULT_FOLDER "D:\\ASSIGNMENT\\ADMIN\\Result"
#define TESTCASE_FOLDER "D:\\ASSIGNMENT\\ADMIN\\Testcases\\"
#define PROBLEM_NAME "Calculate"
#define USER_COMPLINE_FILES_NAMES "CalculateLib.cpp"
#define TEST_NUMBER 5
#define MAKEFILE_DIRECTORY "D:\\ASSIGNMENT\\ADMIN\\Compline\\makefile"
#define VCVARS_DIRECTORY "C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\"



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
#endif
