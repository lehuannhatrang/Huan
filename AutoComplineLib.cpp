#include"AutoComplineLib.h"


bool ComplineAndRun(string Direct[],string ID,int count) {

	/*Create new folder*/
	string NewFolder = PROGRAM_FOLDER + ID + "\\Sub"+to_string(count+1)+"\\";
	string NewFoldercmd = "md \"" + NewFolder + "\"&&";
	NewFoldercmd += "md \"" + NewFolder + "Output\\\"&&";

	/*Text file output*/
	string outputFile = "test."+to_string(count+1)+".txt";

	/*COPY user files command line */
	string CPUserFile;
	for (int i = 0; i < NUMBER_OF_FILE_SUB; i++) {
		CPUserFile += "COPY \"" + Direct[i] + "\"" + " \"" + NewFolder + "\"&&";
	}

	/*Making Command Line*/
	string ComplineAndRuncmd =
		CPUserFile
		+ "COPY \"" + MAIN_DIRECT + "\"" + " \"" + NewFolder + "main.cpp\""
		+ "&&cd " + NewFolder
		+ "&&" + NewFolder[0] + ":"
		+ "&&g++ -c main.cpp -o " + NewFolder + "Output\\" + "main.o"
		+ "&&g++ -c " + USER_COMPLINE_FILES_NAMES + " -o" + NewFolder + "Output\\" + "Calculate.o"
		+ "&&g++ " + NewFolder + "Output\\" + "main.o " + NewFolder + "Output\\" + "Calculate.o " + "-o " + NewFolder + "Output\\" + PROBLEM_NAME
		+ "&&"+ NewFolder + "Output\\"+ PROBLEM_NAME + ".exe > Output\\" + outputFile + "&&exit";
		
	//convert to char
	string cmd = "/k "+NewFoldercmd+ComplineAndRuncmd;
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