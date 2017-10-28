#pragma once

#include <stdint.h>

struct ByteRange
{
	const void* data;
	size_t size;
	const uint8_t* begin() const { return reinterpret_cast<const uint8_t*>( data ); }
	const uint8_t* end() const { return reinterpret_cast<const uint8_t*>( data ) + size; }
};