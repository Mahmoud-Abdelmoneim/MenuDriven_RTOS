/***********************************************************************************************/
/***********************************************************************************************/
/********************************** Author: Mahmoud Abdelmoneim*********************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: GPIO ******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/* Base address of peripherals */
#define GPIOA_BASE_ADDRESS           0x40010800
#define GPIOB_BASE_ADDRESS           0x40010C00
#define GPIOC_BASE_ADDRESS           0x40011000

typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_t;

#define GPIOA                        ((GPIO_t*)GPIOA_BASE_ADDRESS)
#define GPIOB                        ((GPIO_t*)GPIOB_BASE_ADDRESS)
#define GPIOC                        ((GPIO_t*)GPIOC_BASE_ADDRESS)

#endif
