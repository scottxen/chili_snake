#include "Board.h"

Board::Board(Graphics & gfx, Location screenLoc) : gfx(gfx), brdLoc(screenLoc)
{
}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int ofs = borderPadding + borderWidth + cellPadding;

	gfx.DrawRectDim(
		loc.x * dimension + brdLoc.x + ofs,
		loc.y * dimension + brdLoc.y + ofs,
		dimension - cellPadding * 2,
		dimension - cellPadding * 2,
		c);
}

void Board::DrawBorder()
{
	int bw = width * dimension + borderPadding * 2;
	int bh = height * dimension + borderPadding * 2;
	gfx.DrawRectDim(brdLoc.x, brdLoc.y, 2 * borderWidth + bw, borderWidth, borderColour);
	gfx.DrawRectDim(brdLoc.x, brdLoc.y + borderWidth, borderWidth, bh, borderColour);
	gfx.DrawRectDim(brdLoc.x, brdLoc.y + borderWidth + bh, 2 * borderWidth + bw, borderWidth, borderColour);
	gfx.DrawRectDim(brdLoc.x + borderWidth + bw, brdLoc.y + borderWidth, borderWidth, bh, borderColour);
}

bool Board::IsOnBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width 
		&& loc.y >= 0 && loc.y < height;
}
