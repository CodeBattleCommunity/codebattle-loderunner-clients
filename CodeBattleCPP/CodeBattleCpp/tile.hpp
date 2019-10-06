#pragma once

#include <cstdint>

class tile {
public:
	enum tile_id_ : uint16_t
	{
		NONE = L' ',
		BRICK = L'#',
		//PIT_FILL = L'1234',
		UNDESTROYABLE_WALL = L'☼',
		DRILL_PIT = L'*',
		YELLOW_GOLD = L'$',
		GREEN_GOLD = L'&',
		RED_GOLD = L'@',
		LADDER = L'H',
		PIPE = L'~',
		PIT_FILL_1 = L'1',
		PIT_FILL_2 = L'2',
		PIT_FILL_3 = L'3',
		PIT_FILL_4 = L'4',
		PORTAL = L'⊛',
		THE_SHADOW_PILL = L'S',
		//твой герой
		HERO_DIE = L'Ѡ',
		HERO_DRILL_LEFT = L'Я',
		HERO_DRILL_RIGHT = L'R',
		HERO_LADDER = L'Y',
		HERO_LEFT = L'◄',
		HERO_RIGHT = L'►',
		HERO_FALL_LEFT = L']',
		HERO_FALL_RIGHT = L'[',
		HERO_PIPE_LEFT = L'{',
		HERO_PIPE_RIGHT = L'}',
		HERO_SHADOW_DRILL_LEFT = L'⊰',
		HERO_SHADOW_DRILL_RIGHT = L'⊱',
		HERO_SHADOW_LADDER = L'⍬',
		HERO_SHADOW_LEFT = L'⊲',
		HERO_SHADOW_RIGHT = L'⊳',
		HERO_SHADOW_FALL_LEFT = L'⊅',
		HERO_SHADOW_FALL_RIGHT = L'⊄',
		HERO_SHADOW_PIPE_LEFT = L'⋜',
		HERO_SHADOW_PIPE_RIGHT = L'⋝',
		//герои других охотников
		OTHER_HERO_DIE = L'Z',
		OTHER_HERO_LEFT = L')',
		OTHER_HERO_RIGHT = L'(',
		OTHER_HERO_LADDER = L'U',
		OTHER_HERO_PIPE_LEFT = L'Э',
		OTHER_HERO_PIPE_RIGHT = L'Є',
		OTHER_HERO_SHADOW_DIE = L'⋈',
		OTHER_HERO_SHADOW_LEFT = L'⋊',
		OTHER_HERO_SHADOW_RIGHT = L'⋉',
		OTHER_HERO_SHADOW_LADDER = L'⋕',
		OTHER_HERO_SHADOW_PIPE_LEFT = L'⊣',
		OTHER_HERO_SHADOW_PIPE_RIGHT = L'⊢',
		//враг охотник
		ENEMY_LADDER = L'Q',
		ENEMY_LEFT = L'«',
		ENEMY_RIGHT = L'»',
		ENEMY_PIPE_LEFT = '<',
		ENEMY_PIPE_RIGHT = L'>',
		ENEMY_PIT = L'X'
	};
	tile_id_ id_;
	enum tile_type_ {
		type_ladder,
		type_enemy,
		type_player,
		type_me,
		type_breakable,
		type_pickable,
		type_gold,
		type_pill,
		type_pipe,
		type_pit,
		type_unbreakable,
		type_none
	};
public:
	tile() : id_(NONE) {}
	tile(tile_id_ id) : id_(id) {}
	tile_id_ get_id() { return id_; }
	bool is_ladder() {	return id_ == LADDER || id_ == ENEMY_LADDER || id_ == HERO_LADDER || id_ == OTHER_HERO_LADDER || id_ == OTHER_HERO_SHADOW_LADDER || id_ == HERO_SHADOW_LADDER; }
	bool is_me() {
		return id_ == HERO_DIE || id_ == HERO_DRILL_LEFT || id_ == HERO_DRILL_RIGHT || id_ == HERO_FALL_LEFT || id_ == HERO_FALL_RIGHT
			|| id_ == HERO_LADDER || id_ == HERO_LEFT || id_ == HERO_PIPE_LEFT || id_ == HERO_PIPE_RIGHT || id_ == HERO_RIGHT || is_my_shadow();
	}
	bool is_my_shadow() {
		return id_ == HERO_SHADOW_DRILL_LEFT || id_ == HERO_SHADOW_DRILL_RIGHT || id_ == HERO_SHADOW_FALL_LEFT || id_ == HERO_SHADOW_FALL_RIGHT
			|| id_ == HERO_SHADOW_LADDER || id_ == HERO_SHADOW_LEFT || id_ == HERO_SHADOW_PIPE_LEFT || id_ == HERO_SHADOW_PIPE_RIGHT || id_ == HERO_SHADOW_RIGHT;
	}
	bool is_pit() { return id_ == PIT_FILL_1 || id_ == PIT_FILL_2 || id_ == PIT_FILL_3 || id_ == PIT_FILL_4; }
	bool is_enemy_bot() { return id_ == ENEMY_LADDER || id_ == ENEMY_LEFT || id_ == ENEMY_PIPE_LEFT || id_ == ENEMY_PIPE_RIGHT || id_ == ENEMY_PIT || id_ == ENEMY_RIGHT; }
	bool is_player() { return is_player_shadow() || id_ == OTHER_HERO_DIE || id_ == OTHER_HERO_LADDER || id_ == OTHER_HERO_LEFT || id_ == OTHER_HERO_PIPE_LEFT || id_ == OTHER_HERO_PIPE_RIGHT || id_ == OTHER_HERO_RIGHT; }
	bool is_player_shadow() { return  id_ == OTHER_HERO_SHADOW_LADDER || id_ == OTHER_HERO_SHADOW_LEFT || id_ == OTHER_HERO_SHADOW_PIPE_LEFT || id_ == OTHER_HERO_SHADOW_PIPE_RIGHT || id_ == OTHER_HERO_SHADOW_RIGHT || id_ == OTHER_HERO_SHADOW_DIE; }
	bool is_pipe() { return id_ == PIPE || id_ == ENEMY_PIPE_LEFT || id_ == ENEMY_PIPE_RIGHT || id_ == OTHER_HERO_PIPE_LEFT || id_ == OTHER_HERO_PIPE_RIGHT || id_ == HERO_PIPE_LEFT || id_ == HERO_PIPE_RIGHT; }
	bool is_unbreakable() { return id_ == UNDESTROYABLE_WALL; }
	bool is_gold() { return id_ == YELLOW_GOLD || id_ == RED_GOLD || id_ == GREEN_GOLD; }
	bool is_brick() { return id_ == BRICK; }
	tile_type_ get_type() {
		if (is_enemy_bot()) return type_enemy;
		if (is_player()) return type_player;
		if (is_me()) return type_me;
		if (is_ladder()) return type_ladder;
		if (is_pipe()) return type_pipe;
		if (is_gold()) return type_gold;
		if (is_unbreakable()) return type_unbreakable;
		if (is_brick()) return type_breakable;
		if (is_pit()) return type_pit;
	}
	tile& operator=(const tile& l) { this->id_ = l.id_; return *this; }
	operator tile_id_() { return get_id(); }
};