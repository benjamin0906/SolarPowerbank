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

typedef struct sButtonDescriptor
{
    dtGPIOs Pin;
    uint32 ButtonTimestamp;
    uint8 ButtonState;
    uint8 ButtonStatus;
} dtButtonDescriptor;

static dtBtnDriverStates BtnDriverStates;

static dtButtonDescriptor BtnDesc[3] = {
        {.Pin = BTN1, .ButtonTimestamp = 0, .ButtonState = 0, .ButtonStatus = 0},
        {.Pin = BTN2, .ButtonTimestamp = 0, .ButtonState = 0, .ButtonStatus = 0},
        {.Pin = BTN3, .ButtonTimestamp = 0, .ButtonState = 0, .ButtonStatus = 0},
};

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
            for(uint8 looper = 0; looper < (sizeof(BtnDesc)/sizeof(BtnDesc[0])); looper++)
            {
                uint8 BtnCurrentState = GPIO_Get(BtnDesc[looper].Pin);
                switch(BtnDesc[looper].ButtonState)
                {
                    case 0:
                        if(BtnCurrentState == 0)
                        {
                            BtnDesc[looper].ButtonState = 1;
                            BtnDesc[looper].ButtonTimestamp = SysTime();
                        }
                        break;
                    case 1:
                        if(TimePassed(BtnDesc[looper].ButtonTimestamp, 50))
                        {
                            if(BtnCurrentState != 0)
                            {
                                BtnDesc[looper].ButtonState = 0;
                            }
                            else
                            {
                                BtnDesc[looper].ButtonState = 2;
                            }
                        }
                        break;
                    case 2:
                        if(BtnCurrentState != 0)
                        {
                           if(TimePassed(BtnDesc[looper].ButtonTimestamp, 1000))
                           {
                               BtnDesc[looper].ButtonStatus = 2;
                           }
                           else if(TimePassed(BtnDesc[looper].ButtonTimestamp, 200))
                           {
                               BtnDesc[looper].ButtonStatus = 1;
                           }
                           BtnDesc[looper].ButtonState = 0;
                        }
                        break;
                }
            }
            break;
    }
}

uint8 BtnDriver_Btn1Get(void)
{
    uint8 ret = BtnDesc[0].ButtonStatus;
    BtnDesc[0].ButtonStatus = 0;
    return ret;
}

uint8 BtnDriver_Btn2Get(void)
{
    uint8 ret = BtnDesc[1].ButtonStatus;
    BtnDesc[1].ButtonStatus = 0;
    return ret;
}

uint8 BtnDriver_Btn3Get(void)
{
    uint8 ret = BtnDesc[2].ButtonStatus;
    BtnDesc[2].ButtonStatus = 0;
    return ret;
}
