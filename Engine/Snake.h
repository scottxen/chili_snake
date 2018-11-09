#pragma once

#include "Board.h";

class Snake 
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& loc);
		void InitBody(Color c);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		inline const Location& GetLocation() const { return loc; };
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& delta_loc) const;
	void Grow();
	void Draw(Board& brd) const;
	bool IsInNextBodyLocation(const Location& loc) const;
	bool IsInSnake(const Location& loc) const;
	void Reset();
private:
	static constexpr Color headColour = Colors::Yellow;
	static constexpr int maxSegments = 100;
	static constexpr int nSegColours = 5;
	static constexpr Color segColours[nSegColours]
	{ 
		{ 10, 100, 32 },
		{ 10, 130, 32 },
		{ 10, 160, 32 },
		{ 10, 140, 32 },
		{ 10, 180, 32 },
	};
	int segColourIndex = 0;
	Segment segments[maxSegments];
	int nSegments = 1;

};