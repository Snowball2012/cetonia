#pragma once

#include "Connection.h"

class SMConnection:
	public Connection
{
public:
	SMConnection( const char* segment_name );
	~SMConnection();

private:

	// Connection
	virtual bool SendBundle( const void * data, size_t size ) override;
	virtual size_t GetMaxBufferSize() const override;

	std::string m_segment_name;
};

