/***********************************************************************************************/
/***********************************************************************************************/
/********************************** Author: Mahmoud Abdelmoneim*********************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: RCC* ******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_config.h"
#include "RCC_private.h"

void MRCC_voidInit(void)
{
#if RCC_SYSCLK_SRC == RCC_HSI
	RCC->CR = 0;
	RCC->CR |= (RCC_CSS_ON << 19);
	if(RCC_HSI_TRIMMING_VAL <= 32 && RCC_HSI_TRIMMING_VAL >= 0)
	{
		RCC->CR |= (RCC_HSI_TRIMMING_VAL << 3);
	}
	RCC->CR |= (RCC_HSI_ON << 0);
	while(!((RCC->CR >> 1)&1));

	RCC->CFGR = 0;
	RCC->CFGR |= (RCC_MCO_SRC << 24);
	RCC->CFGR |= (RCC_ADC_PRESCALER << 14);
	RCC->CFGR |= (RCC_APB2_PRESCALER << 11);
	RCC->CFGR |= (RCC_APB1_PRESCALER << 8);
	RCC->CFGR |= (RCC_AHB_PRESCALER << 4);

	RCC->CFGR |= (RCC_SYSCLK_SRC << 0);

#elif RCC_SYSCLK_SRC == RCC_HSE
	RCC->CR = 0;
	RCC->CR |= (RCC_CSS_ON << 19);
	RCC->CR |= (RCC_HSE_BYP << 18);
	RCC->CR |= (RCC_HSE_ON << 16);
	while(!((RCC->CR >> 17)&1));

	RCC->CFGR = 0;
	RCC->CFGR |= (RCC_MCO_SRC << 24);
	RCC->CFGR |= (RCC_ADC_PRESCALER << 14);
	RCC->CFGR |= (RCC_APB2_PRESCALER << 11);
	RCC->CFGR |= (RCC_APB1_PRESCALER << 8);
	RCC->CFGR |= (RCC_AHB_PRESCALER << 4);

	RCC->CFGR |= (RCC_SYSCLK_SRC << 0);

#elif RCC_SYSCLK_SRC == RCC_PLL

	//HCLK to 72MHz
	//SYSCLK to72MHz
	//AHBCLK to 72MHz
	//APB1CLK to 36MHz
	//APB2CLK to 72MHz

	/* setting 2 wait states  */
	FLASH_ACR &= ~(0b111 << 0);
	FLASH_ACR |= (RCC_FLASH_LATENCY << 0);

	/* Buses prescaler */
	RCC->CFGR |= (RCC_ADC_PRESCALER << 14);
	RCC->CFGR |= (RCC_APB2_PRESCALER << 11);
	RCC->CFGR |= (RCC_APB1_PRESCALER << 8);
	RCC->CFGR |= (RCC_AHB_PRESCALER << 4);

	/* HSE not div */
	RCC->CFGR |= (RCC_PLL_HSE << 17);

	/* Enable HSE */
	RCC->CR |= (RCC_HSE_ON << 16);
	while(!((RCC->CR >> 17)&1));

	/* HSE is pll source */
	RCC->CFGR |= (RCC_PLL_SOURCE << 16);
	/* PLLMUL = 9 */
	RCC->CFGR |= (RCC_MUL_FACTOR << 18);
	/* Enable PLL */
	RCC->CR |= (RCC_PLL_ON << 24);
	while(!((RCC->CR >> 25)&1));

	/* Set PLL as source to system clock */
	RCC->CFGR |= (RCC_SYSCLK_SRC << 0);
	while((GET_BET(RCC->CFGR,3)!=1) && (GET_BET(RCC->CFGR,2)!=0));


#endif

}
void MRCC_voidPeripheralClockEnable(u8 Copy_u8BusName,peripherals_t Copy_u8PeripheralName)
{
	switch(Copy_u8BusName)
	{
	case RCC_AHB:
		SET_BET(RCC->AHBENR,Copy_u8PeripheralName);
		break;
	case RCC_APB1:
		SET_BET(RCC->APB1ENR,Copy_u8PeripheralName);
		break;
	case RCC_APB2:
		SET_BET(RCC->APB2ENR,Copy_u8PeripheralName);
		break;
	}
}
void MRCC_voidPeripheralClockDisable(u8 Copy_u8BusName,peripherals_t Copy_u8PeripheralName)
{
	switch(Copy_u8BusName)
	{
	case RCC_AHB:
		CLR_BET(RCC->AHBENR,Copy_u8PeripheralName);
		break;
	case RCC_APB1:
		CLR_BET(RCC->APB1ENR,Copy_u8PeripheralName);
		break;
	case RCC_APB2:
		CLR_BET(RCC->APB2ENR,Copy_u8PeripheralName);
		break;
	}
}
