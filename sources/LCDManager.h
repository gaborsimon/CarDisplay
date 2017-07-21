#ifndef LCDMANAGER_H_
#define LCDMANAGER_H_


//====== Header includes =======================================================
#include <avr/pgmspace.h>

#include "typedef.h"

#include "LCDCharacters_HD44780.h"
#include "LCDDriver_HD44780.h"
#include "MicroControllerHAL.h"
#include "Sensor_DHT22.h"


//====== Public Constants ======================================================
#define LCM__WELCOME           (1u)
#define LCM__BATTERY           (2u)
#define LCM__DHT22             (3u)


//====== Public Signals ========================================================


//====== Public Functions ======================================================
#ifdef __cplusplus
extern "C" {
#endif

    extern void LCM_Init(void);
    extern void LCM_Refresh(uint8 _Element);

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* LCDMANAGER_H_ */
