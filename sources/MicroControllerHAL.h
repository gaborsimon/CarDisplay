#ifndef MICROCONTROLLERHAL_H_
#define MICROCONTROLLERHAL_H_


//====== Header includes =======================================================
#include <avr/io.h>

#include "typedef.h"
#include "utils.h"


//====== Public Constants ======================================================
/******************************************************************************/
/****** PROCESSOR CONFIGURATION */
/******************************************************************************/
#define F_CPU (16000000UL)

/******************************************************************************/
/****** PIN CONFIGURATION */
/******************************************************************************/
//TODO: Verify the pin configuration
/* GPS module */

#define MCH__P_GPS_DATA         (PD0)   /* PIN 030 */
#define MCH__DDR_GPS            (DDRD)
#define MCH__PIN_GPS            (PIND)

/* LCD panel */
#define MCH__P_LCD_RS           (PD1)   /* PIN 031 */
#define MCH__P_LCD_RW           (PD2)   /* PIN 032 */
#define MCH__P_LCD_EN           (PD3)   /* PIN 001 */
#define MCH__P_LCD_D4           (PD4)   /* PIN 002 */
#define MCH__P_LCD_D5           (PD5)   /* PIN 009 */
#define MCH__P_LCD_D6           (PD6)   /* PIN 010 */
#define MCH__P_LCD_D7           (PD7)   /* PIN 011 */
#define MCH__DDR_LCD            (DDRD)
#define MCH__PIN_LCD            (PIND)
#define MCH__PORT_LCD           (PORTD)

/* DHT22 */
#define MCH__P_DHT22_DATA       (PB0)   /* PIN 012 */
#define MCH__DDR_DHT22          (DDRB)
#define MCH__PIN_DHT22          (PINB)
#define MCH__PORT_DHT22         (PORTB)

/* Battery Voltage Measurement */
#define MCH__P_BVM              (PC0)   /* PIN 023 */
#define MCH__DDR_BVM            (DDRC)

/******************************************************************************/
/****** PIN CONTROL */
/******************************************************************************/
#define MCH__GPIO_DIRECTION(ddr, p, dir)    ((dir)   ? U__BIT_SET((ddr),  (p)) : U__BIT_CLR((ddr),  (p)))
#define MCH__GPIO_WRITE(port, p, value)     ((value) ? U__BIT_SET((port), (p)) : U__BIT_CLR((port), (p)))
#define MCH__GPIO_READ(pin, p)              (U__BIT_GET((pin), (p)))

/******************************************************************************/
/****** PERIPHERAL CONSTANTS */
/******************************************************************************/
/* ADC */
#define MCH__ADC_CHANNEL_0       (0u)
#define MCH__ADC_CHANNEL_1       (1u)
#define MCH__ADC_CHANNEL_2       (2u)
#define MCH__ADC_CHANNEL_3       (3u)
#define MCH__ADC_CHANNEL_4       (4u)
#define MCH__ADC_CHANNEL_5       (5u)
#define MCH__ADC_CHANNEL_6       (6u)
#define MCH__ADC_CHANNEL_7       (7u)

/* I2C */
#define MCH__I2C_START_READ      (1u)
#define MCH__I2C_START_WRITE     (0u)
#define MCH__I2C_READ_PENDING    (1u)
#define MCH__I2C_READ_STOP       (2u)
#define MCH__I2C_NO_ERROR        (1u)
#define MCH__I2C_ERROR           (2u)


/******************************************************************************/
/****** ASSEMBLY INSTRUCTIONS */
/******************************************************************************/
#define MCH__INTERRUPT_ENABLED()    __asm__ __volatile__("sei")
#define MCH__INTERRUPT_DISABLED()   __asm__ __volatile__("cli")
#define MCH__WD_RESET()             __asm__ __volatile__("wdr")
#define MCH__SLEEP()                __asm__ __volatile__("sleep")


//====== Public Signals ========================================================


//====== Public Functions ======================================================
#ifdef __cplusplus
extern "C" {
#endif

    extern void  MCH_InitPins(void);
    extern void  MCH_InitWatchdog(void);
    extern void  MCH_InitSleepMode(void);
    extern void  MCH_InitTimer0(void);
    extern void  MCH_InitTimer1(void);
    extern void  MCH_InitTimer2(void);
    extern void  MCH_InitADC(void);
    extern uint16 MCH_ReadADC(uint8 _Channel);
    extern void  MCH_InitUSART(uint32 _Baud);
    extern void  MCH_InitI2C(uint16 _SCLFreqKHZ);
    extern uint8 MCH_I2CStart(uint8 _Address, uint8 _ReadWrite);
    extern uint8 MCH_I2CWrite(uint8 _Data);
    extern void  MCH_I2CRead(uint8 *_Data, uint8 _ReadStatus);
    extern void  MCH_I2CStop(void);

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* MICROCONTROLLERHAL_H_ */
