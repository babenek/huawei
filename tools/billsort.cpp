#include <stdlib.h>
#include <cstdio>
//#include <iostream>
#include <cstdint>
#include <vector>
//#include <iomanip>

using namespace std;

//! disabes padding for all structures
#pragma pack(push, 1)

struct Header{
uint32_t serial;
uint8_t type;
/*
//! Serial Number	4	Number for the tickets being generated since the switch has been started.
//! Ticket Type	1	"Call type of this ticket record
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
//! Note: 0x11 means that the ticket be explained by this table"
*/
};

//------------------------------------------------------------------------------

struct DetailedTicket{

uint8_t checksum;
//Checksum	1

uint8_t flags1;
//Partial Record Indicator	0.25
//Clock Changed Flag	0.125
//Free Flag	0.125
//Validity	0.125
//Call Attempt Flag	0.125
//Complaint Flag	0.125
//Centralized Charging Flag	0.125

uint8_t flags2;
//PPS Flag	0.125
//Charging Method	0.25
//NP Call Flag	0.125
//Payer	0.5

uint8_t YY;
uint8_t MM;
uint8_t DD;
uint8_t HH;
uint8_t MI;
uint8_t SS;
//Conversation End Time	6
/*
//! Conversation end date and time (Format: YYMMDDHHMMSS)
//! YY: 0-99 (binary)
//! MM: 1-12 (binary)
//! DD: 1-31 (binary)
//! HH: 0-23 (binary)
//! MM: 0-59 (binary)
//! SS: 0-59 (bianry)
*/

uint32_t duration;
//Conversation Duration	4

uint32_t callerSeizureDuration;
//Caller Seizure Duration	4

uint32_t calledSeizureDuration;
//Called Seizure Duration	4

uint8_t flag3;
//Incomplete Call Watch	0.25
//Caller ISDN Access	0.125
//Called ISDN Access	0.125
//ISUP Indication	0.125
//Reserved	0.375

/**
//! Charging Number Address Nature	0.5
//! Caller Number Address Nature	0.5
*/
uint8_t chargingNature;

/**
//! Connected Number Address Nature	0.5
//! Called Number Address nature	0.5
*/
uint8_t connectedNature;

//! Charging Number DNSet	1
uint8_t chargingNumberSet;

//! Charging Number	10
uint8_t chargingNumber [10];

//! Caller Number DNSet	1
uint8_t callerNumberSet;

//! Caller Number	10
uint8_t callerNumber [10];

//! Connected Number DNSet	1
uint8_t connectedNumberSet;

//! Connected Number	10
uint8_t connectedNumber [10];

//! Called Number DNSet	1
uint8_t calledNumberSet;

//! Called Number	10
uint8_t calledNumber [10];

//! Dialed Number	12
uint8_t dialedNumber [12];

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

//! Reserved	fill up to 154
uint8_t reserved[154];
};

//------------------------------------------------------------------------------

void printNumber(const uint8_t number[], const size_t count)
{
	printf(",'");
	for(size_t n=0; n<count; ++n)
	{
		uint8_t a=(0xF0 & number[n])>>4;
		uint8_t b=(0x0F & number[n]);
		if(a<10) 
			printf("%d",a);
		if(b<10) 
			printf("%d",b);
	}
	printf("'");
}

//------------------------------------------------------------------------------

int main (int argc, char *argv[])
{
	if (argc==2)
	{
		FILE *file;
		if(file=fopen(argv[1],"r"))
		{		
			while(!feof(file) )
			{
				Header header;
				fread(&header,5,1,file);

				switch(header.type)
				{
					case 0x01:
						DetailedTicket ticket;
						if(fread(&ticket,149,1,file))
						{
							printf("insert into bill values(%d",header.serial);
							printf(",'20%02d-%02d-%02d %02d:%02d:%02d'",ticket.YY,ticket.MM,ticket.DD,ticket.HH,ticket.MI,ticket.SS);
							printf(",%d",ticket.duration);
							//Conversation Duration	4
							printf(",%d",ticket.callerSeizureDuration);
							//Caller Seizure Duration	4
							printf(",%d",ticket.calledSeizureDuration);
							//Called Seizure Duration	4
							//! Caller Number	10
				//			printNumber(ticket.callerNumber,sizeof(ticket.callerNumber));
							//! Dialed Number	12
					//		printNumber(ticket.dialedNumber,sizeof(ticket.dialedNumber));
							//! Release Cause Value	1
							printf(",%d",ticket.releaseCause);
							




printf(",%u", ticket.checksum);
//Checksum	1

printf(",'%x'", ticket.flags1);

printf(",'%x'", ticket.flags2);
printf(",'%x'", ticket.flag3);
printf(",'%x'", ticket.chargingNature);
printf(",'%x'", ticket.connectedNature);


printf(",'%x'",ticket.chargingNumberSet);

//! Charging Number	10
printNumber(ticket.chargingNumber ,10);

//! Caller Number DNSet	1
printf(",'%x'",ticket.callerNumberSet);

//! Caller Number	10
printNumber(ticket.callerNumber,10);

//! Connected Number DNSet	1
printf(",'%x'",ticket.connectedNumberSet);

//! Connected Number	10
printNumber(ticket.connectedNumber ,10);

//! Called Number DNSet	1
printf(",'%x'",ticket.calledNumberSet);

//! Called Number	10
printNumber(ticket.calledNumber ,10);

//! Dialed Number	12
printNumber(ticket.dialedNumber,12);

//! CENTREX Group Number	2
printf(",'%x'",ticket.groupNumber);

//! Caller CENTREX Short Number	4
printf(",'%x'",ticket.callerShortNumber);

//! Called CENTREX Short Number	4
printf(",'%x'",ticket.calledShortNumber);

//! Caller Module Number	1
printf(",'%x'",ticket.callerModuleNumber);

//! Called Module Number	1
printf(",'%x'",ticket.calledModuleNumber);

//! Incoming Trunk Group Number	2
printf(",'%x'",ticket.incomingTrunkGN);

//! Outgoing Trunk Group Number	2
printf(",'%x'",ticket.outgoingTrunkGN);

//! Incoming Subroute Number	2
printf(",'%x'",ticket.incomingSubrouteNumber);

//! Outgoing Subroute Number	2
printf(",'%x'",ticket.outgoingSubrouteNumber); 

//! Caller Device Type	1
printf(",'%x'",ticket.callerDeviceType);

//! Called Device Type	1
printf(",'%x'",ticket.calledDeviceType);

//! Caller Port Number	2
printf(",'%x'",ticket.callerPortNumber);

//! Called Port Number	2
printf(",'%x'",ticket.calledPortNumber);

//! Caller Category	1
printf(",'%x'",ticket.callerCategory);

//! Called Category	1
printf(",'%x'",ticket.calledCategory);

//! Call Type	0.5
//! Service Type	0.5
printf(",'%x'",ticket.callServiceTypes);

//! Supplementary Service Type	1
printf(",'%x'",ticket.supplementaryServiceType);

//! Charging Case	2
printf(",'%x'",ticket.chargingCase);

//! Tariff	2
printf(",'%x'",ticket.tariff);

//! Charging Pulse	4
printf(",'%x'",ticket.chargingPulse);

//! Fee	4
printf(",'%x'",ticket.fee);
 
//! Balance	4
printf(",'%x'",ticket.balance);

//! Bearer Service	1
printf(",'%x'",ticket.bearerService);

//! Teleservice	0.5
//! Release Party	0.375
//! Release Index	1.125
printf(",'%x'",ticket.teleservice);

//! Release Cause Value	1
printf(",'%x'",ticket.releaseCause);

//! UUS1 Count	1
printf(",'%x'",ticket.UUS1);

//! UUS2 Count	1
printf(",'%x'",ticket.UUS2);

//! UUS3 Count	1
printf(",'%x'",ticket.UUS3);

//! OPC	4
printf(",'%x'",ticket.OPC);

//! DPC	4
printf(",'%x'",ticket.DPC);

printf(",'%x'",ticket.bNum);






							printf(",'%s');\n",argv[1]);				
						}
						break;
					default:
						if(fread(&ticket,149,1,file)){
							fprintf(stderr,"Serial:%d Unknown format:%d ",header.serial,header.type);
						    fprintf(stderr,",20%02d-%02d-%02d %02d:%02d:%02d \n",ticket.YY,ticket.MM,ticket.DD,ticket.HH,ticket.MI,ticket.SS);
						}
						break;
				};
			};
			fclose(file);
		}
		else
		{
			fprintf(stderr,"cannot open file %s\n",argv[1]);
		}
	}
	else
	{
    	fprintf(stderr,"wrong number of arguments\n");
	}
    fprintf(stderr,"done\n");

	return 0;

}
