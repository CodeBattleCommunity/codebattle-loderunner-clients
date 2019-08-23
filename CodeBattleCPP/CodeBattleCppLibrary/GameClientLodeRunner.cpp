#include "GameClientLodeRunner.h"
#include <iostream>


GameClientLodeRunner::GameClientLodeRunner(std::string _server, std::string _userId, std::string _code)
{
	map = nullptr;
	board = nullptr;
	map_size = 0;

	path = "ws://" + _server + "/codenjoy-contest/ws?user=" + _userId + "&code=" + _code;

	is_running = false;
}


GameClientLodeRunner::~GameClientLodeRunner()
{
	is_running = false;
	work_thread->join();
}

void GameClientLodeRunner::Run(std::function<void()> _message_handler)
{
	is_running = true;
	work_thread = new std::thread(&GameClientLodeRunner::update_func, this, _message_handler);
}

void GameClientLodeRunner::update_func(std::function<void()> _message_handler)
{
#ifdef _WIN32
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		throw new std::exception("WSAStartup Failed.\n");
	else
		std::cout << "Connection established" << std::endl;
#endif

	web_socket = easywsclient::WebSocket::from_url(path);
	if (web_socket == nullptr)is_running = false;
	while (is_running)
	{
		web_socket->poll();
		web_socket->dispatch([&](const std::string &message)
		{
			int size_needed = MultiByteToWideChar(CP_UTF8, 0, &message[0], (int)message.size(), NULL, 0);
			std::wstring wmessage(size_needed, 0);
			MultiByteToWideChar(CP_UTF8, 0, &message[0], (int)message.size(), &wmessage[0], size_needed);

			uint32_t size = sqrt(wmessage.size() - 6);
			if (map_size != size)
			{
				if (map_size != 0)
				{
					for (uint32_t j = 0; j < map_size; j++)
						delete[] map[j];
					delete[] map;
				}
				map_size = size;

				map = new BoardElement*[map_size];
				for (uint32_t j = 0; j < map_size; j++)
				{
					map[j] = new BoardElement[map_size];
					for (uint32_t i = 0; i < map_size; i++)
					{
						map[j][i] = BoardElement::NONE;
					}
				}
			}
			
			uint32_t chr = 6;
			for (uint32_t j = 0; j < map_size; j++)
			{
				for (uint32_t i = 0; i < map_size; i++)
				{
					map[j][i] = (BoardElement)wmessage[chr];
					chr++;
					
					if (map[j][i] == BoardElement::HERO_DIE ||
						map[j][i] == BoardElement::HERO_DRILL_LEFT ||
						map[j][i] == BoardElement::HERO_DRILL_RIGHT ||
						map[j][i] == BoardElement::HERO_LADDER ||
						map[j][i] == BoardElement::HERO_LEFT ||
						map[j][i] == BoardElement::HERO_RIGHT ||
						map[j][i] == BoardElement::HERO_FALL_LEFT ||
						map[j][i] == BoardElement::HERO_FALL_RIGHT ||
						map[j][i] == BoardElement::HERO_PIPE_LEFT ||
						map[j][i] == BoardElement::HERO_PIPE_RIGHT
						)
					{
						player_x = i;
						player_y = j;
					}
					
				}
			}
			board = new GameBoard(map, map_size);
			std::cout << board << '\n';
			_message_handler();
		});
	}
	if (web_socket)web_socket->close();

#ifdef _WIN32
	WSACleanup();
#endif
}
