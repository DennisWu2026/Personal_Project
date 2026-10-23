#ifndef REGISTERS_H
#define REGISTERS_H

#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <valarray>
#include "sub.h"
struct I2CRegister {
    std::string name;
    uint8_t msb;
    uint8_t lsb;
    uint16_t address;
    uint16_t dft_val;
    I2CRegister(std::string n, uint8_t m, uint8_t l, uint16_t addr, uint16_t dft_value)
        : name(std::move(n)), msb(m), lsb(l), address(addr), dft_val(dft_value) {}
};
//A0 register map
const I2CRegister CHIP_ID_H = I2CRegister("CHIP_ID_H", 7, 0, 0x00, 0x16);
const I2CRegister CHIP_ID_L = I2CRegister("CHIP_ID_L", 7, 3, 0x01, 0x10);
const I2CRegister CHIP_ID_TRIM = I2CRegister("CHIP_ID_TRIM", 2, 0, 0x01, 0x02);
const I2CRegister RESERVED = I2CRegister("RESERVED", 7, 3, 0x02, 0x00);
const I2CRegister CHIP_REV = I2CRegister("CHIP_REV", 2, 0, 0x02, 0x00);
const I2CRegister TRANSFER_PHASE = I2CRegister("TRANSFER_PHASE", 7, 7, 0x03, 0x00);
const I2CRegister OTP_STAT = I2CRegister("OTP_STAT", 6, 6, 0x03, 0x00);
const I2CRegister OVP1_STAT = I2CRegister("OVP1_STAT", 5, 5, 0x03, 0x00);
const I2CRegister OVP2_STAT = I2CRegister("OVP2_STAT", 4, 4, 0x03, 0x00);
const I2CRegister OCP_STAT = I2CRegister("OCP_STAT", 3, 3, 0x03, 0x00);
const I2CRegister SCP_STAT = I2CRegister("SCP_STAT", 2, 2, 0x03, 0x00);
const I2CRegister RECT_ON_FM_POR = I2CRegister("RECT_ON_FM_POR", 1, 1, 0x03, 0x00);
const I2CRegister EN_LDO_FM_POR = I2CRegister("EN_LDO_FM_POR", 0, 0, 0x03, 0x00);
const I2CRegister FSK_DDM_INT = I2CRegister("FSK_DDM_INT", 7, 7, 0x04, 0x00);
const I2CRegister OTP = I2CRegister("OTP", 6, 6, 0x04, 0x00);
const I2CRegister OVP1 = I2CRegister("OVP1", 5, 5, 0x04, 0x00);
const I2CRegister OVP2 = I2CRegister("OVP2", 4, 4, 0x04, 0x00);
const I2CRegister OCP = I2CRegister("OCP", 3, 3, 0x04, 0x00);
const I2CRegister SCP = I2CRegister("SCP", 2, 2, 0x04, 0x00);
const I2CRegister WARMUP_DONE = I2CRegister("WARMUP_DONE", 1, 1, 0x04, 0x00);
const I2CRegister TTP_INT = I2CRegister("TTP_INT", 0, 0, 0x04, 0x00);
const I2CRegister FORCE_INT_OFF = I2CRegister("FORCE_INT_OFF", 7, 7, 0x05, 0x00);
const I2CRegister FORCE_EPT_DIS = I2CRegister("FORCE_EPT_DIS", 6, 6, 0x05, 0x00);
const I2CRegister FORCE_DMY_OFF = I2CRegister("FORCE_DMY_OFF", 5, 5, 0x05, 0x00);
const I2CRegister FORCE_SINK_OFF = I2CRegister("FORCE_SINK_OFF", 4, 4, 0x05, 0x00);
const I2CRegister FORCE_RECT_LS_OFF = I2CRegister("FORCE_RECT_LS_OFF", 3, 3, 0x05, 0x00);
const I2CRegister FORCE_LDO_OFF = I2CRegister("FORCE_LDO_OFF", 2, 2, 0x05, 0x00);
const I2CRegister FORCE_RECT_LS_ON = I2CRegister("FORCE_RECT_LS_ON", 1, 1, 0x05, 0x00);
const I2CRegister FORCE_LDO_ON = I2CRegister("FORCE_LDO_ON", 0, 0, 0x05, 0x00);
const I2CRegister AP_SET_PKT2_EN = I2CRegister("AP_SET_PKT2_EN", 7, 7, 0x06, 0x00);
const I2CRegister AP_SET_PKT2 = I2CRegister("AP_SET_PKT2", 6, 0, 0x06, 0x00);
const I2CRegister FORCE_RECT_HS_OFF = I2CRegister("FORCE_RECT_HS_OFF", 7, 7, 0x07, 0x00);
const I2CRegister ASK_DMY_H = I2CRegister("ASK_DMY_H", 6, 3, 0x07, 0x00);
const I2CRegister ASK_DMY_L = I2CRegister("ASK_DMY_L", 2, 0, 0x07, 0x00);
const I2CRegister FORCE_IIC_OS_ACR = I2CRegister("FORCE_IIC_OS_ACR", 7, 7, 0x08, 0x00);
const I2CRegister PROT_SR_OFF_RESET = I2CRegister("PROT_SR_OFF_RESET", 6, 6, 0x08, 0x00);
const I2CRegister PROT_MLDO_OFF_RESET = I2CRegister("PROT_MLDO_OFF_RESET", 5, 5, 0x08, 0x00);
const I2CRegister IIC_COMM_RDSON_OPT = I2CRegister("IIC_COMM_RDSON_OPT", 4, 4, 0x08, 0x00);
const I2CRegister ASK_SINK_EN = I2CRegister("ASK_SINK_EN", 3, 3, 0x08, 0x00);
const I2CRegister ASK_DUMMY_EN = I2CRegister("ASK_DUMMY_EN", 2, 2, 0x08, 0x00);
const I2CRegister COMM2_DIS = I2CRegister("COMM2_DIS", 1, 1, 0x08, 0x00);
const I2CRegister COMM1_DIS = I2CRegister("COMM1_DIS", 0, 0, 0x08, 0x00);
const I2CRegister IIC_DUMMY_RESERVED = I2CRegister("IIC_DUMMY_RESERVED", 7, 4, 0x09, 0x00);
const I2CRegister IIC_DUMMY = I2CRegister("IIC_DUMMY", 3, 0, 0x09, 0x00);
const I2CRegister ASK_INT_EN = I2CRegister("ASK_INT_EN", 7, 7, 0x0A, 0x00);
const I2CRegister PKT_FSM_DIS = I2CRegister("PKT_FSM_DIS", 6, 6, 0x0A, 0x00);
const I2CRegister PKT_ST_SEL = I2CRegister("PKT_ST_SEL", 5, 5, 0x0A, 0x00);
const I2CRegister PKT_MSG_SEL = I2CRegister("PKT_MSG_SEL", 4, 4, 0x0A, 0x00);
const I2CRegister PKT_HED_SEL = I2CRegister("PKT_HED_SEL", 3, 3, 0x0A, 0x00);
const I2CRegister PKT_PRE_DIS = I2CRegister("PKT_PRE_DIS", 2, 2, 0x0A, 0x00);
const I2CRegister PKT_PRE_OPT = I2CRegister("PKT_PRE_OPT", 1, 1, 0x0A, 0x00);
const I2CRegister PKT_IIC_ST = I2CRegister("PKT_IIC_ST", 0, 0, 0x0A, 0x00);
const I2CRegister ASK_MOD_OPT_RESERVED = I2CRegister("ASK_MOD_OPT_RESERVED", 7, 7, 0x0B, 0x00);
const I2CRegister BMC_END_OPT = I2CRegister("BMC_END_OPT", 6, 4, 0x0B, 0x00);
const I2CRegister TTP_LAST_DATA_LT = I2CRegister("TTP_LAST_DATA_LT", 3, 0, 0x0B, 0x00);
const I2CRegister ASK_TTP_LT = I2CRegister("ASK_TTP_LT", 7, 0, 0x0C, 0x00);
const I2CRegister ASK_PRE_LT = I2CRegister("ASK_PRE_LT", 7, 0, 0x0D, 0x00);
const I2CRegister ASK_TTP_HEADER = I2CRegister("ASK_TTP_HEADER", 7, 0, 0x0E, 0x00);
const I2CRegister MAIN_LOOP_CTRL_RESERVED = I2CRegister("MAIN_LOOP_CTRL_RESERVED", 7, 5, 0x0F, 0x00);
const I2CRegister IIC_CE_FAST = I2CRegister("IIC_CE_FAST", 4, 4, 0x0F, 0x00);
const I2CRegister FORCE_LAST_CE_00_DIS = I2CRegister("FORCE_LAST_CE_00_DIS", 3, 3, 0x0F, 0x00);
const I2CRegister FSK_DDM_TTP_EN = I2CRegister("FSK_DDM_TTP_EN", 2, 2, 0x0F, 0x00);
const I2CRegister FSK_DDM_03_EN = I2CRegister("FSK_DDM_03_EN", 1, 1, 0x0F, 0x00);
const I2CRegister TTP_EN = I2CRegister("TTP_EN", 0, 0, 0x0F, 0x00);
const I2CRegister TTP_DATA0 = I2CRegister("TTP_DATA0", 7, 0, 0x10, 0x00);
const I2CRegister TTP_DATA1 = I2CRegister("TTP_DATA1", 7, 0, 0x11, 0x00);
const I2CRegister TTP_DATA2 = I2CRegister("TTP_DATA2", 7, 0, 0x12, 0x00);
const I2CRegister TTP_DATA3 = I2CRegister("TTP_DATA3", 7, 0, 0x13, 0x00);
const I2CRegister TTP_DATA4 = I2CRegister("TTP_DATA4", 7, 0, 0x14, 0x00);
const I2CRegister TTP_DATA5 = I2CRegister("TTP_DATA5", 7, 0, 0x15, 0x00);
const I2CRegister TTP_DATA6 = I2CRegister("TTP_DATA6", 7, 0, 0x16, 0x00);
const I2CRegister TTP_DATA7 = I2CRegister("TTP_DATA7", 7, 0, 0x17, 0x00);
const I2CRegister ASK_STAT_RESERVED = I2CRegister("ASK_STAT_RESERVED", 7, 7, 0x18, 0x00);
const I2CRegister ASK_START_SIGNAL = I2CRegister("ASK_START_SIGNAL", 6, 4, 0x18, 0x00);
const I2CRegister ASK_PERIOD = I2CRegister("ASK_PERIOD", 3, 3, 0x18, 0x00);
const I2CRegister AP_NO_UPDATE_TTP_BUF = I2CRegister("AP_NO_UPDATE_TTP_BUF", 2, 2, 0x18, 0x00);
const I2CRegister ASK_DONE = I2CRegister("ASK_DONE", 1, 1, 0x18, 0x00);
const I2CRegister BUF_BUSY_FLAG = I2CRegister("BUF_BUSY_FLAG", 0, 0, 0x18, 0x00);
const I2CRegister FSK_DMOD_CTRL_0_RESERVED = I2CRegister("FSK_DMOD_CTRL_0_RESERVED", 7, 5, 0x19, 0x00);
const I2CRegister FSK_DMOD_CYCLE_SEL = I2CRegister("FSK_DMOD_CYCLE_SEL", 4, 2, 0x19, 0x00);
const I2CRegister PREAMBLE_MODE = I2CRegister("PREAMBLE_MODE", 1, 1, 0x19, 0x00);
const I2CRegister FSK_DMOD_CH_SEL = I2CRegister("FSK_DMOD_CH_SEL", 0, 0, 0x19, 0x00);
const I2CRegister DEG_PERIOD_STATE_NUM = I2CRegister("DEG_PERIOD_STATE_NUM", 7, 5, 0x1A, 0x00);
const I2CRegister DMOD_PERIOD_STATE_METHOD_TYPE = I2CRegister("DMOD_PERIOD_STATE_METHOD_TYPE", 4, 4, 0x1A, 0x00);
const I2CRegister PACK_TYPE = I2CRegister("PACK_TYPE", 3, 3, 0x1A, 0x00);
const I2CRegister STORE_BYTE_TYPE = I2CRegister("STORE_BYTE_TYPE", 2, 2, 0x1A, 0x00);
const I2CRegister FSK_DMOD_CTRL_1_RESERVED = I2CRegister("FSK_DMOD_CTRL_1_RESERVED", 1, 0, 0x1A, 0x00);
const I2CRegister TIMEOUT_INT_MASK = I2CRegister("TIMEOUT_INT_MASK", 7, 7, 0x1B, 0x00);
const I2CRegister DELAY_TIME_SEL = I2CRegister("DELAY_TIME_SEL", 6, 5, 0x1B, 0x00);
const I2CRegister FORCE_FSK_DMOD = I2CRegister("FORCE_FSK_DMOD", 4, 4, 0x1B, 0x00);
const I2CRegister ONE_BIT_CYCLE_NUM_TYPE = I2CRegister("ONE_BIT_CYCLE_NUM_TYPE", 3, 2, 0x1B, 0x00);
const I2CRegister TIMEOUT_TIME_SEL = I2CRegister("TIMEOUT_TIME_SEL", 1, 1, 0x1B, 0x00);
const I2CRegister PACK_DONE_TARGET_TYPE = I2CRegister("PACK_DONE_TARGET_TYPE", 0, 0, 0x1B, 0x00);
const I2CRegister FSK_DMOD_BIT_HYS_F = I2CRegister("FSK_DMOD_BIT_HYS_F", 7, 0, 0x1C, 0x00);
const I2CRegister FSK_DMOD_BIT_THD_R = I2CRegister("FSK_DMOD_BIT_THD_R", 7, 0, 0x1D, 0x00);
const I2CRegister FSK_DMOD_CTRL_5_RESERVED = I2CRegister("FSK_DMOD_CTRL_5_RESERVED", 7, 2, 0x1E, 0x00);
const I2CRegister FSK_DMOD_CTRL_5_FSK_DMOD_BIT_THD_R = I2CRegister("FSK_DMOD_CTRL_5_FSK_DMOD_BIT_THD_R", 1, 0, 0x1E, 0x00);
const I2CRegister FSK_DEG_TIME = I2CRegister("FSK_DEG_TIME", 7, 0, 0x1F, 0x00);
const I2CRegister DECODE_STATUS0_RESERVED = I2CRegister("DECODE_STATUS0_RESERVED", 7, 5, 0x20, 0x00);
const I2CRegister DECODE_ERROR_INT_FLAG = I2CRegister("DECODE_ERROR_INT_FLAG", 4, 4, 0x20, 0x00);
const I2CRegister DECODE_DONE_INT_FLAG = I2CRegister("DECODE_DONE_INT_FLAG", 3, 3, 0x20, 0x00);
const I2CRegister BUFF_FULL_INT_FAG = I2CRegister("BUFF_FULL_INT_FAG", 2, 2, 0x20, 0x00);
const I2CRegister TIMEOUT_INT_FLAG = I2CRegister("TIMEOUT_INT_FLAG", 1, 1, 0x20, 0x00);
const I2CRegister FSK_DMOD_EN = I2CRegister("FSK_DMOD_EN", 0, 0, 0x20, 0x00);
const I2CRegister DECODE_STATUS1_RESERVED = I2CRegister("DECODE_STATUS1_RESERVED", 7, 7, 0x21, 0x00);
const I2CRegister CHECKSUM_RESULT_ERROR = I2CRegister("CHECKSUM_RESULT_ERROR", 6, 6, 0x21, 0x00);
const I2CRegister CHECKSUM_ERROR = I2CRegister("CHECKSUM_ERROR", 5, 5, 0x21, 0x00);
const I2CRegister STOP_BIT_ERROR = I2CRegister("STOP_BIT_ERROR", 4, 4, 0x21, 0x00);
const I2CRegister PARITY_BIT_ERROR = I2CRegister("PARITY_BIT_ERROR", 3, 3, 0x21, 0x00);
const I2CRegister START_BIT_ERROR = I2CRegister("START_BIT_ERROR", 2, 2, 0x21, 0x00);
const I2CRegister PREAMBLE_NUM_ERROR = I2CRegister("PREAMBLE_NUM_ERROR", 1, 1, 0x21, 0x00);
const I2CRegister BUFF_OVERFLOW = I2CRegister("BUFF_OVERFLOW", 0, 0, 0x21, 0x00);
const I2CRegister VALID_BIT_NUM_OF_LAST_BUFF = I2CRegister("VALID_BIT_NUM_OF_LAST_BUFF", 7, 4, 0x22, 0x00);
const I2CRegister VALID_BYTE_NUM = I2CRegister("VALID_BYTE_NUM", 3, 0, 0x22, 0x00);
const I2CRegister BYTE_BUFF0 = I2CRegister("BYTE_BUFF0", 7, 0, 0x23, 0x00);
const I2CRegister BYTE_BUFF1 = I2CRegister("BYTE_BUFF1", 7, 0, 0x24, 0x00);
const I2CRegister BYTE_BUFF2 = I2CRegister("BYTE_BUFF2", 7, 0, 0x25, 0x00);
const I2CRegister BYTE_BUFF3 = I2CRegister("BYTE_BUFF3", 7, 0, 0x26, 0x00);
const I2CRegister BYTE_BUFF4 = I2CRegister("BYTE_BUFF4", 7, 0, 0x27, 0x00);
const I2CRegister BYTE_BUFF5 = I2CRegister("BYTE_BUFF5", 7, 0, 0x28, 0x00);
const I2CRegister BYTE_BUFF6 = I2CRegister("BYTE_BUFF6", 7, 0, 0x29, 0x00);
const I2CRegister BYTE_BUFF7 = I2CRegister("BYTE_BUFF7", 7, 0, 0x2A, 0x00);
const I2CRegister FSK_BASE_DATA_LOW_BYTE = I2CRegister("FSK_BASE_DATA_LOW_BYTE", 7, 0, 0x2B, 0x00);
const I2CRegister FSK_BASE_DATA_HIGH_BYTE = I2CRegister("FSK_BASE_DATA_HIGH_BYTE", 7, 0, 0x2C, 0x00);
const I2CRegister FSK_DM_DATA_LOW_BYTE = I2CRegister("FSK_DM_DATA_LOW_BYTE", 7, 0, 0x2D, 0x00);
const I2CRegister FSK_DM_DATA_HIGH_BYTE = I2CRegister("FSK_DM_DATA_HIGH_BYTE", 7, 0, 0x2E, 0x00);
const I2CRegister OPT_0_RESERVED = I2CRegister("OPT_0_RESERVED", 7, 5, 0x30, 0x00);
const I2CRegister VRECT_OVP2_THD = I2CRegister("VRECT_OVP2_THD", 4, 4, 0x30, 0x00);
const I2CRegister VRECT_OVP1_THD = I2CRegister("VRECT_OVP1_THD", 3, 3, 0x30, 0x00);
const I2CRegister TRIM_BMC_END = I2CRegister("TRIM_BMC_END", 2, 2, 0x30, 0x00);
const I2CRegister LDO_OCP_THD = I2CRegister("LDO_OCP_THD", 1, 0, 0x30, 0x00);
const I2CRegister RES_OFFSET23_X2 = I2CRegister("RES_OFFSET23_X2", 7, 7, 0x31, 0x00);
const I2CRegister RES_OFFSET1_X2 = I2CRegister("RES_OFFSET1_X2", 6, 6, 0x31, 0x00);
const I2CRegister COMP_LS_OFF_VTH = I2CRegister("COMP_LS_OFF_VTH", 5, 4, 0x31, 0x00);
const I2CRegister MIN_OFF_SET = I2CRegister("MIN_OFF_SET", 3, 2, 0x31, 0x00);
const I2CRegister MOT_SET = I2CRegister("MOT_SET", 1, 0, 0x31, 0x00);
const I2CRegister OPT1_LOCK = I2CRegister("OPT1_LOCK", 7, 7, 0x32, 0x00);
const I2CRegister OPT_2_RESERVED = I2CRegister("OPT_2_RESERVED", 6, 4, 0x32, 0x00);
const I2CRegister MTP_DUMMY_0 = I2CRegister("MTP_DUMMY_0", 3, 0, 0x32, 0x08);
const I2CRegister MANU_CODE_H = I2CRegister("MANU_CODE_H", 7, 0, 0x33, 0x00);
const I2CRegister MANU_CODE_L = I2CRegister("MANU_CODE_L", 7, 0, 0x34, 0x5C);
const I2CRegister OPT_5_RESERVED = I2CRegister("OPT_5_RESERVED", 7, 6, 0x35, 0x00);
const I2CRegister MTP_ACR1 = I2CRegister("MTP_ACR1", 5, 0, 0x35, 0x3F);
const I2CRegister OPT_6_RESERVED = I2CRegister("OPT_6_RESERVED", 7, 5, 0x36, 0x00);
const I2CRegister MTP_OFFSET1 = I2CRegister("MTP_OFFSET1", 4, 0, 0x36, 0x1F);
const I2CRegister OPT_7_RESERVED = I2CRegister("OPT_7_RESERVED", 7, 5, 0x37, 0x00);
const I2CRegister MTP_OFFSET2_3 = I2CRegister("MTP_OFFSET2_3", 4, 0, 0x37, 0x1F);
const I2CRegister MTP_VOUT_SET = I2CRegister("MTP_VOUT_SET", 7, 0, 0x38, 0x7D);
const I2CRegister OPT_9_RESERVED = I2CRegister("OPT_9_RESERVED", 7, 7, 0x39, 0x00);
const I2CRegister LDO_ON_OPT = I2CRegister("LDO_ON_OPT", 6, 5, 0x39, 0x00);
const I2CRegister LDO_VDROP = I2CRegister("LDO_VDROP", 4, 2, 0x39, 0x00);
const I2CRegister ILOAD_OPT = I2CRegister("ILOAD_OPT", 1, 0, 0x39, 0x00);
const I2CRegister OPT10_RESERVED = I2CRegister("OPT10_RESERVED", 7, 7, 0x3A, 0x00);
const I2CRegister MTP_CE_LMT = I2CRegister("MTP_CE_LMT", 6, 5, 0x3A, 0x00);
const I2CRegister WARM_UP_OPT = I2CRegister("WARM_UP_OPT", 4, 4, 0x3A, 0x00);
const I2CRegister MTP_CE_LARGE = I2CRegister("MTP_CE_LARGE", 3, 3, 0x3A, 0x00);
const I2CRegister CYCLE_EN = I2CRegister("CYCLE_EN", 2, 2, 0x3A, 0x00);
const I2CRegister TINTERVAL_OPT = I2CRegister("TINTERVAL_OPT", 1, 0, 0x3A, 0x00);
const I2CRegister OPT11_RESERVED = I2CRegister("OPT11_RESERVED", 7, 6, 0x3B, 0x00);
const I2CRegister SCP_OFF_LDO_DIS = I2CRegister("SCP_OFF_LDO_DIS", 5, 5, 0x3B, 0x00);
const I2CRegister OCP_OFF_LDO_DIS = I2CRegister("OCP_OFF_LDO_DIS", 4, 4, 0x3B, 0x00);
const I2CRegister OTP_OFF_LDO_DIS = I2CRegister("OTP_OFF_LDO_DIS", 3, 3, 0x3B, 0x00);
const I2CRegister OVP2_OFF_SR_DIS = I2CRegister("OVP2_OFF_SR_DIS", 2, 2, 0x3B, 0x00);
const I2CRegister LOAD0_COMM_RDSON_OPT = I2CRegister("LOAD0_COMM_RDSON_OPT", 1, 1, 0x3B, 0x01);
const I2CRegister MTP_OVP_EPT_EN = I2CRegister("MTP_OVP_EPT_EN", 0, 0, 0x3B, 0x00);
const I2CRegister FSK_DDM_MASK = I2CRegister("FSK_DDM_MASK", 7, 7, 0x3C, 0x00);
const I2CRegister OTP_MASK = I2CRegister("OTP_MASK", 6, 6, 0x3C, 0x00);
const I2CRegister OVP1_MASK = I2CRegister("OVP1_MASK", 5, 5, 0x3C, 0x00);
const I2CRegister OVP2_MASK = I2CRegister("OVP2_MASK", 4, 4, 0x3C, 0x00);
const I2CRegister OCP_MASK = I2CRegister("OCP_MASK", 3, 3, 0x3C, 0x00);
const I2CRegister SCP_MASK = I2CRegister("SCP_MASK", 2, 2, 0x3C, 0x00);
const I2CRegister WARM_UP_MASK = I2CRegister("WARM_UP_MASK", 1, 1, 0x3C, 0x00);
const I2CRegister TTP_INT_MASK = I2CRegister("TTP_INT_MASK", 0, 0, 0x3C, 0x00);
const I2CRegister BDI_B6 = I2CRegister("BDI_B6", 7, 0, 0x3D, 0x00);
const I2CRegister OPT2_LOCK = I2CRegister("OPT2_LOCK", 7, 7, 0x3E, 0x00);
const I2CRegister OPT14_RESERVED = I2CRegister("OPT14_RESERVED", 6, 0, 0x3E, 0x00);
const I2CRegister ADC_IOUT_FILT_L = I2CRegister("ADC_IOUT_FILT_L", 7, 0, 0x3F, 0x00);
const I2CRegister ADC_IOUT_FILT_H_RESERVED = I2CRegister("ADC_IOUT_FILT_H_RESERVED", 7, 2, 0x40, 0x00);
const I2CRegister ADC_IOUT_FILT_H = I2CRegister("ADC_IOUT_FILT_H", 1, 0, 0x40, 0x00);
const I2CRegister ADC_VOUT_FILT_L = I2CRegister("ADC_VOUT_FILT_L", 7, 0, 0x41, 0x00);
const I2CRegister ADC_VOUT_FILT_H_RESERVED = I2CRegister("ADC_VOUT_FILT_H_RESERVED", 7, 2, 0x42, 0x00);
const I2CRegister ADC_VOUT_FILT_H = I2CRegister("ADC_VOUT_FILT_H", 1, 0, 0x42, 0x00);
const I2CRegister ADC_VRECT_FILT_L = I2CRegister("ADC_VRECT_FILT_L", 7, 0, 0x43, 0x00);
const I2CRegister ADC_VRECT_FILT_H_RESERVED = I2CRegister("ADC_VRECT_FILT_H_RESERVED", 7, 3, 0x44, 0x00);
const I2CRegister ADC_VRECT_FILT_H = I2CRegister("ADC_VRECT_FILT_H", 2, 0, 0x44, 0x00);
const I2CRegister ADC_TEMP_CONV_L = I2CRegister("ADC_TEMP_CONV_L", 7, 0, 0x47, 0x00);
const I2CRegister ADC_TEMP_CONV_H_RESERVED = I2CRegister("ADC_TEMP_CONV_H_RESERVED", 7, 2, 0x48, 0x00);
const I2CRegister ADC_TEMP_CONV_H = I2CRegister("ADC_TEMP_CONV_H", 1, 0, 0x48, 0x00);
const I2CRegister ADC_INTB_CONV_L = I2CRegister("ADC_INTB_CONV_L", 7, 0, 0x49, 0x00);
const I2CRegister ADC_INTB_CONV_H_RESERVED = I2CRegister("ADC_INTB_CONV_H_RESERVED", 7, 2, 0x4A, 0x00);
const I2CRegister ADC_INTB_CONV_H = I2CRegister("ADC_INTB_CONV_H", 1, 0, 0x4A, 0x00);
const I2CRegister ADC_SDA_CONV_L = I2CRegister("ADC_SDA_CONV_L", 7, 0, 0x4B, 0x00);
const I2CRegister ADC_SDA_CONV_H_RESERVED = I2CRegister("ADC_SDA_CONV_H_RESERVED", 7, 2, 0x4C, 0x00);
const I2CRegister ADC_SDA_CONV_H = I2CRegister("ADC_SDA_CONV_H", 1, 0, 0x4C, 0x00);
const I2CRegister ADC_SCL_CONV_L = I2CRegister("ADC_SCL_CONV_L", 7, 0, 0x4D, 0x00);
const I2CRegister ADC_SCL_CONV_H_RESERVED = I2CRegister("ADC_SCL_CONV_H_RESERVED", 7, 2, 0x4E, 0x00);
const I2CRegister ADC_SCL_CONV_H = I2CRegister("ADC_SCL_CONV_H", 1, 0, 0x4E, 0x00);
const I2CRegister VRECT_TARGET_L_RESERVED = I2CRegister("VRECT_TARGET_L_RESERVED", 7, 3, 0x4F, 0x00);
const I2CRegister VRECT_TARGET_L = I2CRegister("VRECT_TARGET_L", 2, 0, 0x4F, 0x02);
const I2CRegister VRECT_TARGET_H = I2CRegister("VRECT_TARGET_H", 7, 0, 0x50, 0x51);
const I2CRegister VOUT_CODE_H = I2CRegister("VOUT_CODE_H", 1, 0, 0x51, 0x00);
const I2CRegister VOUT_CODE_L = I2CRegister("VOUT_CODE_L", 7, 0, 0x52, 0x7d);
const I2CRegister ACR_MOS = I2CRegister("ACR_MOS", 7, 0, 0x53, 0x8E);
const I2CRegister OFFSET_RESERVED = I2CRegister("OFFSET_RESERVED", 7, 6, 0x55, 0x00);
const I2CRegister OFFSET = I2CRegister("OFFSET", 5, 0, 0x55, 0x00);
const I2CRegister LOAD_STATE_RESERVED = I2CRegister("LOAD_STATE_RESERVED", 7, 2, 0x56, 0x00);
const I2CRegister LOAD_STATE = I2CRegister("LOAD_STATE", 1, 0, 0x56, 0x00);
const I2CRegister DUMMY_RESERVED = I2CRegister("DUMMY_RESERVED", 7, 6, 0x57, 0x00);
const I2CRegister DUMMY = I2CRegister("DUMMY", 5, 0, 0x57, 0x10);
const I2CRegister DUMMY_CTRL_RESERVED = I2CRegister("DUMMY_CTRL_RESERVED", 7, 4, 0x58, 0x00);
const I2CRegister DUMMY_CTRL = I2CRegister("DUMMY_CTRL", 3, 0, 0x58, 0x08);
const I2CRegister CODE_LDO_VDROP_LDO_VDROP = I2CRegister("CODE_LDO_VDROP_LDO_VDROP", 7, 0, 0x5A, 0x96);
const I2CRegister RCV_POWER = I2CRegister("RCV_POWER", 7, 0, 0x5C, 0x00);
const I2CRegister PROT_STAT_RESERVED = I2CRegister("PROT_STAT_RESERVED", 7, 2, 0x5D, 0x00);
const I2CRegister D_PROT_SR_OFF = I2CRegister("D_PROT_SR_OFF", 1, 1, 0x5D, 0x00);
const I2CRegister D_PROT_MLDO_OFF = I2CRegister("D_PROT_MLDO_OFF", 0, 0, 0x5D, 0x00);
const I2CRegister I2C_OTP_ADDR = I2CRegister("I2C_OTP_ADDR", 7, 0, 0x70, 0x00);
const I2CRegister I2C_OTP_CTRL0_RESERVED = I2CRegister("I2C_OTP_CTRL0_RESERVED", 7, 6, 0x71, 0x00);
const I2CRegister NVM_SETTING = I2CRegister("NVM_SETTING", 5, 2, 0x71, 0x00);
const I2CRegister OTP_IPP_MODE = I2CRegister("OTP_IPP_MODE", 1, 1, 0x71, 0x00);
const I2CRegister I2C_OTP_CTRL0_I2C_OTP_ADDR = I2CRegister("I2C_OTP_CTRL0_I2C_OTP_ADDR", 0, 0, 0x71, 0x00);
const I2CRegister I2C_OTP_CTRL1_RESERVED = I2CRegister("I2C_OTP_CTRL1_RESERVED", 7, 3, 0x72, 0x00);
const I2CRegister NVM_PROG_SETTING = I2CRegister("NVM_PROG_SETTING", 2, 0, 0x72, 0x03);
const I2CRegister I2C_NVM_OTP_WDATA = I2CRegister("I2C_NVM_OTP_WDATA", 7, 0, 0x73, 0x00);
const I2CRegister I2C_OTP_CMD = I2CRegister("I2C_OTP_CMD", 7, 0, 0x74, 0x00);
const I2CRegister RELOAD_NVM = I2CRegister("RELOAD_NVM", 7, 7, 0x75, 0x00);
const I2CRegister PROG_1_BIT = I2CRegister("PROG_1_BIT", 6, 6, 0x75, 0x00);
const I2CRegister LOAD_1_BYTE = I2CRegister("LOAD_1_BYTE", 5, 5, 0x75, 0x00);
const I2CRegister CMD_ERROR = I2CRegister("CMD_ERROR", 4, 4, 0x75, 0x00);
const I2CRegister PROG_ERROR = I2CRegister("PROG_ERROR", 3, 3, 0x75, 0x00);
const I2CRegister I2C_OTP_STATES_RESERVED = I2CRegister("I2C_OTP_STATES_RESERVED", 2, 2, 0x75, 0x00);
const I2CRegister AUTO_PROG_DONE = I2CRegister("AUTO_PROG_DONE", 1, 1, 0x75, 0x00);
const I2CRegister RELOAD_DONE = I2CRegister("RELOAD_DONE", 0, 0, 0x75, 0x00);
const I2CRegister TRIM_LS1_COMP = I2CRegister("TRIM_LS1_COMP", 7, 4, 0x80, 0x00);
const I2CRegister TRIM_LS2_COMP = I2CRegister("TRIM_LS2_COMP", 3, 0, 0x80, 0x00);
const I2CRegister TRIM_BG = I2CRegister("TRIM_BG", 7, 2, 0x81, 0x00);
const I2CRegister TRIM_1_RESERVED = I2CRegister("TRIM_1_RESERVED", 1, 1, 0x81, 0x00);
const I2CRegister TRIM_DIS_CLPH_ADAP = I2CRegister("TRIM_DIS_CLPH_ADAP", 0, 0, 0x81, 0x00);
const I2CRegister TRIM_ADC_VREF_BUFFER = I2CRegister("TRIM_ADC_VREF_BUFFER", 7, 2, 0x82, 0x00);
const I2CRegister TRIM_ACLOW_EN = I2CRegister("TRIM_ACLOW_EN", 1, 1, 0x82, 0x00);
const I2CRegister TRIM_EN_MOT_MULTI = I2CRegister("TRIM_EN_MOT_MULTI", 0, 0, 0x82, 0x00);
const I2CRegister TRIM_OSC = I2CRegister("TRIM_OSC", 7, 1, 0x83, 0x00);
const I2CRegister TRIM_3_RESERVED = I2CRegister("TRIM_3_RESERVED", 0, 0, 0x83, 0x00);
const I2CRegister TRIM_ZTC = I2CRegister("TRIM_ZTC", 7, 3, 0x84, 0x00);
const I2CRegister OTP_DIS_RES_SET = I2CRegister("OTP_DIS_RES_SET", 2, 2, 0x84, 0x00);
const I2CRegister TRIM_SS_01_PKT_DIS = I2CRegister("TRIM_SS_01_PKT_DIS", 1, 1, 0x84, 0x00);
const I2CRegister TRIM_4_RESERVED = I2CRegister("TRIM_4_RESERVED", 0, 0, 0x84, 0x00);
const I2CRegister TRIM_ISNS_GAIN = I2CRegister("TRIM_ISNS_GAIN", 7, 1, 0x85, 0x00);
const I2CRegister TRIM_5_RESERVED = I2CRegister("TRIM_5_RESERVED", 0, 0, 0x85, 0x00);
const I2CRegister TRIM_ISNS_OFFSET = I2CRegister("TRIM_ISNS_OFFSET", 7, 2, 0x86, 0x00);
const I2CRegister TRIM_IIC_ADDR = I2CRegister("TRIM_IIC_ADDR", 1, 0, 0x86, 0x00);
const I2CRegister TRIM_ADC_VIN_BUFFER = I2CRegister("TRIM_ADC_VIN_BUFFER", 7, 2, 0x87, 0x00);
const I2CRegister TRIM_DIS_OTP = I2CRegister("TRIM_DIS_OTP", 1, 1, 0x87, 0x00);
const I2CRegister TRIM_7_RESERVED = I2CRegister("TRIM_7_RESERVED", 0, 0, 0x87, 0x00);
const I2CRegister TRIM_8_RESERVED = I2CRegister("TRIM_8_RESERVED", 7, 6, 0x88, 0x00);
const I2CRegister TRIM_EN_LOW_I = I2CRegister("TRIM_EN_LOW_I", 5, 5, 0x88, 0x00);
const I2CRegister VOUT_DMY_EN = I2CRegister("VOUT_DMY_EN", 4, 4, 0x88, 0x00);
const I2CRegister TRAN_BOOST_IBM = I2CRegister("TRAN_BOOST_IBM", 3, 3, 0x88, 0x00);
const I2CRegister TRIM_VRECT_DMY_DIS = I2CRegister("TRIM_VRECT_DMY_DIS", 2, 2, 0x88, 0x00);
const I2CRegister TRAN_BOOST = I2CRegister("TRAN_BOOST", 1, 0, 0x88, 0x00);
const I2CRegister EN_OV_SHORT_LS = I2CRegister("EN_OV_SHORT_LS", 7, 7, 0x89, 0x00);
const I2CRegister TTP_FSK_DIS = I2CRegister("TTP_FSK_DIS", 6, 6, 0x89, 0x00);
const I2CRegister AC_CHECK_500K = I2CRegister("AC_CHECK_500K", 5, 5, 0x89, 0x00);
const I2CRegister TRIM_DIG_IOUT_OFFSET = I2CRegister("TRIM_DIG_IOUT_OFFSET", 4, 0, 0x89, 0x00);
const I2CRegister TRIM_LOCK = I2CRegister("TRIM_LOCK", 7, 7, 0x8A, 0x00);
const I2CRegister TRIM_A_RESERVED = I2CRegister("TRIM_A_RESERVED", 6, 5, 0x8A, 0x00);
const I2CRegister TRIM_DEIVICE_ID = I2CRegister("TRIM_DEIVICE_ID", 4, 2, 0x8A, 0x02);
const I2CRegister TRIM_QI_ID = I2CRegister("TRIM_QI_ID", 1, 0, 0x8A, 0x00);
const I2CRegister EN_ANA_MUX = I2CRegister("EN_ANA_MUX", 7, 7, 0x90, 0x00);
const I2CRegister EN_DIG_MUX = I2CRegister("EN_DIG_MUX", 6, 6, 0x90, 0x00);
const I2CRegister MUX_DIG = I2CRegister("MUX_DIG", 5, 0, 0x90, 0x00);
const I2CRegister TMOD_CTRL = I2CRegister("TMOD_CTRL", 7, 4, 0x91, 0x00);
const I2CRegister MUX_ANA = I2CRegister("MUX_ANA", 3, 0, 0x91, 0x00);
const I2CRegister I2C_CTRL = I2CRegister("I2C_CTRL", 7, 7, 0x92, 0x00);
const I2CRegister I2C_DIS_OVP_FAST = I2CRegister("I2C_DIS_OVP_FAST", 6, 6, 0x92, 0x00);
const I2CRegister I2C_EN_OVP = I2CRegister("I2C_EN_OVP", 5, 5, 0x92, 0x00);
const I2CRegister I2C_EN_TSD = I2CRegister("I2C_EN_TSD", 4, 4, 0x92, 0x00);
const I2CRegister I2C_EN_OSC = I2CRegister("I2C_EN_OSC", 3, 3, 0x92, 0x00);
const I2CRegister I2C_EN_LDO1 = I2CRegister("I2C_EN_LDO1", 2, 2, 0x92, 0x00);
const I2CRegister I2C_ILOAD_H = I2CRegister("I2C_ILOAD_H", 1, 1, 0x92, 0x00);
const I2CRegister ILOAD_300MA = I2CRegister("ILOAD_300MA", 0, 0, 0x92, 0x00);
const I2CRegister I2C_INT_OUT = I2CRegister("I2C_INT_OUT", 7, 7, 0x93, 0x00);
const I2CRegister I2C_EN_VCP = I2CRegister("I2C_EN_VCP", 6, 6, 0x93, 0x00);
const I2CRegister I2C_FORCE_01_EXIT = I2CRegister("I2C_FORCE_01_EXIT", 5, 5, 0x93, 0x00);
const I2CRegister I2C_SDA = I2CRegister("I2C_SDA", 4, 4, 0x93, 0x00);
const I2CRegister I2C_COM2_ON = I2CRegister("I2C_COM2_ON", 3, 3, 0x93, 0x00);
const I2CRegister I2C_COM1_ON = I2CRegister("I2C_COM1_ON", 2, 2, 0x93, 0x00);
const I2CRegister I2C_SINK_ON = I2CRegister("I2C_SINK_ON", 1, 1, 0x93, 0x00);
const I2CRegister I2C_EN_RECT_LS = I2CRegister("I2C_EN_RECT_LS", 0, 0, 0x93, 0x00);
const I2CRegister I2C_EN_RECT_HS = I2CRegister("I2C_EN_RECT_HS", 7, 7, 0x94, 0x00);
const I2CRegister TM_CTRL3_RESERVED = I2CRegister("TM_CTRL3_RESERVED", 6, 5, 0x94, 0x00);
const I2CRegister I2C_FORCE_AC_CK_DIS = I2CRegister("I2C_FORCE_AC_CK_DIS", 4, 4, 0x94, 0x00);
const I2CRegister I2C_DIS_SS = I2CRegister("I2C_DIS_SS", 3, 3, 0x94, 0x00);
const I2CRegister I2C_DIS_FSK_DMOD_EN = I2CRegister("I2C_DIS_FSK_DMOD_EN", 2, 2, 0x94, 0x00);
const I2CRegister I2C_EN_LDO_PWR = I2CRegister("I2C_EN_LDO_PWR", 1, 1, 0x94, 0x00);
const I2CRegister I2C_EN_DUMMY = I2CRegister("I2C_EN_DUMMY", 0, 0, 0x94, 0x00);
const I2CRegister I2C_REF_IN = I2CRegister("I2C_REF_IN", 7, 0, 0x95, 0x00);
const I2CRegister I2C_IBIAS_IO = I2CRegister("I2C_IBIAS_IO", 7, 4, 0x96, 0x00);
const I2CRegister I2C_PSEU_R = I2CRegister("I2C_PSEU_R", 3, 0, 0x96, 0x00);
const I2CRegister T_RSAMPLE = I2CRegister("T_RSAMPLE", 7, 7, 0x97, 0x00);
const I2CRegister TM_ADC = I2CRegister("TM_ADC", 6, 6, 0x97, 0x00);
const I2CRegister TM_CH_SEL = I2CRegister("TM_CH_SEL", 5, 3, 0x97, 0x00);
const I2CRegister TM_ADC_EN = I2CRegister("TM_ADC_EN", 2, 2, 0x97, 0x00);
const I2CRegister TM_ADC_START = I2CRegister("TM_ADC_START", 1, 1, 0x97, 0x00);
const I2CRegister TM_CONTINUE_MODE = I2CRegister("TM_CONTINUE_MODE", 0, 0, 0x97, 0x00);
const I2CRegister TM_ADC_DATA_L = I2CRegister("TM_ADC_DATA_L", 7, 0, 0x98, 0x00);
const I2CRegister TM_ADC_DATA_H_RESERVED = I2CRegister("TM_ADC_DATA_H_RESERVED", 7, 2, 0x99, 0x00);
const I2CRegister TM_ADC_DATA_H = I2CRegister("TM_ADC_DATA_H", 1, 0, 0x99, 0x00);
const I2CRegister TM_ADMIN_RESERVED = I2CRegister("TM_ADMIN_RESERVED", 7, 6, 0xF7, 0x00);
const I2CRegister OPT1_BAK_LOCK = I2CRegister("OPT1_BAK_LOCK", 5, 5, 0xF7, 0x00);
const I2CRegister TM_ADMIN_OPT1_LOCK = I2CRegister("TM_ADMIN_OPT1_LOCK", 4, 4, 0xF7, 0x00);
const I2CRegister TM_ADMIN_OPT2_LOCK = I2CRegister("TM_ADMIN_OPT2_LOCK", 3, 3, 0xF7, 0x00);
const I2CRegister TM_ADMIN_TRIM_LOCK = I2CRegister("TM_ADMIN_TRIM_LOCK", 2, 2, 0xF7, 0x00);
const I2CRegister TM_CUST = I2CRegister("TM_CUST", 1, 1, 0xF7, 0x00);
const I2CRegister TM_ADMIN = I2CRegister("TM_ADMIN", 0, 0, 0xF7, 0x00);
const I2CRegister TM_CUST_TM_CUST = I2CRegister("TM_CUST_TM_CUST", 7, 0, 0xF8, 0x00);
const I2CRegister SCAN_MODE = I2CRegister("SCAN_MODE", 7, 0, 0xF9, 0x00);

class RegisterValuePair {
public:
	I2CRegister reg;
	uint32_t value;

	RegisterValuePair(const I2CRegister& r, uint32_t v) : reg(r), value(v) {}
};

struct RegisterEntry {
	uint16_t address;
	uint32_t value;

	RegisterEntry(uint16_t addr, uint32_t val) : address(addr), value(val) {}
};

class RegisterManager {
private:
	std::unordered_map<uint16_t, uint32_t> register_history_values;
	std::vector<RegisterEntry> register_current_values;

	void setCurrentRegisterValue(uint16_t address, uint32_t value) {
		for (auto& entry : register_current_values) {
			if (entry.address == address) {
				entry.value = value;
				return;
			}
		}
		register_current_values.emplace_back(address, value);
	}

	uint32_t getCurrentRegisterValue(uint16_t address) const {
		for (const auto& entry : register_current_values) {
			if (entry.address == address) {
				return entry.value;
			}
		}
		return 0; // Default value if the address is not found
	}

public:
	void setfields(const std::vector<RegisterValuePair>& pairs) {
		register_current_values.clear();
		for (const auto& pair : pairs) {
			const I2CRegister& reg = pair.reg;
			uint32_t value = pair.value;

			uint32_t mask = ((1 << (reg.msb - reg.lsb + 1)) - 1) << reg.lsb;
			uint32_t reg_value = (value << reg.lsb) & mask;

			uint32_t his_value = register_history_values[reg.address] & ~mask;
			uint32_t current_value = getCurrentRegisterValue(reg.address) & ~mask;
			current_value = current_value | reg_value | his_value;
			setCurrentRegisterValue(reg.address, current_value);
			register_history_values[reg.address] = current_value;
			I2CWriteAllSites(reg.address, current_value);//add, sites data same
		}
		printCurrentValues();
		printHistoryValues();
		// for (const auto& entry : register_current_values) {
		//I2CWriteData(I2C_ADDR_DEVICE, entry.address, entry.value);
		//}

	}

	void historyClear() {
		register_current_values.clear();
		register_history_values.clear();
		std::cout << "Current and history reg were cleared:" << std::endl;
		register_history_values[0x00] = 0x16;
		register_history_values[0x01] = 0x82;
		register_history_values[0x18] = 0x00;
		register_history_values[0x32] = 0x8;
		register_history_values[0x34] = 0x5c;
		register_history_values[0x35] = 0x3f;
		register_history_values[0x36] = 0x1f;
		register_history_values[0x37] = 0x1f;
		register_history_values[0x38] = 0x7d;
		register_history_values[0x3B] = 0x2;
		register_history_values[0x4F] = 0x2;
		register_history_values[0x50] = 0x51;
		register_history_values[0x52] = 0x7d;
		register_history_values[0x53] = 0x8e;
		register_history_values[0x57] = 0x10;
		register_history_values[0x58] = 0x8;
		register_history_values[0x5A] = 0x96;
		register_history_values[0x72] = 0x3;
		register_history_values[0x8A] = 0x8;

	}

	void printHistoryValues() const {
		std::cout << "History Values:" << std::endl;
		for (const auto& pair : register_history_values) {
			std::cout << "Address: 0x"
				<< std::setw(4) << std::setfill('0') << std::hex << pair.first
				<< ", Value: 0x"
				<< std::setw(2) << std::setfill('0') << std::hex << pair.second << std::endl;
		}
	}


	void printCurrentValues() const {
		std::cout << "Current Values:" << std::endl;
		for (const auto& entry : register_current_values) {
			std::cout << "Address: 0x"
				<< std::setw(4) << std::setfill('0') << std::hex << entry.address
				<< ", Value: 0x"
				<< std::setw(2) << std::setfill('0') << std::hex << entry.value << std::endl;
		}
	}
};

#endif 

