// cetoniaut.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cetonia/client.h>
#include <cetonia/parser.h>

#include <iostream>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

int main( int argc, char** argv )
{
	if ( argc == 1 )
	{
		ctConnectionHandle connection;
		if ( ctFailed( ctCreateConnection( &connection ) ) )
		{
			std::cerr << "connection failed";
			return 1;
		}

		std::string message( "Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn" );

		if ( ctFailed( ctSendArbitrary( connection, message.c_str(), message.size() ) ) )
		{
			std::cerr << "send failed";
			return 2;
		}


		std::cout << argv[0];
		system( ( std::string( argv[0] ) + " child" ).c_str() );

		if ( ctFailed( ctCloseConnection( connection ) ) )
		{
			std::cerr << "connection destruction failed";
		}
	}
	else
	{
		struct remover
		{
			~remover()
			{
				shared_memory_object::remove( "cetonia" );
			}
		} onremove;
		shared_memory_object shm( open_only, "cetonia", read_only );

		mapped_region region( shm, read_only );
		if ( region.get_size() == 0 )
		{
			std::cerr << "empty region";
			return 4;
		}

		system ( "pause" );

		size_t msg_size = *reinterpret_cast<const size_t*>( region.get_address() );

		const char* msg = reinterpret_cast<const char*>( region.get_address() ) + sizeof( size_t );

		std::cout << "client, recieved msg:\n";
		size_t stride = 0;
		while ( stride < msg_size )
		{
			size_t token_shift;
			ctToken token;
			if ( ctFailed( ctParseToken( msg + stride, msg_size - stride, &token, &token_shift ) ) || ! ctIsTokenValid( token.type ) )
			{
				std::cerr << "failed to read token";
				return 6;
			}
			stride += token_shift;

			switch ( token.type )
			{
			case CT_Arbitrary:
			{
				std::cout << "arb, size = " << token.data.arbitrary.size << " data: ";
				for ( size_t i = 0; i < token.data.arbitrary.size; ++i )
					std::cout << *((const char*)token.data.arbitrary.data + i);
				std::cout << std::endl;
				break;
			}
			default:
				std::cerr << "Token notimpl";
				return 10;
			}
		}
		
		std::cout.flush();
	}
    return 0;
}

