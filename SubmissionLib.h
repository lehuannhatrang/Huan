#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<string>
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<fstream>
#include"tinyxml.h"
#include<stdlib.h>
#include<time.h>
#define PROGRAM_FOLDER "D:\\ASSIGNMENT\\"
#define USER_FOLDER "D:\\ASSIGNMENT\\USER\\"
#define MAIN_DIRECT "D:\\ASSIGNMENT\\ADMIN\\Compline\\main.cpp"
#define OUTPUT_FOLDER "D:\\ASSIGNMENT\\USER"
#define RESULT_FOLDER "D:\\ASSIGNMENT\\ADMIN\\Result"
#define TESTCASE_FOLDER "D:\\ASSIGNMENT\\ADMIN\\Testcases\\"
#define PROBLEM_NAME "Calculate"
#define USER_COMPLINE_FILES_NAMES "CalculateLib.cpp"
#define NUMBER_OF_FILE_SUB 2
#define TEST_NUMBER 5
using namespace std;


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
	bool CopyFiles(string Direct[], string NewFolder,int count);
	bool CompileAndRun(string Direct[], int count);
	bool Submission::LoadData(int a);
	bool Submission::SaveData(int pos);
	void Print();
	bool Compare(string MSSV, int SubCount, int stt);
	void SaveScore(string MSSV, int SubCount);
	bool Compile(string Direct[], string NewFolder,int count);
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
