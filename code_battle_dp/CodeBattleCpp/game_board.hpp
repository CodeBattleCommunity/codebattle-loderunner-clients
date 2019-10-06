#pragma once

#include "tile.hpp"
#include "vec.hpp"
#include "player_command.hpp"
#include <list>
#include <optional>
#include <queue>
#include <vector>

class game_board
{
	static game_board* old;
public:
	game_board(std::vector<std::vector<tile>>& map);
	vec get_myself();
	bool is_game_over();
	bool has_element_at(vec point, tile element);
	std::optional<tile> get_element_at(vec point);
	//void printBoard();
	std::list<vec> find_all(tile element);
	std::list<vec> get_other_players();
	std::list<vec> get_walls();
	std::list<vec> get_ladders();
	std::list<vec> get_gold();
	std::list<vec> get_pipes();
	std::list<vec> get_hunters();
	bool is_near_to(vec point, tile element);
	bool has_hunter(vec point);
	bool has_player(vec point);
	bool has_wall(vec point);
	bool has_ladder(vec point);
	bool has_gold(vec point);
	bool has_pipe(vec point);
	void dfs(vec at);
	void bfs(vec at);
	~game_board();
	player_command current_act() {
		return next_action_;
	}
	const std::vector<vec>& get_current_path() {
		return opt_path;
	}
	std::vector<std::vector<tile>>& get_board() {
		return map;
	}
private:
	void find_next_direction(vec closest_enemy, vec at);
	static bool enemy_on_tail;
	std::vector<std::vector<tile>> map;
	std::vector<std::vector<std::pair<vec, int>>> graph;
	std::vector<vec> opt_path;
	player_command next_action_;
};