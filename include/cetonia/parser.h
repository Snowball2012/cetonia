#pragma once

#include "cetonia.h"

// If you want to add new token types, please add them right before CT_MAX_TOKEN
enum ctTokenType
{
	CT_MinToken = 0,
	CT_Arbitrary = 1,
	CT_Point2d = 2,
	CT_Line2d = 3,
	CT_MaxToken = 4
};

inline char ctIsTokenValid( ctTokenType token_type )
{
	return token_type > CT_MinToken && token_type < CT_MaxToken;
}

// Here and below all pointers point to source buffer. Don't forget to change pointers if you invalidate the buffer
typedef struct ctTokenArbitrary
{
	void* data;
	size_t size;
} ctTokenArbitrary;

typedef struct ctTokenPoint2d
{
	ctVector2d p;
	ctColor color;
	double size;
} ctTokenPoint2d;

typedef struct ctTokenLine2d
{
	ctVector2d p1, p2;
	ctColor color;
	double thickness;
} ctTokenLine2d;

union ctTokenData
{
	ctTokenArbitrary arbitrary;
	ctTokenPoint2d v2d;
};

typedef struct ctToken
{
	ctTokenType type;
	union
	{
		ctTokenArbitrary arb;
		ctTokenPoint2d pt2;
		ctTokenLine2d line2;
	};
} ctToken;

// Parses next token
// After this you'll need to shift buffer pointer by shift_to_next bytes to get the next token
CETONIA_API ctError ctParseToken( const void* buf, size_t buf_size, ctToken* token, size_t* shift_to_next );