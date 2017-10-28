#include "SMConnection.h"

#include <iostream>
#include <limits>

SMConnection::SMConnection( const char* segment_name )
	: m_segment_name( segment_name )
{
}

SMConnection::~SMConnection()
{
}

bool SMConnection::SendBundle( const void * data, size_t size )
{
	const char* str = reinterpret_cast<const char*>( data );

	for ( size_t i = 0; i < size; ++i )
		std::cout << *str++;

	std::cout << std::endl;

	return true;
}

size_t SMConnection::GetMaxBufferSize() const
{
	return std::numeric_limits<size_t>::max();
}
