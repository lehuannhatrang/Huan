#pragma once
#include"SubmissionLib.h"
#include"tinyxml.h"
class User {
private:
	string ID;
	int SubmitCount;
	SubmissionLinkedList *submissionsList;
public:
	User();
	User(string ID);
	string get_ID();
	void set_ID(string ID);
	bool Submit();
	bool CreateNewUserFolder();
	bool LoadData();
	bool SaveData();
};

