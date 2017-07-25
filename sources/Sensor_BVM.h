#ifndef SENSORBVM_H_
#define SENSORBVM_H_


//====== Header includes =======================================================
#include "MicroControllerHAL.h"

#include "typedef.h"
#include "utils.h"


//====== Public Constants ======================================================


//====== Public Signals ========================================================
typedef struct
{
    float32         BatteryVoltage;
    G_Qualifier_e   Qualifier;
} BVM_Data_s;


#define XBVM__BATTERY_VOLTAGE   ((float32)         BVM_Data.BatteryVoltage)
#define XBVM__DATA_QUALIFIER    ((G_Qualifier_e)   BVM_Data.Qualifier)

extern BVM_Data_s BVM_Data;


//====== Public Functions ======================================================
#ifdef __cplusplus
extern "C" {
#endif

    extern void BVM_Init(void);
    extern void BVM_Refresh(void);

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* SENSORBVM_H_ */
