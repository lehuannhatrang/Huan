#pragma once
#include"UserLib.h"
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<fstream>
#define ACCOUNT_INFOR_FILE_LOCATION "D:\\ASSIGNMENT\\ADMIN\\Accounts\\Accounts.txt"
#define ENCRYPT_KEY "monkey"
using namespace std;

void UserMenu();
bool Login();
bool CreateAccount();
string encrypt(std::string msg, std::string key);
string decrypt(std::string msg, std::string key);
User LoadUserData(string ID);
