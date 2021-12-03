#pragma once
#include <queue>
#include <functional>
#include <stack>
#include "Robot.h"

enum class tile_action {scan, step_onto, collect, ignore};

inline std::queue<Instruction> GetPathToClosest(const Map& map,
                                                const Position beginning_tile,
                                                const std::function<bool(TileInfo)>& can_go_through,
                                                const std::function<bool(TileInfo)>& is_target_ground,
												const std::function<tile_action(TileInfo)>& get_preferred_action)
{
	std::queue<Position> uncheckedTiles;
	uncheckedTiles.push(beginning_tile);
	std::vector<std::vector<Position>> previous_vertice(
		map.FieldSize().height,
		std::vector<Position>(
			map.FieldSize().width,
			{
						static_cast<int>(map.FieldSize().width),
						static_cast<int>(map.FieldSize().height)
			}
			)
	);
	std::queue<Instruction> res;
	while (!uncheckedTiles.empty())
	{
		Position current_tile = uncheckedTiles.front();
		uncheckedTiles.pop();
		if (!map.IsOffBorders(current_tile) && is_target_ground(map[current_tile]))
		{
			tile_action action = get_preferred_action(map[current_tile]);
			if(current_tile == beginning_tile &&
				action == tile_action::step_onto)
			{
				auto add_vertice = [&](const Position point, const Position previous) -> void
				{
					if (!map.IsOffBorders(point) &&
						previous_vertice[point.y][point.x] == Position{ static_cast<int>(map.FieldSize().width), static_cast<int>(map.FieldSize().height) } &&
						(can_go_through(map[point]) || is_target_ground(map[point])))
					{
						uncheckedTiles.push(point);
						previous_vertice[point.y][point.x] = previous;
					}
				};
				add_vertice(current_tile.Left(), current_tile);
				add_vertice(current_tile.Right(), current_tile);
				add_vertice(current_tile.Up(), current_tile);
				add_vertice(current_tile.Down(), current_tile);
				continue;
			}
			std::stack<Instruction> reversedPath;
			while (!(current_tile == beginning_tile))
			{
				auto is_parent = [&](const Position point) -> bool
				{
					if(map.IsOffBorders(point))
					{
						return false;
					}
					return point == previous_vertice[current_tile.y][current_tile.x];
				};

				if (is_parent(current_tile.Left()))
				{
					reversedPath.push(Instruction::MOVE_RIGHT);
					current_tile = current_tile.Left();
					continue;
				}
				if (is_parent(current_tile.Right()))
				{
					reversedPath.push(Instruction::MOVE_LEFT);
					current_tile = current_tile.Right();
					continue;
				}
				if (is_parent(current_tile.Up()))
				{
					reversedPath.push(Instruction::MOVE_DOWN);
					current_tile = current_tile.Up();
					continue;
				}
				if (is_parent(current_tile.Down()))
				{
					reversedPath.push(Instruction::MOVE_UP);
					current_tile = current_tile.Down();
					continue;
				}
				break;
			}
			while (!reversedPath.empty())
			{
				res.push(reversedPath.top());
				reversedPath.pop();
			}
			if (action == tile_action::scan)
			{
				if(res.empty())
				{
					res.push(Instruction::SCAN);
				}
				else
				{
					res.back() = Instruction::SCAN;
				}
			}
			if(action == tile_action::collect)
			{
				res.push(Instruction::COLLECT_APPLE);
			}
			return res;
		}
		auto add_vertice = [&](const Position point, const Position previous) -> void
		{
			if (!map.IsOffBorders(point) &&
				previous_vertice[point.y][point.x] == Position{ static_cast<int>(map.FieldSize().width), static_cast<int>(map.FieldSize().height) } &&
				(can_go_through(map[point]) || is_target_ground(map[point])))
			{
				uncheckedTiles.push(point);
				previous_vertice[point.y][point.x] = previous;
			}
		};
		add_vertice(current_tile.Left(), current_tile);
		add_vertice(current_tile.Right(), current_tile);
		add_vertice(current_tile.Up(), current_tile);
		add_vertice(current_tile.Down(), current_tile);
	}
	res.push(Instruction::AWAIT);
	return res;
}