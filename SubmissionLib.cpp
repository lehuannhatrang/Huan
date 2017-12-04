#include"SubmissionLib.h"

/* Submission class*/
Submission::Submission() {
	ID = "";
	score = 0.0f;
}

Submission::Submission(string ID) {
	this->ID = ID;
	score = 0.0f;
}



bool Submission::Compile(string NewFolder, int count) {
	string OutputFolder = NewFolder + "Output\\";
	create_directories(OutputFolder.c_str());
	/*Making Command Line*/
	string CompileAndRuncmd =
		"cd " + NewFolder + "&&" + NewFolder[0] + ":"
		+ "&&g++ -c main.cpp -o " + NewFolder + "Output\\" + "main.o"
		+ "&&g++ -c " + USER_COMPLINE_FILES_NAMES + " -o" + NewFolder + "Output\\" + "Calculate.o"
		+ "&&g++ " + NewFolder + "Output\\" + "main.o " + NewFolder + "Output\\" + "Calculate.o " + "-o " + NewFolder + "Output\\" + PROBLEM_NAME
		+ "&& exit";

	//convert to char
	string cmd = "/k " + CompileAndRuncmd;
	char *cmdArgs = _strdup(cmd.c_str());

	//some varaiable
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFOA StartupInfo; //This is an [in] parameter
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo; //Only compulsory field

										 //Compline and Run
	if (CreateProcessA("c:\\windows\\system32\\cmd.exe", cmdArgs, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo));

	WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
	CloseHandle(ProcessInfo.hThread);
	CloseHandle(ProcessInfo.hProcess);
	TerminateProcess(ProcessInfo.hProcess, 0);
	return true;
}

bool Submission::CompileAndRun(string filePath, int count) {
	//Create new folder and Copy files from file Path to new folder
	string NewFolder = USER_FOLDER + ID + "\\Sub" + to_string(count + 1) + "\\";
	bool copySuccess = CopyDir(filePath.c_str(), NewFolder.c_str());

	// Check if copy is success
	if (copySuccess == false) return false;

	// Perform compile and return false if compile failed

	bool compileSuccess = Compile(NewFolder, count);
	if (compileSuccess == false) return false;

	string CompileAndRuncmd;
	for (int i = 0; i < TEST_NUMBER; i++) {
		string outputFile = "test." + to_string(i + 1) + ".txt";
		string cmd = NewFolder + "Output\\" + PROBLEM_NAME + ".exe <" + TESTCASE_FOLDER + "testcase" + to_string(i + 1) + ".txt"
			+ ">" + NewFolder + "Output\\" + outputFile + " && ";
		CompileAndRuncmd += cmd;
	}

	//convert to char
	string cmd = "/k cd " + NewFolder + "&&" + NewFolder[0] + ":&&" + CompileAndRuncmd + "exit";
	char *cmdArgs = _strdup(cmd.c_str());


	//some varaiable
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFOA StartupInfo; //This is an [in] parameter
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo; //Only compulsory field

										 /*Compline and Run*/
	CreateProcessA("c:\\windows\\system32\\cmd.exe", cmdArgs,
		NULL, NULL, FALSE, 0, NULL,
		NULL, &StartupInfo, &ProcessInfo);

	WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
	CloseHandle(ProcessInfo.hThread);
	CloseHandle(ProcessInfo.hProcess);
	//TerminateProcess(ProcessInfo.hProcess, 0);
	return true;
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
	data3->SetDoubleAttribute("score", this->score);
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
	cout <<"\nLan " << pos << "." << endl;
	cout << "Diem : " << this->score <<endl;
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

bool Submission::Compare(string MSSV, int SubCount, int stt) {
	string temp = "\\";
	//Địa chỉ file tạo ra
	string output = USER_FOLDER + MSSV + temp + "Sub" + to_string(SubCount)
		+ temp + "Output" + temp + "test." + to_string(stt) + ".txt";
	//Địa chỉ file đáp án
	string result = RESULT_FOLDER + temp + "result" + to_string(stt) + ".txt";
	std::ifstream File1(output);
	std::ifstream File2(result);
	if (!File1.is_open()) {
		cout << "Cannot open " << MSSV << "test." << stt << ".txt" << endl;
		return false;
	}
	if (!File2.is_open()) {
		cout << "Cannot open result" << stt << ".txt" << endl;
		return false;
	}
	string line1, line2;
	while (getline(File1, line1)) {
		getline(File2, line2);
		if (line1.size() != line2.size()) {
			return false;
		}
		else {
			int Stop = line1.size();
			for (int i = 0; i < Stop; i++) {
				if (line1[i] != line2[i]) return false;
			}
		}
	}
	return true;
}

void Submission::SaveScore(string MSSV, int SubCount) {
	string temp = "\\";
	//Địa chỉ của file output
	string output = USER_FOLDER + MSSV + temp + "Sub" + to_string(SubCount) + temp + "result.txt";
	//Địa chỉ file trọng số 1 2 3 2 2
	string weightFolder = RESULT_FOLDER + temp + "weight.txt";
	std::ofstream result;
	result.open(output, ios::app);
	double ScoreArray[TEST_NUMBER+1] = { 0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0 }; //Khởi tạo mảng lưu kết quả so sánh
	for (int i = 1; i <= TEST_NUMBER; i++) {
		if (Compare(MSSV, SubCount, i)) {
			result << "10.0" << " ";
			ScoreArray[i - 1] = 10.0;
		}
		else result << 0 << " ";
	}
	std::ifstream weight;
	weight.open(weightFolder, ios::in);
	string parameter;
	int i = 0;
	while (getline(weight, parameter, ' ')) {
		ScoreArray[TEST_NUMBER] += ScoreArray[i] * atof(parameter.c_str()); //Cập nhật điểm tổng kết
		i++;
	}
	result << ScoreArray[TEST_NUMBER];
	this->score = ScoreArray[TEST_NUMBER];
	weight.close();
	result.close();
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
	
	if (head != NULL) {
		delete head;
		head = NULL;
	}
	for (int i = 0; i < submitCount; i++) {
		Submission submit(ID);
		submit.LoadData(i+1);
		addSubmit(submit);
	}
	return true;
}

char* string2char(string str) {
	char *newchar = new char[str.length()];
	for (int i = 0; i < str.length(); i++) {
		newchar[i] = str[i];
	}
	newchar[str.length()] = '\0';
	return newchar;
}