#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <misc.h>
#include "stm32f4xx.h"
//#include "stm32f4_discovery.h"
GPIO_InitTypeDef  GPIO_InitStructure;
GPIO_InitTypeDef  GPIOA_InitStructure;
void Delay(__IO uint32_t nCount);
uint32_t time ;

void EXTILine0_Config(void);
int main(void)
{
  /* Configure EXTI Line0 (connected to PA0 pin) in interrupt mode */
EXTILine0_Config();

  /* Generate software interrupt: simulate a rising edge applied on EXTI0 line */

  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD, ENABLE);
  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode
  GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIOA_InitStructure.GPIO_OType = GPIO_OType_PP;
  //GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIOA_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIOA_InitStructure);*/
  time=100;
  while (1)
  {
 /*     while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
      {time=time+10;
      Delay (10);}

	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
        {if (time>20,time=time-10);

       else Delay (10);}
*/
      GPIO_SetBits(GPIOD, GPIO_Pin_14|GPIO_Pin_15);
      Delay (time);
      GPIO_ResetBits(GPIOD, GPIO_Pin_14|GPIO_Pin_15);
      Delay (time);
  }
}
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

void EXTILine0_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
  EXTI_InitTypeDef   EXTI_IniStructure;

  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect EXTI Line0 to PA0 pin */
//  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

  /* Configure EXTI Line0 */
  EXTI_IniStructure.EXTI_Line = EXTI_Line0;
  EXTI_IniStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_IniStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_IniStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_IniStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}