// cetoniaut.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cetonia.h>

#include <iostream>

int main()
{
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

    return 0;
}

