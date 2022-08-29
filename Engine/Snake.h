#pragma once
#include "Graphics.h"
#include "Keyboard.h"
#include "Vec2.h"
#include "Color_m.h"
#include <vector>

class SnakeBoard
{
public:
	SnakeBoard() = default;
	SnakeBoard(Graphics& Gfx);

	void Init(Graphics& Gfx);
	void Draw();

	void ChgTileColor(
		const unsigned short TileX,
		const unsigned short TileY,
		const unsigned short R,
		const unsigned short G,
		const unsigned short B);

	void ResetTileColor(
		const unsigned short TileX,
		const unsigned short TileY);

public:
	const Color_m color = Color_m(0, 0, 255);
	bool showGrid = true;

private:
	Graphics* gfx;

	Vec2 pos1;
	Vec2 pos2;

	static constexpr unsigned short tileX = 18;
	static constexpr unsigned short tileY = 18;
	static const unsigned int tilesXcount = 39;
	static const unsigned int tilesYcount = 29;

	Vec2 tiles[tilesXcount][tilesYcount];
	Color_m c_tiles[tilesXcount][tilesYcount];

	bool isInit = false;

	friend class Snake;
};

enum SnakeDirection
{
	STOP, UP, DOWN, LEFT, RIGHT
};
class Snake
{
public:
	Snake() = default;
	Snake(
		Graphics& Gfx,
		const unsigned short startX, 
		const unsigned short startY);

public:
	void Init(
		Graphics& Gfx,
		const unsigned short startX,
		const unsigned short startY);

	void Update(Keyboard& kbd, const float dt);
	void Draw();

private:
	void MoveUp(const float dt);
	void MoveDown(const float dt);
	void MoveLeft(const float dt);
	void MoveRight(const float dt);

private:
	SnakeBoard board;
	SnakeDirection dir = STOP;
	Color_m colorSnake = Color_m(0, 255, 0);
	Color_m colorTale = Color_m(255, 255, 0);
	unsigned int length = 10;

#ifndef NDEBUG
	float velocity = 0.295 * 60.0f;
#else
	float velocity = 0.295 * 60.0f;
#endif

	std::vector<Vec2> snek;

	unsigned int
		keyUp    = VK_UP    ,
		keyDown  = VK_DOWN  ,
		keyLeft  = VK_LEFT  ,
		keyRight = VK_RIGHT ;

	bool inhibitUp = false;
	bool inhibitDown = false;
	bool inhibitLeft = false;
	bool inhibitRight = false;

	bool isInit = false;

private:
	bool isTileEmpty(const short TileX, const short TileY);
};
