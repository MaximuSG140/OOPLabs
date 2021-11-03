#pragma once
#include "Player.h"

enum class player_type{random, user, optimize};

struct Score
{
	size_t firstPlayerScore = 0;
	size_t secondPlayerScore = 0;
};

class Game
{
public:
	explicit Game(size_t amountOfRounds = 1, player_type first = player_type::random, player_type second = player_type::random);
	void Start();
	void PublishWinner() const;
private:
	Player* first;
	Player* second;
	size_t amountOfRounds;
	Score score;
};

