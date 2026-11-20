/*
 * BqLayout.c
 *
 *  Created on: 2026. okt. 22.
 *      Author: Benjamin
 */

#include "BQ25690_Driver.h"
#include "OLED_Driver.h"
#include "Utilities.h"

#define DISPLAY_INFO_LINES 7

typedef struct sEntryDesc
{
    uint8 *const name;
    uint8 name_length;
    uint8 full_length;
    uint8 highlight_enable;
    uint8 argument;
    uint32 (*value_api)(uint8);
    uint8 (*formatter)(uint8* buffer, uint32 value);
    void (*increase_api)(void);
    void (*decrease_api)(void);
} dtEntryDesc;

typedef enum eHighlightState
{
    Highlight_Inactive,
    Highlight_Name,
    Highlight_Value,
} dtHighlightState;

static uint8 EntryHandler(const uint8 *const headline, dtEntryDesc *const entries, const uint8 entries_length, uint8 buttons);

static uint8 NumFormat(uint8 *buffer, uint32 number)
{
    uint8 ret =     Dabler(number, buffer);
    return ret;
}

static uint8 GetNextHighlightIndex(const dtEntryDesc *list, const uint8 list_length, uint8 current)
{
    uint8 i;
    for(i = current + 1; (i < list_length) && (list[i].highlight_enable == 0); i++);
    if(i >= list_length)
    {
        i = 0xFF;
    }
    return i;
}

static uint8 GetPreviousHighlightIndex(const dtEntryDesc *list, uint8 current)
{
    int8 i;
    for(i = current - 1; ((i >= 0) && (list[i].highlight_enable == 0)); i--);
    if(i < 0)
    {
        i = 0xFF;
    }
    return i;
}

static uint32 GetProperty(uint8 property)
{
    uint32 ret = 0;
    const dtBqInfo *bqInfo = BQ25690_GetInfo();
    switch(property)
    {
        case 0:
            ret = bqInfo->PG_stat;
            break;
        case 1:
            ret = bqInfo->Iindpm_stat;
            break;
        case 2:
            ret = bqInfo->Vindpm_stat;
            break;
        case 3:
            ret = bqInfo->Treg_stat;
            break;
        case 4:
            ret = bqInfo->Charge_stat;
            break;
        case 5:
            ret = bqInfo->ICO_stat;
            break;
        case 6:
            ret = bqInfo->TS_stat;
            break;
        case 7:
            ret = bqInfo->Vin_OVP_Fault;
            break;
        case 8:
            ret = bqInfo->BAT_Fault;
            break;
        case 9:
            ret = bqInfo->CHG_TMR_Fault;
            break;
        case 10:
            ret = bqInfo->CV_TMR_Fault;
            break;
        case 11:
            ret = bqInfo->T_SHUT_Fault;
            break;
    }
    return ret;
}

void BqLayout_Status_Runnable(void)
{
    const uint8 *const headline = (uint8*)"       STATS";
    dtEntryDesc entries[] = {
        {.name = (uint8*)"PG", .name_length = sizeof("PG"), .value_api = GetProperty, .argument = 0, .formatter = NumFormat, .increase_api = 0, .decrease_api = 0, .highlight_enable = 0},
        {.name = (uint8*)"Iindpm", .name_length = sizeof("Iindpm"), .value_api = GetProperty, .argument = 1,  .formatter = NumFormat, .increase_api = 0, .decrease_api = 0, .highlight_enable = 0},
        {.name = (uint8*)"Vindpm", .name_length = sizeof("Vindpm"), .value_api = GetProperty, .argument = 2,  .formatter = NumFormat, .increase_api = 0, .decrease_api = 0, .highlight_enable = 0},
        {.name = (uint8*)"Treg", .name_length = sizeof("Treg"), .value_api = GetProperty, .argument = 3,  .formatter = NumFormat, .increase_api = 0, .decrease_api = 0, .highlight_enable = 0},
        {.name = (uint8*)"Chg stat", .name_length = sizeof("Chg stat"), .value_api = GetProperty, .argument = 4,  .formatter = NumFormat, .increase_api = 0, .decrease_api = 0, .highlight_enable = 0},
        {.name = (uint8*)"ICO stat", .name_length = sizeof("ICO stat"), .value_api = GetProperty, .argument = 5,  .formatter = NumFormat, .increase_api = 0, .decrease_api = 0, .highlight_enable = 0},
        {.name = (uint8*)"TS stat", .name_length = sizeof("TS stat"), .value_api = GetProperty, .argument = 6,  .formatter = NumFormat, .increase_api = 0, .decrease_api = 0, .highlight_enable = 0},
    };
    EntryHandler(headline, entries, sizeof(entries) / sizeof(entries[0]), 0);
}

void BqLayout_Faults_Runnable(void)
{
    const uint8 *headline = (uint8*)"       FAULTS";
    dtEntryDesc entries[] = {
        {.name = (uint8*)"Vin OVP", .name_length = sizeof("Vin OVP"), .value_api = GetProperty, .argument = 7, .formatter = NumFormat, .increase_api = 0, .decrease_api = 0, .highlight_enable = 0},
        {.name = (uint8*)"BAT", .name_length = sizeof("BAT"), .value_api = GetProperty, .argument = 8,  .formatter = NumFormat, .increase_api = 0, .decrease_api = 0, .highlight_enable = 0},
        {.name = (uint8*)"CHG TMR", .name_length = sizeof("CHG TMR"), .value_api = GetProperty, .argument = 9,  .formatter = NumFormat, .increase_api = 0, .decrease_api = 0, .highlight_enable = 0},
        {.name = (uint8*)"CV TMR", .name_length = sizeof("CV TMR"), .value_api = GetProperty, .argument = 10,  .formatter = NumFormat, .increase_api = 0, .decrease_api = 0, .highlight_enable = 0},
        {.name = (uint8*)"T shut", .name_length = sizeof("T shut"), .value_api = GetProperty, .argument = 11,  .formatter = NumFormat, .increase_api = 0, .decrease_api = 0, .highlight_enable = 0},
    };
        EntryHandler(headline, entries, sizeof(entries) / sizeof(entries[0]), 0);
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

static uint32 value(uint8 type)
{
    if(type == 0)
    return a;
    else
        return b;
}

static void increase2(void)
{
    b++;
}

static void decrease2(void)
{
    b--;
}


uint8 BqLayout_Cfg_Runnable(uint8 buttons)
{
    const uint8 *headline = (uint8*)"       CONFIG";
    dtEntryDesc entries[9] = {
        {.name = (uint8*)"abc", .name_length = sizeof("abc"), .value_api = value, .argument = 0, .formatter = NumFormat, .increase_api = increase, .decrease_api = decrease, .highlight_enable = 1},
        {.name = (uint8*)"def", .name_length = sizeof("def"), .value_api = value, .argument = 1,  .formatter = NumFormat, .increase_api = increase2, .decrease_api = decrease2, .highlight_enable = 1},
        {.name = (uint8*)"def2", .name_length = sizeof("def2"), .value_api = value, .argument = 1,  .formatter = NumFormat, .increase_api = increase2, .decrease_api = decrease2, .highlight_enable = 1},
        {.name = (uint8*)"def3", .name_length = sizeof("def3"), .value_api = value, .argument = 1,  .formatter = NumFormat, .increase_api = increase2, .decrease_api = decrease2, .highlight_enable = 1},
        {.name = (uint8*)"def4", .name_length = sizeof("def4"), .value_api = value, .argument = 1,  .formatter = NumFormat, .increase_api = increase2, .decrease_api = decrease2, .highlight_enable = 1},
        {.name = (uint8*)"def5", .name_length = sizeof("def5"), .value_api = value, .argument = 1,  .formatter = NumFormat, .increase_api = increase2, .decrease_api = decrease2, .highlight_enable = 1},
        {.name = (uint8*)"def6", .name_length = sizeof("def6"), .value_api = value, .argument = 1,  .formatter = NumFormat, .increase_api = increase2, .decrease_api = decrease2, .highlight_enable = 1},
        {.name = (uint8*)"def7", .name_length = sizeof("def7"), .value_api = value, .argument = 1,  .formatter = NumFormat, .increase_api = increase2, .decrease_api = decrease2, .highlight_enable = 1},
        {.name = (uint8*)"def8", .name_length = sizeof("def8"), .value_api = value, .argument = 1,  .formatter = NumFormat, .increase_api = increase2, .decrease_api = decrease2, .highlight_enable = 1},
};
    return EntryHandler(headline, entries, sizeof(entries) / sizeof(entries[0]), buttons);
}

static uint8 EntryHandler(const uint8 *const headline, dtEntryDesc *const entries, const uint8 entries_length, uint8 buttons)
{
    static uint8 start = 0;
    static dtHighlightState state = 0;
    static int8 highlight = 0;

    uint8 i = 0;
    uint8 entry_looper;
    uint8 string[128];
    uint8 btn1 = buttons & 0x3;
    uint8 btn2 = (buttons >> 2) & 0x3;
    uint8 btn3 = (buttons >> 4) & 0x3;
    uint8 line_highlight = 1;
    uint8 highlight_start = 0;
    uint8 highlight_end = 0;

    i = strlen(headline);
    memcpy_reverse(headline, string, i);
    string[i++] = '\n';

    if(highlight < start)
    {
        start = highlight;
    }
    if(highlight >= (start + DISPLAY_INFO_LINES))
    {
        start = highlight - DISPLAY_INFO_LINES + 1; //inclusive interval
    }
    line_highlight += highlight - start; //adding to initial 1 due to the headline

    for(entry_looper = start; (entry_looper < (start + DISPLAY_INFO_LINES)) && (entry_looper < entries_length); entry_looper++)
    {
        uint8 value_len = 0;
        memcpy_reverse(entries[entry_looper].name, &string[i], entries[entry_looper].name_length);
        i += entries[entry_looper].name_length;
        i--; //due to closing zero
        string[i++] = ':';
        value_len = entries[entry_looper].formatter(&string[i], entries[entry_looper].value_api(entries[entry_looper].argument));
        i += value_len;
        string[i++] = '\n';
        entries[entry_looper].full_length = 1 + value_len + entries[entry_looper].name_length;
    }

    string[i++] = 0;
    switch(state)
    {
        case Highlight_Inactive:
            if(btn2 == 1)
            {
                uint8 index = GetNextHighlightIndex(entries, entries_length, -1);
                if(index != 0xFF)
                {
                    highlight = index;
                    state = Highlight_Name;
                }
            }
            break;
        case Highlight_Name:
            if(btn3 != 0)
            {
                uint8 index = GetNextHighlightIndex(entries, entries_length, highlight);
                if(index != 0xFF) highlight = index;
            }
            if(btn1 != 0)
            {
                uint8 index = GetPreviousHighlightIndex(entries, highlight);
                if(index != 0xFF) highlight = index;
            }
            if(btn2 == 2)
            {
                state = Highlight_Inactive;
            }
            else if(btn2 == 1)
            {
                state = Highlight_Value;
            }
            highlight_start = 0;
            highlight_end = entries[highlight].name_length;
            break;
        case Highlight_Value:
        {
            highlight_start = entries[highlight].name_length;
            highlight_end = entries[highlight].full_length;
            if(btn2 == 1)
            {
                state = Highlight_Name;
            }
            if(btn1 == 1)
            {
                if(entries[highlight].decrease_api != 0)
                {
                    entries[highlight].decrease_api();
                }

            }
            if(btn3 == 1)
            {
                if(entries[highlight].increase_api != 0)
                {
                    entries[highlight].increase_api();
                }
            }
        }
            break;
    }
    OLED_Driver_PutString(string);
    OLED_Driver_InverseSection(line_highlight, highlight_start, highlight_end);
    return state != Highlight_Inactive;
}
