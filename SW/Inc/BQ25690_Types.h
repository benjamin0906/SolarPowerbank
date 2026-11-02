/*
 * BQ25690_Types.h
 *
 *  Created on: 2026. okt. 21.
 *      Author: Benjamin
 */

#ifndef BQ25690_TYPES_H_
#define BQ25690_TYPES_H_

#include "types.h"

typedef union uREG00
{
    uint16 U;
    struct sREG00_Bits
    {
        uint16          :4;
        uint16 VSYSMIN  :11;
        uint16          :1;
    } B;
} dtREG00;

typedef union uREG02
{
    uint16 U;
    struct sREG02_Bits
    {
        uint16      :4;
        uint16 ICHG :8;
        uint16      :4;
    } B;
} dtREG02;

typedef union uREG04
{
    uint16 U;
    struct sREG04_Bits
    {
        uint16      :3;
        uint16 VREG :12;
        uint16      :1;
    } B;
} dtREG04;

typedef union uREG06
{
    uint16 U;
    struct sREG06_Bits
    {
        uint16          :4;
        uint16 IINDPM   :8;
        uint16          :4;
    } B;
} dtREG06;

typedef union uREG08
{
    uint16 U;
    struct sREG08_Bits
    {
        uint16          :4;
        uint16 VINDPM   :11;
        uint16          :1;
    } B;
} dtREG08;

typedef union uREG0A
{
    uint16 U;
    struct sREG0A_Bits
    {
        uint16          :4;
        uint16 IIN_REV  :8;
        uint16          :4;
    } B;
} dtREG0A;

typedef union uREG0C
{
    uint16 U;
    struct sREG0C_Bits
    {
        uint16          :4;
        uint16 VIN_REV  :11;
        uint16          :1;
    } B;
} dtREG0C;

typedef union uREG0E
{
    uint8 U;
    struct sREG0E_Bits
    {
        uint8 IPRECHG   :6;
        uint8           :2;
    } B;
} dtREG0E;

typedef union uREG0F
{
    uint8 U;
    struct sREG0F_Bits
    {
        uint8 ITERM     :6;
        uint8           :2;
    } B;
} dtREG0F;

typedef union uREG10
{
    uint8 U;
    struct sREG10_Bits
    {
        uint8 EN_PRECHG :1;
        uint8 VBAT_LOWV :2;
        uint8 EN_TERM   :1;
        uint8 VRECHG    :2;
        uint8 DIS_STAT  :1;
        uint8 REG_RST   :1;
    } B;
} dtREG10;

typedef union uREG11
{
    uint8 U;
    struct sREG11_Bits
    {
        uint8 EN_TMR2X  :1;
        uint8 CHG_TMR   :2;
        uint8 EN_CHG_TMR:1;
        uint8 WATCHDOG  :2;
        uint8 TOPOFF_TMR:2;
    } B;
} dtREG11;

typedef union uREG12
{
    uint8 U;
    struct sREG12_Bits
    {
        uint8 PRECHG_TMR    :1;
        uint8 STOP_WD_CHG   :1;
        uint8 WD_RST        :1;
        uint8 EN_EXT_BYPASS :1;
        uint8 EN_BYPASS     :1;
        uint8 RBAT_SNS      :1;
        uint8 IBAT_REV      :2;
    } B;
} dtREG12;

typedef union uREG13
{
    uint8 U;
    struct sREG13_Bits
    {
        uint8 EN_BACKUP         :1;
        uint8 EN_REV            :1;
        uint8 RAC_SNS           :1;
        uint8 FORCE_VIN_DSCHG   :1;
        uint8 EN_HIZ            :1;
        uint8 EN_CHG            :1;
        uint8 FORCE_ISYS_DSCHG  :1;
        uint8 EN_AUTO_DSCHG     :1;
    } B;
} dtREG13;

typedef union uREG14
{
    uint8 U;
    struct sREG_14_Bits
    {
        uint8 EN_ICO        :1;
        uint8 FORCE_ICO     :1;
        uint8 FORCE_VINDPM  :1;
        uint8 EN_BAT_DETECT :1;
        uint8 BATFET_CTRL   :1;
        uint8 EN_EXTILIM    :1;
        uint8 VIN_BACKUP    :2;
    } B;
} dtREG14;

typedef union uREG15
{
    uint8 U;
    struct sREG_15_Bits
    {
        uint8 VBAT_DETECT   :2;
        uint8               :1;
        uint8 EN_FAST_VOTG_RESPONSE :1;
        uint8               :4;
    } B;
} dtREG15;

typedef union uREG16
{
    uint8 U;
    struct sREG_16_Bits
    {
        uint8 FSW       :3;
        uint8 EN_DITHER :2;
        uint8 TREG      :1;
        uint8 EN_PFM_OOA:1;
        uint8 EN_PFM    :1;
    } B;
} dtREG16;

typedef union uREG17
{
    uint8 U;
    struct sREG_17_Bits
    {
        uint8 EN_MPPT   :1;
        uint8 VOC_RATE  :2;
        uint8 VOC_DLY   :2;
        uint8 VOC_PCT   :3;
    } B;
} dtREG17;

typedef union uREG18
{
    uint8 U;
    struct sREG_18_Bits
    {
        uint8 TS_TH1    :2;
        uint8 TS_TH2    :2;
        uint8 TS_TH3    :2;
        uint8 TS_TH5    :2;
    } B;
} dtREG18;

typedef union uREG19
{
    uint8 U;
    struct sREG_19_Bits
    {
        uint8 EN_TS         :1;
        uint8 EN_JEITA      :1;
        uint8 JEITA_ISETC   :2;
        uint8 JEITA_ISETH   :1;
        uint8 JEITA_VSET    :2;
        uint8 EN_BYPASS_LL_EXIT:1;
    } B;
} dtREG19;

typedef union uREG1A
{
    uint8 U;
    struct sREG_1A_Bits
    {
        uint8 CV_TMR        :4;
        uint8               :1;
        uint8 TS_REV_COLD   :1;
        uint8 TS_REV_HOT    :2;
    } B;
} dtREG1A;

typedef union uREG1B
{
    uint8 U;
    struct sREG_1B_Bits
    {
        uint8 CELL_PIN          :3;
        uint8 VCHG_PIN          :3;
        uint8 CELL_PIN_OVERRIDE :1;
        uint8 VCHG_PIN_OVERRIDE :1;
    } B;
} dtREG1B;

typedef union uREG1C
{
    uint8 U;
    struct sREG_1C_Bits
    {
        uint8 ICHG_PIN          :3;
        uint8 ICHG_PIN_OVERRIDE :1;
        uint8                   :4;
    } B;
} dtREG1C;

typedef union uREG1D
{
    uint8 U;
    struct sREG_1D_Bits
    {
        uint8 CHARGE_STAT   :3;
        uint8 WD_STAT       :1;
        uint8 TREG_STAT     :1;
        uint8 VINDPM_STAT   :1;
        uint8 IINDPM_STAT   :1;
        uint8 PG_STAT       :1;
    } B;
} dtREG1D;

typedef union uREG1E
{
    uint8 U;
    struct sREG_1E_Bits
    {
        uint8 TS_STAT   :3;
        uint8 REV_STAT  :2;
        uint8 ICO_STAT  :2;
        uint8           :1;
    } B;
} dtREG1E;

typedef union uREG1F
{
    uint8 U;
    struct sREG_1F_Bits
    {
        uint8 REV_TERM_STAT :1;
        uint8               :1;
        uint8 TSHUT_STAT    :1;
        uint8 CV_TMR_STAT   :1;
        uint8 CHG_TMR_STAT  :1;
        uint8 BAT_FAULT_STAT:2;
        uint8 VIN_OVP_STAT  :1;
    } B;
} dtREG1F;

typedef union uREG20
{
    uint8 U;
    struct sREG_20_Bits
    {
        uint8 CHARGE_FLAG   :1;
        uint8 TS_FLAG       :1;
        uint8 ICO_FLAG      :1;
        uint8 WD_FLAG       :1;
        uint8 TREG_FLAG     :1;
        uint8 VINDPM_FLAG   :1;
        uint8 IINDPM_FLAG   :1;
        uint8 PG_FLAG       :1;
    } B;
} dtREG20;

typedef union uREG21
{
    uint8 U;
    struct sREG_21_Bits
    {
        uint8 REV_FLAG      :1;
        uint8               :1;
        uint8 BYPASS_FLAG   :1;
        uint8 TSHUT_FLAG    :1;
        uint8 CV_TMR_FLAG   :1;
        uint8 CHG_TMR_FLAG  :1;
        uint8 BAT_FAULT_FLAG:1;
        uint8 VIN_OVP_FLAG  :1;
    } B;
} dtREG21;

typedef union uREG22
{
    uint8 U;
    struct sREG_22_Bits
    {
        uint8 CHARGE_MASK   :1;
        uint8 TS_MASK       :1;
        uint8 ICO_MASK      :1;
        uint8 WD_MASK       :1;
        uint8 TREG_MASK     :1;
        uint8 VINDPM_MASK   :1;
        uint8 IINDPM_MASK   :1;
        uint8 PG_MASK       :1;
    } B;
} dtREG22;

typedef union uREG23
{
    uint8 U;
    struct sREG_23_Bits
    {
        uint8 REV_MASK      :1;
        uint8               :1;
        uint8 BYPASS_MASK   :1;
        uint8 TSHUT_MASK    :1;
        uint8 CV_TMR_MASK   :1;
        uint8 CHG_TMR_MASK  :1;
        uint8 BAT_FAULT_MASK:1;
        uint8 VIN_OVP_MASK  :1;
    } B;
} dtREG23;

typedef union uREG24
{
    uint16 U;
    struct sREG_24_Bits
    {
        uint16              :4;
        uint16 ICO_IINDPM   :8;
        uint16              :4;
    } B;
} dtREG24;

typedef union uREG26
{
    uint8 U;
    struct sREG_26_Bits
    {
        uint8 DEV_REV   :2;
        uint8 PN        :4;
        uint8           :2;
    } B;
} dtREG26;

typedef struct sBQ25690
{
    dtREG00 REG00;
    dtREG02 REG02;
    dtREG04 REG04;
    dtREG06 REG06;
    dtREG08 REG08;
    dtREG0A REG0A;
    dtREG0C REG0C;
    dtREG0E REG0E;
    dtREG0F REG0F;
    dtREG10 REG10;
    dtREG11 REG11;
    dtREG12 REG12;
    dtREG13 REG13;
    dtREG14 REG14;
    dtREG15 REG15;
    dtREG16 REG16;
    dtREG17 REG17;
    dtREG18 REG18;
    dtREG19 REG19;
    dtREG1A REG1A;
    dtREG1B REG1B;
    dtREG1C REG1C;
    dtREG1D REG1D;
    dtREG1E REG1E;
    dtREG1F REG1F;
    dtREG20 REG20;
    dtREG21 REG21;
    dtREG22 REG22;
    dtREG23 REG23;
    dtREG24 REG24;
    dtREG26 REG26;
} dtBQ25690;

#endif /* BQ25690_TYPES_H_ */
