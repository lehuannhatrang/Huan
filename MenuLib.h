#ifndef MENULIB_H
#define MENULIB_H
#include"CommonLib.h"

void MainMenu();
void UserMenu(string ID);
void AdminMenu();
void TeacherMenu();
bool LoginMenu(string &ID);
void ShowUserMenu();
void ShowAdminMenu();
void ShowTeacherMenu();
void ShowMainMenu();

#endif