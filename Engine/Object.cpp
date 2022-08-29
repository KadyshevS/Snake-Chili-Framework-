#include "Object.h"

/******************************/
/* Object				      */
/******************************/
Object::Object(const int X, const int Y)
{
	pos.x = X;
	pos.y = Y;
}

/******************************/
/* Crosshair				  */
/******************************/
Crosshair::Crosshair() noexcept
{
	isInit = false;
}
Crosshair::Crosshair(
	Graphics& Gfx, 
	const int X, 
	const int Y) noexcept
{
	Init(Gfx, X, Y);
}

void Crosshair::Init(
	Graphics& Gfx, 
	const int X, 
	const int Y) noexcept
{
	gfx = &Gfx;
	distFromBorders = 5;

	pos.Init(X, Y);
	scale.Init(12, 12);
	FixCollision();

	keyUp = VK_UP;
	keyDown = VK_DOWN;
	keyLeft = VK_LEFT;
	keyRight = VK_RIGHT;

	color.Init(255, 0, 0);

	speed = 3 * 60.0f;
}

void Crosshair::MoveUp(const float dt) noexcept
{
	const int Speed = int(speed * dt);
	if (collisionLUp.y - Speed > distFromBorders)
	{
		pos.y -= Speed;
	}
	else
	{
		pos.y = distFromBorders;
	}
	FixCollision();
}
void Crosshair::MoveDown(const float dt) noexcept
{
	const int Speed = int(speed * dt);
	if (collisionRDown.y + Speed < gfx->ScreenHeight - distFromBorders)
	{
		pos.y += Speed;
	}
	else
	{
		pos.y = gfx->ScreenHeight - distFromBorders - scale.y;
	}
	
	FixCollision();
}
void Crosshair::MoveLeft(const float dt) noexcept
{
	const int Speed = int(speed * dt);
	const bool isOut = collisionLUp.x - Speed > distFromBorders;
	if (collisionLUp.x - Speed > distFromBorders)
	{
		pos.x -= Speed;
	}
	else
	{
		pos.x = distFromBorders;
	}
	FixCollision();
}
void Crosshair::MoveRight(const float dt) noexcept
{
	const int Speed = int(speed * dt);
	if (collisionRDown.x + int(speed * dt) < gfx->ScreenWidth - distFromBorders)
	{
		pos.x += int(speed * dt);
	}
	else
	{
		pos.x = gfx->ScreenWidth - distFromBorders - scale.x;
	}
	FixCollision();
}
void Crosshair::Sprint() noexcept
{
	speed = speed == 3 * 60.0f ? 10 * 60.0f : 3 * 60.0f;
}

void Crosshair::FixCollision() noexcept
{
	collisionLUp.x = pos.x;
	collisionLUp.y = pos.y;

	collisionLDown.x = pos.x;
	collisionLDown.y = pos.y + scale.y;

	collisionRUp.x = pos.x + scale.x;
	collisionRUp.y = pos.y;

	collisionRDown.x = pos.x + scale.x;
	collisionRDown.y = pos.y + scale.y;
}

void Crosshair::Draw() noexcept
{
	gfx->PutPixel(pos.x + 5, pos.y + 5, color.r, color.g, color.b);
	gfx->PutPixel(pos.x + 5, pos.y + 4, color.r, color.g, color.b);
	gfx->PutPixel(pos.x + 5, pos.y + 3, color.r, color.g, color.b);
	gfx->PutPixel(pos.x + 5, pos.y + 2, color.r, color.g, color.b);

	gfx->PutPixel(pos.x + 5, pos.y + 9 , color.r, color.g, color.b);
	gfx->PutPixel(pos.x + 5, pos.y + 10, color.r, color.g, color.b);
	gfx->PutPixel(pos.x + 5, pos.y + 11, color.r, color.g, color.b);
	gfx->PutPixel(pos.x + 5, pos.y + 12, color.r, color.g, color.b);

	gfx->PutPixel(pos.x + 0, pos.y + 7, color.r, color.g, color.b);
	gfx->PutPixel(pos.x + 1, pos.y + 7, color.r, color.g, color.b);
	gfx->PutPixel(pos.x + 2, pos.y + 7, color.r, color.g, color.b);
	gfx->PutPixel(pos.x + 3, pos.y + 7, color.r, color.g, color.b);
								   
	gfx->PutPixel(pos.x + 7, pos.y + 7, color.r, color.g, color.b);
	gfx->PutPixel(pos.x + 8, pos.y + 7, color.r, color.g, color.b);
	gfx->PutPixel(pos.x + 9, pos.y + 7, color.r, color.g, color.b);
	gfx->PutPixel(pos.x +10, pos.y + 7, color.r, color.g, color.b);
}
void Crosshair::Update(Keyboard& kbd, const float dt) noexcept
{
	if (kbd.KeyIsPressed(VK_SHIFT))
	{
		if(inhibitSprint) {}
		else
		{
			Sprint();
			inhibitSprint = true;
		}
	}
	else
		inhibitSprint = false;

	if (kbd.KeyIsPressed(keyUp))
	{
		MoveUp(dt);
	}
	if (kbd.KeyIsPressed(keyDown))
	{
		MoveDown(dt);
	}
	if (kbd.KeyIsPressed(keyLeft))
	{
		MoveLeft(dt);
	}
	if (kbd.KeyIsPressed(keyRight))
	{
		MoveRight(dt);
	}
}
void Crosshair::Update(Mouse& mouse, const float dt) noexcept
{
	if (mouse.LeftIsPressed())
	{
		Vec2 center = pos + Vec2(scale.x / 2.0f, scale.y / 2.0f);
		Vec2 toPoint = Vec2(float(mouse.GetPosX()), float(mouse.GetPosY())) - center;
		pos += toPoint.GetNormalized() * speed * dt;
	}
}
