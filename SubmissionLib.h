#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
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
	Submission();
	Submission(string ID);
	void setTime();
	tm getTime();
	void setScore(float score);
	float getScore();
	bool CopyFiles(string Direct[], string NewFolder,int count);
	bool ComplineAndRun(string Direct[], int count);	
	bool LoadData();
	bool SaveData();
};

struct SubmissionNode {
	Submission submit;
	SubmissionNode *next;
	SubmissionNode(Submission submit);
};

class SubmissionLinkedList {
private:
	SubmissionNode *head;
	int count;
public:
	SubmissionLinkedList();
	void addSubmit(Submission submit);
};
