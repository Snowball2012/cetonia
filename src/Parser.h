#pragma once

#include <vector>

#include <cetonia/parser.h>

// Parses ctTokens and serializes tokens

namespace Parser
{

	template<ctTokenType type>
	bool ParseToken( const void* data, size_t max_size, ctTokenData& token, size_t& stride )
	{
		_ASSERT_EXPR( false, "not implemented for this type" );
		return false;
	}
}