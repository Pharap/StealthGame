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

#include <avr/pgmspace.h>

#include "Enemy.h"
#include "Utilities.h"

class EnemyAI
{
public:
	static void update(Enemy & enemy, const World & world)
	{
		auto & scriptReader = enemy.aiState.scriptReader;

		// If the enemy doesn't have a script, do nothing
		if(!scriptReader.hasScript())
			return;

		const auto opcode = static_cast<Opcode>(scriptReader.readByte());

		const auto instructionOffset = execute(opcode, enemy, world);

		scriptReader.offsetIndex(instructionOffset);
	}

private:
	static int8_t execute(Opcode opcode, Enemy & enemy, const World & world)
	{
		auto & variable = enemy.aiState.variable;
		auto & scriptReader = enemy.aiState.scriptReader;

		switch(opcode)
		{
			case Opcode::Nop:
				{
					return 1;
				}
			case Opcode::End:
				{
					scriptReader.resetIndex();
					return 0;
				}
			case Opcode::Forward:
				{
					variable = Utilities::moveForward(enemy, world) ? 1 : 0;
					return 1;
				}
			case Opcode::ForwardCountEarly:
				{
					if(Utilities::moveForward(enemy, world))
					{
						--variable;
						if(variable > 0)
							return 0;
					}
					return 1;
				}
			case Opcode::ForwardCountGreedy:
				{
					Utilities::moveForward(enemy, world);
					--variable;
					return (variable > 0) ? 0 : 1;
				}
			case Opcode::TurnLeft:
				{
					enemy.direction = turnAntiClockwise(enemy.direction);
					return 1;
				}
			case Opcode::TurnRight:
				{
					enemy.direction = turnClockwise(enemy.direction);
					return 1;
				}
			case Opcode::AboutFace:
				{
					enemy.direction = invert(enemy.direction);
					return 1;
				}
			case Opcode::JumpIfZero:
				{
					scriptReader.advanceIndex();
					int8_t offset = scriptReader.readByte();
					return (variable == 0) ? offset : 1;
				}
			case Opcode::JumpIfNotZero:
				{
					scriptReader.advanceIndex();
					int8_t offset = scriptReader.readByte();
					return (variable != 0) ? offset : 1;
				}
			case Opcode::SetVariable:
				{
					scriptReader.advanceIndex();
					variable = scriptReader.readByte();
					return 1;
				}
			case Opcode::Countdown:
				{
					return (variable > 0) ? 0 : 1;
				}
			case Opcode::IsSolidWall:
				{
					variable = Utilities::isFacingSolid(enemy, world) ? ~0 : 0;
					return 1;
				}
			default:
				return 1;
		}
	}
};