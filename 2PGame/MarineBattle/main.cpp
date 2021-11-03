#include "Game.h"
#include "../optionparser-1.7/src/optionparser.h"
#include <chrono>
#include <iostream>

constexpr option::Descriptor usage[] = {
	{
		0, 0, "h" ,"help", option::Arg::None, "--help Writes info about options"
	},
	{
		1, 0, "c", "count", option::Arg::None, "--count Sets amount of rounds play to"
	},
	{
		2, 0, "f", "first", option::Arg::None, "--first Sets type of first player"
	},
	{
		3, 0, "s", "second", option::Arg::None, "--second Sets type of second player"
	}
};

player_type GetPlayer(const option::Option& playerOption)
{
	std::string playerType(&playerOption.name[1]);
	if (playerType == "optimize")return player_type::optimize;
	if (playerType == "random")return player_type::random;
	if (playerType == "interactive")return player_type::user;
	return player_type::random;
}

size_t GetRoundCount(const option::Option& countOption)
{
	if (!countOption)return 1;
	char* end;
	return strtoul(&countOption.name[1], &end, 10);
}

int main(int argc, char** argv)
{
	option::Stats  stats(usage, argc, argv);
	option::Option *options = new option::Option[stats.options_max], *buffer = new option::Option[stats.buffer_max];
	option::Parser parse(true, usage, argc, argv, options, buffer);
	if (options[0] || argc == 0) {
		printUsage(std::cout, usage);
		return 0;
	}
	srand(std::chrono::system_clock::now().time_since_epoch().count());
	Game newGame{GetRoundCount(buffer[0]), GetPlayer(buffer[1]), GetPlayer(buffer[2])};
	newGame.Start();
	newGame.PublishWinner();
	return 0;
}