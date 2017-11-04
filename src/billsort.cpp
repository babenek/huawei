#include <cstdio>
#include <cstring>

#include "TicketHeader.h"
#include "RawTicket.h"
#include "DetailTicket.h"

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		FILE *file;
		if (file = fopen(argv[1], "r"))
		{
			fprintf(stderr, "file %s opened\n", argv[1]);

			RawTicket rawTicket;
			unsigned n=0;
			while (not feof(file) and 1 == fread(&rawTicket, TICKET_SIZE, 1, file))
			{
				if(0==(n&0x0FFF))
					printf("\nCOPY %s (serial, type, checksum, partial_record_indicator, clock_changed_flag, free_flag, validity, call_attempt_flag, compliant_flag, centralized_charging_flag, pps, charging_method, npc, payer, end_time, duration, caller_seizure_duration, called_seizure_duration, incomplete_call_watch, caller_isdn, called_isdn, isup, flag3_reserved, charging_nature, caller_nature, connected_nature, called_nature, charging_number_set, charging_number, caller_number_set, caller_number, connected_number_set, connected_number, called_number_set, called_number, dialed_number, group_number, caller_short_number, called_short_number, caller_module_number, called_module_number, incoming_trunk_gn, outgoing_trunk_gn, incoming_subroute_number, outgoing_subroute_number, caller_device_type, called_device_type, caller_port_number, called_port_number, caller_category, called_category, call_type, service_type, supplementary_service_type, charging_case, tariff, charging_pulse, fee, balance, bearer_service, teleservice, release_party, release_index, release_cause, uus1, uus2, uus3, opc, dpc, b_num, b_num_reserved) FROM stdin;",argv[1]);
				DetailedTicket * detailTicket = reinterpret_cast<DetailedTicket *>(&rawTicket);
				print_copy(detailTicket);
				++n;
				if(0==(n&0x0FFF))
					printf("\n\\.\n\n");
								
			};
			if(0!=(n&0x0FFF))
				printf("\n\\.\n\n");
				
			fclose(file);
		}
		else
		{
			fprintf(stderr, "cannot open file %s\n", argv[1]);
		}
	}
	else
	{
		fprintf(stderr, "use: billsort filename\n");
	}
	fprintf(stderr, "done\n");

	return 0;

}
