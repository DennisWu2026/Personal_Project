//#define MAX_SAMPLES 4096


//#include "awg.h"
//BOOL set_mos_relay_on(int mos_no, int gp_no);
//BOOL set_mos_relay_on_rdson(int mos_no, int gp_no);
//BOOL set_mos_relay_on_rdson_sw(int mos_no, int gp_no);

//sanfeng start//

//BOOL EEPROM_Read(int bank, int* EE_READ, double* EE_IQ);
//BOOL EEPROM_Read1(int bank, int* EE_READ);

//*************ԭTRIMBANK_Interface
//int get_bank(int reg);


#define SITE_COUNT	8
extern double adresult[SITE_COUNT];
extern double adresult0[SITE_COUNT];
extern double adresult1[SITE_COUNT];
extern double adresult2[SITE_COUNT];
extern double adresult3[SITE_COUNT];

extern int site;

extern FOVI VRECT;

extern FOVI V5V;

extern FOVI INTB;

extern FOVI SINK;

extern FOVI AC1;
extern FOVI SCL;

extern FOVI AC2;
extern FOVI SDA;

extern FOVI ENB;
extern FOVI COMM1;

extern FOVI VOUT;
extern FOVI COMM2;

extern FPVI10 FPVI0;

extern QTMU_PLUS QTMU;
extern QVM Qvm;
extern CBIT128 cbit;

extern DIO_PLUS::I2CSite i2c_site1;
extern DIO_PLUS::I2CSite i2c_site2;
extern DIO_PLUS::I2CSite i2c_site3;
extern DIO_PLUS::I2CSite i2c_site4;
extern DIO_PLUS::I2CSite i2c_site5;
extern DIO_PLUS::I2CSite i2c_site6;
extern DIO_PLUS::I2CSite i2c_site7;
extern DIO_PLUS::I2CSite i2c_site8;

void Trim_Retest(void(*measure_func)(/*TRIM_NODE *trim_node, */TREG_MEASURE_FLAG treg_measure_flag, double *results), int step_size, int retest_code_count,
	short funcindex, LPCTSTR funclabel, string trimname_1);

//void Trim_Retest1(void(*measure_func)(/*TRIM_NODE *trim_node, */TREG_MEASURE_FLAG treg_measure_flag, double *results), int step_size1,
//	/*CParam *postTrim, int *retest_flag, */short funcindex, LPCTSTR funclabel, string trimname_1 = "");
//
void Trim_Retest2(void(*measure_func)(/*TRIM_NODE *trim_node, */TREG_MEASURE_FLAG treg_measure_flag, double *results), int step_size2, int retest_code_count2,
	double data0[8], double data1[8], double data2[8], double data3[8], int rdata[8], double Llimit, double Hlimit,
	/*CParam *postTrim, int *retest_flag, */short funcindex, LPCTSTR funclabel, string trimname_1);

void TM_ENTER_TEMPCHAR(FOVI &fovi_force1, FOVI &fovi_force2, double force_value, FOVI_VRNG v_range, FOVI_IRNG i_range);
void TM_ENTER_vi(FOVI &fovi_force, double force_value, FOVI_VRNG v_range, FOVI_IRNG i_range);
void TM_RGE_WRITE();
void TM_EXIT_TEMPCHAR(FOVI &fovi_force1, FOVI &fovi_force2, double force_value, FOVI_VRNG v_range, FOVI_IRNG i_range);
void TM_EXIT_vi(FOVI &fovi_force, double force_value, FOVI_VRNG v_range, FOVI_IRNG i_range);
void wait_relay();
void ALLPINS_INITIALIZE_0V_1V_1MA_ON();
void ALLPINS_INITIALIZE_0V_2V_10MA_ON();
void ALLPINS_INITIALIZE_0V_2V_10MA_OFF();
void I2CWriteAllSites(int REG_Addr, DWORD i2ccode);
void I2CWritedata(int REG_Addr, unsigned char i2ccode[]);
void kelvin_measure(FPVI10 &force_source, FOVI &measure_source, double force_value, double *result);
void I2CFreqRead(double freq, int dev_Addr, int reg_Addr, int read_data[SITE_COUNT], int read_pass[SITE_COUNT]);
double calculateAverageWithoutMinMax(double arr[][SITE_COUNT], int size);

//string int2str(DWORD n);
//void I2CWriteDIINTnega(int REG_Addr, int i2ccode[]);
void EEPROM_Preview();

void EEPROM_VBG_trim();
void EEPROM_ZTC_trim();
void EEPROM_ADC_VREF_BUFFER_trim();
void EEPROM_ADC_VIN_BUFFER_trim();
void EEPROM_OSC_trim();
void EEPROM_AC1_LS_OFF_trim();
void EEPROM_AC2_LS_OFF_trim();
void EEPROM_ISNS_GAIN_trim();
void EEPROM_ISNS_OFFSET_trim();
void measure_VBG_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results);
void measure_ZTC_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results);
void measure_ADC_VREF_BUFFER_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results);
void measure_ADC_VIN_BUFFER_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results);
void measure_OSC_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results);
void measure_AC1_LS_OFF_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results);
void measure_AC2_LS_OFF_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results);
void measure_ISNS_GAIN_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results);
void measure_ISNS_OFFSET_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results);
void convert_dec_to_binary(int code, int bitnum, char* bit);

void measure_ISNS_GAIN_retest(/*TRIM_NODE *trim_node,*/ TREG_MEASURE_FLAG treg_measure_flag, double *results);
