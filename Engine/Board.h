#pragma once

#include "Graphics.h"
#include "Location.h"
#include <assert.h>

class Board
{
public:
	Board(Graphics& gfx, Location screenLoc);
	void DrawCell(const Location& loc, Color c);
	void DrawBorder();
	inline int GetGridWidth() const { return width; };
	inline int GetGridHeight() const { return height; };
	bool IsOnBoard(const Location& loc) const;
private:
	static constexpr int borderWidth = 10;
	static constexpr int borderPadding = 2;
	static constexpr int cellPadding = 1;
	static constexpr int dimension = 20;
	static constexpr int width = 37;
	static constexpr int height = 27;
	static constexpr Color borderColour = Colors::Magenta;
	Graphics& gfx;
	Location brdLoc;
};