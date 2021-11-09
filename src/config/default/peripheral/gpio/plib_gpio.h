/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for R5 pin ***/
#define R5_Set()               (LATGSET = (1<<15))
#define R5_Clear()             (LATGCLR = (1<<15))
#define R5_Toggle()            (LATGINV= (1<<15))
#define R5_OutputEnable()      (TRISGCLR = (1<<15))
#define R5_InputEnable()       (TRISGSET = (1<<15))
#define R5_Get()               ((PORTG >> 15) & 0x1)
#define R5_PIN                  GPIO_PIN_RG15

/*** Macros for B4 pin ***/
#define B4_Set()               (LATESET = (1<<5))
#define B4_Clear()             (LATECLR = (1<<5))
#define B4_Toggle()            (LATEINV= (1<<5))
#define B4_OutputEnable()      (TRISECLR = (1<<5))
#define B4_InputEnable()       (TRISESET = (1<<5))
#define B4_Get()               ((PORTE >> 5) & 0x1)
#define B4_PIN                  GPIO_PIN_RE5

/*** Macros for G5 pin ***/
#define G5_Set()               (LATESET = (1<<6))
#define G5_Clear()             (LATECLR = (1<<6))
#define G5_Toggle()            (LATEINV= (1<<6))
#define G5_OutputEnable()      (TRISECLR = (1<<6))
#define G5_InputEnable()       (TRISESET = (1<<6))
#define G5_Get()               ((PORTE >> 6) & 0x1)
#define G5_PIN                  GPIO_PIN_RE6

/*** Macros for R3 pin ***/
#define R3_Set()               (LATCSET = (1<<2))
#define R3_Clear()             (LATCCLR = (1<<2))
#define R3_Toggle()            (LATCINV= (1<<2))
#define R3_OutputEnable()      (TRISCCLR = (1<<2))
#define R3_InputEnable()       (TRISCSET = (1<<2))
#define R3_Get()               ((PORTC >> 2) & 0x1)
#define R3_PIN                  GPIO_PIN_RC2

/*** Macros for ADDR_A pin ***/
#define ADDR_A_Set()               (LATCSET = (1<<4))
#define ADDR_A_Clear()             (LATCCLR = (1<<4))
#define ADDR_A_Toggle()            (LATCINV= (1<<4))
#define ADDR_A_OutputEnable()      (TRISCCLR = (1<<4))
#define ADDR_A_InputEnable()       (TRISCSET = (1<<4))
#define ADDR_A_Get()               ((PORTC >> 4) & 0x1)
#define ADDR_A_PIN                  GPIO_PIN_RC4

/*** Macros for B5 pin ***/
#define B5_Set()               (LATASET = (1<<0))
#define B5_Clear()             (LATACLR = (1<<0))
#define B5_Toggle()            (LATAINV= (1<<0))
#define B5_OutputEnable()      (TRISACLR = (1<<0))
#define B5_InputEnable()       (TRISASET = (1<<0))
#define B5_Get()               ((PORTA >> 0) & 0x1)
#define B5_PIN                  GPIO_PIN_RA0

/*** Macros for G4 pin ***/
#define G4_Set()               (LATESET = (1<<8))
#define G4_Clear()             (LATECLR = (1<<8))
#define G4_Toggle()            (LATEINV= (1<<8))
#define G4_OutputEnable()      (TRISECLR = (1<<8))
#define G4_InputEnable()       (TRISESET = (1<<8))
#define G4_Get()               ((PORTE >> 8) & 0x1)
#define G4_PIN                  GPIO_PIN_RE8

/*** Macros for R6 pin ***/
#define R6_Set()               (LATBSET = (1<<4))
#define R6_Clear()             (LATBCLR = (1<<4))
#define R6_Toggle()            (LATBINV= (1<<4))
#define R6_OutputEnable()      (TRISBCLR = (1<<4))
#define R6_InputEnable()       (TRISBSET = (1<<4))
#define R6_Get()               ((PORTB >> 4) & 0x1)
#define R6_PIN                  GPIO_PIN_RB4

/*** Macros for G6 pin ***/
#define G6_Set()               (LATBSET = (1<<3))
#define G6_Clear()             (LATBCLR = (1<<3))
#define G6_Toggle()            (LATBINV= (1<<3))
#define G6_OutputEnable()      (TRISBCLR = (1<<3))
#define G6_InputEnable()       (TRISBSET = (1<<3))
#define G6_Get()               ((PORTB >> 3) & 0x1)
#define G6_PIN                  GPIO_PIN_RB3

/*** Macros for B6 pin ***/
#define B6_Set()               (LATBSET = (1<<2))
#define B6_Clear()             (LATBCLR = (1<<2))
#define B6_Toggle()            (LATBINV= (1<<2))
#define B6_OutputEnable()      (TRISBCLR = (1<<2))
#define B6_InputEnable()       (TRISBSET = (1<<2))
#define B6_Get()               ((PORTB >> 2) & 0x1)
#define B6_PIN                  GPIO_PIN_RB2

/*** Macros for R7 pin ***/
#define R7_Set()               (LATBSET = (1<<0))
#define R7_Clear()             (LATBCLR = (1<<0))
#define R7_Toggle()            (LATBINV= (1<<0))
#define R7_OutputEnable()      (TRISBCLR = (1<<0))
#define R7_InputEnable()       (TRISBSET = (1<<0))
#define R7_Get()               ((PORTB >> 0) & 0x1)
#define R7_PIN                  GPIO_PIN_RB0

/*** Macros for G7 pin ***/
#define G7_Set()               (LATBSET = (1<<6))
#define G7_Clear()             (LATBCLR = (1<<6))
#define G7_Toggle()            (LATBINV= (1<<6))
#define G7_OutputEnable()      (TRISBCLR = (1<<6))
#define G7_InputEnable()       (TRISBSET = (1<<6))
#define G7_Get()               ((PORTB >> 6) & 0x1)
#define G7_PIN                  GPIO_PIN_RB6

/*** Macros for B7 pin ***/
#define B7_Set()               (LATBSET = (1<<7))
#define B7_Clear()             (LATBCLR = (1<<7))
#define B7_Toggle()            (LATBINV= (1<<7))
#define B7_OutputEnable()      (TRISBCLR = (1<<7))
#define B7_InputEnable()       (TRISBSET = (1<<7))
#define B7_Get()               ((PORTB >> 7) & 0x1)
#define B7_PIN                  GPIO_PIN_RB7

/*** Macros for R8 pin ***/
#define R8_Set()               (LATASET = (1<<9))
#define R8_Clear()             (LATACLR = (1<<9))
#define R8_Toggle()            (LATAINV= (1<<9))
#define R8_OutputEnable()      (TRISACLR = (1<<9))
#define R8_InputEnable()       (TRISASET = (1<<9))
#define R8_Get()               ((PORTA >> 9) & 0x1)
#define R8_PIN                  GPIO_PIN_RA9

/*** Macros for G8 pin ***/
#define G8_Set()               (LATASET = (1<<10))
#define G8_Clear()             (LATACLR = (1<<10))
#define G8_Toggle()            (LATAINV= (1<<10))
#define G8_OutputEnable()      (TRISACLR = (1<<10))
#define G8_InputEnable()       (TRISASET = (1<<10))
#define G8_Get()               ((PORTA >> 10) & 0x1)
#define G8_PIN                  GPIO_PIN_RA10

/*** Macros for B8 pin ***/
#define B8_Set()               (LATBSET = (1<<8))
#define B8_Clear()             (LATBCLR = (1<<8))
#define B8_Toggle()            (LATBINV= (1<<8))
#define B8_OutputEnable()      (TRISBCLR = (1<<8))
#define B8_InputEnable()       (TRISBSET = (1<<8))
#define B8_Get()               ((PORTB >> 8) & 0x1)
#define B8_PIN                  GPIO_PIN_RB8

/*** Macros for R4 pin ***/
#define R4_Set()               (LATFSET = (1<<3))
#define R4_Clear()             (LATFCLR = (1<<3))
#define R4_Toggle()            (LATFINV= (1<<3))
#define R4_OutputEnable()      (TRISFCLR = (1<<3))
#define R4_InputEnable()       (TRISFSET = (1<<3))
#define R4_Get()               ((PORTF >> 3) & 0x1)
#define R4_PIN                  GPIO_PIN_RF3

/*** Macros for LED pin ***/
#define LED_Set()               (LATASET = (1<<3))
#define LED_Clear()             (LATACLR = (1<<3))
#define LED_Toggle()            (LATAINV= (1<<3))
#define LED_OutputEnable()      (TRISACLR = (1<<3))
#define LED_InputEnable()       (TRISASET = (1<<3))
#define LED_Get()               ((PORTA >> 3) & 0x1)
#define LED_PIN                  GPIO_PIN_RA3

/*** Macros for LATCH pin ***/
#define LATCH_Set()               (LATASET = (1<<5))
#define LATCH_Clear()             (LATACLR = (1<<5))
#define LATCH_Toggle()            (LATAINV= (1<<5))
#define LATCH_OutputEnable()      (TRISACLR = (1<<5))
#define LATCH_InputEnable()       (TRISASET = (1<<5))
#define LATCH_Get()               ((PORTA >> 5) & 0x1)
#define LATCH_PIN                  GPIO_PIN_RA5

/*** Macros for ADDR_D pin ***/
#define ADDR_D_Set()               (LATDSET = (1<<9))
#define ADDR_D_Clear()             (LATDCLR = (1<<9))
#define ADDR_D_Toggle()            (LATDINV= (1<<9))
#define ADDR_D_OutputEnable()      (TRISDCLR = (1<<9))
#define ADDR_D_InputEnable()       (TRISDSET = (1<<9))
#define ADDR_D_Get()               ((PORTD >> 9) & 0x1)
#define ADDR_D_PIN                  GPIO_PIN_RD9

/*** Macros for B3 pin ***/
#define B3_Set()               (LATDSET = (1<<0))
#define B3_Clear()             (LATDCLR = (1<<0))
#define B3_Toggle()            (LATDINV= (1<<0))
#define B3_OutputEnable()      (TRISDCLR = (1<<0))
#define B3_InputEnable()       (TRISDSET = (1<<0))
#define B3_Get()               ((PORTD >> 0) & 0x1)
#define B3_PIN                  GPIO_PIN_RD0

/*** Macros for ADDR_B pin ***/
#define ADDR_B_Set()               (LATCSET = (1<<13))
#define ADDR_B_Clear()             (LATCCLR = (1<<13))
#define ADDR_B_Toggle()            (LATCINV= (1<<13))
#define ADDR_B_OutputEnable()      (TRISCCLR = (1<<13))
#define ADDR_B_InputEnable()       (TRISCSET = (1<<13))
#define ADDR_B_Get()               ((PORTC >> 13) & 0x1)
#define ADDR_B_PIN                  GPIO_PIN_RC13

/*** Macros for CLK pin ***/
#define CLK_Set()               (LATDSET = (1<<3))
#define CLK_Clear()             (LATDCLR = (1<<3))
#define CLK_Toggle()            (LATDINV= (1<<3))
#define CLK_OutputEnable()      (TRISDCLR = (1<<3))
#define CLK_InputEnable()       (TRISDSET = (1<<3))
#define CLK_Get()               ((PORTD >> 3) & 0x1)
#define CLK_PIN                  GPIO_PIN_RD3

/*** Macros for OE pin ***/
#define OE_Set()               (LATDSET = (1<<12))
#define OE_Clear()             (LATDCLR = (1<<12))
#define OE_Toggle()            (LATDINV= (1<<12))
#define OE_OutputEnable()      (TRISDCLR = (1<<12))
#define OE_InputEnable()       (TRISDSET = (1<<12))
#define OE_Get()               ((PORTD >> 12) & 0x1)
#define OE_PIN                  GPIO_PIN_RD12

/*** Macros for G2 pin ***/
#define G2_Set()               (LATDSET = (1<<13))
#define G2_Clear()             (LATDCLR = (1<<13))
#define G2_Toggle()            (LATDINV= (1<<13))
#define G2_OutputEnable()      (TRISDCLR = (1<<13))
#define G2_InputEnable()       (TRISDSET = (1<<13))
#define G2_Get()               ((PORTD >> 13) & 0x1)
#define G2_PIN                  GPIO_PIN_RD13

/*** Macros for ADDR_C pin ***/
#define ADDR_C_Set()               (LATDSET = (1<<4))
#define ADDR_C_Clear()             (LATDCLR = (1<<4))
#define ADDR_C_Toggle()            (LATDINV= (1<<4))
#define ADDR_C_OutputEnable()      (TRISDCLR = (1<<4))
#define ADDR_C_InputEnable()       (TRISDSET = (1<<4))
#define ADDR_C_Get()               ((PORTD >> 4) & 0x1)
#define ADDR_C_PIN                  GPIO_PIN_RD4

/*** Macros for G1 pin ***/
#define G1_Set()               (LATDSET = (1<<7))
#define G1_Clear()             (LATDCLR = (1<<7))
#define G1_Toggle()            (LATDINV= (1<<7))
#define G1_OutputEnable()      (TRISDCLR = (1<<7))
#define G1_InputEnable()       (TRISDSET = (1<<7))
#define G1_Get()               ((PORTD >> 7) & 0x1)
#define G1_PIN                  GPIO_PIN_RD7

/*** Macros for B2 pin ***/
#define B2_Set()               (LATGSET = (1<<1))
#define B2_Clear()             (LATGCLR = (1<<1))
#define B2_Toggle()            (LATGINV= (1<<1))
#define B2_OutputEnable()      (TRISGCLR = (1<<1))
#define B2_InputEnable()       (TRISGSET = (1<<1))
#define B2_Get()               ((PORTG >> 1) & 0x1)
#define B2_PIN                  GPIO_PIN_RG1

/*** Macros for R2 pin ***/
#define R2_Set()               (LATGSET = (1<<0))
#define R2_Clear()             (LATGCLR = (1<<0))
#define R2_Toggle()            (LATGINV= (1<<0))
#define R2_OutputEnable()      (TRISGCLR = (1<<0))
#define R2_InputEnable()       (TRISGSET = (1<<0))
#define R2_Get()               ((PORTG >> 0) & 0x1)
#define R2_PIN                  GPIO_PIN_RG0

/*** Macros for B1 pin ***/
#define B1_Set()               (LATASET = (1<<6))
#define B1_Clear()             (LATACLR = (1<<6))
#define B1_Toggle()            (LATAINV= (1<<6))
#define B1_OutputEnable()      (TRISACLR = (1<<6))
#define B1_InputEnable()       (TRISASET = (1<<6))
#define B1_Get()               ((PORTA >> 6) & 0x1)
#define B1_PIN                  GPIO_PIN_RA6

/*** Macros for R1 pin ***/
#define R1_Set()               (LATASET = (1<<7))
#define R1_Clear()             (LATACLR = (1<<7))
#define R1_Toggle()            (LATAINV= (1<<7))
#define R1_OutputEnable()      (TRISACLR = (1<<7))
#define R1_InputEnable()       (TRISASET = (1<<7))
#define R1_Get()               ((PORTA >> 7) & 0x1)
#define R1_PIN                  GPIO_PIN_RA7

/*** Macros for G3 pin ***/
#define G3_Set()               (LATESET = (1<<4))
#define G3_Clear()             (LATECLR = (1<<4))
#define G3_Toggle()            (LATEINV= (1<<4))
#define G3_OutputEnable()      (TRISECLR = (1<<4))
#define G3_InputEnable()       (TRISESET = (1<<4))
#define G3_Get()               ((PORTE >> 4) & 0x1)
#define G3_PIN                  GPIO_PIN_RE4


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/

typedef enum
{
    GPIO_PORT_A = 0,
    GPIO_PORT_B = 1,
    GPIO_PORT_C = 2,
    GPIO_PORT_D = 3,
    GPIO_PORT_E = 4,
    GPIO_PORT_F = 5,
    GPIO_PORT_G = 6,
} GPIO_PORT;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/

typedef enum
{
    GPIO_PIN_RA0 = 0,
    GPIO_PIN_RA1 = 1,
    GPIO_PIN_RA2 = 2,
    GPIO_PIN_RA3 = 3,
    GPIO_PIN_RA4 = 4,
    GPIO_PIN_RA5 = 5,
    GPIO_PIN_RA6 = 6,
    GPIO_PIN_RA7 = 7,
    GPIO_PIN_RA9 = 9,
    GPIO_PIN_RA10 = 10,
    GPIO_PIN_RA14 = 14,
    GPIO_PIN_RA15 = 15,
    GPIO_PIN_RB0 = 16,
    GPIO_PIN_RB1 = 17,
    GPIO_PIN_RB2 = 18,
    GPIO_PIN_RB3 = 19,
    GPIO_PIN_RB4 = 20,
    GPIO_PIN_RB5 = 21,
    GPIO_PIN_RB6 = 22,
    GPIO_PIN_RB7 = 23,
    GPIO_PIN_RB8 = 24,
    GPIO_PIN_RB9 = 25,
    GPIO_PIN_RB10 = 26,
    GPIO_PIN_RB11 = 27,
    GPIO_PIN_RB12 = 28,
    GPIO_PIN_RB13 = 29,
    GPIO_PIN_RB14 = 30,
    GPIO_PIN_RB15 = 31,
    GPIO_PIN_RC1 = 33,
    GPIO_PIN_RC2 = 34,
    GPIO_PIN_RC3 = 35,
    GPIO_PIN_RC4 = 36,
    GPIO_PIN_RC12 = 44,
    GPIO_PIN_RC13 = 45,
    GPIO_PIN_RC14 = 46,
    GPIO_PIN_RC15 = 47,
    GPIO_PIN_RD0 = 48,
    GPIO_PIN_RD1 = 49,
    GPIO_PIN_RD2 = 50,
    GPIO_PIN_RD3 = 51,
    GPIO_PIN_RD4 = 52,
    GPIO_PIN_RD5 = 53,
    GPIO_PIN_RD6 = 54,
    GPIO_PIN_RD7 = 55,
    GPIO_PIN_RD8 = 56,
    GPIO_PIN_RD9 = 57,
    GPIO_PIN_RD10 = 58,
    GPIO_PIN_RD11 = 59,
    GPIO_PIN_RD12 = 60,
    GPIO_PIN_RD13 = 61,
    GPIO_PIN_RD14 = 62,
    GPIO_PIN_RD15 = 63,
    GPIO_PIN_RE0 = 64,
    GPIO_PIN_RE1 = 65,
    GPIO_PIN_RE2 = 66,
    GPIO_PIN_RE3 = 67,
    GPIO_PIN_RE4 = 68,
    GPIO_PIN_RE5 = 69,
    GPIO_PIN_RE6 = 70,
    GPIO_PIN_RE7 = 71,
    GPIO_PIN_RE8 = 72,
    GPIO_PIN_RE9 = 73,
    GPIO_PIN_RF0 = 80,
    GPIO_PIN_RF1 = 81,
    GPIO_PIN_RF2 = 82,
    GPIO_PIN_RF3 = 83,
    GPIO_PIN_RF4 = 84,
    GPIO_PIN_RF5 = 85,
    GPIO_PIN_RF8 = 88,
    GPIO_PIN_RF12 = 92,
    GPIO_PIN_RF13 = 93,
    GPIO_PIN_RG0 = 96,
    GPIO_PIN_RG1 = 97,
    GPIO_PIN_RG2 = 98,
    GPIO_PIN_RG3 = 99,
    GPIO_PIN_RG6 = 102,
    GPIO_PIN_RG7 = 103,
    GPIO_PIN_RG8 = 104,
    GPIO_PIN_RG9 = 105,
    GPIO_PIN_RG12 = 108,
    GPIO_PIN_RG13 = 109,
    GPIO_PIN_RG14 = 110,
    GPIO_PIN_RG15 = 111,

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
    GPIO_PIN_NONE = -1

} GPIO_PIN;

typedef enum
{
  CN0_PIN = 1 << 0,
  CN1_PIN = 1 << 1,
  CN2_PIN = 1 << 2,
  CN3_PIN = 1 << 3,
  CN4_PIN = 1 << 4,
  CN5_PIN = 1 << 5,
  CN6_PIN = 1 << 6,
  CN7_PIN = 1 << 7,
  CN8_PIN = 1 << 8,
  CN9_PIN = 1 << 9,
  CN10_PIN = 1 << 10,
  CN11_PIN = 1 << 11,
  CN12_PIN = 1 << 12,
  CN13_PIN = 1 << 13,
  CN14_PIN = 1 << 14,
  CN15_PIN = 1 << 15,
  CN16_PIN = 1 << 16,
  CN17_PIN = 1 << 17,
  CN18_PIN = 1 << 18,
  CN19_PIN = 1 << 19,
  CN20_PIN = 1 << 20,
  CN21_PIN = 1 << 21,
}CN_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
    GPIO_PortWrite((GPIO_PORT)(pin>>4), (uint32_t)(0x1) << (pin & 0xF), (uint32_t)(value) << (pin & 0xF));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return (bool)(((GPIO_PortRead((GPIO_PORT)(pin>>4))) >> (pin & 0xF)) & 0x1);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (bool)((GPIO_PortLatchRead((GPIO_PORT)(pin>>4)) >> (pin & 0xF)) & 0x1);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
