#include <cetonia.h>

#include <iostream>

#include "Connection.h"

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
	auto connection = new Connection();

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

	return connection->SendData( data, size ) ? CT_OK : CT_GeneralError;
}