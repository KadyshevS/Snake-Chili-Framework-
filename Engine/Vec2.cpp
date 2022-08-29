#include "Vec2.h"
#include <cmath>
#include <assert.h>

Vec2::Vec2(const int X, const int Y)
	:
	x(X),
	y(Y)
{
	assert(isInit == false);
	isInit = true;
}

void Vec2::Init(const int X, const int Y)
{
	assert(isInit == false);
	x = X;
	y = Y;
	isInit = true;
}

float Vec2::GetLengthSqr() noexcept
{
	return x * x + y * y;
}
float Vec2::GetLength() noexcept
{
	return std::sqrt(GetLengthSqr());
}

Vec2& Vec2::operator=(const Vec2& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}
bool Vec2::operator==(const Vec2& rhs)
{
	return (x == rhs.x && y == rhs.y);
}
Vec2 Vec2::operator+(const Vec2& rhs)
{
	return Vec2(x + rhs.x, y + rhs.y);
}
Vec2& Vec2::operator+=(const Vec2& rhs)
{
	return *this = *this + rhs;
}
Vec2 Vec2::operator-(const Vec2& rhs)
{
	return Vec2(x - rhs.x, y - rhs.y);
}
Vec2& Vec2::operator-=(const Vec2& rhs)
{
	return *this = *this - rhs;
}
Vec2 Vec2::operator*(float rhs)
{
	return Vec2(x*rhs, y*rhs);
}
Vec2& Vec2::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Vec2& Vec2::Normalize()
{
	return *this = GetNormalized();
}

Vec2& Vec2::GetNormalized()
{
	const float len = GetLength();
	if(len != 0)
		return *this * (1.0f / len);
	return *this;
}
