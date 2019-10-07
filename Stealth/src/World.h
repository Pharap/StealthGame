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
#include <stddef.h>
#include <avr/pgmspace.h>

class World
{
private:
	const uint8_t * data;
	size_t width;
	size_t height;

	size_t getIndex(uint8_t x, uint8_t y) const
	{
		return ((y * this->width) + x);
	}

public:
	World() = default;

	template<size_t width, size_t height>
	constexpr World(const uint8_t (&world)[height][width]) :
		data{&world[0][0]}, width{width}, height{height}
	{
	}

	size_t getWidth() const
	{
		return this->width;
	}

	size_t getHeight() const
	{
		return this->height;
	}

	bool isSolid(uint8_t x, uint8_t y) const
	{
		return (this->getValue(x, y) != 0);
	}

	uint8_t getValue(uint8_t x, uint8_t y) const
	{
		return pgm_read_byte(&data[this->getIndex(x, y)]);
	}
};