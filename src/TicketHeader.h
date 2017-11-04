#pragma once

#include <cstdint>

//! disable padding for all structures
#pragma pack(push, 1)

struct TicketHeader
{
	//! Serial Number	4	Number for the tickets being generated since the switch has been started.
	uint32_t serial;

	//! Ticket Type	1	"Call type of this ticket record
	uint8_t type;
	/*
	 0x01: OVSR003 Detailed ticket
	 0x02: DBO call record
	 0x03: IN record
	 0x05: TAX record
	 0x11: OVSR103 Detailed ticket
	 0xF0: Meter table ticket
	 0xF1: Meter table statistics
	 0xF2: Trunk duration statistics
	 0xF3: Free call statistics
	 0xF4: SCCP meter table ticket
	 0xFF: Warn ticket
	 0x55: Failed call ticket (Incomplete call watch ticket, Partial record ticket)
	 //! Note: 0x11 means that the ticket be explained as detailed ticket"
	 */
};


const size_t TICKET_SIZE = 154;
const size_t TICKET_BODY_SIZE = TICKET_SIZE - sizeof(TicketHeader);
