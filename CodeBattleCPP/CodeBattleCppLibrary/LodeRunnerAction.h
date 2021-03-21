#pragma once
#include <string>

enum class LodeRunnerAction {
	GO_LEFT,
	GO_RIGHT,
	GO_UP,
	GO_DOWN,
	DRILL_RIGHT,
	DRILL_LEFT,
	DRILL,
	SUICIDE
};

LodeRunnerAction LodeRunnerActionFromString(const std::string& str);

namespace std {
	std::string to_string(LodeRunnerAction action);
}