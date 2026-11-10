/*
 * PAC193x_Driver.c
 *
 *  Created on: 2026. okt. 22.
 *      Author: Benjamin
 */

#include "types.h"
#include "I2C.h"
#include "main.h"
#include "PAC193x_Driver_Config.h"

typedef enum ePACStates
{
    PAC_Idle,
    PAC_ReadManId,
    PAC_Cfg_1,
    PAC_Cfg_2,
    PAC_Cfg_3,
    PAC_Cfg_Read,
    PAC_Cfg_Proc,
    PAC_Refresh,
    PAC_Read_SetPointer,
    PAC_Read_All,
    PAC_Process,
    PAC_WaitComm,
} dtPACStates;

#ifndef PAC_VARIANT
#error "PAC variant has not been defined"
#elif (PAC_VARIANT < 1) || (PAC_VARIANT > 4)
#error "PAC variant is incorrect"
#endif


typedef union uR01
{
    uint8 U;
    struct s01_B
    {
        uint8 OVF :1;
        uint8 OVF_ALERT :1;
        uint8 ALERT_CC  :1;
        uint8 ALERT_PIN :1;
        uint8 SING      :1;
        uint8 SLEEP     :1;
        uint8 SAMPLE_R  :2;
    } B;
} dtR01;

typedef union uR1C
{
    uint8 U;
    struct s1C_B
    {
        uint8           :1;
        uint8 NO_SKIP   :1;
        uint8 BYTE_COUNT:1;
        uint8 TIMEOUT   :1;
        uint8 CH4_OFF   :1;
        uint8 CH3_OFF   :1;
        uint8 CH2_OFF   :1;
        uint8 CH1_OFF   :1;
    } B;
} dtR1C;

typedef union uR1D
{
    uint8 U;
    struct s1D_B
    {
        uint8 CH4_BIDV :1;
        uint8 CH3_BIDV :1;
        uint8 CH2_BIDV :1;
        uint8 CH1_BIDV :1;
        uint8 CH4_BIDI :1;
        uint8 CH3_BIDI :1;
        uint8 CH2_BIDI :1;
        uint8 CH1_BIDI :1;
    } B;
} dtR1D;

typedef union uRawValue
{
    uint16 U;
    int16 I;
} dtRawValue;

#define READ_START_ADD  0x2
#define ACC_SIZE_ADD    0x2
#define ACC_SIZE_LEN    3
#define VPOWER_ACC_LEN  6
#define VBUS_LEN        2
#define VSENSE_LEN      2
#define VBUS_AVG_LEN    2
#define VSENSE_AVG_LEN  2
#define VPOWER_LEN      4
#define CHANNEL_DATA_LEN (VPOWER_ACC_LEN + VBUS_LEN + VSENSE_LEN + VBUS_AVG_LEN + VSENSE_AVG_LEN + VPOWER_LEN)

#define INDEX_TO_ACC_SIZE() (ACC_SIZE_ADD - READ_START_ADD)
#define INDEX_TO_VPOWER_ACC(ch) ((INDEX_TO_ACC_SIZE() + ACC_SIZE_LEN) + (ch * VPOWER_ACC_LEN))
#define INDEX_TO_VBUS(available_ch, current_ch) (INDEX_TO_VPOWER_ACC(available_ch) + (current_ch * VBUS_LEN))
#define INDEX_TO_VSENSE(available_ch, current_ch) (INDEX_TO_VBUS(available_ch, available_ch) + (current_ch * VSENSE_LEN))
#define INDEX_TO_VBUS_AVG(available_ch, current_ch) (INDEX_TO_VSENSE(available_ch, available_ch) + (current_ch * VBUS_AVG_LEN))
#define INDEX_TO_VSENSE_AVG(available_ch, current_ch) (INDEX_TO_VBUS_AVG(available_ch, available_ch) + (current_ch * VSENSE_AVG_LEN))
#define INDEX_TO_VPOWER(available_ch, current_ch) (INDEX_TO_VSENSE_AVG(available_ch, available_ch) + (current_ch * VPOWER_LEN))

static dtPACStates PacStates;
static dtPACStates NextState;
static dtPACStates PrevState;
static dtR01 R01;
static dtR1C R1C;
static dtR1D R1D;
static uint8 reg_addr;
static uint8 dataBuf[96];
static uint32 Timestamp;
static const uint16 vbus_reference = 32000; // in mV
static const uint8 vsense_reference = 100; // in mV
static uint8 bytes_to_read;
static int8 i2c_session;
static int32 Vbus[PAC_VARIANT];
static int32 Vbus_avg[PAC_VARIANT];
static int32 Vsense[PAC_VARIANT];
static int32 Vsense_avg[PAC_VARIANT];

void ProcessData(void)
{
    uint8 ch_index = 0;
    uint8 available_channels = (bytes_to_read - ACC_SIZE_LEN) / CHANNEL_DATA_LEN;
    uint8 res_index = 0;
    uint8 mask = 0x80;

    for(res_index = 0; res_index < 4; res_index++, mask >>= 1)
    {
        if((R1C.U & (mask)) == 0)
        {
            uint8 raw_index = 0;
            dtRawValue tVbus;
            dtRawValue tVbus_avg;
            dtRawValue tVsense;
            dtRawValue tVsense_avg;
            int32 tCurrent;
            int32 tAvg;

            /* Accumulator */
            raw_index = INDEX_TO_ACC_SIZE();

            /* Bus */
            raw_index = INDEX_TO_VBUS(available_channels, ch_index);
            tVbus.U = ((uint16)dataBuf[raw_index] << 8) | (uint16)dataBuf[raw_index + 1];

            /* Sense */
            raw_index = INDEX_TO_VSENSE(available_channels, ch_index);
            tVsense.U = ((uint16)dataBuf[raw_index] << 8) | (uint16)dataBuf[raw_index + 1];

            /* bus avg */
            raw_index = INDEX_TO_VBUS_AVG(available_channels, ch_index);
            tVbus_avg.U = ((uint16)dataBuf[raw_index] << 8) | (uint16)dataBuf[raw_index + 1];

            /* sense avg */
            raw_index = INDEX_TO_VSENSE_AVG(available_channels, ch_index);
            tVsense_avg.U = ((uint16)dataBuf[raw_index] << 8) | (uint16)dataBuf[raw_index + 1];

            if((R1D.U & (mask)) != 0)
            {
                tCurrent = ((int32)tVsense.I << 1);
                tAvg = ((int32)tVsense_avg.I << 1);
            }
            else
            {
                tCurrent = ((int32)tVsense.U);
                tAvg = ((int32)tVsense_avg.U);
            }
            Vsense[res_index] = tCurrent * vsense_reference;
            Vsense_avg[res_index] = tAvg * vsense_reference;


            if((R1D.U & (mask >> 4)) != 0)
            {
                tCurrent = ((int32)tVbus.I << 1);
                tAvg = ((int32)tVbus_avg.I << 1);
            }
            else
            {
                tCurrent = ((int32)tVbus.I);
                tAvg = ((int32)tVbus_avg.I);
            }
            Vbus[res_index] = tCurrent * vbus_reference;
            Vbus_avg[res_index] = tAvg * vbus_reference;

            ch_index ++;
        }
    }
}

/**
 * @brief Returns with the measured bus voltage of the desired channel
 *
 * Returns the measured sense voltage in [mV]. The return value format is S15Q16
 *
 * @param channel channel id
 *
 * @return Vbus voltage of the channel [mV]
 **/
int32 PAC_193x_Driver_GetVBus(uint8 channel)
{
    return Vbus[channel];
}

/**
 * @brief Returns with the averaged measured bus voltage of the desired channel
 *
 * Returns the measured sense voltage in [mV]. The return value format is S15Q16
 *
 * @param channel channel id
 *
 * @return averaged Vbus voltage of the channel [mV]
 **/
int32 PAC_193x_Driver_GetVBusAvg(uint8 channel)
{
    return Vbus_avg[channel];
}

/**
 * @brief Returns with the measured sense voltage of the desired channel
 *
 * Returns the measured sense voltage in [mV]. The return value format is S15Q16
 *
 * @param channel channel id
 *
 * @return Vsense voltage of the channel [mV]
 **/
int32 PAC_193x_Driver_GetVSense(uint8 channel)
{
    return Vsense[channel];
}

/**
 * @brief Returns with the averaged measured sense voltage of the desired channel
 *
 * Returns the measured sense voltage in [mV]. The return value format is S15Q16
 *
 * @param channel channel id
 *
 * @return averaged Vsense voltage of the channel [mV]
 **/
int32 PAC_193x_Driver_GetVSenseAvg(uint8 channel)
{
    return Vsense_avg[channel];
}

void StartComm(dtI2CInstance session_type, dtPACStates nextState, uint8 reg_len, uint8 data_len)
{
    i2c_session = I2C_Start(I2C1, session_type, 0x10, &reg_addr, reg_len, &dataBuf[0], data_len);
    NextState = nextState;
    PrevState = PacStates;
    PacStates = PAC_WaitComm;
}

void PAC_193x_Driver_Runnable(void)
{
    switch(PacStates)
    {
        case PAC_Idle:
            PacStates = PAC_ReadManId;
            break;
        case PAC_ReadManId:
            if(I2C_Result(I2C1, i2c_session) != Busy)
            {
                reg_addr = 0xFE;
                R1C.U = 0;
                dataBuf[0] = R1C.U;
                StartComm(I2C_Read, PAC_Cfg_1, 1, 1);
            }
            break;
        case PAC_Cfg_1:
            if(I2C_Result(I2C1, i2c_session) != Busy)
            {
                reg_addr = 0x1C;
#if PAC_VARIANT <= 3
                R1C.B.CH4_OFF = 1;
#endif
#if PAC_VARIANT <= 2
                R1C.B.CH3_OFF = 1;
#endif
#if PAC_VARIANT <= 1
                R1C.B.CH2_OFF = 1;
#endif
                dataBuf[0] = R1C.U;
                StartComm(I2C_Write, PAC_Cfg_2, 1, 1);
            }
            break;
        case PAC_Cfg_2:
            if(I2C_Result(I2C1, i2c_session) != Busy)
            {
                reg_addr = 0x1D;
                R1D.B.CH2_BIDV = 1;
                R1D.B.CH1_BIDI = 1;
                dataBuf[0] = R1D.U;
                StartComm(I2C_Write, PAC_Cfg_3,1, 1);

            }
            break;
        case PAC_Cfg_3:
            if(I2C_Result(I2C1, i2c_session) != Busy)
            {
                reg_addr = 0x01;
                R01.U = 0;
                dataBuf[0] = R01.U;
                StartComm(I2C_Write, PAC_Cfg_Read, 1, 1);
            }
            break;
        case PAC_Cfg_Read:
            if(I2C_Result(I2C1, i2c_session) != Busy)
            {
                reg_addr = 0x1C;
                StartComm(I2C_Read, PAC_Cfg_Proc, 1, 1);
                bytes_to_read = 1;
            }
            break;
        case PAC_Cfg_Proc:
            bytes_to_read = 3;
            if(R1C.B.CH1_OFF == 0) bytes_to_read += CHANNEL_DATA_LEN;
#if PAC_VARIANT > 1
            if(R1C.B.CH2_OFF == 0) bytes_to_read += CHANNEL_DATA_LEN;
#endif
#if PAC_VARIANT > 2
            if(R1C.B.CH3_OFF == 0) bytes_to_read += CHANNEL_DATA_LEN;
#endif
#if PAC_VARIANT > 3
            if(R1C.B.CH4_OFF == 0) bytes_to_read += CHANNEL_DATA_LEN;
#endif
            PacStates = PAC_Refresh;
            break;
        case PAC_Refresh:
            if(TimePassed(Timestamp, 100) != 0)
            {
                if(I2C_Result(I2C1, i2c_session) != Busy)
                {
                    dataBuf[0] = 0x00;
                    reg_addr = 0x00;
                    StartComm(I2C_Write, PAC_Read_SetPointer,1, 0);
                    Timestamp = SysTime();
                }
            }
            break;
        case PAC_Read_SetPointer:
            if(TimePassed(Timestamp, 2) != 0)
            {
                if(I2C_Result(I2C1, i2c_session) != Busy)
                {
                    reg_addr = 0x02;
                    StartComm(I2C_Write, PAC_Read_All, 1, 0);
                }
            }
            break;
        case PAC_Read_All:
            if(I2C_Result(I2C1, i2c_session) != Busy)
            {
                reg_addr = 0x02;
                StartComm(I2C_Read, PAC_Process, 0, bytes_to_read);
            }
            break;
        case PAC_Process:
            ProcessData();
            PacStates = PAC_Refresh;
            break;
        case PAC_WaitComm:
        {
            dtI2cSessionResult ret = I2C_Result(I2C1, i2c_session);
            if(ret == Done)
            {
                PacStates = NextState;
            }
            else if(ret == Error)
            {
                PacStates = PrevState;
            }
        }
            break;

    }
}
