#include "game_board.hpp"

game_board* game_board::old = nullptr;

bool game_board::enemy_on_tail = false;

void game_board::find_next_direction(vec closest_enemy, vec at) {
	enemy_on_tail = false;
	if (closest_enemy.dist_to(at) == 1 && at.y == closest_enemy.y) {
		auto element = get_element_at(closest_enemy);
		auto me = get_element_at(at);
		switch (element.value()) {
		case tile::ENEMY_LEFT:
		case tile::OTHER_HERO_LEFT:
		case tile::OTHER_HERO_SHADOW_LEFT:
			if (closest_enemy.x > at.x && get_element_at(vec(at.x + 1, at.y + 1)).value_or(tile::NONE) == tile::BRICK) {
				next_action_ = player_command::dig_right;
				return;
			}
			break;
		case tile::ENEMY_RIGHT:
		case tile::OTHER_HERO_RIGHT:
		case tile::OTHER_HERO_SHADOW_RIGHT:
			if (closest_enemy.x < at.x && get_element_at(vec(at.x - 1, at.y + 1)).value_or(tile::NONE) == tile::BRICK) {
				next_action_ = player_command::dig_left;
				return;
			}
			break;
		}
	}
	enemy_on_tail = closest_enemy.dist_to(at) <= 2;
	if (opt_path.size() > 0) {
		auto to = opt_path[0];
		if (to.x > at.x) next_action_ = player_command::right;
		if (to.x < at.x) next_action_ = player_command::left;
		if (to.y > at.y) next_action_ = player_command::down;
		if (to.y < at.y) next_action_ = player_command::up;

		if (opt_path.size() > 1 && get_element_at(opt_path[1]).value_or(tile::NONE) == tile::BRICK)
		{
			if (next_action_ == player_command::left) next_action_ = player_command::dig_left;
			if (next_action_ == player_command::right) next_action_ = player_command::dig_right;
			if (get_element_at(vec(at.x - 1, at.y)).value_or(tile::NONE).is_gold()) next_action_ = player_command::left;
			if (get_element_at(vec(at.x + 1, at.y)).value_or(tile::NONE).is_gold()) next_action_ = player_command::right;
		}
		if (next_action_ == player_command::down && get_element_at(to).value_or(tile::BRICK) == tile::BRICK) {
			if ((!get_element_at(vec(at.x + 1, at.y + 1)).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough() &&
				get_element_at(vec(at.x + 1, at.y)).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough()) ||
				get_element_at(vec(at.x + 1, at.y)).value_or(tile::NONE).is_ladder())
				next_action_ = player_command::right;
			else if ((!get_element_at(vec(at.x - 1, at.y + 1)).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough() &&
				get_element_at(vec(at.x - 1, at.y)).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough()) ||
				get_element_at(vec(at.x - 1, at.y)).value_or(tile::NONE).is_ladder())
				next_action_ = player_command::left;
			else if (((!get_element_at(vec(at.x - 1, at.y + 1)).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough() &&
				get_element_at(vec(at.x - 1, at.y)).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough()) ||
				get_element_at(vec(at.x - 1, at.y)).value_or(tile::NONE).is_ladder() ||
				(get_element_at(vec(at.x - 1, at.y)).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough() &&
					get_element_at(vec(at.x - 1, at.y + 1)).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough())))
				next_action_ = player_command::left;
			else if ((!get_element_at(vec(at.x + 1, at.y + 1)).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough() &&
				get_element_at(vec(at.x + 1, at.y)).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough()) ||
				get_element_at(vec(at.x + 1, at.y)).value_or(tile::NONE).is_ladder() ||
				(get_element_at(vec(at.x + 1, at.y)).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough() &&
					get_element_at(vec(at.x + 1, at.y + 1)).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough()))
				next_action_ = player_command::right;
			else next_action_ = player_command::kill_self;
		}
	}
}

void game_board::bfs(vec at) {
	//std::queue<vec> q;
	//q.push(at);
	//std::vector<bool> used(map.size() * map.size());
	//std::vector<int> d(map.size() * map.size());
	//std::vector<vec> p(map.size() * map.size());
	std::vector<vec> closest_elems;
	//used[at.y * map.size() + at.x] = true;
	//p[at.y * map.size() + at.x] = vec(-1, -1);
	//while (!q.empty()) {
	//	auto v = q.front();
	//	q.pop();
	//	for (size_t i = 0; i < graph[v.y * map.size() + v.x].size(); ++i) {
	//		auto to = graph[v.y * map.size() + v.x][i];
	//		if (!used[to.y * map.size() + to.x]/* && at.dist_to(to) <= 10000*/) {
	//			auto element = get_element_at(to);
	//			if (element.has_value()) {
	//				switch (element.value().get_type()) {
	//				case tile::type_gold:
	//				case tile::type_enemy:
	//				case tile::type_player:
	//					closest_elems.push_back({ to,element.value() });
	//					break;
	//				}
	//			}
	//			used[to.y * map.size() + to.x] = true;
	//			q.push(to);
	//			d[to.y * map.size() + to.x] = d[v.y * map.size() + v.x] + 1;
	//			p[to.y * map.size() + to.x] = v;
	//		}
	//	}
	//}
	std::vector<int> d(graph.size(), std::numeric_limits<int>::max()), p(graph.size());
	d[at.y * map.size() + at.x] = 0;
	std::vector<char> u(graph.size());
	vec closest_en(-1, -1);
	for (int i = 0; i < graph.size(); ++i) {
		int v = -1;
		for (int j = 0; j < graph.size(); ++j)
			if (!u[j] && (v == -1 || d[j] < d[v]))
				v = j;
		if (d[v] == std::numeric_limits<int>::max())
			break;
		u[v] = true;

		for (size_t j = 0; j < graph[v].size(); ++j) {
			auto to = graph[v][j].first;
			auto element = get_element_at(to);
			if (element.value_or(tile::NONE).get_type() == tile::type_gold)
				closest_elems.push_back(to);
			if (closest_en.x == -1)
				if (element.value_or(tile::NONE).get_type() == tile::type_player || element.value_or(tile::NONE).get_type() == tile::type_enemy)
					closest_en = to;

			int len = graph[v][j].second;
			if (d[v] + len < d[to.y * map.size() + to.x]) {
				d[to.y * map.size() + to.x] = d[v] + len;
				p[to.y * map.size() + to.x] = v;
			}
		}
	}
	/*if (!closest_elems.size())
		return { -1,-1 };
	*/
	//auto first = closest_elems.front();
	int max_gold = 0;
	opt_path.clear();
	for (auto& elem : closest_elems) {
		for (auto v = elem; v != at; v = vec(p[v.y * map.size() + v.x] % map.size(), p[v.y * map.size() + v.x] / map.size()))
			opt_path.push_back(v);
		break;
	}
	std::reverse(opt_path.begin(), opt_path.end());
	//if (opt_path.size())
	//	opt_path.erase(opt_path.begin());
	/*if (first.second.is_gold())*/
	
	find_next_direction(closest_en, at);
}

void game_board::dfs(vec at) {
	auto pos = get_element_at(at);
	if (has_hunter(at) || (pos.has_value() && (pos.value() == tile::UNDESTROYABLE_WALL/* || pos.value() == tile::BRICK*/)))
		return;
	if (at.x == 42 && at.y == 34)
		pos = get_element_at(at);
	if (get_element_at(at).value_or(tile::UNDESTROYABLE_WALL).can_pass_trough() &&
		get_element_at(vec(at.x, at.y + 1)).value_or(tile::UNDESTROYABLE_WALL).cant_step_on())
	{
		if (get_element_at(vec(at.x, at.y + 1)).has_value())
			graph[at.y * map.size() + at.x].push_back({ vec(at.x, at.y + 1), 3 });
		if (!pos.value_or(tile::NONE).is_pipe())
			return;
	}
	auto i = at.y;
	for (auto j = at.x - 1; j <= at.x + 1; j++) {
		if (j == at.x) continue;
		if (pos.value_or(tile::BRICK) == tile::BRICK) continue;
		auto val = get_element_at({ j,i });
		if (val.has_value()) {
			auto element = val.value();
			auto offset = 0;
			switch (element.get_type()) {
			case tile::type_unbreakable:
			case tile::type_breakable:
				break;
			case tile::type_enemy:
			case tile::type_player:
				if (get_myself().dist_to(vec(j, i)) <= 5)
					break;
				if (!get_element_at(vec(j, i + 1)).value_or(tile::PIT_FILL_1).is_pit())
					graph[at.y * map.size() + at.x].push_back({ vec(j, i),5 });
				break;
			case tile::type_gold:
				if (!get_element_at(vec(j, i + 1)).value_or(tile::PIT_FILL_1).is_pit())
					graph[at.y * map.size() + at.x].push_back({ vec(j, i),0 });
				break;
			default:
				if (!get_element_at(vec(j, i + 1)).value_or(tile::PIT_FILL_1).is_pit())
					graph[at.y * map.size() + at.x].push_back({ vec(j, i),1 });
			}
		}
	}
	auto j = at.x;
	for (i = at.y - 1; i <= at.y + 1; i++) {
		if (i < at.y && !pos.value_or(tile::UNDESTROYABLE_WALL).is_ladder()) continue;
		if (i == at.y) continue;

		auto val = get_element_at({ j,i });
		if (val.has_value()) {
			auto element = val.value();
			auto offset = 0;
			switch (element.get_type()) {
			case tile::type_unbreakable:
			case tile::type_player:
				break;
			case tile::type_enemy:
				if (get_myself().dist_to(vec(j, i)) <= 5)
					break;
				if (!get_element_at(vec(j, i + 1)).value_or(tile::PIT_FILL_1).is_pit())
					graph[at.y * map.size() + at.x].push_back({ vec(j, i),100 });
				break;
			case tile::type_breakable:
				if (pos.value_or(tile::BRICK).is_brick() || pos.value_or(tile::UNDESTROYABLE_WALL).is_ladder() || enemy_on_tail)
					break;
				if (!get_element_at(vec(j, i + 1)).value_or(tile::PIT_FILL_1).is_pit())
					graph[at.y * map.size() + at.x].push_back({ vec(j, i), 9 });
				break;
			default:
				if (!get_element_at(vec(j, i + 1)).value_or(tile::PIT_FILL_1).is_pit())
					graph[at.y * map.size() + at.x].push_back({ vec(j, i),  i > at.y ? 3 : 1 });
			}
		}
	}
	//}
}

game_board::game_board(std::vector<std::vector<tile>>& map)
	: map(map) {
	this->graph.resize(map.size() * map.size());
	for (auto i = 0; i < map.size(); i++) {
		for (auto j = 0; j < map[i].size(); j++) {
			auto val = get_element_at(vec(j, i));
			if (val.has_value()) {
				dfs(vec(j, i));
			}
		}
	}
	next_action_ = player_command::kill_self;
	//if (!is_game_over())
	//	bfs(get_myself());

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
	auto res = find_all(tile::YELLOW_GOLD);
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

