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

#include <stdint.h>

#include "../Opcode.h"
#include "../EnemyData.h"

namespace TestLevel
{
	const uint8_t level[][8] PROGMEM
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 1 },
	};

	const uint8_t script[] PROGMEM
	{
		static_cast<uint8_t>(Opcode::Forward),
		static_cast<uint8_t>(Opcode::JumpIfNotZero),
		static_cast<uint8_t>(static_cast<int8_t>(-2)),
		static_cast<uint8_t>(Opcode::TurnLeft),
		static_cast<uint8_t>(Opcode::End),
	};

	const EnemyData enemy PROGMEM
	{
		1, 1, Direction::South, &script[0]
	};
}