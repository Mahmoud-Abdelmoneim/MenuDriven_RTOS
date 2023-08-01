/***********************************************************************************************/
/***********************************************************************************************/
/********************************** Author: Mahmoud Abdelmoneim*********************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: RCC* ******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/* RCC_HSI_ON
		--> HSI ON	>>	1
		--> HSI OFF	>>	0
   RCC_HSE_ON
		--> HSE ON	>>	1
		--> HSE OFF	>>	0
   RCC_PLL_ON
		--> PLL ON	>>	1
		--> PLL OFF	>>	0
 */
#define RCC_HSE_ON                  1
#define RCC_HSI_ON                  1
#define RCC_PLL_ON                  1

/*Clock security system enable
 Options:
        0: Clock detector OFF
        1: Clock detector ON (Clock detector ON if the HSE oscillator is ready , OFF if not)
*/
#define RCC_CSS_ON                  0

/* External high-speed clock bypass
 Options:
        0: external 4-16 MHz oscillator not bypassed
        1: external 4-16 MHz oscillator bypassed with external clock
 */
#define RCC_HSE_BYP                 0

/* Options:
- RCC_MCO_NO                       0
- RCC_MCO_SYSCLK                   4
- RCC_MCO_HSI                      5
- RCC_MCO_HSE                      6
- RCC_MCO_PLL_DIV_2                7
*/
#define RCC_MCO_SRC               0

/* Internal high-speed clock trimming */
#define RCC_HSI_TRIMMING_VAL            16

/* Options:
          -HSI/2  >> 0
          -HSE    >> 1
*/
#define RCC_PLL_SOURCE          1

/* if u choose HSE as an pll source
  Options:
          -HSE   >> 0
          -HSE/2 >> 1
*/
#define RCC_PLL_HSE             0

/*
 -The PLL output frequency must not exceed 72 MHz
These bits are written by software to define the PLL multiplication factor. These bits can be
written only when PLL is disabled.
Caution: The PLL output frequency must not exceed 72 MHz.
0000: PLL input clock x 2
0001: PLL input clock x 3
0010: PLL input clock x 4
0011: PLL input clock x 5
0100: PLL input clock x 6
0101: PLL input clock x 7
0110: PLL input clock x 8
0111: PLL input clock x 9
1000: PLL input clock x 10
1001: PLL input clock x 11
1010: PLL input clock x 12
1011: PLL input clock x 13
1100: PLL input clock x 14
1101: PLL input clock x 15
1110: PLL input clock x 16
1111: PLL input clock x 16
*/
#define RCC_MUL_FACTOR                0b0111

/*ADC prescaler
Set and cleared by software to select the frequency of the clock to the ADCs.
00: PCLK2 divided by 2
01: PCLK2 divided by 4
10: PCLK2 divided by 6
11: PCLK2 divided by 8
*/
#define RCC_ADC_PRESCALER             0b00

/*
APB high-speed prescaler (APB2)
Set and cleared by software to control the division factor of the APB high-speed clock
(PCLK2).
0xx: HCLK not divided
100: HCLK divided by 2
101: HCLK divided by 4
110: HCLK divided by 8
111: HCLK divided by 16
*/
#define RCC_APB2_PRESCALER             0b000

/*
 APB low-speed prescaler (APB1)
Set and cleared by software to control the division factor of the APB low-speed clock
(PCLK1).
Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
0xx: HCLK not divided
100: HCLK divided by 2
101: HCLK divided by 4
110: HCLK divided by 8
111: HCLK divided by 16
*/
#define RCC_APB1_PRESCALER             0b000

/*
 -AHB take clock from SYSCLK
AHB prescaler
Set and cleared by software to control the division factor of the AHB clock.
0xxx: SYSCLK not divided
1000: SYSCLK divided by 2
1001: SYSCLK divided by 4
1010: SYSCLK divided by 8
1011: SYSCLK divided by 16
1100: SYSCLK divided by 64
1101: SYSCLK divided by 128
1110: SYSCLK divided by 256
1111: SYSCLK divided by 512
*/
#define RCC_AHB_PRESCALER             0b0000

/* These bits represent the ratio of the SYSCLK (system clock) period to the Flash access
time.
options:
000: Zero wait state, if 0 < SYSCLK≤ 24 MHz
001: One wait state, if 24 MHz < SYSCLK ≤ 48 MHz
010: Two wait states, if 48 MHz < SYSCLK ≤72 MHz
 */
#define RCC_FLASH_LATENCY           0b010

/*
 Options:
-RCC_HSI
-RCC_HSE
-RCC_PLL
 */
#define RCC_SYSCLK_SRC            RCC_HSE



#endif
