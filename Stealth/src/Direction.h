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

enum class Direction : uint8_t
{
	North,
	East,
	South,
	West,
};

constexpr Direction turnClockwise(Direction direction)
{
	return static_cast<Direction>((static_cast<uint8_t>(direction) + 1) & 0x03);
}

constexpr Direction turnAntiClockwise(Direction direction)
{
	return static_cast<Direction>((static_cast<uint8_t>(direction) - 1) & 0x03);
}

constexpr Direction invert(Direction direction)
{
	return static_cast<Direction>(static_cast<uint8_t>(direction) ^ 0x02);
}