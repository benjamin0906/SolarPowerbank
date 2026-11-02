/*
 * OLED_Driver.h
 *
 *  Created on: 2026. okt. 21.
 *      Author: Benjamin
 */

#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_

#include "types.h"

typedef enum eOledMode
{
    OledMode_Off,
    OledMode_On
} dtOledMode;

extern void OLED_Driver_Runnable(void);
extern void OLED_Driver_Set(dtOledMode mode);
extern uint8 OLED_Driver_Running(void);
extern void OLED_Driver_PutString(uint8 *string);


#endif /* OLED_DRIVER_H_ */
