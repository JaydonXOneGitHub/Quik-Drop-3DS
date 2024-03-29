#pragma once

#include <iostream>
#include "vector2.h"

template<typename T>
void Print(const T& value)
{
    std::cout << value << std::endl;
}

#define FRGB(x) x / 255

// CONCOOR = Console Coordinate
std::string CONCOOR(int x, int y) 
{
    return "\x1b["+(char)x+';'+(char)y+'H';
}

std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
{
	stream << '[' << vec.x << ',' << vec.y << ']';
	return stream;
}