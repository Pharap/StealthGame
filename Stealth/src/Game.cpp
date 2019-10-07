#include "Game.h"

//
// Copyright (C) 2019 Pharap (@Pharap)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "EnemyAI.h"
#include "WorldRenderer.h"
#include "Utilities.h"

void Game::update()
{
	if(arduboy.everyXFrames(15))
		EnemyAI::update(this->enemy, this->world);

	if(this->arduboy.justPressed(UP_BUTTON))
	{
		this->player.direction = Direction::North;
		Utilities::moveForward(this->player, this->world);
	}

	if(this->arduboy.justPressed(DOWN_BUTTON))
	{
		this->player.direction = Direction::South;
		Utilities::moveForward(this->player, this->world);
	}

	if(this->arduboy.justPressed(LEFT_BUTTON))
	{
		this->player.direction = Direction::West;
		Utilities::moveForward(this->player, this->world);
	}

	if(this->arduboy.justPressed(RIGHT_BUTTON))
	{
		this->player.direction = Direction::East;
		Utilities::moveForward(this->player, this->world);
	}
}

constexpr uint8_t tileWidth = 8;
constexpr uint8_t tileHeight = 8;

void drawEntity(Arduboy2 & arduboy, const Entity & entity)
{
	const int16_t drawY = (entity.y * tileHeight);
	const int16_t drawX = (entity.x * tileWidth);

	arduboy.fillRect(drawX + 1, drawY + 1, tileWidth - 2, tileHeight - 2);
}

void drawSightLine(Arduboy2 & arduboy, const Entity & entity)
{
	const int16_t top = (entity.y * tileHeight);
	const int16_t left = (entity.x * tileWidth);
	const int16_t bottom = (top + tileHeight);
	const int16_t right = (left + tileWidth);

	switch(entity.direction)
	{
		case Direction::North:
			{
				const uint8_t y = (top - tileHeight);
				const uint8_t startX = (left - tileWidth);
				const uint8_t endX = (right + tileWidth);

				arduboy.drawLine(left + 1, top + 1, startX, y);
				arduboy.drawLine(right - 1, top + 1, endX, y);
				arduboy.drawFastHLine(startX, y, tileWidth * 3);
			}
			break;
		case Direction::East:
			{
				const uint8_t x = (right + tileWidth);
				const uint8_t startY = (top - tileHeight);
				const uint8_t endY = (bottom + tileHeight);

				arduboy.drawLine(right - 1, top + 1, x, startY);
				arduboy.drawLine(right - 1, bottom - 1, x, endY);
				arduboy.drawFastVLine(x, startY, tileHeight * 3);
			}
			break;
		case Direction::South:
			{
				const uint8_t y = (bottom + tileHeight);
				const uint8_t startX = (left - tileWidth);
				const uint8_t endX = (right + tileWidth);

				arduboy.drawLine(left + 1, bottom - 1, startX, y);
				arduboy.drawLine(right - 1, bottom - 1, endX, y);
				arduboy.drawFastHLine(startX, y, tileWidth * 3);
			}
			break;
		case Direction::West:
			{
				const uint8_t x = (left - tileWidth);
				const uint8_t startY = (top - tileHeight);
				const uint8_t endY = (bottom + tileHeight);

				arduboy.drawLine(left + 1, top + 1, x, startY);
				arduboy.drawLine(left + 1, bottom - 1, x, endY);
				arduboy.drawFastVLine(x, startY, tileHeight * 3);
			}
			break;
	}
}

void drawEnemy(Arduboy2 & arduboy, const Entity & entity)
{
	drawSightLine(arduboy, entity);
	drawEntity(arduboy, entity);
}

void Game::render()
{
	WorldRenderer::render(this->arduboy, this->world);
	drawEnemy(this->arduboy, this->enemy);
	drawEntity(this->arduboy, this->player);
}