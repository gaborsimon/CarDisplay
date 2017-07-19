//====== Header includes =======================================================
#include "MicroControllerHAL.h"


//====== Private Constants =====================================================
#define L__I2C_TWSR_STATUS_MASK      (0xF8u)

#define L__I2C_STATUS_START          (0x08u)
#define L__I2C_STATUS_REP_START      (0x10u)
#define L__I2C_STATUS_W_ADDR_ACK     (0x18u)
#define L__I2C_STATUS_W_ADDR_NOTACK  (0x20u)
#define L__I2C_STATUS_W_DATA_ACK     (0x28u)
#define L__I2C_STATUS_W_DATA_NOTACK  (0x30u)
#define L__I2C_STATUS_ARBIT_LOST     (0x38u)
#define L__I2C_STATUS_R_ADDR_ACK     (0x40u)
#define L__I2C_STATUS_R_ADDR_NOTACK  (0x48u)
#define L__I2C_STATUS_R_DATA_ACK     (0x50u)
#define L__I2C_STATUS_R_DATA_NOTACK  (0x58u)

#define L__I2C_RETRY_MAX_NUMBER      (1000u)


//====== Private Signals =======================================================


//====== Private Function Prototypes ===========================================


//====== Private Functions =====================================================


//====== Public Signals ========================================================


//====== Public Functions ======================================================
/*
 * Name: MCH_InitPins
 *
 * Description: This function initializes uC pins by setting them to digital or
 *              analogue / input or output.
 *
 * Input: None
 *
 * Output: None
 */
void MCH_InitPins(void)
{
    /* GPS */
//    MCH__GPIO_DIRECTION  (MCH__DDR_GPS_CTRL,      MCH__P_GPS_CTRL,     U__OUTPUT);
//    MCH__GPIO_WRITE      (MCH__PORT_GPS_CTRL,     MCH__P_GPS_CTRL,     U__HIGH);

    /* DHT22 */
    MCH__GPIO_DIRECTION  (MCH__DDR_DHT22,         MCH__P_DHT22_DATA,   U__OUTPUT);
    MCH__GPIO_WRITE      (MCH__PORT_DHT22,        MCH__P_DHT22_DATA,   U__HIGH);

    /* LCD DISPLAY */
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,           MCH__P_LCD_RS,       U__OUTPUT);
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,           MCH__P_LCD_RW,       U__OUTPUT);
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,           MCH__P_LCD_EN,       U__OUTPUT);
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,           MCH__P_LCD_D4,       U__OUTPUT);
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,           MCH__P_LCD_D5,       U__OUTPUT);
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,           MCH__P_LCD_D6,       U__OUTPUT);
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,           MCH__P_LCD_D7,       U__OUTPUT);

    /* Battery Voltage Measurement */
    MCH__GPIO_DIRECTION  (MCH__DDR_BVM,           MCH__P_BVM,          U__INPUT);
}


/*
 * Name: MCH_InitWatchdog
 *
 * Description: This function initializes the Watchdog timer.
 *
 * Input: None
 *
 * Output: None
 */
/*
void MCH_InitWatchdog(void)
{
    // Watchdog Timeout by setting 1MHz clock prescaler: 111 = 2048K (2097152 cycles) = ~2.1sec
    U__BIT_SET(WDTCR, WDP2);
    U__BIT_SET(WDTCR, WDP1);
    U__BIT_SET(WDTCR, WDP0);
    
    // Watchdog enabled
    U__BIT_SET(WDTCR, WDE);
}
*/

/*
 * Name: MCH_InitSleepMode
 *
 * Description: This function initializes and enables the desired Sleep Mode of the device.
 *              In our application the "Power-save" mode shall be used because the main
 *              scheduler is clocked from the external watch-clock driven asynchronous
 *              Timer2.
 *
 * Input: None
 *
 * Output: None
 */
/*
void MCH_InitSleepMode(void)
{
    // Setting the "Power-save" mode in sleep mode
    U__BIT_CLR(MCUCR,SM2);
    U__BIT_SET(MCUCR,SM1);
    U__BIT_SET(MCUCR,SM0);
    
    // Enable the sleep mode
    U__BIT_SET(MCUCR,SE);
}
*/

/*
 * Name: MCH_InitTimer0
 *
 * Description: This function initializes the Timer0 peripheral
 *              for PWM generation of LCD backlight.
 *
 * Input: None
 *
 * Output: None
 */
/*
void MCH_InitTimer0(void)
{
    // Reset control register
    TCCR0 = 0x00u;
   
    // Waveform Generation Mode: 3 - Fast PWM, update of OCR0 at BOTTOM 
    U__BIT_SET(TCCR0, WGM01);
    U__BIT_SET(TCCR0, WGM00);
    
    // Compare Output Mode: Non-inverting - clear OC0 on compare match, Set OC0 at BOTTOM
    U__BIT_SET(TCCR0, COM01);
    U__BIT_CLR(TCCR0, COM00);

//TODO: Clarify this part of the code regarding PWM frequency
#define PWM_2

#ifdef PWM_1   
    // Clock Select: CLK / 64 => PWM frequency = 488Hz 
    U__BIT_CLR(TCCR0, CS02);
    U__BIT_SET(TCCR0, CS01);
    U__BIT_SET(TCCR0, CS00);
#endif

#ifdef PWM_2   
    // Clock Select: CLK / 256 => PWM frequency = 122Hz 
    U__BIT_SET(TCCR0, CS02);
    U__BIT_CLR(TCCR0, CS01);
    U__BIT_CLR(TCCR0, CS00);
#endif

#ifdef PWM_3   
    // Clock Select: CLK / 1024 => PWM frequency = 31Hz 
    U__BIT_SET(TCCR0, CS02);
    U__BIT_CLR(TCCR0, CS01);
    U__BIT_SET(TCCR0, CS00);
#endif

    // Reset Timer Register
    TCNT0 = 0u;
    // Reset Output Compare Register
    OCR0 = 0u;
    
    // Output Compare Match Interrupt: Disabled
    U__BIT_CLR(TIMSK, OCIE0);
    // Timer Overflow Interrupt: Disabled
    U__BIT_CLR(TIMSK, TOIE0);
}
*/

/*
 * Name: MCH_InitTimer1
 *
 * Description: This function initializes the Timer1 peripheral
 *              to generate the main tasking periode time of 1 second.
 *
 * Input: None
 *
 * Output: None
 */
void MCH_InitTimer1(void)
{
    // Reset control registers
    TCCR1A = 0x00u;
    TCCR1B = 0x00u;

    // Compare Output Mode for Channel A/B: Normal port operation, OC1A/OC1B disconnected
    U__BIT_CLR(TCCR1A, COM1A1);
    U__BIT_CLR(TCCR1A, COM1A0);
    U__BIT_CLR(TCCR1A, COM1B1);
    U__BIT_CLR(TCCR1A, COM1B0);

    // Waveform Generation Mode: CTC, update of OCR1x Immediate
    U__BIT_CLR(TCCR1B, WGM13);
    U__BIT_SET(TCCR1B, WGM12);
    U__BIT_CLR(TCCR1A, WGM11);
    U__BIT_CLR(TCCR1A, WGM10);
    
    // Input Capture Noise Canceler: Disabled
    U__BIT_CLR(TCCR1B, ICNC1);
    
    // Input Capture Edge Select: Falling (negative) edge
    U__BIT_CLR(TCCR1B, ICES1);
    
    // Clock Select: CLK / 256 = 46.875kHz = 21.33us
    U__BIT_SET(TCCR1B, CS12);
    U__BIT_CLR(TCCR1B, CS11);
    U__BIT_CLR(TCCR1B, CS10);
    
    // Reset Timer Register
    TCNT1 = 0u;
    // Set Output Compare Register for Channel A to 1sec
    OCR1A = 62500u;
    // Reset Output Compare Register for Channel B
    OCR1B = 0u;

    // Timer Input Capture Interrupt: Disabled
    U__BIT_CLR(TIMSK1, ICIE1);
    // Output Compare A Match Interrupt: Enabled
    U__BIT_SET(TIMSK1, OCIE1A);
    // Output Compare B Match Interrupt: Disabled
    U__BIT_CLR(TIMSK1, OCIE1B);
    // Timer Overflow Interrupt: Disabled
    U__BIT_CLR(TIMSK1, TOIE1);
}


/*
 * Name: MCH_InitTimer2
 *
 * Description: This function initializes the Timer2 peripheral for
 *              the main scheduler for counting seconds.
 *              It has its own external watch crystal (32.768kHz) clock source.
 *
 * Input: None
 *
 * Output: None
 */
/*
void MCH_InitTimer2(void)
{
    // Reset control registers
    TCCR2 = 0x00u;
    ASSR  = 0x00u;

    // Waveform Generation Mode: Normal, update of OCR2 Immediate
    U__BIT_CLR(TCCR2, WGM21);
    U__BIT_CLR(TCCR2, WGM20);

    // Compare Output Mode: Normal port operation, OC2 disconnected
    U__BIT_CLR(TCCR2, COM21);
    U__BIT_CLR(TCCR2, COM20);

    // Clock Celect: CLK / 128 = 256Hz = 3.90625ms
    U__BIT_SET(TCCR2, CS22);
    U__BIT_CLR(TCCR2, CS21);
    U__BIT_SET(TCCR2, CS20);

    // Reset Timer Register
    TCNT2 = 0u;
    // Reset Output Compare Register
    OCR2 = 0u;

    // Asynchronous Timer2: Clocked from external Crystal Oscillator connected to TOSC1 pin
    U__BIT_SET(ASSR,AS2);

    // Output Compare Match Interrupt: Disabled
    U__BIT_CLR(TIMSK, OCIE2);
    // Timer Overflow Interrupt: Enabled
    U__BIT_SET(TIMSK, TOIE2);
}
*/

/*
 * Name: MCH_InitADC
 *
 * Description: This function initializes the ADC peripheral of the MCU.
 *
 * Input:  None
 *
 * Output: None
 */
void MCH_InitADC(void)
{
    // Reset control registers
    ADMUX  = 0x00u;
    ADCSRA = 0x00u; 
    
    // Reference Selection: AVcc with external capacitor at VREF pin
    U__BIT_CLR(ADMUX, REFS1);
    U__BIT_SET(ADMUX, REFS0);
    
    // ADC Left Adjust Result: Enabled
    U__BIT_CLR(ADMUX, ADLAR);
    
    // Analog Channel and Gain Selection Bits: Single mode
    U__BIT_CLR(ADMUX, MUX3);
    U__BIT_CLR(ADMUX, MUX2);
    U__BIT_CLR(ADMUX, MUX1);
    U__BIT_CLR(ADMUX, MUX0);

    // ADC Auto Trigger: Disabled 
    U__BIT_CLR(ADCSRA, ADATE);
    
    // ADC Interrupt: Disabled
    U__BIT_CLR(ADCSRA, ADIE);
    
    // ADC Prescaler Select: CLK / 128 = 93.75kHz
    U__BIT_SET(ADCSRA, ADPS2);
    U__BIT_SET(ADCSRA, ADPS1);
    U__BIT_SET(ADCSRA, ADPS0);
   
    // ADC: Enabled
    U__BIT_SET(ADCSRA, ADEN); 
}


/*
 * Name: MCH_ReadADC
 *
 * Description: This function performs an AD conversion with the given channel.
 *              The result is stored in 8-bit precision (lower 2 bits of 10-bit ADC are not used).
 *
 * Input:  Desired AD input channel
 *
 * Output: Result of the AD conversion with 8-bit precision
 */
uint16 MCH_ReadADC(uint8 _Channel)
{
    uint16 _Ret = U__INIT_VALUE_UINT;


    // Only the 7 single channels can be selected
    _Channel &= 0x07u;

    // Set the desired channel
    ADMUX = (ADMUX & 0xF8u) | _Channel;

    // Start AD conversion
    U__BIT_SET(ADCSRA, ADSC);
    
    // Wait for the conversion to complete
    loop_until_bit_is_clear(ADCSRA, ADSC);

    //_Ret = (uint16)((uint16)(ADCL) | (uint16)(ADCH << 8u));
    _Ret = (uint16)(ADCL | ADCH << 8u);
//_Ret = ADCH;

    return _Ret;
}


/*
 * Name: MCH_InitUSART
 *
 * Description: This function initializes the USART peripheral of the MCU.
 *
 * Input: intended baud rate of the USART in bps dimension
 *
 * Output: None
 */
/*
void MCH_InitUSART(uint32 _Baud)
{
    uint16 _UBRR = U__INIT_VALUE_UINT;
    

    // Setting the USART Baud Rate Register 
    _UBRR = (uint16)((F_CPU / 16u / _Baud) - 1u);
    UBRRH = (uint8)(_UBRR >> 8u);
    UBRRL = (uint8)(_UBRR);
*/   
    /* IMPORTANT: UCSRC has to be written in a special way!
     * The UBRRH Register shares the same I/O location as the UCSRC Register. Therefore some special
     * consideration must be taken when accessing this I/O location.
     * When doing a write access of this I/O location, the high bit of the value written, the USART Register Select
     * (URSEL) bit, controls which one of the two registers that will be written. If URSEL is zero during a write
     * operation, the UBRRH value will be updated. If URSEL is one, the UCSRC setting will be updated.
     * This has to be performed in an atomic register write.
     */
/*
    // Asynchronous USART
    // 8-bit data mode
    // 1 stop bit
    // Parity mode disabled 
    UCSRC = (1u << URSEL) | (1u << UCSZ1) | (1u << UCSZ0);

    // Enable interrupt for RX line
    U__BIT_SET(UCSRB, RXCIE);

    // Enable the Receiver module
    U__BIT_SET(UCSRB, RXEN);
}
*/

/*
 * Name: MCH_InitI2C
 *
 * Description: This function initializes the I2C peripheral of the MCU.
 *
 * Input: clock frequency of the I2C in kHz dimension
 *
 * Output: None
 */
/*
void MCH_InitI2C(uint16 _SCLFreqKHZ)
{
    // Enable internal pull-up resistors
    U__BIT_CLR(MCH__DDR_I2C,  MCH__P_I2C_SCL);
    U__BIT_SET(MCH__PORT_I2C, MCH__P_I2C_SCL);
    U__BIT_CLR(MCH__DDR_I2C,  MCH__P_I2C_SDA);
    U__BIT_SET(MCH__PORT_I2C, MCH__P_I2C_SDA);

    // Reset control registers
    TWBR = 0x00u;
    TWCR = 0x00u;
    
    // Bit Rate Register
    // SCL [Hz] = CPU [Hz] / (16 + 2x(TWBR)x4^(TWPS))
    // 100 kHz => BitRate = 18 / Prescaler = 1
    TWBR = (uint8)((((uint8)(F_CPU / 1000UL / _SCLFreqKHZ)) - 16u) / 2u);
    
    // TWI Acknowledge: Enabled
    U__BIT_SET(TWCR, TWEA);
    // TWI: Enabled
    U__BIT_SET(TWCR, TWEN);

    // TWI Interrupt: Disabled
    U__BIT_CLR(TWCR, TWIE);    
   
    // TWI Prescaler: 1 
    U__BIT_CLR(TWSR, TWPS0);
    U__BIT_CLR(TWSR, TWPS1);
}
*/

/*
 * Name: MCH_I2CStart
 *
 * Description: This function starts a read or write I2C package.
 *
 * Input: address of the I2C peripheral
 *        type of package (read or write)
 *
 * Output: status of the I2C action (ERROR or NO_ERROR)
 */
/*
uint8 MCH_I2CStart(uint8 _Address, uint8 _ReadWrite)
{
    uint8 _Status               = U__INIT_VALUE_UINT;
    uint8 _Res                  = MCH__I2C_ERROR;
    static uint16 L_LoopCounter = U__INIT_VALUE_UINT;

    
    _Address |= _ReadWrite;

    // Repeat start 1000 times if it is needed
    for (L_LoopCounter = 0u; L_LoopCounter < L__I2C_RETRY_MAX_NUMBER; L_LoopCounter++)
    {
        // Send START condition
        U__BIT_SET(TWCR, TWSTA);
        U__BIT_SET(TWCR, TWINT);
        U__BIT_SET(TWCR, TWEA);
        U__BIT_SET(TWCR, TWEN);
        
        loop_until_bit_is_set(TWCR,TWINT);

        _Status = TWSR & L__I2C_TWSR_STATUS_MASK;
        
        if ((L__I2C_STATUS_START     == _Status) ||
            (L__I2C_STATUS_REP_START == _Status))
        {
            TWDR = _Address;
            
            U__BIT_CLR(TWCR, TWSTA);
            U__BIT_SET(TWCR, TWINT);
            U__BIT_SET(TWCR, TWEA);
            U__BIT_SET(TWCR, TWEN);
            
            loop_until_bit_is_set(TWCR,TWINT);
            
            _Status = TWSR & L__I2C_TWSR_STATUS_MASK;
            
            if ( ((MCH__I2C_START_WRITE == _ReadWrite) && (L__I2C_STATUS_W_ADDR_ACK == _Status)) ||
                 ((MCH__I2C_START_READ  == _ReadWrite) && (L__I2C_STATUS_R_ADDR_ACK == _Status)) )
            {
                return MCH__I2C_NO_ERROR;
            }
            else
            {
                _Res = MCH__I2C_ERROR;
            }

            L_LoopCounter = 2000u;
        }
    }

    _Res = MCH__I2C_ERROR;

    return _Res;
}
*/

/*
 * Name: MCH_I2CWrite
 *
 * Description: This function writes a byte to the I2C peripheral.
 *
 * Input: 8-bit data
 *
 * Output: status of the I2C action (ERROR or NO_ERROR)
 */
/*
uint8 MCH_I2CWrite(uint8 _Data)
{
    uint8 _Status   = U__INIT_VALUE_UINT;
    uint8 _Res      = MCH__I2C_ERROR;

    
    TWDR = _Data;
    
    U__BIT_SET(TWCR, TWINT);
    U__BIT_SET(TWCR, TWEA);
    U__BIT_SET(TWCR, TWEN);
    
    loop_until_bit_is_set(TWCR, TWINT);

    _Status = TWSR & L__I2C_TWSR_STATUS_MASK;
    
    if (L__I2C_STATUS_W_DATA_ACK == _Status)
    {
        _Res = MCH__I2C_NO_ERROR;
    }
    else
    {
        _Res = MCH__I2C_ERROR;
    }

    return _Res;
}
*/

/*
 * Name: MCH_I2CRead
 *
 * Description: This function reads a data byte from the I2C peripheral.
 *
 * Input: pointer to the 8-bit data
 *        status of the read command (PENDING or STOP)
 *
 * Output: status of the I2C action (ERROR or NO_ERROR)
 */
/*
void MCH_I2CRead(uint8 *_Data, uint8 _ReadStatus)
{
    switch (_ReadStatus)
    {
        case MCH__I2C_READ_PENDING:
        {
            U__BIT_SET(TWCR, TWEA);
        }
        break;

        case MCH__I2C_READ_STOP:
        {
            U__BIT_CLR(TWCR, TWEA);
        }
        break;
        
        default:
        {
*/
            /* Nothing to do */
/*
}
        break;
    }
    U__BIT_SET(TWCR, TWINT);
    U__BIT_SET(TWCR, TWEN);

    loop_until_bit_is_set(TWCR, TWINT);

    *_Data = ((sint8) TWDR);
}
*/

/*
 * Name: MCH_I2CStop
 *
 * Description: This function stops the communication with I2C peripheral.
 *
 * Input: None
 *
 * Output: None
 */
/*
void MCH_I2CStop(void)
{
    U__BIT_SET(TWCR, TWSTO);
    U__BIT_SET(TWCR, TWEA);
    U__BIT_SET(TWCR, TWINT);
    U__BIT_SET(TWCR, TWEN);

    loop_until_bit_is_clear(TWCR, TWSTO);
}
*/
