#include "ConsolePlayer.h"
#include <iostream>
#include <string>

Position ConsolePlayer::GetAim()
{
	Position aim;
	PrintFields();
	std::cout << "Enter the X and Y coordinates:" << std::endl;
	std::cin >> aim.x >> aim.y;
	while(enemyField[aim] != tile_state::unknown)
	{
		std::cout << "You can't shoot at one tile twice!" << std::endl;
		std::cout << "Enter the X and Y coordinates:" << std::endl;
		std::cin >> aim.x >> aim.y;
	}
	return aim;
}

Ship GetShipData(int length)
{
	Position pos;
	std::cout << "Enter the coordinates for " << length << " tile long ship:" << std::endl;
	std::cin >> pos.x >> pos.y;
	std::cout << "Should it be vertical?(Y/N)" << std::endl;
	std::string directionDecision;
	std::cin >> directionDecision;
	while (directionDecision != "Y" && directionDecision != "N")
	{
		std::cout << "Try again!" << std::endl;
		std::cout << "Should it be vertical?(Y/N)" << std::endl;
		std::cin >> directionDecision;
	}
	return { pos, length, directionDecision == "Y" ? direction::vertical : direction::horizontal };
}

void ConsolePlayer::EmplaceShips()
{
	friendlyField = Map(map_type::friendly);
	enemyField = Map(map_type::hostile);
	for(int length = MIN_SHIP_LENGTH; length <= MAX_SHIP_LENGTH; length++)
	{
		for(int i = 0; i < GetAmmountFromLength(length); ++i)
		{
			while (!friendlyField.PlaceShip(GetShipData(length)))
			{
				std::cout << "This ship can't be placed there! Try again!" << std::endl;
			}
			PrintFields();
		}
	}
}


