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
	CT_GeneralError = 1
};

inline char ctSucceeded( ctError err )
{
	return err == CT_OK;
}

inline char ctFailed( ctError err )
{
	return ! ctSucceeded( err );
}

// hello, world! =)
CETONIA_API void ctHelloWorld();

// default connection, uses shared memory buffer
CETONIA_API ctError ctCreateConnection( ctConnectionHandle* connection );

// closes connection. invalidates handle
CETONIA_API ctError ctCloseConnection( ctConnectionHandle connection );

// sends arbitrary data through connection (synchronously)
// data size should be less or equal than the size of the connection buffer
CETONIA_API ctError ctSendData( ctConnectionHandle connection, const void* data, size_t size );

// starts to record all commands for connection. Flush all commands with ctFlush
// estimate size can be 0
CETONIA_API ctError ctBeginRecording( ctConnectionHandle connection, size_t estimate_size );
// flushes all commands. does nothing if command buffer is empty
CETONIA_API ctError ctFlush( ctConnectionHandle connection );
