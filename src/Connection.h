#pragma once

class Connection
{
public:
	Connection();

	virtual bool SendData( const void* data, size_t size );

	virtual ~Connection();
};

