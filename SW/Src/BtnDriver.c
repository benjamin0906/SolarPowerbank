/*
 * BtnDriver.c
 *
 *  Created on: 2026. nov. 10.
 *      Author: Benjamin
 */

#include "types.h"
#include "GPIO.h"
#include "main.h"
#include "config.h"

typedef enum BtnDriverStates
{
    BtnDriverState_Init,
    BtnDriverState_Monitor,
} dtBtnDriverStates;

typedef struct sBtnFlags
{
    uint8 Btn1 :2;
    uint8 Btn2 :2;
    uint8 Btn3 :2;
} dtBtnFlags;

static dtBtnDriverStates BtnDriverStates;
static dtBtnFlags BtnFlags;
static uint32 Btn1Timestamp;
static uint32 Btn3Timestamp;
static uint8 Btn1State;
static uint8 Btn3State;

void BtnDriver_Runnable(void)
{
    switch(BtnDriverStates)
    {
        case BtnDriverState_Init:
            const dtGPIOConfig BtnCfg = {.DefState = 0, .Mode = Input, .PUPD = PullUp, .Speed = Medium, .Type = PushPull};
            GPIO_PinInit(BTN1, BtnCfg);
            GPIO_PinInit(BTN2, BtnCfg);
            GPIO_PinInit(BTN3, BtnCfg);
            BtnDriverStates = BtnDriverState_Monitor;
            break;
        case BtnDriverState_Monitor:
        {
            uint8 Btn1CurrentState = GPIO_Get(BTN1);
            uint8 Btn3CurrentState = GPIO_Get(BTN3);
            switch(BtnFlags.Btn1)
            {
                case 0:
                    if(Btn1CurrentState == 0)
                    {
                        BtnFlags.Btn1 = 1;
                        Btn1Timestamp = SysTime();
                    }
                    break;
                case 1:
                    if(TimePassed(Btn1Timestamp, 50))
                    {
                        if(Btn1CurrentState != 0)
                        {
                            BtnFlags.Btn1 = 0;
                        }
                        else
                        {
                            BtnFlags.Btn1 = 2;
                        }
                    }
                    break;
                case 2:
                    if(Btn1CurrentState != 0)
                    {
                       if(TimePassed(Btn1Timestamp, 1000))
                       {
                           Btn1State = 2;
                       }
                       else if(TimePassed(Btn1Timestamp, 200))
                       {
                           Btn1State = 1;
                       }
                       BtnFlags.Btn1 = 0;
                    }
                    break;
            }
            switch(BtnFlags.Btn3)
            {
                case 0:
                    if(Btn3CurrentState == 0)
                    {
                        BtnFlags.Btn3 = 1;
                        Btn3Timestamp = SysTime();
                    }
                    break;
                case 1:
                    if(TimePassed(Btn3Timestamp, 50))
                    {
                        if(Btn3CurrentState != 0)
                        {
                            BtnFlags.Btn3 = 0;
                        }
                        else
                        {
                            BtnFlags.Btn3 = 2;
                        }
                    }
                    break;
                case 2:
                    if(Btn3CurrentState != 0)
                    {
                       if(TimePassed(Btn3Timestamp, 1000))
                       {
                           Btn3State = 2;
                       }
                       else if(TimePassed(Btn3Timestamp, 100))
                       {
                           Btn3State = 1;
                       }
                       BtnFlags.Btn3 = 0;
                    }
                    break;
            }
        }
            break;
    }
}

uint8 BtnDriver_Btn1Get(void)
{
    uint8 ret = Btn1State;
    Btn1State = 0;
    return ret;
}

uint8 BtnDriver_Btn3Get(void)
{
    uint8 ret = Btn3State;
    Btn3State = 0;
    return ret;
}
