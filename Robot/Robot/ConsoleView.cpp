#include "ConsoleView.h"
#include "Collector.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "ChangeRobotBehaviour.h"
#include "CreateCollector.h"
#include "CreateSapper.h"
#include "DeleteRobot.h"

char InfoToChar(const TileInfo info)
{
	switch(info)
	{
	case TileInfo::UNKNOWN: return '?';
	case TileInfo::EMPTY: return ' ';
	case TileInfo::MINE: return '*';
	case TileInfo::APPLE: return '0';
	case TileInfo::ROCK: return '^';
	}
	throw std::logic_error("Inconsistent enum value");
}

UserCommandWrapper ConsoleView::GetCommand()
{
	std::cout << "Enter command:" << std::endl;
	std::string command;
	std::cin >> command;
	std::unordered_map<std::string, std::function<UserCommand*()>> read_answer =
		{
			{
				"SET_MODE",
				[&]()->auto
				{
					std::unordered_map<std::string, RobotBehaviourModel> read_behaviour =
						{
							{
								"auto", RobotBehaviourModel::COLLECT
							},
							{
								"scan", RobotBehaviourModel::SCOUT
							},
							{
								"manual", RobotBehaviourModel::MANUAL
							}
						};
					int id;
					std::cin >> id;
					std::string line;
					std::getline(std::cin, line);
					std::stringstream args(line);
					std::string behaviour;
					args >> behaviour;
					std::string arg;
					std::vector<std::string> arguments;
					while(args >> arg)
					{
						arguments.push_back(arg);
					}
					return new ChangeCollectorBehaviour(reinterpret_cast<SmartRobot*>(id),
														read_behaviour.at(behaviour),
														arguments);
				}
			},
			{
				"CREATE_COLLECTOR",
				[&]() -> auto
				{
					std::string line;
					std::getline(std::cin, line);
					return new CreateCollector();
				}
			},
			{
					"SAPPER_ON",
					[&]()->auto
					{
						int master_id;
						std::cin >> master_id;
						std::string line;
						std::getline(std::cin, line);
						return new CreateSapper(reinterpret_cast<SmartRobot*>(master_id));
					}
			},
			{
				"REMOVE_ROBOT",
				[&]()->UserCommand*
				{
					int remove_id;
					std::cin >> remove_id;
					return new DeleteRobot(reinterpret_cast<SmartRobot*>(remove_id));
				}
			}
		};
	return UserCommandWrapper(read_answer.at(command)());
}

Instruction ConsoleView::GetInstruction()
{
	std::cout << "Enter instruction for collector" << std::endl;
	std::string string_instruction;
	std::unordered_map<std::string, Instruction> read_instruction =
		{
			{
				"L", Instruction::MOVE_LEFT
			},
			{
				"R", Instruction::MOVE_RIGHT
			},
			{
				"U", Instruction::MOVE_UP
			},
			{
				"D", Instruction::MOVE_DOWN
			},
			{
				"SCAN", Instruction::SCAN
			},
			{
				"GRAB", Instruction::COLLECT_APPLE
			},
			{
				"STOP", Instruction::AWAIT
			},
			{
				"WAIT", Instruction::WAIT
			}
	};
	std::cin >> string_instruction;
	try
	{
		if(string_instruction == "MOVE")
		{
			std::string string_direction;
			std::cin >> string_direction;
			return read_instruction.at(string_direction);
		}
		return read_instruction.at(string_instruction);
	}
	catch(std::exception&)
	{
		std::cout << "Wrong command!" << std::endl;
		return GetInstruction();
	}
}

void ConsoleView::PrintRobotState(SmartRobot& sender)
{
	ScaleMap map = sender.GetMap();
	Position center = sender.GetPosition();
	std::cout << "Robot ID: " << reinterpret_cast<int>(&sender) << std::endl;
	std::cout << "Role: " << sender.GetRole() << std::endl;
	std::cout << "State: " << (sender.IsActive() ? "Active" : "Sleep") << std::endl;
	std::cout << "Cached map:" << std::endl;
	for (int i = std::max(map.UpperBorder(), center.y - 5); i < std::min(map.BottomBorder(), center.y + 5); ++i)
	{
		for (int j = std::max(map.LeftBorder(), center.x - 5); j < std::min(map.RightBorder(), center.x + 5); ++j)
		{
			if (sender.GetPosition() == Position{ j, i })
			{
				std::cout << 'C';
			}
			else
			{
				std::cout << InfoToChar(map[{j, i}]);
			}
		}
		std::cout << std::endl;
	}
	std::cout << "=======================" << std::endl;
}