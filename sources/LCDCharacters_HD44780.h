#ifndef LCDCHARACTERS_H_
#define LCDCHARACTERS_H_


//====== Header includes =======================================================


//====== Public Constants ======================================================
#define LCD__CHARACTER_ROW_SIZE (8u)


/*
 *******************************************************************************
 * SUN TIME
 *******************************************************************************
 */
static const uint8 LCD_CharSunRise[LCD__CHARACTER_ROW_SIZE] =
{
    0b00100,
    0b01110,
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00000
};

static const uint8 LCD_CharSunSet[LCD__CHARACTER_ROW_SIZE] =
{
    0b00000,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b11111,
    0b01110,
    0b00100
};


/*
 *******************************************************************************
 * MOON
 *******************************************************************************
 */
static const uint8 LCD_CharMoonLeft100[LCD__CHARACTER_ROW_SIZE] =
{
    0b00011,
    0b00111,
    0b01111,
    0b01111,
    0b01111,
    0b01111,
    0b00111,
    0b00011
};

static const uint8 LCD_CharMoonLeft25[LCD__CHARACTER_ROW_SIZE] =
{
    0b00011,
    0b00110,
    0b01100,
    0b01100,
    0b01100,
    0b01100,
    0b00110,
    0b00011
};

static const uint8 LCD_CharMoonLeft75[LCD__CHARACTER_ROW_SIZE] =
{
    0b00011,
    0b00101,
    0b01011,
    0b01011,
    0b01011,
    0b01011,
    0b00101,
    0b00011
};

static const uint8 LCD_CharMoonLeft0[LCD__CHARACTER_ROW_SIZE] =
{
    0b00011,
    0b00100,
    0b01000,
    0b01000,
    0b01000,
    0b01000,
    0b00100,
    0b00011
};

static const uint8 LCD_CharMoonRight100[LCD__CHARACTER_ROW_SIZE] =
{
    0b11000,
    0b11100,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11100,
    0b11000
};

static const uint8 LCD_CharMoonRight25[LCD__CHARACTER_ROW_SIZE] =
{
    0b11000,
    0b01100,
    0b00110,
    0b00110,
    0b00110,
    0b00110,
    0b01100,
    0b11000
};

static const uint8 LCD_CharMoonRight75[LCD__CHARACTER_ROW_SIZE] =
{
    0b11000,
    0b10100,
    0b11010,
    0b11010,
    0b11010,
    0b11010,
    0b10100,
    0b11000
};

static const uint8 LCD_CharMoonRight0[LCD__CHARACTER_ROW_SIZE] =
{
    0b11000,
    0b00100,
    0b00010,
    0b00010,
    0b00010,
    0b00010,
    0b00100,
    0b11000
};


/*
 *******************************************************************************
 * DCF77
 *******************************************************************************
 */

static const uint8 LCD_CharGPSRxOK[LCD__CHARACTER_ROW_SIZE] =
{
    0b10101,
    0b10100,
    0b10011,
    0b01000,
    0b00111,
    0b00000,
    0b00000,
    0b0000
};

static const uint8 LCD_CharGPSRxNO[LCD__CHARACTER_ROW_SIZE] =
{
    0b00001,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};

/*
static const uint8 LCD_CharDCF77RxOK[LCD__CHARACTER_ROW_SIZE] =
{
    0b01110,
    0b10001,
    0b00100,
    0b01010,
    0b00000,
    0b00100,
    0b00100,
    0b00100
};

static const uint8 LCD_CharDCF77RxNO[LCD__CHARACTER_ROW_SIZE] =
{
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00100,
    0b00100,
    0b00100
};
*/

/*
 *******************************************************************************
 * BATTERY
 *******************************************************************************
 */
/*
static const uint8 LCD_CharBattery0[LCD__CHARACTER_ROW_SIZE] =
{
    0b01110,
    0b11011,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b11111
};

static const uint8 LCD_CharBattery10[LCD__CHARACTER_ROW_SIZE] =
{
    0b01110,
    0b11011,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
    0b11111
};

static const uint8 LCD_CharBattery30[LCD__CHARACTER_ROW_SIZE] =
{
    0b01110,
    0b11011,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
    0b11111,
    0b11111
};

static const uint8 LCD_CharBattery50[LCD__CHARACTER_ROW_SIZE] =
{
    0b01110,
    0b11011,
    0b10001,
    0b10001,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};

static const uint8 LCD_CharBattery70[LCD__CHARACTER_ROW_SIZE] =
{
    0b01110,
    0b11011,
    0b10001,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};

static const uint8 LCD_CharBattery90[LCD__CHARACTER_ROW_SIZE] =
{
    0b01110,
    0b11011,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};

static const uint8 LCD_CharBattery100[LCD__CHARACTER_ROW_SIZE] =
{
    0b01110,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};
*/


//====== Public Signals ========================================================


//====== Public Functions ======================================================


#endif /* LCDCHARACTERS_H_ */
