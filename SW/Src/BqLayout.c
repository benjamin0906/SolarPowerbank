/*
 * BqLayout.c
 *
 *  Created on: 2026. okt. 22.
 *      Author: Benjamin
 */

#include "BQ25690_Driver.h"
#include "OLED_Driver.h"

static uint8 string[] = "       STATS\nPG: 0\nIindpm: 0\nVindpm: 0\nTreg: 0\nChg stat: 0\nICO stat: 0\nTS stat: 0";

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
