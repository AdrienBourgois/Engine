#include "Color.h"

Core::CoreType::Color::Color(float _r, float _g, float _b, float _a): r(_r), g(_g), b(_b), a(_a)
{}

Core::CoreType::Color::Color(int _r, int _g, int _b, int _a)
{
	r = (1.f / 256.f) * _r;
	g = (1.f / 256.f) * _g;
	b = (1.f / 256.f) * _b;
	a = (1.f / 256.f) * _a;
}

Core::CoreType::Color Core::CoreType::Color::White = Color(1.f, 1.f, 1.f, 1.f);
Core::CoreType::Color Core::CoreType::Color::Black = Color(0.f, 0.f, 0.f, 1.f);
Core::CoreType::Color Core::CoreType::Color::Red   = Color(1.f, 0.f, 0.f, 1.f);
Core::CoreType::Color Core::CoreType::Color::Green = Color(0.f, 1.f, 0.f, 1.f);
Core::CoreType::Color Core::CoreType::Color::Blue  = Color(0.f, 0.f, 1.f, 1.f);