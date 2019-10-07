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
#include <avr/pgmspace.h>

struct ScriptReader
{
	const uint8_t * script;
	uint8_t index;

	ScriptReader() = default;

	constexpr ScriptReader(const uint8_t * script) :
		script{script}, index{0}
	{
	}

	bool hasScript() const
	{
		return this->script != nullptr;
	}

	uint8_t readByte() const
	{
		return pgm_read_byte(&this->script[this->index]);
	}

	void resetIndex()
	{
		this->index = 0;
	}

	void advanceIndex()
	{
		++this->index;
	}

	void offsetIndex(int8_t offset)
	{
		this->index = (this->index + offset);
	}
};