#pragma once

class Vec2
{
public:
	Vec2() noexcept = default;
	Vec2(const int X, const int Y);

	void Init(const int X, const int Y);

	float GetLengthSqr() noexcept;
	float GetLength() noexcept;

	Vec2& operator = (const Vec2& rhs);
	bool operator == (const Vec2& rhs);
	Vec2 operator + (const Vec2& rhs);
	Vec2& operator += (const Vec2& rhs);
	Vec2 operator - (const Vec2& rhs);
	Vec2& operator -= (const Vec2& rhs);
	Vec2 operator * (float rhs);
	Vec2& operator *= (float rhs);

	Vec2& Normalize();
	Vec2& GetNormalized();

public:
	int x;
	int y;

	bool isInit = false;
};