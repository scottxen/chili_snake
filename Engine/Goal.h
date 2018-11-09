#pragma once

#include "Snake.h"
#include "Board.h"
#include <random>

class Goal
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Draw(Board& brd) const;
	inline const Location& GetLocation() { return loc; };
	inline bool IsHit(const Location& testLoc) const { return loc == testLoc; };
private:
	Location loc;
	static constexpr Color c = Colors::White;
};
