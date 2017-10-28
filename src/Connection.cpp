#include "Connection.h"

#include <iostream>
#include <boost/range/algorithm.hpp>

#include "Utils.h"

Connection::Connection()
{
}

Connection::~Connection()
{
}

bool Connection::StartRecording( boost::optional<size_t> estimate_size )
{
	if ( m_recording )
		return true;

	constexpr size_t megabyte = 1024 * 1024;
	m_buffer.clear();
	if ( estimate_size )
		m_buffer.reserve( *estimate_size );
	else
		m_buffer.reserve( megabyte );

	m_recording = true;
	return true;
}

bool Connection::FinishRecording()
{
	if ( ! m_recording || m_buffer.empty() )
		return true;

	m_recording = false;
	
	if ( ! SendBundle( m_buffer.data(), m_buffer.size() * sizeof( decltype( m_buffer )::value_type ) ) )
		return false;

	m_buffer.clear();
	return true;
}

bool Connection::PushData( const void* data, size_t size )
{
	size_t new_size = m_buffer.size() + size;

	if ( new_size > GetMaxBufferSize() )
		return false;

	m_buffer.reserve( new_size );
	for ( auto byte : ByteRange{ data, size } )
		m_buffer.push_back( byte );

	return FlushIfNotRecording();
}

bool Connection::FlushIfNotRecording()
{
	if ( ! m_recording )
	{
		m_recording = true;
		return FinishRecording();
	}
	return true;
}
