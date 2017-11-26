#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<string>
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include"tinyxml.h"
#include<time.h>
#define PROGRAM_FOLDER "D:\\ASSIGNMENT\\"
#define USER_FOLDER "D:\\ASSIGNMENT\\USER\\"
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
	bool ComplineAndRun(string Direct[], int count);	
	bool Submission::LoadData(int a);
	bool Submission::SaveData(int pos);
	void Print();
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
