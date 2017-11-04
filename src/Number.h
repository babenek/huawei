#pragma once

#include <cstdint>

//------------------------------------------------------------------------------

void printNumber(const uint8_t number[], const size_t count)
{
	size_t tmp = 0;
	for (size_t n = 0; n < count; ++n)
	{
		uint8_t a = (0xF0 & number[n]) >> 4;
		uint8_t b = (0x0F & number[n]);
		if (a < 10)
			tmp++;
		if (b < 10)
			tmp++;
	}
	if (0 != tmp)
	{
		printf("\"");
		for (size_t n = 0; n < count; ++n)
		{
			uint8_t a = (0xF0 & number[n]) >> 4;
			uint8_t b = (0x0F & number[n]);
			if (a < 10)
				printf("%d", a);
			if (b < 10)
				printf("%d", b);
		}
		printf("\"");
	}
	else
	{
		printf("null");
	}
}

//------------------------------------------------------------------------------

void printNumberCopy(const uint8_t number[], const size_t count)
{
	size_t tmp = 0;
	for (size_t n = 0; n < count; ++n)
	{
		uint8_t a = (0xF0 & number[n]) >> 4;
		uint8_t b = (0x0F & number[n]);
		if (a < 10)
			tmp++;
		if (b < 10)
			tmp++;
	}
	if (0 != tmp)
	{
		for (size_t n = 0; n < count; ++n)
		{
			uint8_t a = (0xF0 & number[n]) >> 4;
			uint8_t b = (0x0F & number[n]);
			if (a < 10)
				printf("%d", a);
			if (b < 10)
				printf("%d", b);
		}
	}
	else
	{
		printf("\\N");
	}
}

//------------------------------------------------------------------------------
