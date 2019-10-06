#include "interpolation.hpp"
#include <iostream>


interpolation::interpolation() {

}

interpolation::~interpolation() {

}

void interpolation::predict_field() {
	if (old_fields.size() < 2)
		return;
	static constexpr std::array xoffsets = { 1,-1,0,0 };
	static constexpr std::array yoffsets = { 0,0,-1,1 };
	auto first = old_fields.back();
	old_fields.pop_back();
	auto second = old_fields.back();
	old_fields.push_back(first);
	auto first_field = first->get_board();
	auto second_field = second->get_board();
	pred_field = first_field;
	for (auto i = 0; i < first_field.size(); i++) {
		for (auto j = 0; j < first_field[i].size(); j++) {
			if (first_field[i][j].is_enemy_bot()) {
				vec velocity(0, 0);

				for (auto k = 0; k < 4; k++) {
					if (second_field[i + yoffsets[k]][j + xoffsets[k]].is_enemy_bot()) {
						velocity.x = -xoffsets[k];
						velocity.y = -yoffsets[k]; 
						break;
					}
				}
				if (velocity.x != 0 || velocity.y != 0) {
					for (auto k = 0; k < 4; k++) {
						if (k < 2 && pred_field[i + 1][j] == tile::NONE)
							continue;
						switch (pred_field[i + yoffsets[k]][j + xoffsets[k]].get_type())
						{
						case tile::type_none:
						case tile::type_gold:
						case tile::type_player:
							if(k != 2)
								pred_field[i + yoffsets[k]][j + xoffsets[k]] = k == 0 ? tile::ENEMY_RIGHT : tile::ENEMY_LEFT;
							break;
						case tile::type_ladder:
							if (k != 2 || pred_field[i][j].is_ladder())
							pred_field[i + yoffsets[k]][j + xoffsets[k]] = tile::ENEMY_LADDER;
							break;
						case tile::type_pipe:
							if (k != 2)
								pred_field[i + yoffsets[k]][j + xoffsets[k]] = tile::ENEMY_PIPE_LEFT;
							break;
						case tile::type_pit:
							if (k != 2)
								pred_field[i + yoffsets[k]][j + xoffsets[k]] = tile::ENEMY_PIT;
							break;
						}
					}
				}
			}
			if (first_field[i][j].is_player()) {
				vec velocity(0, 0);
				for (auto k = 0; k < 4; k++) {
					if (second_field[i + yoffsets[k]][j + xoffsets[k]].is_player()) {
						velocity.x = -xoffsets[k];
						velocity.y = -yoffsets[k];
						break;
					}
				}
				if (velocity.x != 0 || velocity.y != 0) {
					for (auto k = 0; k < 4; k++) {
						if (k < 2 && pred_field[i + 1][j] == tile::NONE)
							continue;
						switch (pred_field[i + yoffsets[k]][j + xoffsets[k]].get_type())
						{
						case tile::type_none:
						case tile::type_gold:
						case tile::type_player:
							if (k != 2)
							pred_field[i + yoffsets[k]][j + xoffsets[k]] = k == 0 ? tile::OTHER_HERO_RIGHT : tile::OTHER_HERO_LEFT;
							break;
						case tile::type_ladder:
							if(k != 2 || pred_field[i][j].is_ladder())
							pred_field[i + yoffsets[k]][j + xoffsets[k]] = tile::OTHER_HERO_LADDER;
							break;
						case tile::type_pipe:
							if (k != 2)
							pred_field[i + yoffsets[k]][j + xoffsets[k]] = tile::OTHER_HERO_PIPE_LEFT;
							break;
						case tile::type_pit:
							pred_field[i + yoffsets[k]][j + xoffsets[k]] = tile::OTHER_HERO_LEFT;
							break;
						}
					}
				}
				else pred_field[i][j] = tile::UNDESTROYABLE_WALL;
			}
		}
	}
	predicted_ = std::make_shared<game_board>(pred_field);
	predicted_->bfs(predicted_->get_myself());
}