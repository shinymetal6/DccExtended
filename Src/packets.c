/*
 * packets.c
 *
 *  Created on: Oct 31, 2019
 *      Author: fil
 */

#include "main.h"
#include <string.h>

extern len3_dcc_pack 	len3_packet;
extern len4_dcc_pack 	len4_packet;
extern len5_dcc_pack 	len5_packet;
extern len6_dcc_pack 	len6_packet;

extern dcc_struct	 	packets;
extern uint16_t 	shadow_buf[sizeof(len6_dcc_pack)];

void init_bufs(void)
{
uint16_t	*pkt;
uint16_t i;

	packets.len3_packet = &len3_packet;
	packets.len4_packet = &len4_packet;
	packets.len5_packet = &len5_packet;
	packets.len6_packet = &len6_packet;
	packets.len3_packet_len = sizeof(len3_dcc_pack)/2;
	packets.len4_packet_len = sizeof(len4_dcc_pack)/2;
	packets.len5_packet_len = sizeof(len5_dcc_pack)/2;
	packets.len6_packet_len = sizeof(len6_dcc_pack)/2;
	packets.packet_type = PACKET_TYPE_1;
	pkt=(uint16_t	*)&len3_packet.preamble[0];
	for(i=0;i<packets.len3_packet_len;i++)
		pkt[i] = BIT_0;
	pkt=(uint16_t	*)&len4_packet.preamble[0];
	for(i=0;i<packets.len4_packet_len;i++)
		pkt[i] = BIT_0;
	pkt=(uint16_t	*)&len5_packet.preamble[0];
	for(i=0;i<packets.len5_packet_len;i++)
		pkt[i] = BIT_0;
	pkt=(uint16_t	*)&len6_packet.preamble[0];
	for(i=0;i<packets.len6_packet_len;i++)
		pkt[i] = BIT_0;
	for(i=0;i<PREAMBLE_LEN;i++)
	{
		len3_packet.preamble[i] = BIT_1;
		len4_packet.preamble[i] = BIT_1;
		len5_packet.preamble[i] = BIT_1;
		len6_packet.preamble[i] = BIT_1;
	}

	len3_packet.closer = BIT_1;
	len4_packet.closer = BIT_1;
	len5_packet.closer = BIT_1;
	len6_packet.closer = BIT_1;
	pkt=(uint16_t	*)&len6_packet.preamble[0];

	memcpy(shadow_buf,pkt,sizeof(len6_dcc_pack));
}

