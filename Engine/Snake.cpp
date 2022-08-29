#include "Snake.h"
#include <assert.h>

/*************************/
/* Snake board			 */	
/*************************/
SnakeBoard::SnakeBoard(Graphics& Gfx)
{
	Init(Gfx);
}

void SnakeBoard::Init(Graphics& Gfx)
{
	assert(isInit == false);

	gfx = &Gfx;

	pos1 = Vec2(19, 19);
	pos2 = Vec2(gfx->ScreenWidth - 19, gfx->ScreenHeight - 19);

	for (int i = 0; i < tilesXcount; i++)
	{
		for (int j = 0; j < tilesYcount; j++)
		{
			tiles[i][j] = Vec2(30 + pos1.x*i, 25 + pos1.y*j);
			c_tiles[i][j] = Color_m(50, 50, 50);
		}
	}

	isInit = true;
}
void SnakeBoard::Draw()
{
	for (int i = pos1.y; i <= pos2.y; i++)
	{
		gfx->PutPixel(pos1.x, i, color.r, color.g, color.b);
	}
	for (int i = pos1.y; i <= pos2.y; i++)
	{
		gfx->PutPixel(pos2.x, i, color.r, color.g, color.b);
	}
	for (int i = pos1.x; i <= pos2.x; i++)
	{
		gfx->PutPixel(i, pos1.y, color.r, color.g, color.b);
	}
	for (int i = pos1.x; i <= pos2.x; i++)
	{
		gfx->PutPixel(i, pos2.y, color.r, color.g, color.b);
	}

	if (showGrid)
	{
		for (int _i = 0; _i < tilesXcount; _i++)
		{
			for (int _j = 0; _j < tilesYcount; _j++)
			{
				for(int i = tiles[_i][_j].x+1; i <= tiles[_i][_j].x + tileX; i++)
				{
					for (int j = tiles[_i][_j].y+1; j <= tiles[_i][_j].y + tileY; j++)
					{
						gfx->PutPixel(i, j, c_tiles[_i][_j].r, c_tiles[_i][_j].g, c_tiles[_i][_j].b);
					}
				}
			}
		}
	}
}
void SnakeBoard::ChgTileColor(const unsigned short TileX, const unsigned short TileY, const unsigned short R, const unsigned short G, const unsigned short B)
{
	assert(TileX < tilesXcount);
	assert(TileY < tilesYcount);

	c_tiles[TileX][TileY].r = R;
	c_tiles[TileX][TileY].g = G;
	c_tiles[TileX][TileY].b = B;
}
void SnakeBoard::ResetTileColor(const unsigned short TileX, const unsigned short TileY)
{
	c_tiles[TileX][TileY].r = 50;
	c_tiles[TileX][TileY].g = 50;
	c_tiles[TileX][TileY].b = 50;
}

/*************************/
/* Snake 				 */
/*************************/
Snake::Snake(Graphics& Gfx, const unsigned short startX, const unsigned short startY)
{
	Init(Gfx, startX, startY);
}

void Snake::Init(Graphics& Gfx, const unsigned short startX, const unsigned short startY)
{
	assert(startX >= 0);
	assert(startX <= board.tilesXcount);
	assert(startY >= 0);
	assert(startY <= board.tilesYcount);

	board.Init(Gfx);

	snek.push_back(Vec2(startX, startY));
	for (int i = 1; i < length; i++)
	{
		snek.push_back(Vec2(startX +i, startY));
	}

	isInit = true;
}

void Snake::Update(Keyboard& kbd, const float dt)
{
	if (kbd.KeyIsPressed(keyUp))
	{
		if (inhibitUp) {}
		else
		{
			if (dir != DOWN)
				dir = UP;
			inhibitUp = true;
		}
	}
	else
		inhibitUp = false;
	if (kbd.KeyIsPressed(keyDown))
	{
		if (inhibitDown) {}
		else
		{
			if (dir != UP)
				dir = DOWN;
			inhibitDown = true;
		}
	}
	else
		inhibitDown = false;
	if (kbd.KeyIsPressed(keyLeft))
	{
		if (inhibitLeft) {}
		else
		{
			if (dir != RIGHT)
				dir = LEFT;
			inhibitLeft = true;
		}
	}
	else
		inhibitLeft = false;
	if (kbd.KeyIsPressed(keyRight))
	{
		if (inhibitRight) {}
		else
		{
			if (dir != LEFT)
				dir = RIGHT;
			inhibitRight = true;
		}
	}
	else
		inhibitRight = false;

	switch (dir)
	{
	case UP:
		MoveUp(dt);
		break;
	case DOWN:
		MoveDown(dt);
		break;
	case LEFT:
		MoveLeft(dt);
		break;
	case RIGHT:
		MoveRight(dt);
		break;
	}
}
void Snake::Draw()
{
	board.Draw();
	for (int i = 0; i < board.tilesXcount; i++)
	{
		for (int j = 0; j < board.tilesYcount; j++)
		{
			if(isTileEmpty(i, j))
				board.ResetTileColor(i, j);
		}
	}
	board.ChgTileColor(snek[0].x, snek[0].y, colorSnake.r, colorSnake.g, colorSnake.b);
	for (int i = 1; i < length; i++)
	{
		board.ChgTileColor(snek[i].x, snek[i].y, colorTale.r, colorTale.g, colorTale.b);
	}
}

void Snake::MoveUp(const float dt)
{
	bool isInTale = false;
	for (int i = 0; i < length; i++)
	{
		if( snek[0].y - int(velocity*dt) != snek[i].y || snek[0].x != snek[i].x ) {}
		else
		{
			isInTale = true;
			break;
		}
	}
	if (snek[0].y - int(velocity*dt) >= 0 && !isInTale)
	{
		const std::vector<Vec2> temp = snek;
		snek[0].y -= int(velocity*dt);
		for (int i = 1; i < length; i++)
		{
			snek[i] = temp[i - 1];
		}
	}
}
void Snake::MoveDown(const float dt)
{
	bool isInTale = false;
	for (int i = 0; i < length; i++)
	{
		if (snek[0].y + int(velocity*dt) != snek[i].y || snek[0].x != snek[i].x) {}
		else
		{
			isInTale = true;
			break;
		}
	}
	if (snek[0].y + int(velocity*dt) < board.tilesYcount && !isInTale)
	{
		const std::vector<Vec2> temp = snek;
		snek[0].y += int(velocity*dt);
		for (int i = 1; i < length; i++)
		{
			snek[i] = temp[i - 1];
		}
	}
}
void Snake::MoveLeft(const float dt)
{
	bool isInTale = false;
	for (int i = 0; i < length; i++)
	{
		if (snek[0].y != snek[i].y || snek[0].x - int(velocity*dt) != snek[i].x) {}
		else
		{
			isInTale = true;
			break;
		}
	}
	if (snek[0].x - int(velocity*dt) >= 0 && !isInTale)
	{
		const std::vector<Vec2> temp = snek;
		snek[0].x -= int(velocity*dt);
		for (int i = 1; i < length; i++)
		{
			snek[i] = temp[i - 1];
		}
	}
}
void Snake::MoveRight(const float dt)
{
	bool isInTale = false;
	for (int i = 0; i < length; i++)
	{
		if (snek[0].y != snek[i].y || snek[0].x + int(velocity*dt) != snek[i].x) {}
		else
		{
			isInTale = true;
			break;
		}
	}
	if (snek[0].x + int(velocity*dt) < board.tilesXcount && !isInTale)
	{
		const std::vector<Vec2> temp = snek;
		snek[0].x += int(velocity*dt);
		for (int i = 1; i < length; i++)
		{
			snek[i] = temp[i - 1];
		}
	}
}

bool Snake::isTileEmpty(const short TileX, const short TileY)
{
	for (int i = 0; i < length; i++)
		if (snek[i].x == TileX && snek[i].y == TileY)
			return false;

	return true;
}
