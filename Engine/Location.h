#pragma once

class Location
{
public:
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}
	bool operator==(const Location& rhsLoc) const
	{
		return x == rhsLoc.x && y == rhsLoc.y;
	}
	int x;
	int y;
};