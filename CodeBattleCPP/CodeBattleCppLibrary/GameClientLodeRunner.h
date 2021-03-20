#pragma once

#include <string>
#include <memory>
#include <functional>

#include "LodeRunnerAction.h"

namespace easywsclient
{
	class WebSocket;
} // namespace easywsclient
class GameBoard;

class GameClientLodeRunner
{
public:
	GameClientLodeRunner(const std::string &_server);
	~GameClientLodeRunner();

	void Run(std::function<LodeRunnerAction(const GameBoard &)> _message_handler);

private:
	std::unique_ptr<easywsclient::WebSocket> web_socket;
	std::string path;
};
