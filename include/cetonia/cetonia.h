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
