#pragma once
#include<string>
#include<iostream>
#include<Windows.h>
#include<iomanip>
#define PROGRAM_FOLDER "D:\\ASSIGNMENT\\"
#define MAIN_DIRECT "D:\\ASSIGNMENT\\ADMIN\\Compline\\main.cpp"
#define PROBLEM_NAME "Calculate"
#define USER_COMPLINE_FILES_NAMES "CalculateLib.cpp"
#define NUMBER_OF_FILE_SUB 2
using namespace std;

bool ComplineAndRun(string Direct[],string ID,int count);
