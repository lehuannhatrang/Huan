#ifndef XMLPROCESS_H
#define XMLPROCESS_H
#include<iostream>
#include"tinyxml2.h"
#include<boost\filesystem.hpp>
#include<boost\operators.hpp>

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace std;
using namespace boost::filesystem;
using namespace tinyxml2;

// Create an XML file contains file structure of loadFolder and save at
int CreateData(const char* loadFolder, const char* savedFolder);
// The functions support for above function
void SetupData(const char* folder, tinyxml2::XMLDocument& XMLFile);
void SetupAttribute(XMLElement*& object);

// Extract the path to the file with the specified name and save it as a string
int ExtractData(const char* XMLFile, const char* fileName,string& dataOut);

// Copy all files in a directory into a new directory
bool CopyDir(boost::filesystem::path const & source,
	boost::filesystem::path const & destination);

#endif