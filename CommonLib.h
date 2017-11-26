#pragma once
#include"UserLib.h"
#include"AVLTree.h"
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<fstream>
#include<stdio.h>
#define ACCOUNT_INFOR_FILE_LOCATION "D:\\ASSIGNMENT\\ADMIN\\Accounts\\Accounts.txt"
#define ENCRYPT_KEY "monkey"
using namespace std;

bool Login(string &ID);
bool CreateAccount();
string encrypt(std::string msg, std::string key);
string decrypt(std::string msg, std::string key);
User LoadUserData(string ID);
bool CheckID(string ID);
AVLTree<User>* LoadAllData();
bool CheckNumber(string str);
bool FindingUser();
