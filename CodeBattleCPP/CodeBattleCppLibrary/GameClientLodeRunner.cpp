#include "GameClientLodeRunner.h"
#include <iostream>
#include <cmath>
#include <algorithm>

#include "utf8tools.h"

GameClientLodeRunner::GameClientLodeRunner(std::string _server)
{
	path = _server.replace(_server.find("http"), sizeof("http")-1, "ws");
	path = path.replace(path.find("board/player/"),sizeof("board/player/")-1,"ws?user=");
	path = path.replace(path.find("?code="),sizeof("?code=")-1,"&code=");

	is_running = false;
}

GameClientLodeRunner::~GameClientLodeRunner()
{
	is_running = false;
	if(work_thread.joinable())
		work_thread.join();
}

void GameClientLodeRunner::Run(std::function<void()> _message_handler)
{
	is_running = true;
	work_thread = std::move(std::thread(&GameClientLodeRunner::update_func, this, _message_handler));
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
			board = std::move(GameBoard(message.begin()+6, message.end()));
			_message_handler();
		});
	}
	if (web_socket)web_socket->close();

#ifdef _WIN32
	WSACleanup();
#endif
}
