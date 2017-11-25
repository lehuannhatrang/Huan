#pragma once
#include"AutoComplineLib.h"
#include"tinyxml.h"
class User {
private:
	string ID;
	int SubmitCount;
public:
	User(string ID);
	string get_ID();
	void set_ID(string ID);
	bool Submit();
	bool CreateNewUserFolder();
};
