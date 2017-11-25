#include"UserLib.h"

User::User(string ID) {
	this->ID = ID;
	SubmitCount = 0;
}

bool User::CreateNewUserFolder() {
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFOA StartupInfo; //This is an [in] parameter
	string NewFolder = PROGRAM_FOLDER + ID + "\\";
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

bool User::Submit() {
	string direct[NUMBER_OF_FILE_SUB];
	for (int i = 0; i < NUMBER_OF_FILE_SUB; i++) {
		cout << "Nhap duong dan toi file "<< i+1 << ": ";
		getline(cin >> ws, direct[i]);
	}
	if (ComplineAndRun(direct, ID,SubmitCount)) {
		cout << "Success!!" << endl;
		SubmitCount++;
		return 1;
	}
	else {
		cout << "false" << endl;
		return 0;
	}
}
