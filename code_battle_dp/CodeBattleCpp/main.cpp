#include <iostream>
#include <random>

#include "client.hpp"
#include "graphics.hpp"
#include "window.hpp"

std::shared_ptr<client> gcb;
std::unique_ptr<graphics> gfx;
/*
 After completing registration you will be redirected to gamefield
 Example url: http://localhost:8888/codenjoy-contest/board/player/cg601yim3186cotnftue?code=307643814057246189&gameName=loderunner
 @url: localhost:8888
 @user_id: cg601yim3186cotnftue
 @user_code: 8887669793631271133
*/
void run_client(std::string_view url, std::string_view user_id, std::string_view user_code) {
	gcb = std::make_shared<client>(url, user_id, user_code);
	gcb->run([&]() {
		auto gb = gcb->get_game_board();
		gcb->send(interpolation::instance()->next_action());
		});
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	app_window->initialize(hInstance, window::flags_console);
	run_client("35.228.224.190:8080", "qjbbjpt7eduoiguuz5w4", "9042115526546430278");
	gfx = std::make_unique<graphics>(app_window->get_window_handle());

	while (app_window->tick())
		gfx->render_scene(gcb);

	return 0;
}
