#pragma once
#include"UserLib.h"
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<fstream>
#include<stdio.h>
#define ACCOUNT_INFOR_FILE_LOCATION "D:\\ASSIGNMENT\\ADMIN\\Accounts\\Accounts.txt"
#define ENCRYPT_KEY "monkey"
using namespace std;

void MainMenu();
void UserMenu(string ID);
void AdminMenu();
bool LoginMenu(string &ID);
bool Login(string &ID);
bool CreateAccount();
string encrypt(std::string msg, std::string key);
string decrypt(std::string msg, std::string key);
User LoadUserData(string ID);
bool CheckID(string ID);