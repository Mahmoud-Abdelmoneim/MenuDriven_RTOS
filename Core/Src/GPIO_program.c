/***********************************************************************************************/
/***********************************************************************************************/
/********************************** Author: Mahmoud Abdelmoneim*********************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: GPIO ******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_config.h"
#include "GPIO_private.h"

void MGPIO_voidSetPinMode(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Mode)
{
    switch(Copy_u8Port)
    {
    case PORTA:
            if(Copy_u8Pin <= 7)
            {
                    GPIOA->CRL &= ~((0b1111) << (Copy_u8Pin * 4));
                    GPIOA->CRL |= (Copy_u8Mode << (Copy_u8Pin * 4));
            }
            else if(Copy_u8Pin <= 15)
            {
                    Copy_u8Pin = Copy_u8Pin - 8;
                    GPIOA->CRH &= ~((0b1111) << (Copy_u8Pin * 4));
                    GPIOA->CRH |= (Copy_u8Mode << (Copy_u8Pin * 4));
            }
            break;

    case PORTB:
            if(Copy_u8Pin <= 7)
            {
                    GPIOB->CRL &= ~((0b1111) << ((Copy_u8Pin) * 4));
                    GPIOB->CRL |= (Copy_u8Mode << ((Copy_u8Pin) * 4));
            }
            else if(Copy_u8Pin <= 15)
            {
                    Copy_u8Pin = Copy_u8Pin - 8;
                    GPIOB->CRH &= ~((0b1111) << (Copy_u8Pin * 4));
                    GPIOB->CRH |= (Copy_u8Mode << (Copy_u8Pin * 4));
            }
            /* Check if pulled up or pulled down */
            if(Copy_u8Mode == GPIO_INPUT_PU_PD)
            {
            	GPIOB->ODR |= (1 << Copy_u8Pin);
            }
            else if(Copy_u8Mode == GPIO_INPUT_PU_PD)
            {
            	GPIOB->ODR &= ~(1 << Copy_u8Pin);
            }
            break;

    case PORTC:
            if(Copy_u8Pin <= 7)
            {
                    GPIOC->CRL &= ~((0b1111) << (Copy_u8Pin * 4));
                    GPIOC->CRL |= (Copy_u8Mode << (Copy_u8Pin * 4));
            }
            else if(Copy_u8Pin <= 15)
            {
                    Copy_u8Pin = Copy_u8Pin - 8;
                    GPIOC->CRH &= ~((0b1111) << (Copy_u8Pin * 4));
                    GPIOC->CRH |= (Copy_u8Mode << (Copy_u8Pin * 4));
            }
            /* Check if pulled up or pulled down */
            if(Copy_u8Mode == GPIO_INPUT_PU_PD)
            {
            	GPIOC->ODR |= (1 << Copy_u8Pin);
            }
            else if(Copy_u8Mode == GPIO_INPUT_PU_PD)
            {
            	GPIOC->ODR &= ~(1 << Copy_u8Pin);
            }
            break;
    }
}

void MGPIO_voidSetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value)
{
	switch(Copy_u8Port)
	{
	case PORTA:
		if(Copy_u8Value == GPIO_HIGH)
		{
			GPIOA->BSRR = (1 << Copy_u8Pin);
		}
		else if(Copy_u8Value == GPIO_LOW)
		{
			GPIOA->BRR = (1 << Copy_u8Pin);
		}
		break;

	case PORTB:
		if(Copy_u8Value == GPIO_HIGH)
		{
			GPIOB->BSRR = (1 << Copy_u8Pin);
		}
		else if(Copy_u8Value == GPIO_LOW)
		{
			GPIOB->BRR = (1 << Copy_u8Pin);
		}
		break;

	case PORTC:
		if(Copy_u8Value == GPIO_HIGH)
		{
			GPIOC->BSRR = (1 << Copy_u8Pin);
		}
		else if(Copy_u8Value == GPIO_LOW)
		{
			GPIOC->BRR = (1 << Copy_u8Pin);
		}
		break;
	}

}

u8 MGPIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	u8 Local_u8ReturnValue = 0;

	switch(Copy_u8Port)
	{
	case PORTA:
		Local_u8ReturnValue = GET_BET(GPIOA->IDR,Copy_u8Pin);
		break;
	case PORTB:
		Local_u8ReturnValue = GET_BET(GPIOB->IDR,Copy_u8Pin);
		break;
	case PORTC:
		Local_u8ReturnValue = GET_BET(GPIOC->IDR,Copy_u8Pin);
		break;
	}
	return Local_u8ReturnValue;
}

