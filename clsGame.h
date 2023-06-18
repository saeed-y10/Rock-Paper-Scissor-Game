// Programmer: Saeed Lahmdi

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "clsPlayer.h"

using namespace std;

class clsGame
{

private:

	enum enWinner;

	struct stGameResults;
	struct stRoundResults;

	short _GameRounds;
	short _Player1WonTimes;
	short _Player1LoseTimes;
	short _Player2WonTimes;
	short _Player2LoseTimes;
	short _DrawTimes;

	vector<stRoundResults> _RoundsResults;

	// compare given choices and return enwinner enum
	enWinner _GetRoundWinner(clsPlayer::enGameChoice Player1Choice, clsPlayer::enGameChoice Player2Choice)
	{
		if (Player1Choice == Player2Choice)
			return enWinner::eDraw;

		else if ((Player1Choice == clsPlayer::enGameChoice::ePaper) && (Player2Choice == clsPlayer::enGameChoice::eScissor))
			return enWinner::ePlayer2;

		else if ((Player1Choice == clsPlayer::enGameChoice::eRock) && (Player2Choice == clsPlayer::enGameChoice::ePaper))
			return enWinner::ePlayer2;

		else if ((Player1Choice == clsPlayer::enGameChoice::eScissor) && (Player2Choice == clsPlayer::enGameChoice::eRock))
			return enWinner::ePlayer2;

		else
			return enWinner::ePlayer1;
	}

	// increase counters won , draw times
	void _UpdateWonCounters(enWinner Winner)
	{
		if (Winner == enWinner::ePlayer1)
		{
			_Player1WonTimes++;
			_Player2LoseTimes++;
		}

		else if (Winner == enWinner::ePlayer2)
		{
			_Player2WonTimes++;
			_Player1LoseTimes++;
		}

		else
			_DrawTimes++;
	}

public:

	// parameterize constructor
	clsGame(clsPlayer PL1, clsPlayer PL2, short Rounds)
		: Player1(PL1), Player2(PL2) 
	{
		_GameRounds = Rounds;
		_Player1WonTimes = 0;
		_Player1LoseTimes = 0;
		_Player2WonTimes = 0;
		_Player1LoseTimes = 0;
		_DrawTimes = 0;
	}

	enum enWinner
	{
		ePlayer1 = 1,
		ePlayer2 = 2,
		eDraw = 3,
	};

	struct stRoundResults
	{
		short RoundNumber = 0;
		clsPlayer::enGameChoice Player1Choice;
		clsPlayer::enGameChoice Player2Choice;
		enWinner RoundWinner;
	};

	struct stGameResults
	{
		short GameRounds = 0;
		short Player1WonTimes = 0;
		short Player1LoseTimes = 0;
		short Player2WonTimes = 0;	
		short Player2LoseTimes = 0;
		short DrawTimes = 0;
		enWinner Winner;
	};

	clsPlayer Player1;
	clsPlayer Player2;
	stGameResults GameResults;

	void setGameRounds(short Rounds)
	{
		_GameRounds = Rounds;
	}

	short getGameRounds()
	{
		return _GameRounds;
	}
	__declspec(property(get = getGameRounds, put = setGameRounds)) short GameRounds;

	// set last round results and push it to _RoundsResults vector
	void FillRoundResults()
	{
		stRoundResults Results;

		short RoundNumber = 1;

		RoundNumber = (_RoundsResults.empty() ? 1 : getLastRoundResults().RoundNumber + 1);

		Results.RoundNumber = RoundNumber;
		Results.Player1Choice = Player1.Choice;
		Results.Player2Choice = Player2.Choice;
		Results.RoundWinner = _GetRoundWinner(Player1.Choice, Player2.Choice);

		_RoundsResults.push_back(Results);

		_UpdateWonCounters(Results.RoundWinner);
	}

	// set final results and winner in GameResults structure
	void FillGameResults()
	{
		GameResults.GameRounds = _GameRounds;
		GameResults.Player1WonTimes = _Player1WonTimes;
		GameResults.Player2WonTimes = _Player2WonTimes;
		GameResults.DrawTimes = _DrawTimes;
		GameResults.Winner = getFinalWinner();
	}

	// get total rounds history size
	short RoundsResultsSize()
	{
		return _RoundsResults.size();
	}

	// return true if thre are no rounds history saved
	bool IsRoundsResultsEmpty()
	{
		return _RoundsResults.empty();
	}

	// get _RoundsResults structure has last round results
	stRoundResults getLastRoundResults()
	{
		if (_RoundsResults.empty())
			return stRoundResults{};

		return _RoundsResults.back();
	}

	// get _RoundsResults structure by given round index
	stRoundResults getRoundResults(short RoundIndex)
	{
		if (_RoundsResults.size() < RoundIndex + 1)
			return stRoundResults{};

		return _RoundsResults[RoundIndex];
	}

	// get all rounds results vector of stRoundsResults structure 
	vector <stRoundResults> getRoundsResults()
	{
		return _RoundsResults;
	}

	// get final results
	stGameResults getGameResults()
	{
		return GameResults;
	}

	// get winner name by given enWinner enum
	string WinnerName(enWinner Winner)
	{
		switch (Winner)
		{
		case enWinner::ePlayer1:
			return Player1.Name;

		case enWinner::ePlayer2:
			return Player2.Name;

		default:
			return "Draw";
		}
	}

	// get final winner of enWinner enum by _Player1WonTimes and _Player2WonTimes counters
	enWinner getFinalWinner()
	{
		if (_Player1WonTimes == _Player2WonTimes)
			return enWinner::eDraw;

		else if (_Player1WonTimes > _Player2WonTimes)
			return enWinner::ePlayer1;
		
		else
			return enWinner::ePlayer2;
	}

	// reset all rounds history
	void Clear()
	{
		if (_RoundsResults.empty())
			return;

		_GameRounds = 0;
		_Player1WonTimes = 0;
		_Player2WonTimes = 0;
		_DrawTimes = 0;

		_RoundsResults.clear();
	}

};

