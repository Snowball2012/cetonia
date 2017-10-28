#pragma once

#include "cetonia.h"

typedef struct ctConnection ctConnection;
typedef ctConnection* ctConnectionHandle;

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
