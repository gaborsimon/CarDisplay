#ifndef TASKING_H_
#define TASKING_H_


//====== Header includes =======================================================
#include <avr/interrupt.h>

#include "typedef.h"

#include "LCDCharacters_HD44780.h"
#include "LCDDriver_HD44780.h"
#include "MicroControllerHAL.h"
//#include "RealTimeClock.h"
//#include "Sensor_GPS.h"
//#include "Sensor_DHT22.h"


//====== Public Constants ======================================================


//====== Public Signals ========================================================


//====== Public Functions ======================================================
#ifdef __cplusplus
extern "C" {
#endif

    extern void Task_Init(void);
    extern void Task_Main(void);

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* TASKING_H_ */
