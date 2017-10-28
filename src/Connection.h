#pragma once

#include <boost/optional.hpp>
#include <vector>

class Connection
{
public:
	Connection();

	bool StartRecording( boost::optional<size_t> estimate_size );
	bool FinishRecording();
	bool PushData( const void* data, size_t size );

	virtual ~Connection();

private:
	virtual bool SendBundle( const void* data, size_t size ) = 0;
	virtual size_t GetMaxBufferSize() const = 0;

	bool FlushIfNotRecording();

	bool m_recording;
	std::vector<uint8_t> m_buffer;
};

