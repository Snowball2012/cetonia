#pragma once

#ifdef __cplusplus
	#define C_ABI extern "C"
#else
	#define C_ABI
#endif // __cplusplus

#ifdef CETONIA_API_EXPORT
	#define CETONIA_API C_ABI __declspec(dllexport)
#else
	#define CETONIA_API C_ABI __declspec(dllimport)
#endif // CETONIA_API_EXPORT

#include <stdint.h>

typedef struct ctConnection ctConnection;
typedef ctConnection* ctConnectionHandle;

enum ctError
{
	CT_OK = 0,
	CT_GeneralError
};

inline char ctSucceeded( ctError err )
{
	return err == CT_OK;
}

// hello, world! =)
CETONIA_API void ctHelloWorld();

// default connection, uses shared memory buffer
CETONIA_API ctError ctCreateConnection( ctConnectionHandle* connection );

// closes connection. invalidates handle
CETONIA_API ctError ctCloseConnection( ctConnectionHandle connection );

// sends arbitrary data through connection (synchronously)
// data size should be less or equal than the size of the connection buffer
CETONIA_API ctError ctSendData( ctConnectionHandle connection, void* data, size_t size );