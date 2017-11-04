#pragma once

#include <stdint.h>

#ifdef _DEBUG
#define VERIFY( expr ) ( (!!(expr)) || ( _ASSERT_EXPR( false, #expr ), false ) )
#else
#define VERIFY( expr ) (!!(expr))
#endif

template<typename T>
constexpr bool IsAlignedTo( T* ptr, uint32_t alignment )
{
	return uint64_t( ptr ) % alignment == 0;
}

template<class T>
T GetClosestAlignedTo( T ptr_or_offset, uint32_t alignment )
{
	uint64_t res = uint64_t( ptr_or_offset );

	if ( uint32_t bytes_off_alignment = res % alignment )
		res += alignment - bytes_off_alignment;

	return (T) res;
}

template<class T>
constexpr uint64_t GetByteDiff( T* lhs, T* rhs )
{
	return uint64_t( rhs ) - uint64_t( lhs );
}

template<class T>
const T& ReadFromPtr( const void* ptr )
{
	return *reinterpret_cast<const T*>( ptr );
}


struct ByteRange
{
	const void* data;
	size_t size;
	const uint8_t* begin() const { return reinterpret_cast<const uint8_t*>( data ); }
	const uint8_t* end() const { return reinterpret_cast<const uint8_t*>( data ) + size; }
};