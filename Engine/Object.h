#pragma once
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Vec2.h"
#include "Color_m.h"

class Object
{
protected:
	Vec2 pos;

public:
	Object() = default;
	Object(const int X, const int Y);
};

class Crosshair : public Object
{
protected:
	Graphics* gfx;

	Color_m color;
	Vec2 scale;

	Vec2
		collisionLUp,
		collisionLDown,
		collisionRUp,
		collisionRDown;

	unsigned int
		keyUp,
		keyDown,
		keyLeft,
		keyRight;

	unsigned int speed;
	unsigned int distFromBorders;
	bool inhibitSprint = false;

	bool isInit;

public:
	Crosshair() noexcept;
	Crosshair(
		Graphics& Gfx, 
		const int X = 400, 
		const int Y = 300) noexcept;

	void Init(Graphics& Gfx, 
		const int X = 400, 
		const int Y = 300) noexcept;

	virtual void MoveUp(const float dt) noexcept;
	virtual void MoveDown(const float dt) noexcept;
	virtual void MoveLeft(const float dt) noexcept;
	virtual void MoveRight(const float dt) noexcept;
	void Sprint() noexcept;

	virtual void FixCollision() noexcept;

	virtual void Draw() noexcept;
	virtual void Update(Keyboard& kbd, const float dt) noexcept;
	virtual void Update(Mouse& mouse, const float dt) noexcept;
};