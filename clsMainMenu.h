#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsString.h"
#include "clsGame.h"
#include "clsPlayer.h"

using namespace std;

class clsMainMenu
{

private:

	static clsPlayer::enGameChoice _ReadGameChoice()
	{
		cout << "\n Enter Your Choice [1] Rock, [2] Paper, [3] Scissors? ";

		return (clsPlayer::enGameChoice)clsInputValidate::ReadNumberbetween<short>(1, 3, " Enter Your Choice [1] Rock, [2] Paper, [3] Scissors? ");
	}

	static short _ReadTotalRounds()
	{
		cout << " Enter How Many Rounds To Play? ";

		return clsInputValidate::ReadNumber<short>(" Enter How Many Rounds To Play? ");
	}

	static void _PauseScreen()
	{
		cout << "\n Press Any Key To Continue...\n ";

		system("pause > 0");
	}

	static void _ResetScreenColor()
	{
		system("color 0F");
	}

	static void _ChangeScreenColor(clsGame::enWinner Winner)
	{
		switch (Winner)
		{
		case::clsGame::enWinner::ePlayer1:
			system("color 2F");
			break;

		case::clsGame::enWinner::ePlayer2:
			system("color 4F");
			break;

		default:
			system("color 6F");
			break;
		}

	}

	static void _PrintFinalResult(clsGame Game)
	{
		clsGame::stGameResults Results = Game.getGameResults();

		_ChangeScreenColor(Results.Winner);

		cout << "\n\n" << clsUtil::Tabs(5) << clsUtil::Spaces(5) << "________________ [GAME RESULTS] ________________\n\n";

		cout << clsUtil::Tabs(6) << clsUtil::Spaces(5) << "Game rounds      :      " << Results.GameRounds << endl;
		cout << clsUtil::Tabs(6) << clsUtil::Spaces(5) << "User won times   :      " << Results.Player1WonTimes << endl;
		cout << clsUtil::Tabs(6) << clsUtil::Spaces(5) << "Cpu won times    :      " << Results.Player2WonTimes << endl;
		cout << clsUtil::Tabs(6) << clsUtil::Spaces(5) << "Draw times       :      " << Results.DrawTimes << endl;
		cout << clsUtil::Tabs(6) << clsUtil::Spaces(5) << "Final winner     :      " << Game.WinnerName(Results.Winner) << endl;

		cout << clsUtil::Tabs(5) << clsUtil::Spaces(5) << "________________________________________________\n";
	}

	static void _PrintRoundResults(clsGame Game, short RoundNumber)
	{
		clsGame::stRoundResults* RoundResults = Game.getRoundResults(RoundNumber);
		
		_ChangeScreenColor(RoundResults->RoundWinner);

		cout << "\n" << clsUtil::Tabs(5) << clsUtil::Spaces(5) << "___________________ Round[" << RoundResults->RoundNumber << "] ___________________\n\n";
		cout << clsUtil::Tabs(6) << clsUtil::Spaces(5) << " User choice        :      " << clsPlayer::ChoiceName(RoundResults->Player1Choice) << endl;
		cout << clsUtil::Tabs(6) << clsUtil::Spaces(5) << " Cpu choice         :      " << clsPlayer::ChoiceName(RoundResults->Player2Choice) << endl;
		cout << clsUtil::Tabs(6) << clsUtil::Spaces(5) << " Round winner       :      " << Game.WinnerName(RoundResults->RoundWinner) << endl;
		cout << clsUtil::Tabs(5) << clsUtil::Spaces(5) << "________________________________________________\n";

		_PauseScreen();
		_ResetScreenColor();

		clsUtil::ResetScreen();
	}

	static void _ShowStartHeader()
	{
		cout << "\n";
		cout << clsUtil::Tabs(5) << clsUtil::Spaces(7) << "===============================================\n";

		cout << clsUtil::Tabs(5) << clsUtil::Spaces(7) << "|" << left << setw(45) << "           ROCK PAPER SCISSOR GAME" << "|\n";

		cout << clsUtil::Tabs(5) << clsUtil::Spaces(7) << "===============================================\n" << endl;
	}

	static void _ShowEndHeader()
	{
		clsUtil::ResetScreen();

		cout << "\n";
		cout << clsUtil::Tabs(5) << clsUtil::Spaces(7) << "===============================================\n";

		cout << clsUtil::Tabs(5) << clsUtil::Spaces(7) << "|" << left << setw(45) << "\t                  GAME END" << "|\n";

		cout << clsUtil::Tabs(5) << clsUtil::Spaces(7) << "===============================================\n" << endl;
	}

	static bool _PlayAgain()
	{
		char PlayAgain = 'N';

		cout << "\nDo You Want To Play Again? Y/N? ";
		cin >> PlayAgain;

		return (toupper(PlayAgain) == 'Y');
	}

	static void _PlayGame()
	{
		short Rounds = _ReadTotalRounds();

		clsGame Game(clsPlayer::enPlayer::ePlayer1, clsPlayer::enPlayer::eCpu, Rounds);

		Game.Player1.Name = "USER";
		Game.Player2.Name = "CPU";

		for (short i = 0; i < Rounds; i++)
		{
			cout << "\n Round [" << i + 1 << "] Begins:\n";

			Game.Player1.Choice = _ReadGameChoice();
			Game.Player2.setRandomChoice();
			Game.FillRoundResults();

			_PrintRoundResults(Game, i);
		}

		Game.FillGameResults();

		_PrintFinalResult(Game);
	}

public:

	static void ShowMainMenu()
	{
		do
		{
			clsUtil::ResetScreen();
			_ResetScreenColor();

			_ShowStartHeader();

			_PlayGame();

		} while (_PlayAgain());

		_ShowEndHeader();
	}

};

