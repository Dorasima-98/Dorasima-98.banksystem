#pragma once

union
{
	unsigned char condition;
	struct
	{
		unsigned char fileopened : 1;
		unsigned char fileclosed : 1;
		unsigned char termination : 1;
		unsigned char b0 : 1;
		unsigned char b1 : 1;
		unsigned char b2 : 1;
		unsigned char b3 : 1;
		unsigned char b4 : 1;

	}bits;
}condition_t;
