#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = nSegments  - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadLocation(const Location & delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Grow()
{
	if (nSegments < maxSegments)
	{
		segments[nSegments].InitBody(segColours[segColourIndex]);
		nSegments++;
		segColourIndex = (++segColourIndex) % nSegColours;
	}
}

void Snake::Draw(Board& brd) const
{
	for (int ix = 0; ix < nSegments; ix++)
	{
		segments[ix].Draw(brd);
	}
}

bool Snake::IsInNextBodyLocation(const Location& loc) const
{
	for (int sx = 0; sx < nSegments - 1; sx++)
	{
		if (segments[sx].GetLocation() == loc)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInSnake(const Location & loc) const
{
	for (int sx = 0; sx < nSegments; sx++)
	{
		if (segments[sx].GetLocation() == loc)
		{
			return true;
		}
	}
	return false;
}

void Snake::Reset()
{
	segColourIndex = 0;
	nSegments = 1;
	segments[0].InitHead({ 2,2 });
	
}

void Snake::Segment::InitHead(const Location& loc)
{
	this->loc = loc;
	c = Snake::headColour;
}

void Snake::Segment::InitBody(Color segColour)
{
	c = segColour;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}
