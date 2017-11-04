#pragma once

#include <cstdint>

#include "Number.h"

//! disable padding for all structures
#pragma pack(push, 1)

struct DetailedTicket: public TicketHeader
{
	//! Checksum	1
	uint8_t checksum;

	/**
	 Partial Record Indicator	0.25
	 Clock Changed Flag	0.125
	 Free Flag	0.125
	 Validity	0.125
	 Call Attempt Flag	0.125
	 Complaint Flag	0.125
	 Centralized Charging Flag	0.125
	 */
	uint8_t flags1;

	/**
	 PPS Flag	0.125
	 Charging Method	0.25
	 NP Call Flag	0.125
	 Payer	0.5
	 */
	uint8_t flags2;

	/**
	 Conversation End Time	6
	 Conversation end date and time (Format: YYMMDDHHMMSS)
	 YY: 0-99 (binary)
	 MM: 1-12 (binary)
	 DD: 1-31 (binary)
	 HH: 0-23 (binary)
	 MM: 0-59 (binary)
	 SS: 0-59 (binary)
	 */
	uint8_t YY;
	uint8_t MM;
	uint8_t DD;
	uint8_t HH;
	uint8_t MI;
	uint8_t SS;

	//! Conversation Duration	4
	uint32_t duration;

	//! Caller Seizure Duration	4
	uint32_t callerSeizureDuration;

	//! Called Seizure Duration	4
	uint32_t calledSeizureDuration;

	/**
	 Incomplete Call Watch	0.25
	 Caller ISDN Access	0.125
	 Called ISDN Access	0.125
	 ISUP Indication	0.125
	 Reserved	0.375
	 */
	uint8_t flag3;

	/**
	 Charging Number Address Nature	0.5
	 Caller Number Address Nature	0.5
	 */
	uint8_t chargingNature;

	/**
	 Connected Number Address Nature	0.5
	 Called Number Address nature	0.5
	 */
	uint8_t connectedNature;

	//! Charging Number DNSet	1
	uint8_t chargingNumberSet;

	//! Charging Number	10
	uint8_t chargingNumber[10];

	//! Caller Number DNSet	1
	uint8_t callerNumberSet;

	//! Caller Number	10
	uint8_t callerNumber[10];

	//! Connected Number DNSet	1
	uint8_t connectedNumberSet;

	//! Connected Number	10
	uint8_t connectedNumber[10];

	//! Called Number DNSet	1
	uint8_t calledNumberSet;

	//! Called Number	10
	uint8_t calledNumber[10];

	//! Dialed Number	12
	uint8_t dialedNumber[12];

	//! CENTREX Group Number	2
	uint16_t groupNumber;

	//! Caller CENTREX Short Number	4
	uint32_t callerShortNumber;

	//! Called CENTREX Short Number	4
	uint32_t calledShortNumber;

	//! Caller Module Number	1
	uint8_t callerModuleNumber;

	//! Called Module Number	1
	uint8_t calledModuleNumber;

	//! Incoming Trunk Group Number	2
	uint16_t incomingTrunkGN;

	//! Outgoing Trunk Group Number	2
	uint16_t outgoingTrunkGN;

	//! Incoming Subroute Number	2
	uint16_t incomingSubrouteNumber;

	//! Outgoing Subroute Number	2
	uint16_t outgoingSubrouteNumber;

	//! Caller Device Type	1
	uint8_t callerDeviceType;

	//! Called Device Type	1
	uint8_t calledDeviceType;

	//! Caller Port Number	2
	uint16_t callerPortNumber;

	//! Called Port Number	2
	uint16_t calledPortNumber;

	//! Caller Category	1
	uint8_t callerCategory;

	//! Called Category	1
	uint8_t calledCategory;

	//! Call Type	0.5
	//! Service Type	0.5
	uint8_t callServiceTypes;

	//! Supplementary Service Type	1
	uint8_t supplementaryServiceType;

	//! Charging Case	2
	uint16_t chargingCase;

	//! Tariff	2
	uint16_t tariff;

	//! Charging Pulse	4
	uint32_t chargingPulse;

	//! Fee	4
	uint32_t fee;

	//! Balance	4
	uint8_t balance;

	//! Bearer Service	1
	uint8_t bearerService;

	//! Teleservice	0.5
	//! Release Party	0.375
	//! Release Index	1.125
	uint16_t teleservice;

	//! Release Cause Value	1
	uint8_t releaseCause;

	//! UUS1 Count	1
	uint8_t UUS1;

	//! UUS2 Count	1
	uint8_t UUS2;

	//! UUS3 Count	1
	uint8_t UUS3;

	//! OPC	4
	uint32_t OPC;

	//! DPC	4
	uint32_t DPC;

	//! B_num	0.625
	//! Reserved3	0.375
	uint8_t bNum;

};

//------------------------------------------------------------------------------

void print_json( const DetailedTicket * ticket)
{
	// header
	printf("{\"serial\":%u", ticket->serial);
	printf(",\"type\":%u" , ticket->type);

	// detailed
	printf(",\"checksum\":%u" , ticket->checksum);

	// uint8_t flags1;
	printf(",\"partial_record_indicator\":%u", (ticket->flags1) & 0x3);
	printf(",\"clock_changed_flag\":%u", (ticket->flags1>>2) & 0x1);
	printf(",\"free_flag\":%u", (ticket->flags1>>3) & 0x1);
	printf(",\"validity\":%u", (ticket->flags1>>4) & 0x1);
	printf(",\"call_attempt_flag\":%u", (ticket->flags1>>5) & 0x1);
	printf(",\"compliant_flag\":%u", (ticket->flags1>>6) & 0x1);
	printf(",\"centralized_charging_flag\":%u", (ticket->flags1>>7) & 0x1);



	//uint8_t flags2;
	printf(",\"pps\":%u", (ticket->flags2)&0x1);
	printf(",\"charging_method\":%u", (ticket->flags2>>1)&0x3);
	printf(",\"npc\":%u", (ticket->flags2>>3)&0x1);
	printf(",\"payer\":%u", (ticket->flags2>>4)&0xF);




	//2016-06-01T12:59:53.941+0200
	printf(",\"end_time\":\"20%02d-%02d-%02dT%02d:%02d:%02d\"", ticket->YY, ticket->MM, ticket->DD, ticket->HH, ticket->MI, ticket->SS);

	printf(",\"duration\":%u", ticket->duration);

	printf(",\"caller_seizure_duration\":%u", ticket->callerSeizureDuration);

	printf(",\"called_seizure_duration\":%u", ticket->calledSeizureDuration);


	printf(",\"incomplete_call_watch\":%u", (ticket->flag3>>0)&0x3);
	printf(",\"caller_isdn\":%u", (ticket->flag3>>2)&0x1);
	printf(",\"called_isdn\":%u", (ticket->flag3>>3)&0x1);
	printf(",\"isup\":%u", (ticket->flag3>>4)&0x1);
	printf(",\"flag3_reserved\":%u", (ticket->flag3>>5)&0x7);

	printf(",\"charging_nature\":%u", (ticket->chargingNature)&0xF);
	printf(",\"caller_nature\":%u", (ticket->chargingNature>>4)&0xF);

	printf(",\"connected_nature\":%u", (ticket->connectedNature)&0xF);
	printf(",\"called_nature\":%u", (ticket->connectedNature>>4)&0xF);

	printf(",\"charging_number_set\":%u", ticket->chargingNumberSet);

	printf(",\"charging_number\":");
	printNumber(ticket->chargingNumber, 10);

	printf(",\"caller_number_set\":%u", ticket->callerNumberSet);

	printf(",\"caller_number\":");
	printNumber(ticket->callerNumber, 10);

	printf(",\"connected_number_set\":%u", ticket->connectedNumberSet);

	printf(",\"connected_number\":");
	printNumber(ticket->connectedNumber, 10);

	printf(",\"called_number_set\":%u", ticket->calledNumberSet);

	printf(",\"called_number\":");
	printNumber(ticket->calledNumber, 10);

	printf(",\"dialed_number\":");
	printNumber(ticket->dialedNumber, 12);


	printf(",\"group_number\":%u", ticket->groupNumber);

	printf(",\"caller_short_number\":%u", ticket->callerShortNumber);

	printf(",\"called_short_number\":%u", ticket->calledShortNumber);

	printf(",\"caller_module_number\":%u", ticket->callerModuleNumber);

	printf(",\"called_module_number\":%u", ticket->calledModuleNumber);

	printf(",\"incoming_trunk_gn\":%u", ticket->incomingTrunkGN);

	printf(",\"outgoing_trunk_gn\":%u", ticket->outgoingTrunkGN);

	printf(",\"incoming_subroute_number\":%u", ticket->incomingSubrouteNumber);

	printf(",\"outgoing_subroute_number\":%u", ticket->outgoingSubrouteNumber);

	printf(",\"caller_device_type\":%u", ticket->callerDeviceType);

	printf(",\"called_device_type\":%u", ticket->calledDeviceType);

	printf(",\"caller_port_number\":%u", ticket->callerPortNumber);

	printf(",\"called_port_number\":%u", ticket->calledPortNumber);

	printf(",\"caller_category\":%u", ticket->callerCategory);

	printf(",\"called_category\":%u", ticket->calledCategory);

	printf(",\"call_type\":%u", (ticket->callServiceTypes)&0xF);
	printf(",\"service_type\":%u", (ticket->callServiceTypes>>4)&0xF);

	printf(",\"supplementary_service_type\":%u", ticket->supplementaryServiceType);

	printf(",\"charging_case\":%u", ticket->chargingCase);

	printf(",\"tariff\":%u", ticket->tariff);

	printf(",\"charging_pulse\":%u", ticket->chargingPulse);

	printf(",\"fee\":%u", ticket->fee);

	printf(",\"balance\":%u", ticket->balance);

	printf(",\"bearer_service\":%u", ticket->bearerService);

	printf(",\"teleservice\":%u", ticket->teleservice&0xF);
	printf(",\"release_party\":%u", (ticket->teleservice>>4)&0x7);
	printf(",\"release_index\":%u", (ticket->teleservice>>7)&0x1);

	printf(",\"release_cause\":%u", ticket->releaseCause);

	printf(",\"uus1\":%u", ticket->UUS1);

	printf(",\"uus2\":%u", ticket->UUS2);

	printf(",\"uus3\":%u", ticket->UUS3);

	printf(",\"opc\":%u", ticket->OPC);

	printf(",\"dpc\":%u", ticket->DPC);

	printf(",\"b_num\":%u", ticket->bNum&0x1F);
	printf(",\"b_num_reserved\":%u", (ticket->bNum>>5)&0x7);

	printf("}\n");
}
//------------------------------------------------------------------------------

void print_copy( const DetailedTicket * ticket)
{
	// header
	printf("\n%u", ticket->serial);
	printf("\t" "%u" , ticket->type);

	// detailed
	printf("\t" "%u" , ticket->checksum);

	// uint8_t flags1;
	printf("\t" "%u", (ticket->flags1) & 0x3);
	printf("\t" "%u", (ticket->flags1>>2) & 0x1);
	printf("\t" "%u", (ticket->flags1>>3) & 0x1);
	printf("\t" "%u", (ticket->flags1>>4) & 0x1);
	printf("\t" "%u", (ticket->flags1>>5) & 0x1);
	printf("\t" "%u", (ticket->flags1>>6) & 0x1);
	printf("\t" "%u", (ticket->flags1>>7) & 0x1);



	//uint8_t flags2;
	printf("\t" "%u", (ticket->flags2)&0x1);
	printf("\t" "%u", (ticket->flags2>>1)&0x3);
	printf("\t" "%u", (ticket->flags2>>3)&0x1);
	printf("\t" "%u", (ticket->flags2>>4)&0xF);




	//2016-06-01T12:59:53.941+0200
	printf("\t" "20%02d-%02d-%02d %02d:%02d:%02d", ticket->YY, ticket->MM, ticket->DD, ticket->HH, ticket->MI, ticket->SS);

	printf("\t" "%u", ticket->duration);

	printf("\t" "%u", ticket->callerSeizureDuration);

	printf("\t" "%u", ticket->calledSeizureDuration);


	printf("\t" "%u", (ticket->flag3>>0)&0x3);
	printf("\t" "%u", (ticket->flag3>>2)&0x1);
	printf("\t" "%u", (ticket->flag3>>3)&0x1);
	printf("\t" "%u", (ticket->flag3>>4)&0x1);
	printf("\t" "%u", (ticket->flag3>>5)&0x7);

	printf("\t" "%u", (ticket->chargingNature)&0xF);
	printf("\t" "%u", (ticket->chargingNature>>4)&0xF);

	printf("\t" "%u", (ticket->connectedNature)&0xF);
	printf("\t" "%u", (ticket->connectedNature>>4)&0xF);

	printf("\t" "%u", ticket->chargingNumberSet);

	printf("\t");
	printNumberCopy(ticket->chargingNumber, 10);

	printf("\t" "%u", ticket->callerNumberSet);

	printf("\t");
	printNumberCopy(ticket->callerNumber, 10);

	printf("\t" "%u", ticket->connectedNumberSet);

	printf("\t");
	printNumberCopy(ticket->connectedNumber, 10);

	printf("\t" "%u", ticket->calledNumberSet);

	printf("\t");
	printNumberCopy(ticket->calledNumber, 10);

	printf("\t");
	printNumberCopy(ticket->dialedNumber, 12);


	printf("\t" "%u", ticket->groupNumber);

	printf("\t" "%u", ticket->callerShortNumber);

	printf("\t" "%u", ticket->calledShortNumber);

	printf("\t" "%u", ticket->callerModuleNumber);

	printf("\t" "%u", ticket->calledModuleNumber);

	printf("\t" "%u", ticket->incomingTrunkGN);

	printf("\t" "%u", ticket->outgoingTrunkGN);

	printf("\t" "%u", ticket->incomingSubrouteNumber);

	printf("\t" "%u", ticket->outgoingSubrouteNumber);

	printf("\t" "%u", ticket->callerDeviceType);

	printf("\t" "%u", ticket->calledDeviceType);

	printf("\t" "%u", ticket->callerPortNumber);

	printf("\t" "%u", ticket->calledPortNumber);

	printf("\t" "%u", ticket->callerCategory);

	printf("\t" "%u", ticket->calledCategory);

	printf("\t" "%u", (ticket->callServiceTypes)&0xF);
	printf("\t" "%u", (ticket->callServiceTypes>>4)&0xF);

	printf("\t" "%u", ticket->supplementaryServiceType);

	printf("\t" "%u", ticket->chargingCase);

	printf("\t" "%u", ticket->tariff);

	printf("\t" "%u", ticket->chargingPulse);

	printf("\t" "%u", ticket->fee);

	printf("\t" "%u", ticket->balance);

	printf("\t" "%u", ticket->bearerService);

	printf("\t" "%u", ticket->teleservice&0xF);
	printf("\t" "%u", (ticket->teleservice>>4)&0x7);
	printf("\t" "%u", (ticket->teleservice>>7)&0x1);

	printf("\t" "%u", ticket->releaseCause);

	printf("\t" "%u", ticket->UUS1);

	printf("\t" "%u", ticket->UUS2);

	printf("\t" "%u", ticket->UUS3);

	printf("\t" "%u", ticket->OPC);

	printf("\t" "%u", ticket->DPC);

	printf("\t" "%u", ticket->bNum&0x1F);
	printf("\t" "%u", (ticket->bNum>>5)&0x7);
}
