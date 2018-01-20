#pragma once

#include <vector>

#include <cetonia/parser.h>

#include "Utils.h"

// ctTokens parsing and serialization
namespace Parser
{

	// data pointer should be aligned to 64bit border
	template<ctTokenType type>
	bool ParseToken( const void* data, size_t max_size, ctTokenData& token, size_t& stride )
	{
		_ASSERT_EXPR( false, "not implemented for this type" );
		return false;
	}

	template<>
	bool ParseToken<CT_Arbitrary>( const void* data, size_t max_size, ctTokenData& token, size_t& data_stride )
	{
		if ( ! VERIFY( IsAlignedTo( data, 8 ) ) )
			return false;
		if ( ! VERIFY( max_size >= sizeof( uint64_t ) ) )
			return false;

		auto data_64_ptr = reinterpret_cast<const uint64_t*>( data );

		token.arbitrary.size = *data_64_ptr;
		data_stride = token.arbitrary.size + sizeof( uint64_t );

		if ( ! VERIFY( max_size >= data_stride ) )
			return false;

		token.arbitrary.data = data_64_ptr + 1;

		return true;
	}

	template<>
	bool ParseToken<CT_Line2d>( const void* data, size_t max_size, ctTokenData& token, size_t& data_stride )
	{
		if ( ! VERIFY( IsAlignedTo( data, 8 ) ) )
			return false;

		constexpr size_t data_size = sizeof( token.l2d );
		if ( ! VERIFY( max_size >= data_size ) )
			return false;

		auto data_64_ptr = reinterpret_cast<const ctTokenLine2d*>( data );

		token.l2d = *data_64_ptr;
		data_stride = data_size;

		return true;
	}

	inline bool ParseToken( const void* data, size_t max_size, ctToken& token, size_t& token_stride )
	{
		if ( ! VERIFY( max_size >= 8 ) )
			return false;
		if ( ! VERIFY( IsAlignedTo( data, 8 ) ) )
			return false;

		auto data_64_ptr = reinterpret_cast<const uint64_t*>( data );

		token.type = ctTokenType( *data_64_ptr );
		if ( ! VERIFY( ctIsTokenValid( token.type ) ) )
			return false;

		data_64_ptr++;
		token_stride = 8;
		max_size -= 8;
		size_t data_stride = 0;
		switch ( token.type )
		{
			case CT_Arbitrary:
			{
				if ( ! ParseToken<CT_Arbitrary>( data_64_ptr, max_size, token.data, data_stride ) )
					return false;
				break;
			}
			case CT_Line2d:
			{
				if ( ! ParseToken<CT_Line2d>( data_64_ptr, max_size, token.data, data_stride ) )
					return false;
				break;
			}
			default:
				_ASSERT_EXPR( false, "not implemented" );
				return false;
		}

		token_stride = GetClosestAlignedTo( token_stride + data_stride, 8 );

		return true;
	}
}