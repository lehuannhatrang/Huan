#pragma once
#include"SubmissionLib.h"
#include"tinyxml.h"
#include<boost\filesystem.hpp>
using namespace boost::filesystem;

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
	void PrintScores();
	bool LoadData();
	bool SaveData();
};

