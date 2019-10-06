#pragma once

#include <string>
#include <thread>
#include "easywsclient\easywsclient.hpp"
#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif
#include <Windows.h>
#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string_view>
#include <functional>
#include <memory>
#include <mutex>

#include "tile.hpp"
#include "player_command.hpp"
#include "game_board.hpp"


class tile;

class client
{
	std::vector<std::vector<tile>> map_;
	std::shared_ptr<game_board> board;

	easywsclient::WebSocket* web_socket;
	std::string path, statistic_info, user_id;

	bool is_running;
	std::thread* work_thread;
	void update_func(std::function<void()> _message_handler);

public:
	client(std::string_view _server, std::string_view _userEmail, std::string_view _userPassword = "");
	~client();

	void run(std::function<void()> _message_handler);
	void send(player_command action = player_command::idle) {
		switch (action)
		{
		case player_command::dig_left:
			send(std::string("ACT,LEFT"));
			break;
		case player_command::dig_right:
			send(std::string("ACT,RIGHT"));
			break;
		case player_command::down:
			send(std::string("DOWN"));
			break;
		case player_command::up:
			send(std::string("UP"));
			break;
		case player_command::left:
			send(std::string("LEFT"));
			break;
		case player_command::right:
			send(std::string("RIGHT"));
			break;
		case player_command::kill_self:
			send(std::string("ACT(0)"));
			break;
		case player_command::dig:
			send(std::string("ACT"));
			break;
		default:
			send(std::string("STOP"));
			break;
		}
	}
	std::shared_ptr<game_board> get_game_board() { return board; }
	const std::vector<std::vector<tile>>& get_map() { return map_; }
	void lock() { board_lock.lock(); }
	void unlock() { board_lock.unlock(); }
	bool try_lock() { return board_lock.try_lock(); }
private:
	std::mutex board_lock;
	void send(std::string msg)
	{
		std::cout << "Sending: " << msg << std::endl;
		web_socket->send(msg);
	}
};
