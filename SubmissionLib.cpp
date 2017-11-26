#include"SubmissionLib.h"

/* Submission class*/
Submission::Submission() {
	ID = "";
	score = -1.0f;
}

Submission::Submission(string ID) {
	this->ID = ID;
}

bool Submission::CopyFiles(string Direct[],string NewFolder ,int count) {
	string NewFoldercmd = "md \"" + NewFolder + "\"&&";
	NewFoldercmd += "md \"" + NewFolder + "Output\\\"&&";

	string CPUserFile;
	for (int i = 0; i < NUMBER_OF_FILE_SUB; i++) {
		CPUserFile += "COPY \"" + Direct[i] + "\"" + " \"" + NewFolder + "\"&&";
	}

	string ComplineAndRuncmd =
		CPUserFile
		+ "COPY \"" + MAIN_DIRECT + "\"" + " \"" + NewFolder + "main.cpp\"&& exit";

	//convert to char
	string cmd = "/k " + NewFoldercmd + ComplineAndRuncmd;
	char *cmdArgs = new char[cmd.length()];
	for (int i = 0; i < cmd.length(); i++) {
		cmdArgs[i] = cmd[i];
	}
	cmdArgs[cmd.length()] = '\0';

	//some varaiable
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFOA StartupInfo; //This is an [in] parameter
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo; //Only compulsory field

										 /*Compline and Run*/
	if (CreateProcessA("c:\\windows\\system32\\cmd.exe", cmdArgs,
		NULL, NULL, FALSE, 0, NULL,
		NULL, &StartupInfo, &ProcessInfo))
	{
		/*WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
		CloseHandle(ProcessInfo.hThread);
		CloseHandle(ProcessInfo.hProcess);*/
		return 1;
	}
	else
	{
		return 0;
	}
}

bool Submission::ComplineAndRun(string Direct[],int count) {

	/*Create new folder*/
	string NewFolder = USER_FOLDER + ID + "\\Sub"+to_string(count+1)+"\\";
	
	/*Text file output*/
	string outputFile = "test."+to_string(count+1)+".txt";

	/*Copy files to new folder*/
	if(!CopyFiles(Direct, NewFolder ,count)) return 0;
	

	/*Making Command Line*/
	string ComplineAndRuncmd =		
		"cd " + NewFolder+ "&&" + NewFolder[0] + ":"
		+ "&&g++ -c main.cpp -o " + NewFolder + "Output\\" + "main.o"
		+ "&&g++ -c " + USER_COMPLINE_FILES_NAMES + " -o" + NewFolder + "Output\\" + "Calculate.o"
		+ "&&g++ " + NewFolder + "Output\\" + "main.o " + NewFolder + "Output\\" + "Calculate.o " + "-o " + NewFolder + "Output\\" + PROBLEM_NAME
		+ "&&"+ NewFolder + "Output\\"+ PROBLEM_NAME + ".exe > Output\\" + outputFile + "&&exit";
		
	//convert to char
	string cmd = "/k "+ComplineAndRuncmd;
	char *cmdArgs = new char[cmd.length()];
	for (int i = 0; i < cmd.length(); i++) {
		cmdArgs[i] = cmd[i];
	}
	cmdArgs[cmd.length()] = '\0';


	//some varaiable
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFOA StartupInfo; //This is an [in] parameter
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo; //Only compulsory field

	 /*Compline and Run*/
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

void Submission::setTime() {
	time_t now = time(0);	
	Time_Submission = *localtime(&now);
}

tm Submission::getTime(){
	return Time_Submission;
}

void Submission::setSubmitTime(const tm & submitTime)
{
	this->Time_Submission = submitTime;
}

void Submission::setScore(float score) {
	this->score = score;
}

float Submission::getScore() {
	return score;
}

bool Submission::LoadData(int a) {
	string backslash = "\\";
	string submitFile = "Sub";
	string XMLfilename = "project1.xml";

	// Set up a path links to location of XML file
	string XMLPath = USER_FOLDER + this->ID
		+ backslash + submitFile + to_string(a) + backslash + XMLfilename;

	// Convert string to char*, which can be used to load data using tinyxml library
	const char* ok = XMLPath.c_str();
	cout << XMLPath << endl;
	TiXmlDocument doc(ok);
	if (!doc.LoadFile(ok)) {
		throw  "Loading failed. Try again...\n";
		return false;
	}

	TiXmlElement* root = doc.RootElement();

	TiXmlElement* element = root->FirstChildElement();
	//===================
	//=Ignore ID Element=
	//===================

	element = element->NextSiblingElement();

	// Get information about submit time 
	struct tm time;
	TiXmlElement* childElement = element->FirstChildElement();
	childElement->QueryIntAttribute("second", &time.tm_sec);
	childElement = childElement->NextSiblingElement();
	childElement->QueryIntAttribute("minute", &time.tm_min);
	childElement = childElement->NextSiblingElement();
	childElement->QueryIntAttribute("hour", &time.tm_hour);
	childElement = childElement->NextSiblingElement();
	childElement->QueryIntAttribute("day", &time.tm_mday);
	childElement = childElement->NextSiblingElement();
	childElement->QueryIntAttribute("month", &time.tm_mon);
	childElement = childElement->NextSiblingElement();
	childElement->QueryIntAttribute("year", &time.tm_year);
	this->setSubmitTime(time);
	element = element->NextSiblingElement();

	// Set score's object of value of score attribute in xml file
	element->QueryFloatAttribute("score", &this->score);
	pos = a;
	return true;
}

// This function saves only the data of the submidID-th submission of a student
// Data will be written into a XML file following the path: 
// D:\ASSIGNMENT\USER\1610491\Submit+(submidID)\project1.xml

bool Submission::SaveData(int pos) {
	TiXmlDocument XMLFile;

	// Set the prolog of XML file
	TiXmlDeclaration* prolog = new TiXmlDeclaration("1.0", "utf-8", "");
	XMLFile.LinkEndChild(prolog);

	// This is just a comment
	TiXmlComment* cmt = new TiXmlComment("Data Structure and Algorithm");
	XMLFile.LinkEndChild(cmt);

	TiXmlElement* root = new TiXmlElement("SubmitData");
	XMLFile.LinkEndChild(root);

	// Write student ID downto XML file
	TiXmlElement* data1 = new TiXmlElement("ID");
	const char* studentID = this->ID.c_str();
	data1->SetAttribute("id", studentID);
	root->LinkEndChild(data1);

	// Write submission time downto XML file
	TiXmlElement* data2 = new TiXmlElement("Time");
	{
		this->setTime();
		TiXmlElement* second = new TiXmlElement("Second");
		second->SetAttribute("second", this->Time_Submission.tm_sec);
		data2->LinkEndChild(second);
		TiXmlElement* minute = new TiXmlElement("Minute");
		minute->SetAttribute("minute", this->Time_Submission.tm_min);
		data2->LinkEndChild(minute);
		TiXmlElement* hour = new TiXmlElement("Hour");
		hour->SetAttribute("hour", this->Time_Submission.tm_hour);
		data2->LinkEndChild(hour);
		TiXmlElement* day = new TiXmlElement("Day");
		day->SetAttribute("day", this->Time_Submission.tm_mday);
		data2->LinkEndChild(day);
		TiXmlElement* month = new TiXmlElement("Month");
		month->SetAttribute("month", this->Time_Submission.tm_mon);
		data2->LinkEndChild(month);
		TiXmlElement* year = new TiXmlElement("Year");
		year->SetAttribute("year", this->Time_Submission.tm_year );
		data2->LinkEndChild(year);
	}
	root->LinkEndChild(data2);

	// Write submission score downto XML file
	// Scrore will be calculated through compile and run process
	// Updating......
	TiXmlElement* data3 = new TiXmlElement("Score");
	data3->SetDoubleAttribute("score", 0.5);
	root->LinkEndChild(data3);

	// Finish action.... Create a path to submit folder
	// Example path: D:\ASSIGNMENT\USER\1610491\Submit1\project1.xml
	string backslash = "\\";
	string submitFile = "Sub";
	string XMLfilename = "project1.xml";

	// Set up a path links to location of XML file
	string XMLPath = USER_FOLDER + this->ID
		+ backslash + submitFile + to_string(pos) + backslash + XMLfilename;

	// Convert string to char*, which can be used to load data using tinyxml library
	const char* ok = XMLPath.c_str();
	XMLFile.SaveFile(ok);

	return true;
}

void Submission::Print() {
	cout << pos << "." << endl;
	cout << "Diem : " << score <<endl;
	cout << "Thoi gian nop: " <<Time_Submission.tm_hour << ":";
	cout << Time_Submission.tm_min << ":";
	cout << Time_Submission.tm_sec << "  ";
	cout  << Time_Submission.tm_mday << " /";
	cout << 1 + Time_Submission.tm_mon << " /";
	cout << 1900 + Time_Submission.tm_year <<endl;	
	
}

void Submission::setpos(int pos) {
	this->pos = pos;
}

/* SubmissionNode Class*/
SubmissionNode::SubmissionNode(Submission submit) {
	this->data = submit;
	next = NULL;
}

/* Submission Linked List class*/

SubmissionLinkedList::SubmissionLinkedList(){
	head = NULL;
	
}

SubmissionNode* SubmissionLinkedList::getHead() {
	return head;
}

void SubmissionLinkedList::addSubmit(Submission submit) {
	SubmissionNode *pnew = new SubmissionNode(submit);
	pnew->next = head;
	head = pnew;
}

bool SubmissionLinkedList::LoadData(int submitCount,string ID) {
	for (int i = 0; i < submitCount; i++) {
		Submission submit(ID);
		submit.LoadData(i+1);
		addSubmit(submit);
	}
	return true;
}

