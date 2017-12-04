#ifndef USERLIB_H
#define USERLIB_H
#include"SubmissionLib.h"


class User {
private:
	string ID;
	int SubmitCount;
	SubmissionLinkedList *submissionsList;
	float highScore;
public:
	User();
	User(string ID);
	string get_ID();
	void set_ID(string ID);
	bool Submit();
	bool CreateNewUserFolder();
	void PrintScores();
	void GetHighScore();
	bool LoadData();
	bool SaveData();
	float getScore();
};
#endif


