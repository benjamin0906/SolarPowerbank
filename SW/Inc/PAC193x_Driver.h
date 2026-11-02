/*
 * PAC193x_Driver.h
 *
 *  Created on: 2026. okt. 22.
 *      Author: Benjamin
 */

#ifndef PAC193X_DRIVER_H_
#define PAC193X_DRIVER_H_

extern void PAC_193x_Driver_Runnable(void);
extern int32 PAC_193x_Driver_GetVSense(uint8 channel);
extern int32 PAC_193x_Driver_GetVBus(uint8 channel);

#endif /* PAC193X_DRIVER_H_ */
