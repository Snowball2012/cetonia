#include "SMConnection.h"

#include <iostream>
#include <limits>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

SMConnection::SMConnection( const char* segment_name )
	: m_segment_name( segment_name )
{
}

SMConnection::~SMConnection()
{
	shared_memory_object::remove( m_segment_name.c_str() );
}

bool SMConnection::SendBundle( const void* data, size_t size )
{
	shared_memory_object shm( open_or_create, m_segment_name.c_str(), read_write );
	shm.truncate( size + sizeof(size) );

	mapped_region region( shm, read_write, 0, size + sizeof(size) );
	size_t* region_ptr = reinterpret_cast<size_t*>( region.get_address() );

	*region_ptr = size;
	memcpy( region_ptr + 1, data, size );

	return true;
}

size_t SMConnection::GetMaxBufferSize() const
{
	return std::numeric_limits<size_t>::max();
}
