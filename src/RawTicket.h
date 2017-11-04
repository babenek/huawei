#pragma once

#include <cstdint>

//! disable padding for all structures
#pragma pack(push, 1)

struct RawTicket: public TicketHeader
{
	uint8_t raw[TICKET_BODY_SIZE];
};

//------------------------------------------------------------------------------

void print( const RawTicket * ticket)
{

//	fprintf(stderr, "20%02d-%02d-%02d %02d:%02d:%02d", ticket->raw[3], ticket->raw[4], ticket->raw[5], ticket->raw[6], ticket->raw[7], ticket->raw[8]);

//	size_t n = 0;
//	while (n < TICKET_SIZE)
//	{
//		fprintf(stderr, " %02x", ticket->raw[n]);
//		++n;
//		if (0 == (n & 0xF))
//			fprintf(stderr, "\n");
//	}
}
