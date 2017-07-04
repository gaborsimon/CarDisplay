//====== Header includes =======================================================
#include "LCDDriver_HD44780.h"


//====== Private Constants =====================================================
// LCD size (e.g.: 4x20)
#define L__DISPLAY_ROW ( 2u)
#define L__DISPLAY_COL (16u)

// Commands
#define L__CMD_CLEAR_DISPLAY     (0x01u)
#define L__CMD_RETURN_HOME       (0x02u)
#define L__CMD_ENTRY_MODE_SET    (0x04u)
#define L__CMD_DISPLAY_CONTROL   (0x08u)
#define L__CMD_CURSOR_SHIFT      (0x10u)
#define L__CMD_FUNCTION_SET      (0x20u)
#define L__CMD_SET_CGRAM         (0x40u)
#define L__CMD_SET_DDRAM         (0x80u)

// Entry mode set configurations
#define L__ENTRY_MODE_INCREMENT  (0x02u)
#define L__ENTRY_MODE_DECREMENT  (0x00u)

// Display control configurations
#define L__DISPLAY_ON            (0x04u)
#define L__DISPLAY_OFF           (0x00u)
#define L__CURSOR_ON             (0x02u)
#define L__CURSOR_OFF            (0x00u)
#define L__CURSOR_BLINK_ON       (0x01u)
#define L__CURSOR_BLINK_OFF      (0x00u)

// Cursor shift control configurations
#define L__DISPLAY_SHIFT         (0x08u)
#define L__CURSOR_MOVE           (0x00u)
#define L__SHIFT_TO_RIGHT        (0x04u)
#define L__SHIFT_TO_LEFT         (0x00u)

// Function set configuration
#define L__FUNCTION_8BIT_MODE    (0x10u)
#define L__FUNCTION_4BIT_MODE    (0x00u)
#define L__FUNCTION_2LINE        (0x08u)
#define L__FUNCTION_1LINE        (0x00u)
#define L__FUNCTION_5x10_DOTS    (0x04u)
#define L__FUNCTION_5x8_DOTS     (0x00u)

#define L__RS_COMMAND (0u)
#define L__RS_DATA    (1u)
#define L__RW_WRITE   (0u)
#define L__RW_READ    (1u)

#define L__COMMAND        (0u)
#define L__DATA           (1u)


//====== Private Signals =======================================================


//====== Private Function Prototypes ===========================================
static void L_EnableTransfer(void);
static void L_Send(uint8 type, uint8 package);


//====== Private Functions =====================================================
/*
 * Name: L_EnableTransfer
 *
 * Description: This function sends an enable pulse to the LCD controller in
 *              order to confirm a data/command transfer.
 *              Execution time: ~100us
 *
 * Input: None
 *
 * Output: None
 */
static void L_EnableTransfer(void)
{
    // Enable the sending
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_EN, U__LOW);
    _delay_us(1u);

    // EN pulse shall be greater than 450ns
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_EN, U__HIGH);
    _delay_us(1u);

    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_EN, U__LOW);

    // Commands need more than 37us to settle
    _delay_us(100u);
}


/*
 * Name: L_Send
 *
 * Description: This function sends the given command or data to the LCD
 *              controller in 4-bit mode.
 *              Execution time: ~200us
 *
 * Input: type - command or data
          package - sent command or data
 *
 * Output: None
 */
static void L_Send(uint8 type, uint8 package)
{

    // Command/Data & Write
    switch (type)
    {
        case L__COMMAND:
        {
            MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_RS, L__RS_COMMAND);
        }
        break;

        case L__DATA:
        {
            MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_RS, L__RS_DATA);
        }
        break;
    }
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_RW, L__RW_WRITE);

    // Just to be sure, set data pins to output
    MCH__GPIO_DIRECTION(MCH__DDR_LCD, MCH__P_LCD_D4, U__OUTPUT);
    MCH__GPIO_DIRECTION(MCH__DDR_LCD, MCH__P_LCD_D5, U__OUTPUT);
    MCH__GPIO_DIRECTION(MCH__DDR_LCD, MCH__P_LCD_D6, U__OUTPUT);
    MCH__GPIO_DIRECTION(MCH__DDR_LCD, MCH__P_LCD_D7, U__OUTPUT);

    // Send the MSB 4 bits
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_D4, ((package >> 4u) & 0x01u));
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_D5, ((package >> 5u) & 0x01u));
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_D6, ((package >> 6u) & 0x01u));
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_D7, ((package >> 7u) & 0x01u));

    L_EnableTransfer();

    // Send the LSB 4 bits
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_D4, ((package >> 0u) & 0x01u));
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_D5, ((package >> 1u) & 0x01u));
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_D6, ((package >> 2u) & 0x01u));
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_D7, ((package >> 3u) & 0x01u));

    L_EnableTransfer();
}


//====== Public Signals ========================================================


//====== Public Functions ======================================================
/*
 * Name: LCD_Init
 *
 * Description: This function initializes the LCD controller (panel) according
 *              to the datasheet/manual of HD44780 controller.
 *              Execution time: ~65ms
 *
 * Input: None
 *
 * Output: None
 */
void LCD_Init(void)
{
    //****** STEP 1. **********************************************************/
    // Wait more than 15ms after Vdd rises to 4.5V
    _delay_ms(50u);

    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_RS, U__LOW);
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_RW, U__LOW);
    MCH__GPIO_WRITE(MCH__PORT_LCD, MCH__P_LCD_EN, U__LOW);

    //****** STEP 2. **********************************************************/
    // 4-bit mode initialization according to datasheet p46
    L_Send(L__COMMAND, 0x03u);
    _delay_ms(5u);
    L_Send(L__COMMAND, 0x03u);
    _delay_ms(5u);
    L_Send(L__COMMAND, 0x03u);
    _delay_us(500u);
    L_Send(L__COMMAND, 0x02u);

    //****** STEP 3. **********************************************************/
    // Function set: 0 0 1 DL N F 0 0
    //                      | | |------ = 0 : 5x8 dots character font
    //                      | |-------- = 1 : 2-line mode
    //                      |---------- = 0 : 4-bit mode
    L_Send(L__COMMAND,
           L__CMD_FUNCTION_SET   |
           L__FUNCTION_4BIT_MODE |
           L__FUNCTION_2LINE     |
           L__FUNCTION_5x8_DOTS);

    //****** STEP 4. **********************************************************/
    // Display control: 0 0 0 0 1 D C B
    //                            | | |-- = 0 : Cursor Blink OFF
    //                            | |---- = 0 : Cursor OFF
    //                            |------ = 0 : Display OFF
    L_Send(L__COMMAND,
           L__CMD_DISPLAY_CONTROL |
           L__DISPLAY_OFF         |
           L__CURSOR_OFF          |
           L__CURSOR_BLINK_OFF);

    //****** STEP 5. **********************************************************/
    // Display clear
    LCD_Clear();

    //****** STEP 6. **********************************************************/
    // Entry mode set: 0 0 0 0 0 0 1 I/D S
    //                                |  |-- = 0 : Cursor moves not the display
    //                                |----- = 1 : Increment cursor move
    L_Send(L__COMMAND,
           L__CMD_ENTRY_MODE_SET   |
           L__ENTRY_MODE_INCREMENT |
           L__CURSOR_MOVE);
}


/*
 * Name: LCD_SwitchOn
 *
 * Description: This function turns on the LCD display. Remained data - if there
 *              is any - will be shown again.
 *
 * Input: None
 *
 * Output: None
 */
void LCD_SwitchOn(void)
{
    L_Send(L__COMMAND, L__CMD_DISPLAY_CONTROL | L__DISPLAY_ON);
}


/*
 * Name: LCD_SwitchOff
 *
 * Description: This function turns off the LCD display. Data remains after it
 *              will be turned on.
 *
 * Input: None
 *
 * Output: None
 */
void LCD_SwitchOff(void)
{
    L_Send(L__COMMAND, L__CMD_DISPLAY_CONTROL | L__DISPLAY_OFF);
}


/*
 * Name: LCD_Clear
 *
 * Description: This function clears the LCD display and sets the cursor
 *              to home position.
 *
 * Input: None
 *
 * Output: None
 */
void LCD_Clear(void)
{
    L_Send(L__COMMAND, L__CMD_CLEAR_DISPLAY);
    _delay_ms(2u);
}


/*
 * Name: LCD_SetCursor
 *
 * Description: This function sets the cursor to the given position.
 *              If the given position is out of the configured size than they
 *              will be set to the maximum (saturation).
 *              Function support currently only 4x20 display.
 *
 * Input: Row    - counted from 1
 *        Column - counted from 1
 *
 * Output: None
 */
void LCD_SetCursor(uint8 _Row, uint8 _Column)
{
    uint8 _PositionAddress = U__INIT_VALUE_UINT;


    // Saturation of row and column
    if (_Row    > L__DISPLAY_ROW) { _Row    = L__DISPLAY_ROW; }
    if (_Column > L__DISPLAY_COL) { _Column = L__DISPLAY_COL; }

    // Setting the row DDRAM address
    switch (_Row)
    {
      case 1u: { _Row = 0x00u; } break;
      case 2u: { _Row = 0x40u; } break;
      case 3u: { _Row = 0x14u; } break;
      case 4u: { _Row = 0x54u; } break;
    }

    // Setting the column DDRAM address
    _Column--;

    // Calculation of the DDRAM address
    _PositionAddress = _Row + _Column;

    // Sending the DDRAM address to the LCD controller
    L_Send(L__COMMAND, L__CMD_SET_DDRAM | _PositionAddress);
}


/*
 * Name: LCD_WriteChar
 *
 * Description: This function writes only one ASCII character to the display.
 *
 * Input: ASCII Character
 *
 * Output: None
 */
void LCD_WriteChar(uint8 _Character)
{
    L_Send(L__DATA, _Character);
}


/*
 * Name: LCD_WriteString
 *
 * Description: This function writes an ASCII string to the display.
 *
 * Input: ASCII String
 *
 * Output: None
 */
void LCD_WriteString(const char* _PoiString)
{
    while(*_PoiString)
    {
        LCD_WriteChar(*_PoiString);
        _PoiString++;
    }
}


void LCD_WriteStringM(const char* _PoiString)
{
    while(pgm_read_byte(_PoiString))
    {
        LCD_WriteChar(pgm_read_byte(_PoiString));
        _PoiString++;
    }
}


/*
 * Name: LCD_WriteInt
 *
 * Description: This function writes a signed integer number to the display.
 *
 * Input: Number (-32768 .. 32767)
 *
 * Output: None
 */
void LCD_WriteInt(sint16 _Number)
{
    char _String[L__DISPLAY_COL];


    itoa(_Number, _String, 10);
    LCD_WriteString(_String);
}


/*
 * Name: LCD_StoreCustomChar
 *
 * Description: This function stores a predefined custom character into the
 *              given CGRAM address of the LCD controller.
 *              CGRAM can be 0..7.
 *
 * Input: Location of character (0..7)
 *        Predefined character map array
 *
 * Output: None
 */
void LCD_StoreCustomChar(uint8 _Location, const uint8 _CustomCharMap[])
{
    uint8 _LoopCounter = U__INIT_VALUE_UINT;


    _Location &= 0x07u;

    L_Send(L__COMMAND, L__CMD_SET_CGRAM | (_Location << 3u));

    for (_LoopCounter = 0u; _LoopCounter < 8u; _LoopCounter++)
    {
        L_Send(L__DATA, _CustomCharMap[_LoopCounter]);
    }
}


/*
 * Name: LCD_WriteCustomChar
 *
 * Description: This function writes a stored custom character to the display
 *              addressed by the CGRAM location (0..7).
 *
 * Input: CGRAM location (0..7)
 *
 * Output: None
 */
void LCD_WriteCustomChar(uint8 _Location)
{
    L_Send(L__DATA, _Location);
}
