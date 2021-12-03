#include "Game.h"
#include <boost/program_options.hpp>
#include <chrono>
#include <iostream>
#include <string>

player_type GetPlayerType(std::string type)
{
	if (type == "console")return player_type::user;
	if (type == "random")return player_type::random;
	if (type == "optimize")return player_type::optimize;
}

int main(int argc, char** argv)
{
	/*boost::program_options::options_description desc("Options");
	desc.add_options()
		("help,h","write info about options")
		("count,c", boost::program_options::value<int>(), "Set rounds ammount")
		("first,f", boost::program_options::value<std::string>(), "Set first player type(console, random, optimize)")
		("second,s", boost::program_options::value<std::string>(), "Set second player type(console, random, optimize)");

	boost::program_options::variables_map map;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), map);
	boost::program_options::notify(map);
	if (map.count("help,h")) 
	{
		std::cout << desc << "\n";
		return 0;
	}
	srand(std::chrono::system_clock::now().time_since_epoch().count());
	Game newGame{map.count("count,c") ? map["count,c"].as<int>() : 1,
		map.count("first,f") ? GetPlayerType(map["first,f"].as<std::string>()):player_type::random,
		map.count("second,f") ? GetPlayerType(map["second,f"].as<std::string>()):player_type::random};*/
	Game newGame{ 1, player_type::user, player_type::optimize };
	newGame.Start();
	newGame.PublishWinner();
	return 0;
}