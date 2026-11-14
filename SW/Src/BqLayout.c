/*
 * BqLayout.c
 *
 *  Created on: 2026. okt. 22.
 *      Author: Benjamin
 */

#include "BQ25690_Driver.h"
#include "OLED_Driver.h"
#include "Utilities.h"

typedef struct sEntryDesc
{
    uint8 *name;
    uint32 (*value_api)(void);
    uint8 (*formatter)(uint8* buffer, uint32 value);
    void (*increase_api)(void);
    void (*decrease_api)(void);
} dtEntryDesc;

static uint8 string[] = "       STATS\nPG: 0\nIindpm: 0\nVindpm: 0\nTreg: 0\nChg stat: 0\nICO stat: 0\nTS stat: 0";

static uint8 NumFormat(uint8 *buffer, uint32 number)
{
    uint8 ret = 0;
    if(buffer != 0)
    {
        *buffer = '0' + number;
        ret ++;
    }
    return ret;
}

void BqLayout_Status_Runnable(void)
{
    //uint8 string[] = "       STATS\nPG: 0\nIindpm: 0\nVindpm: 0\nTreg: 0\nChg stat: 0\nICO stat: 0\nTS stat: 0";
    dtBqInfo bqInfo = BQ25690_GetInfo();

    string[17] = '0' + bqInfo.PG_stat;

    string[27] = '0' + bqInfo.Iindpm_stat;

    string[37] = '0' + bqInfo.Vindpm_stat;

    string[45] = '0' + bqInfo.Treg_stat;

    string[57] = '0' + bqInfo.Charge_stat;

    string[69] = '0' + bqInfo.ICO_stat;

    string[80] = '0' + bqInfo.TS_stat;

    OLED_Driver_PutString(string);
}

void BqLayout_Faults_Runnable(void)
{
    uint8 i = 0;
    uint8 string[128];
    dtBqInfo bqInfo = BQ25690_GetInfo();

    string[i++] = ' ';
    string[i++] = ' ';
    string[i++] = ' ';
    string[i++] = ' ';
    string[i++] = ' ';
    string[i++] = ' ';
    string[i++] = ' ';
    string[i++] = 'F';
    string[i++] = 'A';
    string[i++] = 'U';
    string[i++] = 'L';
    string[i++] = 'T';
    string[i++] = 'S';
    string[i++] = '\n';

    string[i++] = 'V';
    string[i++] = 'i';
    string[i++] = 'n';
    string[i++] = ' ';
    string[i++] = 'O';
    string[i++] = 'V';
    string[i++] = 'P';
    string[i++] = ':';
    string[i++] = ' ';
    string[i++] = '0' + bqInfo.Vin_OVP_Fault;
    string[i++] = '\n';


    string[i++] = 'B';
    string[i++] = 'A';
    string[i++] = 'T';
    string[i++] = ':';
    string[i++] = ' ';
    string[i++] = '0' + bqInfo.BAT_Fault;
    string[i++] = '\n';

    string[i++] = 'C';
    string[i++] = 'H';
    string[i++] = 'G';
    string[i++] = ' ';
    string[i++] = 'T';
    string[i++] = 'M';
    string[i++] = 'R';
    string[i++] = ':';
    string[i++] = ' ';
    string[i++] = '0' + bqInfo.CHG_TMR_Fault;
    string[i++] = '\n';

    string[i++] = 'C';
    string[i++] = 'V';
    string[i++] = ' ';
    string[i++] = 'T';
    string[i++] = 'M';
    string[i++] = 'R';
    string[i++] = ':';
    string[i++] = ' ';
    string[i++] = '0' + bqInfo.CV_TMR_Fault;
    string[i++] = '\n';

    string[i++] = 'T';
    string[i++] = 's';
    string[i++] = 'h';
    string[i++] = 'u';
    string[i++] = 't';
    string[i++] = ':';
    string[i++] = ' ';
    string[i++] = '0' + bqInfo.T_SHUT_Fault;
    string[i++] = '\n';

    string[i++] = 0;
    OLED_Driver_PutString(string);
}

static uint8 a;
static uint8 b;

static void increase(void)
{
    a++;
}

static void decrease(void)
{
    a--;
}

static uint32 value(void)
{
    return a;
}

static void increase2(void)
{
    b++;
}

static void decrease2(void)
{
    b--;
}
static uint32 value2(void)
{
    return b;
}

static uint8 GetLineIndex(uint8 line, uint8 *buffer, uint8 limit)
{
    uint8 found = 0;
    uint8 i = 0;
    while((i < limit) && (found < line))
    {
        if(buffer[i] == '\n') found ++;
        i++;
    }
    return i;
}

void BqLayout_Cfg_Runnable(uint8 buttons)
{
    uint8 i = 0;
    uint8 entry_looper;
    uint8 string[128];
    uint8 btn1 = buttons & 0x3;
    uint8 btn2 = (buttons >> 2) & 0x3;
    uint8 btn3 = (buttons >> 4) & 0x3;
    static uint8 state = 0;
    static int8 highlight = 1;
    dtBqInfo bqInfo = BQ25690_GetInfo();

    dtEntryDesc entries[2] = {
            {.name = "abc", .value_api = value, .formatter = NumFormat, .increase_api = increase, .decrease_api = decrease},
            {.name = "def", .value_api = value2, .formatter = NumFormat, .increase_api = increase2, .decrease_api = decrease2},
    };

    string[i++] = ' ';
    string[i++] = ' ';
    string[i++] = ' ';
    string[i++] = ' ';
    string[i++] = ' ';
    string[i++] = ' ';
    string[i++] = ' ';
    string[i++] = 'C';
    string[i++] = 'O';
    string[i++] = 'N';
    string[i++] = 'F';
    string[i++] = 'I';
    string[i++] = 'G';
    string[i++] = '\n';

    for(entry_looper = 0; entry_looper < ((sizeof(entries))/(sizeof(entries[0]))); entry_looper++)
    {
        uint8 name_len = strlen(entries[entry_looper].name);
        uint8 value_len = 0;
        memcpy_reverse(entries[entry_looper].name, &string[i], name_len);
        i += name_len;
        string[i++] = ':';
        value_len = entries[entry_looper].formatter(&string[i], entries[entry_looper].value_api());
        i += value_len;
        string[i++] = '\n';
    }

    string[i++] = 0;
    OLED_Driver_PutString(string);
    switch(state)
    {
        case 0:
            if(btn2 == 1)
            {
                state = 1;
                highlight = 1;
            }
            break;
        case 1:
            if(btn3 != 0)
            {
                if(highlight < ((sizeof(entries))/(sizeof(entries[0])))) highlight++;
            }
            if(btn1 != 0)
            {
                if(highlight > 0) highlight--;
            }
            if(btn2 == 2)
            {
                highlight = 1;
                state = 0;
            }
            else if(btn2 == 1)
            {
                state = 2;
            }

            uint8 start = 0;
            uint8 end = 0;
            uint8 current_line = 0;
            uint8 i = 0;
            while((i < 128) && (current_line < highlight))
            {
                if(string[i] == '\n') current_line++;
                i++;
            }
            /*while((i < 128) && (string[i] != ':'))
            {
                i++;
                start++;
            }
            i++; // the ':' character
            start++;*/
            end = start;
            while((i < 128) && ((string[i] != ' ') && (string[i] != '\n') && (string[i] != 0)))
            {
                i++;
                end++;
            }
            OLED_Driver_InverseSection(highlight, 0, end);
            break;
        case 2:
        {
            uint8 start = 0;
            uint8 end = 0;
            uint8 current_line = 0;
            uint8 i = 0;
            while((i < 128) && (current_line < highlight))
            {
                if(string[i] == '\n') current_line++;
                i++;
            }
            while((i < 128) && (string[i] != ':'))
            {
                i++;
                start++;
            }
            i++; // the ':' character
            start++;
            end = start;
            while((i < 128) && ((string[i] != ' ') && (string[i] != '\n') && (string[i] != 0)))
            {
                i++;
                end++;
            }

            OLED_Driver_InverseSection(highlight, start, end);
            if(btn2 == 1)
            {
                state = 1;
            }
            if(btn1 == 1)
            {
                entries[highlight-1].decrease_api();
            }
            if(btn3 == 1)
            {
                entries[highlight-1].increase_api();
            }
        }
            break;
    }

}
