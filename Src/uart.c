/*
 * uart.c
 *
 *  Created on: Oct 30, 2019
 *      Author: fil
 */
#include "main.h"
#include <string.h>
#include <stdlib.h>

extern	UART_HandleTypeDef huart2;
extern	DMA_HandleTypeDef hdma_usart2_tx;
extern uint8_t uart2_rx_buffer_ready;
extern s_uart_rxbuf uart_rxbuf;

uint16_t busy_flag;
void tx_buffer(uint8_t *pData)
{
	busy_flag = 1;
	HAL_UART_Transmit_DMA(&huart2, pData, strlen((char *)pData));
}

void tx_buffer_end(void)
{
	busy_flag = 0;
}

void uart_start(void)
{
	HAL_UART_Receive_IT(&huart2, &uart_rxbuf.packet[0], 1);
	tx_buffer((uint8_t *)("Ciao fil\n\r"));
}

uint8_t header=0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Packet is
	!1122# or
	$112233# or
	&11223344# or
	=1122334455#
	*/
	if ( header == 0 )
	{
		switch(uart_rxbuf.packet[0])
		{
		case	'!' : 	uart_rxbuf.byte_count=6;
						header = 1;
						break;
		case	'$' : 	uart_rxbuf.byte_count=8;
						header = 1;
						break;
		case	'&' : 	uart_rxbuf.byte_count=10;
						header = 1;
						break;
		case	'=' : 	uart_rxbuf.byte_count=12;
						header = 1;
						break;
		default :
						HAL_UART_Receive_IT(&huart2, &uart_rxbuf.packet[0], 1);
						break;
		}
		if ( header == 1 )
		{
			HAL_UART_Receive_IT(&huart2, &uart_rxbuf.packet[1], uart_rxbuf.byte_count-1);
		}
	}
	else
	{
		if( uart_rxbuf.packet[uart_rxbuf.byte_count-1] == '#')
			uart2_rx_buffer_ready=1;
		header = 0;
		HAL_UART_Receive_IT(&huart2, &uart_rxbuf.packet[0], 1);
	}
}

extern uint16_t 	shadow_buf[sizeof(len6_dcc_pack)];
uint8_t tbyte[6];
char a[2];
uint16_t	i,j=0,err_check=0,shadow_buf_index,bye_count=0;
uint16_t 	l_shadow_buf[8];
void compile_shadow(void)
{


	for(i=0;i< uart_rxbuf.packet[uart_rxbuf.byte_count];i+=2)
	{
		a[0] = (char )uart_rxbuf.packet[i+1];
		a[1] = (char )uart_rxbuf.packet[i+2];
		tbyte[bye_count] = (uint8_t )strtol(a, NULL, 16);
		err_check ^= tbyte[bye_count];
		bye_count++;
	}
	tbyte[bye_count] = err_check;
	for(i=0;i< bye_count+1;i++)
	{
		shadow_buf_index=16;
		for (j=0;j<8;j++)
		{
			l_shadow_buf[7-i] = BIT_0;
			if ( (tbyte[i] & (1 << i)) != 0 )
				l_shadow_buf[7-i] = BIT_1;
		}
		memcpy(&shadow_buf[shadow_buf_index],l_shadow_buf,sizeof(l_shadow_buf));
		shadow_buf_index+=9;
	}
}


