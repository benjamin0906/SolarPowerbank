/*
 * MeasLayout.c
 *
 *  Created on: 2026. okt. 25.
 *      Author: Benjamin
 */

#include "types.h"
#include "PAC193x_Driver.h"
#include "OLED_Driver.h"
#include "Utilities.h"

static const uint8 ShuntResistance = 100;

void MeasLayout_Layout(void)
{
    uint8 i = 0;
    uint8 string[128];
    int32 temp;

    temp = PAC_193x_Driver_GetVBusAvg(0);

    string[i++] = 'V';
    string[i++] = 'b';
    string[i++] = 'u';
    string[i++] = 's';
    string[i++] = '0';
    string[i++] = ':';
    string[i++] = ' ';
    if(temp < 0)
    {
        string[i++] = '-';
        temp *= -1;
    }
    i += UQNumToStr(temp, 16, 2, &string[i]);
    string[i++] = '\n';

    temp = PAC_193x_Driver_GetVBusAvg(1);

    string[i++] = 'V';
    string[i++] = 'b';
    string[i++] = 'u';
    string[i++] = 's';
    string[i++] = '1';
    string[i++] = ':';
    string[i++] = ' ';
    if(temp < 0)
    {
        string[i++] = '-';
        temp *= -1;
    }
    i += UQNumToStr(temp, 16, 4, &string[i]);
    string[i++] = '\n';

    temp = PAC_193x_Driver_GetVSenseAvg(0) / 10;

    string[i++] = 'I';
    string[i++] = '0';
    string[i++] = ':';
    string[i++] = ' ';
    if(temp < 0)
    {
        string[i++] = '-';
        temp *= -1;
    }
    i += UQNumToStr(temp, 16, 4, &string[i]);
    string[i++] = '\n';

    temp = PAC_193x_Driver_GetVSenseAvg(1) / 10;

    string[i++] = 'I';
    string[i++] = '1';
    string[i++] = ':';
    string[i++] = ' ';
    if(temp < 0)
    {
        string[i++] = '-';
        temp *= -1;
    }
    i += UQNumToStr(temp, 16, 2, &string[i]);
    string[i++] = '\n';

    string[i] = 0;
    OLED_Driver_PutString(string);
}
