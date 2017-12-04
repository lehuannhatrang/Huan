#include "XMLProcess.h"

int CreateData(const char* loadFolder,const char* savedFolder){
	XMLDocument xmlDoc;
	SetupData(loadFolder, xmlDoc);
	// Checking and saving data
	XMLError eResult = xmlDoc.SaveFile(savedFolder);
	XMLCheckResult(eResult);
}

void SetupData(const char* folder, XMLDocument & XMLFile){
	// Creat a root node, which contains all elements within the document. 
	XMLNode* root = XMLFile.NewElement("SubmitFolder");
	XMLFile.InsertFirstChild(root);

	XMLElement* headerElement = XMLFile.NewElement("HeaderFiles");
	XMLElement* sourceElement = XMLFile.NewElement("SourceFiles");
	XMLElement* otherElement = XMLFile.NewElement("OtherFiles");

	// Set content for the XML Document
	path myPath{ folder };
	directory_iterator i{ myPath };
	while (i != directory_iterator{}) {
		// Get all paths link to *.h files in submit folder
		if (i->path().extension() == ".h") {
			XMLElement * childElement = XMLFile.NewElement("Header");
			// Set value of element
			string comeToFile = i->path().string();
			childElement->SetText(comeToFile.c_str());
			// Set attribute of element
			string fileName = i->path().filename().string();
			childElement->SetAttribute("name", fileName.c_str());
			// Attach into parent element
			headerElement->InsertEndChild(childElement);
		}

		// Get all paths link to *.cpp files in submit folder
		else if (i->path().extension() == ".cpp") {
			XMLElement * childElement = XMLFile.NewElement("Source"); 
			// Set value of element
			string comeToFile = i->path().string();
			childElement->SetText(comeToFile.c_str()); 
			// Set attribute of element
			string fileName = i->path().filename().string();
			childElement->SetAttribute("name", fileName.c_str());

			sourceElement->InsertEndChild(childElement);
		}

		// Get all paths link to other type files in submit folder
		else {
			XMLElement * childElement = XMLFile.NewElement("Other"); 
			// Set value of element
			string comeToFile = i->path().string();
			childElement->SetText(comeToFile.c_str()); 
			// Set attribute of element
			string fileName = i->path().filename().string();
			childElement->SetAttribute("name", fileName.c_str());
			// Attach into parent element
			otherElement->InsertEndChild(childElement);
		}
		*i++;
	}

	// Set number-files attribute for the elements
	SetupAttribute(headerElement);
	SetupAttribute(sourceElement);
	SetupAttribute(otherElement);

	// Attachinng above elements into root
	root->InsertEndChild(headerElement);
	root->InsertEndChild(sourceElement);
	root->InsertEndChild(otherElement);
}

// This function specifies the number of files of each type
void SetupAttribute(XMLElement*& object){
	XMLElement* children = object->FirstChildElement();
	int numberElement = 0;
	while (children) {
		numberElement++;
		children = children->NextSiblingElement();
	}
	object->SetAttribute("number-files", numberElement);
}

int ExtractData(const char* XMLFile,const char* fileName,string& dataOut){
	XMLDocument xmlFile;
	XMLError eResult = xmlFile.LoadFile(XMLFile);
	XMLCheckResult(eResult);

	XMLNode * root = xmlFile.FirstChild();
	if (root == nullptr) return XML_ERROR_FILE_READ_ERROR;

	XMLElement * element = root->FirstChildElement();
	if (element == nullptr) return XML_ERROR_PARSING_ELEMENT;

	const char* beforeSearch = dataOut.c_str();
	while (element) {
		XMLElement * childElement = element->FirstChildElement();
		if (childElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

		while (childElement) {
			const char * szAttributeText = nullptr;
			szAttributeText = childElement->Attribute("name");

			if (strcmp(szAttributeText, fileName) == 0) {
				dataOut = childElement->GetText();
				return XML_SUCCESS;
			}
			childElement = childElement->NextSiblingElement();
		}
		element = element->NextSiblingElement();
	}

	return XML_ERROR_FILE_NOT_FOUND;
}

bool CopyDir(boost::filesystem::path const & source,
	boost::filesystem::path const & destination)
{
	try
	{
		// Check whether the function call is valid
		if (!boost::filesystem::exists(source) ||
			!boost::filesystem::is_directory(source))
		{
			std::cerr << "Source directory "
				<< source.string()
				<< " does not exist or is not a directory."
				<< '\n';
			return false;
		}

		if (boost::filesystem::exists(destination))
		{
			std::cerr << "Destination directory "
				<< destination.string()
				<< " already exists." << '\n';
			return false;
		}

		// Create the destination directory
		if (!boost::filesystem::create_directory(destination))
		{
			std::cerr << "Unable to create destination directory"
				<< destination.string() << '\n';
			return false;
		}
	}

	catch (boost::filesystem::filesystem_error const & e)
	{
		std::cerr << e.what() << '\n';
		return false;
	}

	// Iterate through the source directory
	for (boost::filesystem::directory_iterator file(source);
		file != boost::filesystem::directory_iterator();
		++file)
	{
		try
		{
			boost::filesystem::path current(file->path());
			if (boost::filesystem::is_directory(current))
			{
				// Found directory: Recursion
				if (!CopyDir(current, destination / current.filename()))
				{
					return false;
				}
			}
			else
			{
				// Found file: Copy
				boost::filesystem::copy_file(current,
					destination / current.filename());
			}
		}

		catch (boost::filesystem::filesystem_error const & e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return true;
}