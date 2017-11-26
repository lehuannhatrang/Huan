#include"SubmissionLib.h"

/* Submission class*/
Submission::Submission() {
	ID = "";
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
	string NewFolder = PROGRAM_FOLDER + ID + "\\Sub"+to_string(count+1)+"\\";
	
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

void Submission::setScore(float score) {
	this->score = score;
}

float Submission::getScore() {
	return score;
}

bool Submission::LoadData() {
	return true;
}

bool Submission::SaveData() {
	return true;
}


/* SubmissionNode Class*/
SubmissionNode::SubmissionNode(Submission submit) {
	this->submit = submit;
	next = NULL;
}

SubmissionLinkedList::SubmissionLinkedList(){
	head = NULL;
	count = 0;
}

/* Submission Linked List class*/
void SubmissionLinkedList::addSubmit(Submission submit) {
	SubmissionNode *pnew = new SubmissionNode(submit);
	pnew->next = head;
	head = pnew;
	count++;
}

