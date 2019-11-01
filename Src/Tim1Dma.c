/*
 * Tim1Dma.c
 *
 *  Created on: Oct 31, 2019
 *      Author: fil
 */
#include "stm32f3xx_hal.h"
#include "main.h"

extern	TIM_HandleTypeDef htim1;
extern  uint16_t	dmatim1_flag;

void dma_half(DMA_HandleTypeDef *hdma);
void dma_full(DMA_HandleTypeDef *hdma);
//TIM_CHANNEL_1
void PWM_Start_DMA(uint32_t *pData, uint16_t Length)
{
	htim1.hdma[TIM_DMA_ID_CC1]->XferHalfCpltCallback = dma_half;
	htim1.hdma[TIM_DMA_ID_CC1]->XferCpltCallback = dma_full;
	/* Set the DMA error callback */
	htim1.hdma[TIM_DMA_ID_CC1]->XferErrorCallback = TIM_DMAError ;
	/* Enable the DMA channel */
	HAL_DMA_Start_IT( htim1.hdma[TIM_DMA_ID_CC1], (uint32_t)pData, (uint32_t)&htim1.Instance->PSC, Length);

	/* Enable the TIM Capture/Compare 1 DMA request */
	htim1.Instance->DIER |= TIM_DMA_CC1;
	/* Enable the Capture compare channel */
	TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1); //starts PWM on CH1N pin

	htim1.Instance->BDTR|=TIM_BDTR_MOE;
	//htim1.Instance->CR1|=TIM_CR1_CEN;

	/* Enable the Peripheral */
	htim1.Instance->CR1|=TIM_CR1_CEN;
}


HAL_StatusTypeDef L_HAL_TIM_PWM_Start_DMAorig(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length)
{
  /* Set the DMA Period elapsed callback for half and full transfer*/
  htim->hdma[TIM_DMA_ID_CC1]->XferHalfCpltCallback = dma_half;
  htim->hdma[TIM_DMA_ID_CC1]->XferCpltCallback = dma_full;
  /* Set the DMA error callback */
  htim->hdma[TIM_DMA_ID_CC1]->XferErrorCallback = TIM_DMAError ;
  /* Enable the DMA channel */
  HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)pData, (uint32_t)&htim->Instance->PSC, Length);

  /* Enable the TIM Capture/Compare 1 DMA request */
  __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC1);
  /* Enable the Capture compare channel */
  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);
  //TIM_CCxNChannelCmd(htim->Instance, Channel, TIM_CCxN_ENABLE);
  HAL_TIMEx_PWMN_Start(htim, TIM_CHANNEL_1); //starts PWM on CH1N pin

__HAL_TIM_MOE_ENABLE(htim);

  /* Enable the Peripheral */
  __HAL_TIM_ENABLE(htim);

  /* Return function status */
  return HAL_OK;
}
extern void write_shadow(uint16_t *dest);

void dma_half(DMA_HandleTypeDef *hdma)
{
	//HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);    //starts PWM on CH1 pin
	//write_shadow((uint16_t *)&DCC_Packet[0]);

}

void dma_full(DMA_HandleTypeDef *hdma)
{
	dmatim1_flag=1;
	//HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);    //starts PWM on CH1 pin
	//write_shadow((uint16_t *)&DCC_Packet[1]);

}



