#include "RandomPlayer.h"

Position RandomPlayer::GetAim()
{
	Position aim;
	int number = rand() % (MAP_SIZE*MAP_SIZE - shotsAmount);

	auto MoveNextTile = [&]()->void
	{
		number -= enemyField[aim] == tile_state::unknown;
		if (aim.x < MAP_SIZE - 1)
		{
			aim.x++;
		}
		else
		{
			aim.y++;
			aim.x = 0;
		}
	};

	while(number)
	{
		MoveNextTile();
	}
	while(enemyField[aim] != tile_state::unknown)
	{
		MoveNextTile();
	}
	return aim;
}

void RandomPlayer::EmplaceShips()
{
	friendlyField = Map(map_type::friendly);
	enemyField = Map(map_type::hostile);
	for(int length = MIN_SHIP_LENGTH; length <= MAX_SHIP_LENGTH; ++length)
	{
		for(int i = 0; i < GetAmmountFromLength(length); ++i)
		{
			Position toPlace(rand() % MAP_SIZE, rand() % MAP_SIZE);
			direction dir = rand() % 2 ? direction::horizontal : direction::vertical;
			while (!friendlyField.PlaceShip({ toPlace, length, dir }))
			{
				toPlace = { rand() % MAP_SIZE, rand() % MAP_SIZE };
				dir = rand() % 2 ? direction::horizontal : direction::vertical;
			}
		}
	}
}

void RandomPlayer::OnShot()
{
	shotsAmount++;
}
