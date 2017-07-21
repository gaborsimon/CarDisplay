//====== Header includes =======================================================
#include "Sensor_DHT22.h"


//====== Private Constants =====================================================
// Read sensor in every N second
#define L__DHT22_READ_PERIOD_SEC     (5u)

#define L__DHT22_BIT_TIME_THRESHOLD  (25u)
#define L__DHT22_DATA_BIT_COUNT      (40u)

// Port macros
#define L__DHT22_OUTPUT    MCH__GPIO_DIRECTION(MCH__DDR_DHT22, MCH__P_DHT22_DATA, U__OUTPUT)
#define L__DHT22_INPUT     MCH__GPIO_DIRECTION(MCH__DDR_DHT22, MCH__P_DHT22_DATA, U__INPUT)
#define L__DHT22_HIGH      MCH__GPIO_WRITE(MCH__PORT_DHT22, MCH__P_DHT22_DATA, U__HIGH)    
#define L__DHT22_LOW       MCH__GPIO_WRITE(MCH__PORT_DHT22, MCH__P_DHT22_DATA, U__LOW)    
#define L__DHT22_READ      MCH__GPIO_READ(MCH__PIN_DHT22, MCH__P_DHT22_DATA) 


//====== Private Signals =======================================================
typedef enum
{
    L_Error_NONE        = 1u,
    L_Error_CUT_OFF     = 2u,
    L_Error_CHECKSUM    = 3u
} L_Error_e;


//====== Private Function Prototypes ===========================================
static L_Error_e L_ReadSensor(void);


//====== Private Functions =====================================================
/*
 * Name: L_ReadSensor
 *
 * Description: The function reads out the temperature and relative humidity
*               data of DHT22 sensor via special 1-wire communication interface.
 *
 * Input: None
 *
 * Output: Error state
 */
static L_Error_e L_ReadSensor(void)
{
    uint8  _BitTime     = U__INIT_VALUE_UINT;
    uint8  _LoopCounter = U__INIT_VALUE_UINT;
    uint8  _CalcCS      = U__INIT_VALUE_UINT;
    uint16 _DataRH      = U__INIT_VALUE_UINT;
    uint16 _DataT       = U__INIT_VALUE_UINT;
    uint8  _DataCS      = U__INIT_VALUE_UINT;


    //****** STEP 1. **********************************************************/
    // Send activate signal
    L__DHT22_OUTPUT;
    L__DHT22_HIGH;
    _delay_ms(1u);
    L__DHT22_LOW;
    _delay_ms(10u);
    L__DHT22_HIGH;
    _delay_us(40u);
    L__DHT22_INPUT;

    //****** STEP 2. **********************************************************/
    // Find the start of the ACK signal
    _BitTime = U__INIT_VALUE_UINT;
    do
    {
        if (_BitTime > 50u)
        {
            return L_Error_CUT_OFF;
        }
        _BitTime++;
        _delay_us(1u);
    } while(L__DHT22_READ == U__HIGH);

    //****** STEP 3. **********************************************************/
    // Response signal: 80us LOW
    _BitTime = U__INIT_VALUE_UINT;
    do
    {
        if (_BitTime > 150u)
        {
            return L_Error_CUT_OFF;
        }
        _BitTime++;
        _delay_us(1u);
    } while(L__DHT22_READ == U__LOW);
    
    // Response signal: 80us HIGH
    _BitTime = U__INIT_VALUE_UINT;
    do
    {
        if (_BitTime > 150u)
        {
            return L_Error_CUT_OFF;
        }
        _BitTime++;
        _delay_us(1u);
    } while(L__DHT22_READ == U__HIGH);
    
    //****** STEP 4. **********************************************************/
    // Read the 40 bit data stream
    for(_LoopCounter = U__INIT_VALUE_UINT; _LoopCounter < L__DHT22_DATA_BIT_COUNT; _LoopCounter++)
    {
        // Measure the width of the data pulse
        _BitTime = U__INIT_VALUE_UINT;
        do
        {
            if (_BitTime > 150u)
            {
                return L_Error_CUT_OFF;
            }
            _BitTime++;
            _delay_us(1u);
        } while(L__DHT22_READ == U__LOW);

        // Measure the width of the data pulse
        _BitTime = U__INIT_VALUE_UINT;

        do
        {
            if (_BitTime > 150u)
            {
                return L_Error_CUT_OFF;
            }
            _BitTime++;
            _delay_us(1u);
        } while(L__DHT22_READ == U__HIGH);

        // Identify the bit values
        if (_BitTime > L__DHT22_BIT_TIME_THRESHOLD)
        {
            // Relative Humidity
            if (_LoopCounter < 16u)
            {
                _DataRH |= (1u << (15u - _LoopCounter));
            }
            // Temperature
            else if ((_LoopCounter > 15u) && (_LoopCounter < 32u))
            {
                _DataT |= (1u << (31u - _LoopCounter));
            }
            // Check Sum
            else if ((_LoopCounter > 31u) && (_LoopCounter < 40u))
            {
                _DataCS |= (1u << (39u - _LoopCounter));
            }
        }
    }

    //****** STEP 5. **********************************************************/
    // Release the bus - idle state
    L__DHT22_OUTPUT;
    L__DHT22_HIGH;

    //****** STEP 6. **********************************************************/
    // Calculate the Check Sum
    _CalcCS += ((uint8)((_DataRH & 0xFF00u) >> 8u));    
    _CalcCS += ((uint8) (_DataRH & 0x00FFu));    
    _CalcCS += ((uint8)((_DataT  & 0xFF00u) >> 8u));    
    _CalcCS += ((uint8) (_DataT  & 0x00FFu));    

    //****** STEP 7. **********************************************************/
    // Convert the raw data into physical values
    if(_DataCS == _CalcCS) 
    {
        DHT22_Data.HumidityValue    = ((float32)(_DataRH / 10.0f));
        DHT22_Data.TemperatureValue = ((float32)((_DataT & 0x7FFFu) / 10.0f));

        if(_DataT & 0x8000u)
        {
            DHT22_Data.TemperatureValue *= -1.0f;
        }

        return L_Error_NONE;
    }
    else
    {
        return L_Error_CHECKSUM;
    }
}


//====== Public Signals ========================================================
DHT22_Data_s DHT22_Data;


//====== Public Functions ======================================================
/*
 * Name: DHT22_Init
 *
 * Description: The function initializes the global variables.
 *
 * Input: None
 *
 * Output: None
 */
void DHT22_Init(void)
{
    DHT22_Data.Qualifier        = Signal_NOT_RELIABLE;
    DHT22_Data.TemperatureValue = U__INIT_VALUE_FLOAT;
    DHT22_Data.HumidityValue    = U__INIT_VALUE_FLOAT;
    DHT22_Data.Updated          = Flag_CLEAR;
}


/*
 * Name: DHT22_Refresh
 *
 * Description:  The function performs periodically the sensor read action
 *               trough an internal state machine.
 *
 * Input: None
 *
 * Output: None
 */
void DHT22_Refresh(void)
{
    static uint8        L_TickCounter   = U__INIT_VALUE_UINT;
           L_Error_e    _Res            = U__INIT_VALUE_UINT;


    L_TickCounter++;
    
    // Read out the conversion data
    if (L__DHT22_READ_PERIOD_SEC == L_TickCounter)
    {
        L_TickCounter = U__INIT_VALUE_UINT;
        
        _Res = L_ReadSensor();

        if (L_Error_NONE == _Res)
        {
            DHT22_Data.Qualifier = Signal_RELIABLE; 
        }
        else
        {
            DHT22_Data.Qualifier = Signal_NOT_RELIABLE; 
        }
        
        DHT22_Data.Updated = Flag_SET;
    }
    /* IDLE mode */
    else
    {
        DHT22_Data.Updated = Flag_CLEAR;
    }
}
