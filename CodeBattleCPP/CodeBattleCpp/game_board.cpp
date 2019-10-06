#include "game_board.hpp"


game_board::game_board(std::vector<std::vector<tile>>& map)
	: map(map) {
	next_action_ = player_command::kill_self;
}
vec game_board::get_myself() {
	std::list<vec> result = find_all(tile::HERO_DIE);
	result.splice(result.end(), find_all(tile::HERO_DRILL_LEFT));
	result.splice(result.end(), find_all(tile::HERO_DRILL_RIGHT));
	result.splice(result.end(), find_all(tile::HERO_LADDER));
	result.splice(result.end(), find_all(tile::HERO_LEFT));
	result.splice(result.end(), find_all(tile::HERO_RIGHT));
	result.splice(result.end(), find_all(tile::HERO_FALL_LEFT));
	result.splice(result.end(), find_all(tile::HERO_FALL_RIGHT));
	result.splice(result.end(), find_all(tile::HERO_PIPE_LEFT));
	result.splice(result.end(), find_all(tile::HERO_PIPE_RIGHT));
	return result.front();
}
bool game_board::is_game_over() {
	for (uint32_t j = 0; j < map.size(); j++)
	{
		for (uint32_t i = 0; i < map.size(); i++)
		{
			if (map[j][i] == tile::HERO_DIE)
				return true;
		}
	}
	return false;
}
bool game_board::has_element_at(vec point, tile element) {
	auto val = get_element_at(point);
	return val.has_value() && val.value() == element;
}
std::optional<tile> game_board::get_element_at(vec point) {
	if (point.isOutOfBoard(map.size()))
		return std::nullopt;
	return map[point.y][point.x];
}
std::list<vec> game_board::find_all(tile element) {
	std::list<vec> result;
	for (uint32_t j = 0; j < map.size(); j++)
	{
		for (uint32_t i = 0; i < map.size(); i++)
		{
			if (map[j][i] == element) {
				result.push_back(vec(i, j));
			}
		}
	}
	return result;
}
std::list<vec> game_board::get_other_players() {
	std::list<vec> result = find_all(tile::OTHER_HERO_DIE);
	result.splice(result.end(), find_all(tile::OTHER_HERO_LEFT));
	result.splice(result.end(), find_all(tile::OTHER_HERO_RIGHT));
	result.splice(result.end(), find_all(tile::OTHER_HERO_LADDER));
	result.splice(result.end(), find_all(tile::OTHER_HERO_PIPE_LEFT));
	result.splice(result.end(), find_all(tile::OTHER_HERO_PIPE_RIGHT));
	return result;
}
std::list<vec> game_board::get_walls() {
	std::list<vec> result = find_all(tile::BRICK);
	result.splice(result.end(), find_all(tile::UNDESTROYABLE_WALL));
	return result;
}
std::list<vec> game_board::get_ladders() {
	std::list<vec> result = find_all(tile::LADDER);
	result.splice(result.end(), find_all(tile::HERO_LADDER));
	result.splice(result.end(), find_all(tile::OTHER_HERO_LADDER));
	result.splice(result.end(), find_all(tile::ENEMY_LADDER));
	return result;
}
std::list<vec> game_board::get_gold() {
	auto res =  find_all(tile::YELLOW_GOLD);
	res.splice(res.end(), find_all(tile::RED_GOLD));
	res.splice(res.end(), find_all(tile::GREEN_GOLD));
	return res;
}
std::list<vec> game_board::get_pipes() {
	std::list<vec> result = find_all(tile::PIPE);
	result.splice(result.end(), find_all(tile::HERO_PIPE_LEFT));
	result.splice(result.end(), find_all(tile::HERO_PIPE_RIGHT));
	result.splice(result.end(), find_all(tile::OTHER_HERO_PIPE_LEFT));
	result.splice(result.end(), find_all(tile::OTHER_HERO_PIPE_RIGHT));
	result.splice(result.end(), find_all(tile::ENEMY_PIPE_LEFT));
	result.splice(result.end(), find_all(tile::ENEMY_PIPE_RIGHT));
	return result;
}
std::list<vec> game_board::get_hunters() {
	std::list<vec> result = find_all(tile::ENEMY_LADDER);
	result.splice(result.end(), find_all(tile::ENEMY_LEFT));
	result.splice(result.end(), find_all(tile::ENEMY_PIPE_LEFT));
	result.splice(result.end(), find_all(tile::ENEMY_PIPE_RIGHT));
	result.splice(result.end(), find_all(tile::ENEMY_RIGHT));
	result.splice(result.end(), find_all(tile::ENEMY_PIT));
	return result;
}
bool game_board::is_near_to(vec point, tile element) {
	if (point.isOutOfBoard(map.size())) {
		return false;
	}
	return has_element_at(point.shiftBottom(), element)
		|| has_element_at(point.shiftTop(), element)
		|| has_element_at(point.shiftLeft(), element)
		|| has_element_at(point.shiftRight(), element);
}
bool game_board::has_hunter(vec point) {
	auto elem = get_element_at(point).value_or(tile::NONE);
	return elem == tile::ENEMY_LADDER || elem == tile::ENEMY_LEFT || elem == tile::ENEMY_PIPE_LEFT || elem == tile::ENEMY_PIPE_RIGHT || elem == tile::ENEMY_RIGHT || elem == tile::ENEMY_PIT;
}
bool game_board::has_player(vec point) {
	std::list<vec> enemies = get_other_players();
	for (std::list<vec>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if (it->x == point.x && it->y == point.y)
			return true;

	}
	return false;
}
bool game_board::has_wall(vec point) {
	std::list<vec> enemies = get_walls();
	for (std::list<vec>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if (it->x == point.x && it->y == point.y)
			return true;
	}
	return false;
}
bool game_board::has_ladder(vec point) {
	std::list<vec> enemies = get_ladders();
	for (std::list<vec>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if (it->x == point.x && it->y == point.y)
			return true;
	}
	return false;
}
bool game_board::has_gold(vec point) {
	std::list<vec> enemies = get_gold();
	for (std::list<vec>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if (it->x == point.x && it->y == point.y)
			return true;
	}
	return false;
}
bool game_board::has_pipe(vec point) {
	std::list<vec> enemies = get_pipes();
	for (std::list<vec>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if (it->x == point.x && it->y == point.y)
			return true;
	}
	return false;
}
game_board::~game_board()
{

}

