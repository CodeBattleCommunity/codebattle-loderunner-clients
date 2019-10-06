#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include <chrono>
#include <thread>
#include <memory>
#include <array>
#include <map>


#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d9.lib")

class client;

class graphics {
	struct vertex {
		float x, y, z, rhw;
		uint32_t color;
	};
	LPDIRECT3D9 pd3d;
	D3DPRESENT_PARAMETERS d3dpp;
	LPDIRECT3DDEVICE9 device_;
	LPD3DXSPRITE sprite_;
	//std::thread worker_;
	std::map<tile::tile_id_, LPDIRECT3DTEXTURE9> textures_;
public:
	graphics(HWND hwnd);
	~graphics();
	void invalidate();
	void render_scene(std::shared_ptr<client>& client);
	void draw_line(vec p1, vec p2, uint32_t color);
};