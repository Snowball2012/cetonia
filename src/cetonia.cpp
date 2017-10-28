#include <cetonia.h>

#include <iostream>

#include "Connection.h"
#include "SMConnection.h"

void ctHelloWorld()
{
	std::cout << "hello, world!" << std::endl;
}

namespace
{
	constexpr Connection* Handle2Interface( ctConnectionHandle handle )
	{
		return reinterpret_cast<Connection*>( handle );
	}
}

ctError ctCreateConnection( ctConnectionHandle* handle )
{
	auto connection = new SMConnection( "cetonia" );

	*handle = reinterpret_cast<ctConnectionHandle>( connection );

	return CT_OK;
}

ctError ctCloseConnection( ctConnectionHandle handle )
{
	auto connection = Handle2Interface( handle );

	delete connection;

	return CT_OK;
}

ctError ctSendData( ctConnectionHandle handle, const void* data, size_t size )
{
	auto connection = Handle2Interface( handle );

	return connection->PushData( data, size ) ? CT_OK : CT_GeneralError;
}

ctError ctBeginRecording( ctConnectionHandle handle, size_t estimate_size )
{
	auto connection = Handle2Interface( handle );

	const bool res = connection->StartRecording( estimate_size == 0 ? boost::optional<size_t>(estimate_size) : boost::none );
	
	return res ? CT_OK : CT_GeneralError;
}

ctError ctFlush( ctConnectionHandle handle )
{
	return Handle2Interface( handle )->FinishRecording() ? CT_OK : CT_GeneralError;
}
