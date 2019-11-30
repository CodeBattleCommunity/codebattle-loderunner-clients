#pragma once

#include <string>
#include <thread>
#include "easywsclient\easywsclient.hpp"
#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>
#include <functional>

#include "BoardElement.h"
#include "LoderunnerAction.h"
#include "GameBoard.h"

class GameClientLodeRunner
{
	BoardElement **map;
	GameBoard *board;
	uint32_t map_size, player_x, player_y;

	easywsclient::WebSocket *web_socket;
	std::string path;

	bool is_running;
	std::thread *work_thread;
	void update_func(std::function<void()> _message_handler);

public:
 	GameClientLodeRunner(std::string _server);
	~GameClientLodeRunner();

	void Run(std::function<void()> _message_handler);
	void LoderunnerAction(LoderunnerAction action = LoderunnerAction::DO_NOTHING) {
		switch (action)
		{
		case LoderunnerAction::DRILL_LEFT:
			send(std::string("ACT,LEFT"));
			break;
		case LoderunnerAction::DRILL_RIGHT:
			send(std::string("ACT,RIGHT"));
			break;
		case LoderunnerAction::GO_DOWN:
			send(std::string("DOWN"));
			break;
		case LoderunnerAction::GO_UP:
			send(std::string("UP"));
			break;
		case LoderunnerAction::GO_LEFT:
			send(std::string("LEFT"));
			break;
		case LoderunnerAction::GO_RIGHT:
			send(std::string("RIGHT"));
			break;
		case LoderunnerAction::SUICIDE:
			send(std::string("ACT(0)"));
			break;
		case LoderunnerAction::DRILL:
			send(std::string("ACT"));
			break;
		case LoderunnerAction::DO_NOTHING:
			break;
		default:
			send(std::string("STOP"));
			break;
		}
	}
	GameBoard* get_GameBoard() { return board; }
private:
	void send(std::string msg)
	{
		std::cout << "Sending: " << msg << std::endl;
		web_socket->send(msg);
	}
};
