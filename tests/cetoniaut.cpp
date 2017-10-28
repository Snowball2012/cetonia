// cetoniaut.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cetonia/client.h>

#include <iostream>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

int main( int argc, char** argv )
{
	if ( argc == 1 )
	{
		// parent
		ctHelloWorld();

		ctConnectionHandle connection;
		if ( ctFailed( ctCreateConnection( &connection ) ) )
		{
			std::cerr << "connection failed";
			return 1;
		}

		std::string message( "Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn" );

		if ( ctFailed( ctSendData( connection, message.c_str(), message.size() ) ) )
		{
			std::cerr << "send failed";
			return 2;
		}


		if ( ctFailed( ctCloseConnection( connection ) ) )
		{
			std::cerr << "connection destruction failed";
		}

		std::cout << "\nRound2\n";

		ctCreateConnection( &connection );
		ctBeginRecording( connection, 300 );

		message = "msg1";
		ctSendData( connection, message.c_str(), message.size() );

		std::cout << "parent msg" << std::endl;

		message = "msg2";
		ctSendData( connection, message.c_str(), message.size() );
		ctFlush( connection );

		std::cout << argv[0];
		system( ( std::string( argv[0] ) + " child" ).c_str() );


		ctCloseConnection( connection );
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
		size_t msg_size = *reinterpret_cast<const size_t*>( region.get_address() );

		const char* msg = reinterpret_cast<const char*>( region.get_address() ) + sizeof( size_t );
		
		std::cout << "client, recieved msg:\n";
		for ( size_t i = 0; i < msg_size; ++i )
			std::cout << *msg++;
		std::cout.flush();
	}
    return 0;
}

