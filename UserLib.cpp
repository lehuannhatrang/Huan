#include"UserLib.h"

User::User() {
	ID = "";
	SubmitCount = 0;
	highScore = 0;
}

User::User(string ID) {
	this->ID = ID;
	SubmitCount = 0;
	submissionsList = new SubmissionLinkedList();
	highScore = 0;
}

bool User::CreateNewUserFolder() {
	if (ID == "ADMIN") return false;
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFOA StartupInfo; //This is an [in] parameter
	string NewFolder = USER_FOLDER + ID + "\\";
	string NewFoldercmd = "md \"" + NewFolder + "\"&&";

	string cmd = "/k " + NewFoldercmd + "exit";
	char *cmdArgs = new char[cmd.length()];
	for (int i = 0; i < cmd.length(); i++) {
		cmdArgs[i] = cmd[i];
	}
	cmdArgs[cmd.length()] = '\0';

	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo; //Only compulsory field

	if (CreateProcessA("c:\\windows\\system32\\cmd.exe", cmdArgs,
		NULL, NULL, FALSE, 0, NULL,
		NULL, &StartupInfo, &ProcessInfo))
	{
		WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
		CloseHandle(ProcessInfo.hThread);
		CloseHandle(ProcessInfo.hProcess);

		return 1;
	}
	else
	{
		return 0;
	}

}

string User::get_ID() {
	return ID;
}

void User::set_ID(string ID) {
	this->ID = ID;
}

/* Submit function */
bool User::Submit() {
	string direct[NUMBER_OF_FILE_SUB];
	for (int i = 0; i < NUMBER_OF_FILE_SUB; i++) {
		cout << "Nhap duong dan toi file "<< i+1 << ": ";
		getline(cin >> ws, direct[i]);
	}
	Submission submit(ID);
	submit.setpos(SubmitCount+1);
	submit.setTime();
	
	if (submit.CompileAndRun(direct,SubmitCount)) {
		submissionsList->addSubmit(submit);
		SubmitCount++;		
		submit.SaveScore(ID, SubmitCount);
		submit.SaveData(SubmitCount);
		GetHighScore();
		SaveData();
		return 1;
	}
	else {

		cout << "false" << endl;
		return 0;
	}
}

/* Load User data function*/
bool User::LoadData() {
	// Default the path to a User will be: D:\\ASSIGNMENT\\USER\\studentID
	string backslash = "\\";
	string XMLfilename = "userStatistics.xml";

	// Set up a path links to location of XML file
	string XMLPath = USER_FOLDER + backslash + this->ID + backslash + XMLfilename;

	// Convert string to char*, which can be used to load data using tinyxml library
	const char* ok = XMLPath.c_str();

	TiXmlDocument doc(ok);
	if (!doc.LoadFile()) {
		throw  "Loading failed. Try again...\n";
		return false;
	}

	TiXmlElement* root = doc.RootElement();

	TiXmlElement* element = root->FirstChildElement();
	//===================
	//=Ignore ID Element=
	//===================

	element = element->NextSiblingElement();

	// Get information about submit count
	element->QueryIntAttribute("submitCount", &this->SubmitCount);
	submissionsList->LoadData(this->SubmitCount,this->ID);

	element->QueryFloatAttribute("high_score", &this->highScore);
	submissionsList->LoadData(this->SubmitCount, this->ID);
	return true;

}

// For each submission, the number of submissions increased 1
bool User::SaveData() {


	TiXmlDocument XMLFile;
	
	// Set the prolog of XML file
	TiXmlDeclaration* prolog = new TiXmlDeclaration("1.0", "utf-8", "");
	XMLFile.LinkEndChild(prolog);

	// This is just a comment
	TiXmlComment* cmt = new TiXmlComment("Data Structure and Algorithm");
	XMLFile.LinkEndChild(cmt);


	TiXmlElement* root = new TiXmlElement("UserData");
	XMLFile.LinkEndChild(root);

	// Write student ID downto XML file
	TiXmlElement* data1 = new TiXmlElement("ID");
	const char* studentID = this->ID.c_str();
	data1->SetAttribute("id", studentID);
	root->LinkEndChild(data1);

	// Write submit count downto XML file
	TiXmlElement* data2 = new TiXmlElement("submit_count");
	data2->SetAttribute("submitCount", this->SubmitCount);
	root->LinkEndChild(data2);

	TiXmlElement* data3 = new TiXmlElement("high_score");
	data2->SetAttribute("high_score", this->highScore);
	root->LinkEndChild(data3);

	// Finish action.... Create a path to submit folder
	// Example path: D:\ASSIGNMENT\USER\1610491\userStatistics.xml
	string backslash = "\\";
	string XMLfilename = "userStatistics.xml";

	// Set up a path links to location of XML file
	string XMLPath = USER_FOLDER + backslash + this->ID + backslash + XMLfilename;

	// Convert string to char*, which can be used to load data using tinyxml library
	const char* ok = XMLPath.c_str();
	XMLFile.SaveFile(ok);

	return true;
}

/* Print user scores */
void User::PrintScores() {
	cout << "Highest Score : " << highScore << endl;
	SubmissionNode *pwalk = submissionsList->getHead();
	while (pwalk != NULL) {
		pwalk->data.Print();
		pwalk = pwalk->next;
	}
}

void User::GetHighScore() {
	for (int i = 0; i < SubmitCount; i++) {
		submissionsList->LoadData(i+1,ID);
	}
	SubmissionNode *pwalk=submissionsList->getHead();
	while (pwalk != NULL) {
		if (highScore < pwalk->data.getScore()) {
			highScore = pwalk->data.getScore();			
		}
		pwalk = pwalk->next;
	}
}
