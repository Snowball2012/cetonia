#include <cetonia/client.h>
#include <cetonia/parser.h>

#include <iostream>

#include "Connection.h"
#include "SMConnection.h"

#include "Parser.h"

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

ctError ctSendArbitrary( ctConnectionHandle handle, const void* data, size_t size )
{
	std::vector<uint64_t> adata;

	adata.resize( ( size + 23 ) / 8, 0 );
	adata[0] = CT_Arbitrary;
	adata[1] = size;
	uint8_t* p = reinterpret_cast<uint8_t*>( adata.data() + 2 );
	for ( uint8_t byte : ByteRange{ data, size } )
		*p++ = byte;

	return ctSendData( handle, adata.data(), size + 16 );
}

// parser
ctError ctParseToken( const void* buf, size_t buf_size, ctToken* token, size_t* shift_to_next )
{
	if ( ! ( token && shift_to_next ) )
		return CT_InvalidArgument;

	return Parser::ParseToken( buf, buf_size, *token, *shift_to_next ) ? CT_OK : CT_GeneralError;
}