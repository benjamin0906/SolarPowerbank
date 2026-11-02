/*
 * BQ25690_Driver.c
 *
 *  Created on: 2026. okt. 21.
 *      Author: Benjamin
 */

#include "BQ25690_Types.h"
#include "BQ25690_Driver.h"
#include "main.h"
#include "I2C.h"

typedef enum eBqStates
{
    BqState_Read,
    BqState_WaitI2c,
} dtBqStates;



static uint32 Timestamp;
static dtBQ25690 BQ25690;
static dtBqStates BqState;
static dtBqInfo BqInfo;

static void ProcessRegisters(void)
{
    BqInfo.VSYSMIN      = BQ25690.REG00.B.VSYSMIN   * 20;
    BqInfo.ICHG         = BQ25690.REG02.B.ICHG      * 20;
    BqInfo.VREG         = BQ25690.REG04.B.VREG      * 10;
    BqInfo.IINDPM       = BQ25690.REG06.B.IINDPM    * 20;
    BqInfo.VINDPM       = BQ25690.REG08.B.VINDPM    * 20;
    BqInfo.IPRECHG      = BQ25690.REG0E.B.IPRECHG   * 20;
    BqInfo.ITERM        = BQ25690.REG0F.B.ITERM     * 20;
    BqInfo.Fsw          = BQ25690.REG16.B.FSW;
    BqInfo.Vchg_pin     = BQ25690.REG1B.B.VCHG_PIN;
    BqInfo.Cell_pin     = BQ25690.REG1B.B.CELL_PIN;
    BqInfo.Ichg_pin     = BQ25690.REG1C.B.ICHG_PIN;
    BqInfo.PG_stat      = BQ25690.REG1D.B.PG_STAT;
    BqInfo.Iindpm_stat  = BQ25690.REG1D.B.IINDPM_STAT;
    BqInfo.Vindpm_stat  = BQ25690.REG1D.B.VINDPM_STAT;
    BqInfo.Treg_stat    = BQ25690.REG1D.B.TREG_STAT;
    BqInfo.Charge_stat  = BQ25690.REG1D.B.CHARGE_STAT;
    BqInfo.ICO_stat     = BQ25690.REG1E.B.ICO_STAT;
    BqInfo.TS_stat      = BQ25690.REG1E.B.TS_STAT;
    BqInfo.Vin_OVP_Fault= BQ25690.REG1F.B.VIN_OVP_STAT;
    BqInfo.BAT_Fault    = BQ25690.REG1F.B.BAT_FAULT_STAT;
    BqInfo.CHG_TMR_Fault= BQ25690.REG1F.B.CHG_TMR_STAT;
    BqInfo.CV_TMR_Fault = BQ25690.REG1F.B.CV_TMR_STAT;
    BqInfo.T_SHUT_Fault = BQ25690.REG1F.B.TSHUT_STAT;
}

static int8 i2c_session;

void BQ25690_Runnable(void)
{
    uint8 reg_addr = 0x0;
    switch(BqState)
    {
        case BqState_Read:
            if(TimePassed(Timestamp, 100))
            {
                if(I2C_Result(I2C1, i2c_session) != Busy)
                {
                    Timestamp = SysTime();
                    i2c_session = I2C_Start(I2C1, I2C_Read, 0x6A, &reg_addr, 1, (uint8*)&BQ25690, sizeof(dtBQ25690));
                    BqState = BqState_WaitI2c;
                }
            }
            break;
        case BqState_WaitI2c:
            if(I2C_Result(I2C1, i2c_session) != Busy)
            {
                ProcessRegisters();
                BqState = BqState_Read;
            }
            break;
    }

}

dtBqInfo BQ25690_GetInfo(void)
{
    return BqInfo;
}
