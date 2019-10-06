#include "client.hpp"
#include "graphics.hpp"


using namespace std::chrono_literals;

static constexpr std::array<std::pair<std::wstring_view, tile::tile_id_>, 45> texture_paths_ = {
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/brick.png",tile::BRICK},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/drill_pit.png",tile::DRILL_PIT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/enemy_ladder.png",tile::ENEMY_LADDER},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/enemy_left.png",tile::ENEMY_LEFT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/enemy_pipe_left.png",tile::ENEMY_PIPE_LEFT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/enemy_pipe_right.png",tile::ENEMY_PIPE_RIGHT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/enemy_pit.png",tile::ENEMY_PIT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/enemy_right.png",tile::ENEMY_RIGHT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/gold.png",tile::YELLOW_GOLD},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/gold.png",tile::RED_GOLD},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/gold.png",tile::GREEN_GOLD},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/hero_die.png",tile::HERO_DIE},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/hero_drill_left.png",tile::HERO_DRILL_LEFT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/hero_drill_right.png",tile::HERO_DRILL_RIGHT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/hero_fall_left.png",tile::HERO_FALL_LEFT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/hero_fall_right.png",tile::HERO_FALL_RIGHT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/hero_ladder.png",tile::HERO_LADDER},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/hero_left.png",tile::HERO_LEFT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/hero_pipe_left.png",tile::HERO_PIPE_LEFT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/hero_pipe_right.png",tile::HERO_PIPE_RIGHT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/hero_right.png",tile::HERO_RIGHT},
	std::pair<std::wstring_view, tile::tile_id_>{L"resources/hero_shadow_drill_left.png",tile::HERO_SHADOW_DRILL_LEFT},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/hero_shadow_drill_right.png",tile::HERO_SHADOW_DRILL_RIGHT},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/hero_shadow_fall_left.png",tile::HERO_SHADOW_FALL_LEFT},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/hero_shadow_fall_right.png",tile::HERO_SHADOW_FALL_RIGHT},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/hero_shadow_ladder.png",tile::HERO_SHADOW_LADDER},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/hero_shadow_left.png",tile::HERO_SHADOW_LEFT},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/hero_shadow_right.png",tile::HERO_SHADOW_RIGHT},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/hero_shadow_pipe_left.png",tile::HERO_SHADOW_PIPE_LEFT},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/hero_shadow_pipe_right.png",tile::HERO_SHADOW_PIPE_RIGHT},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/ladder.png",tile::LADDER},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/none.png",tile::NONE},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/other_hero_die.png",tile::OTHER_HERO_DIE},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/other_hero_ladder.png",tile::OTHER_HERO_LADDER},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/other_hero_left.png",tile::OTHER_HERO_LEFT},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/other_hero_pipe_left.png",tile::OTHER_HERO_PIPE_LEFT},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/other_hero_pipe_right.png",tile::OTHER_HERO_PIPE_RIGHT},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/other_hero_right.png",tile::OTHER_HERO_RIGHT},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/pipe.png",tile::PIPE},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/pit_fill_1.png",tile::PIT_FILL_1},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/pit_fill_2.png",tile::PIT_FILL_2},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/pit_fill_3.png",tile::PIT_FILL_3},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/pit_fill_4.png",tile::PIT_FILL_4},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/the_shadow_pill.png",tile::THE_SHADOW_PILL},
	std::pair<std::wstring_view, tile::tile_id_>{ L"resources/undestroyable_wall.png",tile::UNDESTROYABLE_WALL},
};


void graphics::invalidate() {
	D3DXCreateSprite(device_, &sprite_);
	for (auto& elem : texture_paths_)
		D3DXCreateTextureFromFile(device_, elem.first.data(), &textures_[elem.second]);

}

graphics::graphics(HWND hwnd) {
	if ((pd3d = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr) {
		std::cout << "pD3D == nullptr\n";
		return;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferCount = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;


	if (pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device_) < 0) {
		pd3d->Release();
		pd3d = nullptr;
		std::cout << "device is dead :c";
		return;
	}
	invalidate();
}

void graphics::render_scene(std::shared_ptr<client>& gcb) {
	device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);
	auto hresult = device_->TestCooperativeLevel();
	if (hresult == D3DERR_DEVICELOST || hresult == D3DERR_DEVICENOTRESET) {
		device_->Reset(&d3dpp);
		sprite_->Release();
		sprite_ = nullptr;
		for (auto& tex : textures_)
		{
			if(tex.second)
				tex.second->Release();
			tex.second = nullptr;
		}

		if (!FAILED(device_->Reset(&d3dpp)))
			invalidate();

		else return;
	}
	auto result = device_->BeginScene();
	if (SUCCEEDED(result)) {
		std::vector t(gcb->get_map());
		struct {
			float x, y;
		} pos{ 0,0 };
		std::vector<vec> t_path;
		if (gcb->try_lock()) {
			if (gcb->get_game_board().get())
				t_path = gcb->get_game_board()->get_current_path();
			gcb->unlock();
		}
		for (auto& line : t) {
			for (auto& row : line) {
				auto texture = textures_[row.get_id()];
				D3DXMATRIX world;
				D3DXMATRIX scale;
				D3DXMATRIX translation;
				D3DXMatrixIdentity(&world);
				D3DSURFACE_DESC img_info;
				texture->GetLevelDesc(0, &img_info);
				float scl_x = float(img_info.Width) / 16.f;
				float scl_y = float(img_info.Height) / 16.f;
				D3DXMatrixScaling(&scale, scl_x, scl_y, 1.f);
				D3DXMatrixTranslation(&translation, 0.f, 0.f, 0.f);
				world = scale * translation;
				auto vec = D3DXVECTOR3(pos.x, pos.y, 0.f);
				sprite_->Begin(D3DXSPRITE_ALPHABLEND);
				auto color = D3DCOLOR_RGBA(255, 255, 255, 255);
				if (row == tile::RED_GOLD)
					color = D3DCOLOR_RGBA(255, 0, 0, 255);
				if (row == tile::GREEN_GOLD)
					color = D3DCOLOR_RGBA(255, 0, 0, 255);
				sprite_->Draw(texture, nullptr, nullptr, &vec, color);
				sprite_->End();
				pos.x += 16;
			}
			pos.x = 0;
			pos.y += 16;
		}
		if (t_path.size()) {
			auto prev = t_path.front();
			prev.y = prev.y * 16 + 8;
			prev.x = prev.x * 16 + 8;
			for (auto point : t_path) {
				point.y = point.y * 16 + 8;
				point.x = point.x * 16 + 8;
				draw_line(vec(prev.x - 1, prev.y - 1), vec(point.x - 1, point.y - 1), D3DCOLOR_ARGB(255, 0, 240, 0));
				draw_line(prev, point, D3DCOLOR_ARGB(255, 0, 240, 0));
				draw_line(vec(prev.x + 1, prev.y + 1), vec(point.x + 1, point.y + 1), D3DCOLOR_ARGB(255, 0, 240, 0));
				prev = point;
			}
		}
		device_->EndScene();
	}
	result = device_->Present(NULL, NULL, NULL, NULL);
	if (!SUCCEEDED(result)) MessageBox(0, 0, 0, 0);
	std::this_thread::sleep_for(1ms);
}

void graphics::draw_line(vec p1, vec p2, uint32_t col) {

	vertex vert[2] =
	{
		{ p1.x, p1.y, 0.0f, 1.0f, col },
		{ p2.x, p2.y, 0.0f, 1.0f, col }
	};

	device_->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	device_->DrawPrimitiveUP(D3DPT_LINELIST, 1, &vert, sizeof(vertex));

}

graphics::~graphics() {
	device_->Release();
	sprite_->Release();
	sprite_ = nullptr;
	for (auto& tex : textures_)
	{
		if (tex.second)
			tex.second->Release();
		tex.second = nullptr;
	}
}