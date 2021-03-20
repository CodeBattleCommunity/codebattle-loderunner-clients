#include "GameClientLodeRunner.h"
#include "easywsclient/easywsclient.hpp"

#include <iostream>
#include <algorithm>

#ifdef _WIN32
#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#endif

#include "utf8tools.h"

GameClientLodeRunner::GameClientLodeRunner(const std::string &_server) : path(_server)

{
	path = path.replace(path.find("http"), sizeof("http") - 1, "ws");
	path = path.replace(path.find("board/player/"), sizeof("board/player/") - 1, "ws?user=");
	path = path.replace(path.find("?code="), sizeof("?code=") - 1, "&code=");
}

GameClientLodeRunner::~GameClientLodeRunner()
{
	web_socket->close();
#ifdef _WIN32
	WSACleanup();
#endif
}

void GameClientLodeRunner::Run(std::function<LodeRunnerAction(const GameBoard &)> _message_handler)
{
#ifdef _WIN32
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		throw std::exception("WSAStartup Failed.\n");
	else
		std::cout << "Connection established" << std::endl;
#endif

	web_socket.reset(easywsclient::WebSocket::from_url(path));
	while (1)
	{
		web_socket->poll(60 * 1000); //1 minute
		web_socket->dispatch([&](const std::string &message) {
			GameBoard board(message.begin() + 6, message.end());
			const auto result = _message_handler(board);
			std::cout << "Sending: " << std::to_string(result) << '\n';
			web_socket->send(std::to_string(result));
		});
	}
}
