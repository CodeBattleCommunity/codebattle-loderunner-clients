#pragma once

#include <cstdint>

enum class LodeRunnerBlocks : uint16_t
{
	NONE = L' ',
	BRICK = L'#',
	PIT_FILL = L'1234',
	UNDESTROYABLE_WALL = L'☼',
	DRILL_PIT = L'*',
	GOLD = L'$',
	LADDER = L'H',
	PIPE = L'~',
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
	//герои других охотников
	OTHER_HERO_DIE = L'Z',
	OTHER_HERO_LEFT = L')',
	OTHER_HERO_RIGHT = L'(',
	OTHER_HERO_LADDER = L'U',
	OTHER_HERO_PIPE_LEFT = L'Э',
	OTHER_HERO_PIPE_RIGHT = L'Є',
	//враг охотник
	ENEMY_LADDER = L'Q',
	ENEMY_LEFT = L'«',
	ENEMY_RIGHT = L'»',
	ENEMY_PIPE_LEFT = '<',
	ENEMY_PIPE_RIGHT = L'>',
	ENEMY_PIT = L'X'
};

