/***********************************************************************************************/
/***********************************************************************************************/
/********************************** Author: Mahmoud Abdelmoneim*********************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: RCC* ******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/* Buses Names */
#define RCC_AHB                      0
#define RCC_APB1                     1
#define RCC_APB2                     2

/* Clock Systems */
#define RCC_HSI          0b00
#define RCC_HSE          0b01
#define RCC_PLL          0b10


/* Peripherals Names */
typedef enum
{
	DMA_1,
	DMA_2,
	SRAM,
	FLITF=4,
	CRC_=6,
	FSMC=8,
	SDIO=10,
	AFIO_=0,
	GPIO_A=2,
	GPIO_B,
	GPIO_C,
	GPIO_D,
	GPIO_E,
	GPIO_F,
	GPIO_G,
	ADC_1,
	ADC_2,
	TIM_1,
	SPI_1,
	TIM_8,
	USART_1,
	ADC_3,
	TIM_9=19,
	TIM_10,
	TIM_11,
	TIM_2=0,
	TIM_3,
	TIM_4,
	TIM_5,
	TIM_6,
	TIM_7,
	TIM_12,
	TIM_13,
	TIM_14,
	WWDG_=11,
	SPI_2=14,
	SPI3,
	USART_2=17,
	USART_3,
	UART_4,
	UART_5,
	I2C_1,
	I2C_2,
	USB_,
	CAN_=25,
	BKP_=27,
	PWR_,
	DAC_

}peripherals_t;


/* Prototypes of functions */
void MRCC_voidInit(void);
void MRCC_voidPeripheralClockEnable(u8 Copy_u8BusName,peripherals_t Copy_u8PeripheralName);
void MRCC_voidPeripheralClockDisable(u8 Copy_u8BusName,peripherals_t Copy_u8PeripheralName);

#endif
