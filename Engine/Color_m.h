#pragma once

class Color_m
{
public:
	Color_m() = default;
	Color_m(unsigned short R, unsigned short G, unsigned short B);

	void Init(unsigned short R, unsigned short G, unsigned short B);

public:
	unsigned short r = 0;
	unsigned short g = 0;
	unsigned short b = 0;

private:
	bool isInit = false;
};