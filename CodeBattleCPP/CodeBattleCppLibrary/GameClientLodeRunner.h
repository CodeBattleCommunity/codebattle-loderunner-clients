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

#include "LodeRunnerBlocks.h"
#include "PlayerAction.h"

class GameClientLodeRunner
{
	LodeRunnerBlocks **map;
	uint32_t map_size, player_x, player_y;

	easywsclient::WebSocket *web_socket;
	std::string path;

	bool is_running;
	std::thread *work_thread;
	void update_func(std::function<void()> _message_handler);

public:
	GameClientLodeRunner(std::string _server, std::string _userEmail, std::string _userPassword = "");
	~GameClientLodeRunner();

	void Run(std::function<void()> _message_handler);
	
	void Up(PlayerAction _action = PlayerAction::None)
	{
		send(std::string(_action == PlayerAction::ACT ? "ACT," : "") + "UP");
	}
	void Down(PlayerAction _action = PlayerAction::None)
	{
		send(std::string(_action == PlayerAction::ACT ? "ACT," : "") + "DOWN");
	}
	void Right(PlayerAction _action = PlayerAction::None)
	{
		send(std::string(_action == PlayerAction::ACT ? "ACT," : "") + "RIGHT");
	}
	void Left(PlayerAction _action = PlayerAction::None)
	{
		send(std::string(_action == PlayerAction::ACT ? "ACT," : "") + "LEFT");
	}
	void Act() { send("ACT"); }
	

	 

	void Blank() { send(""); }

	LodeRunnerBlocks **get_map() { return map; }
	uint32_t get_map_size() { return map_size; }
	uint32_t get_player_x() { return player_x; }
	uint32_t get_player_y() { return player_y; }

private:
	void send(std::string msg)
	{
		std::cout << "Sending: " << msg << std::endl;
		web_socket->send(msg);
	}
};
