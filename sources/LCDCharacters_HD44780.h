#ifndef LCDCHARACTERS_H_
#define LCDCHARACTERS_H_


//====== Header includes =======================================================


//====== Public Constants ======================================================
#define LCD__CHARACTER_ROW_SIZE (8u)


/*
 *******************************************************************************
 * BATTERY STATUS
 *******************************************************************************
 */
static const uint8 LCD_CharBatteryTop[LCD__CHARACTER_ROW_SIZE] =
{
    0b00011,
    0b00011,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b00011,
    0b00011
};

static const uint8 LCD_CharBatteryMiddle0[LCD__CHARACTER_ROW_SIZE] =
{
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111
};

static const uint8 LCD_CharBatteryMiddle1[LCD__CHARACTER_ROW_SIZE] =
{
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};

static const uint8 LCD_CharBatteryMiddleDisCharge[LCD__CHARACTER_ROW_SIZE] =
{
    0b11111,
	0b00011,
	0b00011,
	0b00111,
	0b00111,
	0b01111,
	0b01111,
	0b11111
};
        
static const uint8 LCD_CharBatteryMiddleCharge[LCD__CHARACTER_ROW_SIZE] =
{
    0b11111,
    0b11101,
    0b11011,
    0b10001,
    0b11011,
    0b10111,
    0b11111,
    0b11111
};

static const uint8 LCD_CharBatteryMiddleChargeInv[LCD__CHARACTER_ROW_SIZE] =
{
    0b11111,
    0b00010,
    0b00100,
    0b01110,
    0b00100,
    0b01000,
    0b00000,
    0b11111
};

static const uint8 LCD_CharBatteryBottom0[LCD__CHARACTER_ROW_SIZE] =
{
    0b11111,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b11111
};

static const uint8 LCD_CharBatteryBottomChargeInv[LCD__CHARACTER_ROW_SIZE] =
{
    0b11111,
    0b00011,
    0b00101,
    0b01111,
    0b00101,
    0b01001,
    0b00001,
    0b11111
};


//====== Public Signals ========================================================


//====== Public Functions ======================================================


#endif /* LCDCHARACTERS_H_ */
