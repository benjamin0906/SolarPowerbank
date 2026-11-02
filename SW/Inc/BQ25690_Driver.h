/*
 * BQ25690_Driver.h
 *
 *  Created on: 2026. okt. 22.
 *      Author: Benjamin
 */

#ifndef BQ25690_DRIVER_H_
#define BQ25690_DRIVER_H_

#include "types.h"

typedef struct sBqInfo
{
    uint16 VSYSMIN;
    uint16 ICHG;
    uint16 VREG;
    uint16 IINDPM;
    uint16 VINDPM;
    uint16 IPRECHG;
    uint16 ITERM;
    uint32 Fsw :3;
    uint32 Vchg_pin :3;
    uint32 Cell_pin :3;
    uint32 Ichg_pin :3;
    uint32 PG_stat  :1;
    uint32 Iindpm_stat :1;
    uint32 Vindpm_stat :1;
    uint32 Treg_stat   :1;
    uint32 Charge_stat :3;
    uint32 ICO_stat    :2;
    uint32 TS_stat     :3;
    uint32 Vin_OVP_Fault    :1;
    uint32 BAT_Fault        :1;
    uint32 CHG_TMR_Fault    :1;
    uint32 CV_TMR_Fault     :1;
    uint32 T_SHUT_Fault     :1;
} dtBqInfo;

extern void BQ25690_Runnable(void);
extern dtBqInfo BQ25690_GetInfo(void);

#endif /* BQ25690_DRIVER_H_ */
