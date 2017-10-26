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

CETONIA_API void hello_world();