/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx, boardLocation),
	rng(std::random_device()()),
	snek({2,2}),
	goal(rng, brd, snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::Restart()
{
	gameIsOver = false;
	snekMoveCounter = 0;
	snekMovePeriod = 20;
	frameCount = 0;
	snek.Reset();
	goal.Respawn(rng, brd, snek);
	delta_loc = { 1,0 };
}

void Game::UpdateModel()
{
	frameCount++;

	if (gameStarted)
	{
		if (!gameIsOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				delta_loc = { 0, -1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				delta_loc = { 0, 1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				delta_loc = { -1, 0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				delta_loc = { 1, 0 };
			}

			snekMoveCounter++;
			if (snekMoveCounter >= snekMovePeriod)
			{
				if (frameCount > 300 && snekMovePeriod > 6)
				{
					// increase the speed every 5 seconds until speed about 10 cells per second
					snekMovePeriod -= 2;;
					frameCount = 0;
				}
				snekMoveCounter = 0;
				const auto nextLoc = snek.GetNextHeadLocation(delta_loc);
				if (!brd.IsOnBoard(nextLoc) || snek.IsInNextBodyLocation(nextLoc))
				{
					gameIsOver = true;
				}
				else
				{
					bool isGoalHit = goal.IsHit(nextLoc);
					if (isGoalHit)
					{
						snek.Grow();
					}
					snek.MoveBy(delta_loc);
					if (isGoalHit)
					{
						goal.Respawn(rng, brd, snek);
					}
				}
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
		{
			Restart();
		}
	}
	else
	{
		gameStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
}

void Game::ComposeFrame()
{
	if (gameStarted)
	{
		brd.DrawBorder();
		snek.Draw(brd);
		goal.Draw(brd);
		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(360, 260, gfx);
		}
	}
	else
	{
		SpriteCodex::DrawTitle(320, 200, gfx);
	}
}
