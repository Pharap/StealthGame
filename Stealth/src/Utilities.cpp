#include "Utilities.h"

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

bool Utilities::moveForward(Entity & entity, const World & world)
{
	switch(entity.direction)
	{
		case Direction::North:
			return moveNorth(entity, world);
		case Direction::East:
			return moveEast(entity, world);
		case Direction::South:
			return moveSouth(entity, world);
		case Direction::West:
			return moveWest(entity, world);
		default:
			return false;
	}
}

bool Utilities::moveNorth(Entity & entity, const World & world)
{
	if(entity.y > 0)
	{
		const uint8_t y = (entity.y - 1);
		if(!world.isSolid(entity.x, y))
		{
			entity.y = y;
			return true;
		}
	}

	return false;
}

bool Utilities::moveEast(Entity & entity, const World & world)
{
	if(entity.x < (world.getWidth() - 1))
	{
		const uint8_t x = (entity.x + 1);
		if(!world.isSolid(x, entity.y))
		{
			entity.x = x;
			return true;
		}
	}
	
	return false;
}

bool Utilities::moveSouth(Entity & entity, const World & world)
{
	if(entity.y < (world.getHeight() - 1))
	{
		const uint8_t y = (entity.y + 1);
		if(!world.isSolid(entity.x, y))
		{
			entity.y = y;
			return true;
		}
	}

	return false;
}

bool Utilities::moveWest(Entity & entity, const World & world)
{
	if(entity.x > 0)
	{
		const uint8_t x = (entity.x - 1);
		if(!world.isSolid(x, entity.y))
		{
			entity.x = x;
			return true;
		}
	}

	return false;
}

bool Utilities::isFacingSolid(const Entity & entity, const World & world)
{
	switch(entity.direction)
	{
		case Direction::North:
			{
				if(entity.y == 0)
					return true;

				const uint8_t y = (entity.y - 1);
				return world.isSolid(entity.x, y);
			}
		case Direction::East:
			{
				if(entity.x == (world.getWidth() - 1))
					return true;

				const uint8_t x = (entity.x + 1);
				return world.isSolid(x, entity.y);
			}
		case Direction::South:
			{
				if(entity.y == (world.getHeight() - 1))
					return true;

				const uint8_t y = (entity.y - 1);
				return world.isSolid(entity.x, y);
			}
		case Direction::West:
			{
				if(entity.x == 0)
					return true;

				const uint8_t x = (entity.x - 1);
				return world.isSolid(x, entity.y);
			}
		default:
			return false;
	}
}