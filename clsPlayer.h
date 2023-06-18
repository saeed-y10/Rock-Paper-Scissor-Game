// Programmer: Saeed Lahmdi

#pragma once

#include <iostream>
#include <string>
#include "clsGame.h"

class clsPlayer
{

private:

	enum enPlayer;
	enum enGameChoice;

	enPlayer _Player;
	enGameChoice _Choice;
	string _Name;


public:

	// parameterize constructor
	clsPlayer(enPlayer Player)
	{
		_Player = Player;

		if (_Player == enPlayer::ePlayer1)
			_Name = "Player 1";
		else if (_Player == enPlayer::ePlayer2)
			_Name = "Player 2";
		else 
			_Name = "Cpu";

		// assign initial random choice
		setRandomChoice();
	};

	enum enPlayer
	{
		ePlayer1 = 1,
		ePlayer2 = 2,
		eCpu = 3,
	};

	enum enGameChoice
	{
		eRock = 1,
		ePaper = 2,
		eScissor = 3,
	};

	void setName(string Name)
	{
		_Name = Name;
	}

	string getName()
	{
		return _Name;
	}
	__declspec(property(get = getName, put = setName)) string Name;

	void setChoice(enGameChoice Choice)
	{
		// you cannot assign a choice if the player is cpu just you can use setRandomChoice() method.
		if (_Player != enPlayer::eCpu)
			_Choice = Choice;
	}

	enGameChoice getChoice()
	{
		return _Choice;
	}
	__declspec(property(get = getChoice, put = setChoice)) enGameChoice Choice;

	void setRandomChoice()
	{
		_Choice = (enGameChoice)clsUtil::RandomNumber(1, 3);
	}

	static string ChoiceName(enGameChoice Choice)
	{
		string Choices[3] = {"Rock", "Paper", "Scissor"};

		return Choices[Choice - 1];
	}

	string ChoiceName()
	{
		return ChoiceName(_Choice);
	}

	// get current player enum
	enPlayer getPlayer()
	{
		return _Player;
	}

};

