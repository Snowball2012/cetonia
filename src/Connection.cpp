#include "Connection.h"

#include <string>
#include <iostream>

Connection::Connection()
{
}

bool Connection::SendData( const void* data, size_t size )
{

	const char* str = reinterpret_cast<const char*>( data );

	for ( size_t i = 0; i < size; ++i )
		std::cout << *str++;

	std::cout << std::endl;

	return true;
}


Connection::~Connection()
{
}
