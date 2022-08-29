#include "Color_m.h"
#include <assert.h>

Color_m::Color_m(unsigned short R, unsigned short G, unsigned short B)
{
	Init(R, G, B);
}

void Color_m::Init(unsigned short R, unsigned short G, unsigned short B)
{
	assert(isInit == false);
	r = R;
	g = G;
	b = B;
	isInit = true;
}
