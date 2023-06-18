// Rock Paper Scissor.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Programmer: Saeed Lahmdi

#include <iostream>
#include <string>
#include "clsMainMenu.h"

using namespace std;

int main()
{
	clsUtil::Srand();

	clsMainMenu::ShowMainMenu();

	return 0;
}