#pragma once
#include <memory>
#include <list>
#include <array>
#include "game_board.hpp"

class interpolation {
public:
	static __forceinline interpolation* instance() {
		static auto inst = new interpolation();
		return inst;
	}
	interpolation();
	~interpolation();
	void add_field(std::vector<std::vector<tile>>& map) {
		old_fields.push_back(std::make_shared<game_board>(map));
		if (old_fields.size() > 5)
			old_fields.pop_front();
	}
	void predict_field();
	player_command next_action() {
		if (predicted_.get())
			return predicted_->current_act();
		return player_command::kill_self;
	}
	std::shared_ptr<game_board>& get_pred_board() {
		return predicted_;
	}
protected:
	std::vector<std::vector<tile>> pred_field;
	std::shared_ptr<game_board> predicted_ = nullptr;
	std::list<std::shared_ptr<game_board>> old_fields;
};