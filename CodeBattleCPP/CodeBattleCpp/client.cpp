#include "client.hpp"
#include "json.hpp"
#include <iostream>

using namespace std::chrono_literals;

client::client(std::string_view _server, std::string_view _userId, std::string_view _code)
{
	map_.clear();
	board = nullptr;

	path = "ws://";
	path += _server;
	path += "/codenjoy-contest/ws?user=";
	path += _userId;
	path += "&code=";
	path += _code;
	statistic_info = "ws://";
	statistic_info += _server;
	statistic_info += "/codenjoy-contest/screen-ws?user=";
	statistic_info += _userId;
	user_id = _userId;
	is_running = false;
}


client::~client()
{
	is_running = false;
	work_thread->join();
}

void client::run(std::function<void()> _message_handler)
{
	is_running = true;
	work_thread = new std::thread(&client::update_func, this, _message_handler);
}

void client::update_func(std::function<void()> _message_handler)
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
	nlohmann::json object;
	object["allPlayersScreen"] = false;
	object["gameName"] = "loderunner";
	object["name"] = "getScreen";
	object["players"][0] = user_id;
	auto web_socket1 = easywsclient::WebSocket::from_url(statistic_info);
	if (web_socket1)
		web_socket1->send(object.dump());
	while (is_running)
	{
		web_socket->poll();
		web_socket->dispatch([&](const std::string& message)
			{
				int size_needed = MultiByteToWideChar(CP_UTF8, 0, &message[0], (int)message.size(), NULL, 0);
				std::wstring wmessage(size_needed, 0);
				MultiByteToWideChar(CP_UTF8, 0, &message[0], (int)message.size(), &wmessage[0], size_needed);

				uint32_t size = sqrt(wmessage.size() - 6);
				if (map_.size() != size)
				{
					map_.clear();
					map_.resize(size);
					//map = new tile*[map_size];
					for (uint32_t j = 0; j < size; j++)
					{
						map_[j].resize(size);
						for (uint32_t i = 0; i < size; i++)
							map_[j][i] = tile(static_cast<tile::tile_id_>(tile::NONE));
					}
				}

				uint32_t chr = 6;
				for (uint32_t j = 0; j < map_.size(); j++)
					for (uint32_t i = 0; i < map_.size(); i++)
						map_[j][i] = tile(static_cast<tile::tile_id_>(wmessage[chr++]));
				lock();
				board = std::make_shared<game_board>(map_);
				unlock();
				_message_handler();
			});
		web_socket1->poll();
		web_socket1->dispatch([&](const std::string& message) {
			auto obj = nlohmann::json::parse(message, nullptr, false);
			if (!obj.is_discarded()) {
				std::cout << "score: " << obj[user_id]["score"].get<std::int32_t>() << "\n";
			}
			web_socket1->send(object.dump());
			});
		std::this_thread::sleep_for(1ms);
	}
	if (web_socket)web_socket->close();

#ifdef _WIN32
	WSACleanup();
#endif
}
