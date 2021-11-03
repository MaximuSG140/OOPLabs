#include "Game.h"

#include <iostream>

#include "ConsolePlayer.h"
#include "RandomPlayer.h"
#include "EffectivePlayer.h"

Player* CreatePlayer(const player_type type)
{
	switch (type)
	{
	case player_type::random: 
		return new RandomPlayer();
	case player_type::user: 
		return new ConsolePlayer();
	case player_type::optimize: 
		return new EffectivePlayer();
	}
}

Game::Game(const size_t amountOfRounds, const player_type first, const player_type second)
	: amountOfRounds(amountOfRounds)
{
	this->first = CreatePlayer(first);
	this->second = CreatePlayer(second);
}

void Game::Start()
{
	for(size_t i = 0; i < amountOfRounds; ++i)
	{
		first->EmplaceShips();
		second->EmplaceShips();
		while(first->HasAliveShips() && second->HasAliveShips())
		{
			first->Attack(*second);
			second->Attack(*first);
		}
		if (first->HasAliveShips())score.firstPlayerScore++;
		else score.secondPlayerScore++;
	}
}

void Game::PublishWinner() const
{
	if(score.firstPlayerScore > score.secondPlayerScore)
	{
		std::cout << "First player won" << std::endl;
	}
	else
	{
		std::cout << "Second player won" << std::endl;
	}
}
