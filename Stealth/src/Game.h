#pragma once

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

#include <Arduboy2.h>

#include "Levels.h"
#include "World.h"
#include "Direction.h"
#include "Enemy.h"
#include "Player.h"

class Game
{
private:
	Arduboy2 arduboy;
	Player player { 1, 1, Direction::North } ;
	World world { TestLevel::level };
	Enemy enemy;

public:
	void setup()
	{
		this->arduboy.begin();
		enemy.x = pgm_read_byte(&TestLevel::enemy.x);
		enemy.y = pgm_read_byte(&TestLevel::enemy.y);
		enemy.direction = static_cast<Direction>(pgm_read_byte(&TestLevel::enemy.direction));
		enemy.aiState = static_cast<const uint8_t *>(pgm_read_ptr(&TestLevel::enemy.script));
	}

	void loop()
	{
		if(!this->arduboy.nextFrame())
			return;

		this->arduboy.pollButtons();

		this->update();

		this->arduboy.clear();

		this->render();

		this->arduboy.display();
	}

private:
	void update();
	void render();
};