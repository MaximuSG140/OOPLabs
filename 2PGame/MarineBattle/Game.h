#pragma once
#include "Player.h"

enum class player_type{random, user, optimize};

struct Score
{
	int firstPlayerScore = 0;
	int secondPlayerScore = 0;
};

class Game
{
public:
	explicit Game(int amountOfRounds = 1, player_type first = player_type::random, player_type second = player_type::random);
	void Start();
	void PublishWinner() const;
	~Game();
private:
	Player* first;
	Player* second;
	int amountOfRounds;
	Score score;
};

