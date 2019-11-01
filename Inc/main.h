/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define VCP_RX_Pin GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA
#define LD3_Pin GPIO_PIN_3
#define LD3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
/* Used for uart */
#define	BUFLEN	0x1f

#define		BIT_0		124
#define		BIT_1		62
#define		PREAMBLE_LEN		16
#define		LEN1_ADDR_LEN		8
#define		LEN1_CMD_LEN		8
#define		CHECK_LEN			8

#define		PACKET_LEN	256

typedef struct {
	uint16_t preamble[PREAMBLE_LEN];
	uint16_t byte1_start;
	uint16_t byte1[LEN1_ADDR_LEN];
	uint16_t byte2_start;
	uint16_t byte2[LEN1_CMD_LEN];
	uint16_t errdet_start;
	uint16_t errcheck[CHECK_LEN];
	uint16_t closer;
} len3_dcc_pack;

typedef struct {
	uint16_t preamble[PREAMBLE_LEN];
	uint16_t byte1_start;
	uint16_t byte1[LEN1_ADDR_LEN];
	uint16_t byte2_start;
	uint16_t byte2[LEN1_CMD_LEN];
	uint16_t byte3_start;
	uint16_t byte3[LEN1_CMD_LEN];
	uint16_t errdet_start;
	uint16_t errcheck[CHECK_LEN];
	uint16_t closer;
} len4_dcc_pack;

typedef struct {
	uint16_t preamble[PREAMBLE_LEN];
	uint16_t byte1_start;
	uint16_t byte1[LEN1_ADDR_LEN];
	uint16_t byte2_start;
	uint16_t byte2[LEN1_CMD_LEN];
	uint16_t byte3_start;
	uint16_t byte3[LEN1_CMD_LEN];
	uint16_t byte4_start;
	uint16_t byte4[LEN1_CMD_LEN];
	uint16_t errdet_start;
	uint16_t errcheck[CHECK_LEN];
	uint16_t closer;
} len5_dcc_pack;

typedef struct {
	uint16_t preamble[PREAMBLE_LEN];
	uint16_t byte1_start;
	uint16_t byte1[LEN1_ADDR_LEN];
	uint16_t byte2_start;
	uint16_t byte2[LEN1_CMD_LEN];
	uint16_t byte3_start;
	uint16_t byte3[LEN1_CMD_LEN];
	uint16_t byte4_start;
	uint16_t byte4[LEN1_CMD_LEN];
	uint16_t byte5_start;
	uint16_t byte5[LEN1_CMD_LEN];
	uint16_t errdet_start;
	uint16_t errcheck[CHECK_LEN];
	uint16_t closer;
} len6_dcc_pack;

#define	PACKET_TYPE_1	3
#define	PACKET_TYPE_2	4
#define	PACKET_TYPE_3	5
#define	PACKET_TYPE_4	6

typedef struct {
	uint16_t packet_type;	/* can be 0,1 or 2, used as index for following structs */
	uint16_t len3_packet_len;
	len3_dcc_pack *len3_packet;
	uint16_t len4_packet_len;
	len4_dcc_pack *len4_packet;
	uint16_t len5_packet_len;
	len5_dcc_pack *len5_packet;
	uint16_t len6_packet_len;
	len6_dcc_pack *len6_packet;
} dcc_struct;

/* UART */

typedef struct {
	uint8_t byte_count;
	uint8_t packet[12];
} s_uart_rxbuf;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
