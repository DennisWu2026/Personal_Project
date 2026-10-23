#include "stdafx.h"
#include "sub.h"
#include "math.h"

//extern string int2str(DWORD n);
//#include "Pin_Channel_define.h"  
extern int site;
extern RegisterManager manager;
extern int Global_Tempchar_Program_Flag;
extern int VoltageGP, TempCharGP;
extern int newmethod;


//DIO_PLUS::I2CSite *pI2CSites[] = { &i2c_site1, &i2c_site2, &i2c_site3, &i2c_site4, &i2c_site5, &i2c_site6, &i2c_site7, &i2c_site8 };
int READ[SITE_NUM] = { 0 };


//1.testmode enter,用于进入测试模式
void TM_ENTER_TEMPCHAR(FOVI &fovi_force1, FOVI &fovi_force2, double force_value, FOVI_VRNG v_range, FOVI_IRNG i_range)
{
	fovi_force1.Set(FV, 0, v_range, i_range, RELAY_ON);
	fovi_force2.Set(FV, 0, v_range, i_range, RELAY_ON);
	delay_us(500);
	fovi_force1.Set(FV, force_value, v_range, i_range, RELAY_ON);
	fovi_force2.Set(FV, force_value, v_range, i_range, RELAY_ON);
	delay_us(3000);//原则上数字上电后1.5ms即可完成warmup

	I2CWriteAllSites(0XF7, 0X00);
	I2CWriteAllSites(0XF7, 0x69);
	I2CWriteAllSites(0XF7, 0X96);
	I2CWriteAllSites(0XF7, 0X99);
	I2CWriteAllSites(0XF7, 0X66);
	delay_us(1000);

	manager.historyClear();//clear history value

	//High temperature = 105||125, disable over temperature protection
	if (TempCharGP == 5 || TempCharGP == 6)
	{
		manager.setfields({ { TRIM_DIS_OTP, 1 } });
	}
}
void TM_ENTER_vi(FOVI &fovi_force, double force_value, FOVI_VRNG v_range, FOVI_IRNG i_range)
{
	fovi_force.Set(FV, 0, v_range, i_range, RELAY_ON);
	delay_us(500);
	fovi_force.Set(FV, force_value, v_range, i_range, RELAY_ON, 1);
	delay_us(2000);//原则上数字上电后1.5ms即可完成warmup
	
	I2CWriteAllSites(0XF7, 0X00);
	I2CWriteAllSites(0XF7, 0x69);
	I2CWriteAllSites(0XF7, 0X96);
	I2CWriteAllSites(0XF7, 0X99);
	I2CWriteAllSites(0XF7, 0X66);
	delay_us(1000);

	manager.historyClear();//clear history value

	//High temperature = 105||125, disable over temperature protection
	if (TempCharGP == 5 || TempCharGP == 6)
	{
		manager.setfields({ { TRIM_DIS_OTP, 1 } });
	}

}
void TM_RGE_WRITE()
{
	I2CWriteAllSites(0XF7, 0X00);
	I2CWriteAllSites(0XF7, 0x69);
	I2CWriteAllSites(0XF7, 0X96);
	I2CWriteAllSites(0XF7, 0X99);
	I2CWriteAllSites(0XF7, 0X66);
	delay_us(1000);
}
//2.testmode exit,用于退出测试模式
void TM_EXIT_TEMPCHAR(FOVI &fovi_force1, FOVI &fovi_force2, double force_value, FOVI_VRNG v_range, FOVI_IRNG i_range)
{
	//I2CWriteAllSites(0XF7, 0X00);
	//delay_us(1000);

	fovi_force1.Set(FV, 0, v_range, i_range, RELAY_ON, 1);
	fovi_force2.Set(FV, 0, v_range, i_range, RELAY_ON, 1);
	delay_us(500);
	fovi_force1.Set(FV, 0, v_range, i_range, RELAY_OFF);
	fovi_force2.Set(FV, 0, v_range, i_range, RELAY_OFF);
	delay_us(500);

}
void TM_EXIT_vi(FOVI &fovi_force, double force_value, FOVI_VRNG v_range, FOVI_IRNG i_range)
{
	//I2CWriteAllSites(0XF7, 0X00);
	//delay_us(1000);

	fovi_force.Set(FV, 0, v_range, i_range, RELAY_ON, 1);
	delay_us(500);
	fovi_force.Set(FV, 0, v_range, i_range, RELAY_OFF);
	delay_us(500);

}
//3.一个统一的在配置寄存器后delay的时间，单位ms 
void wait_relay()
{
	delay_ms(3);
}
//4.用于将所有FOVI置为同一状态以使用PIN组, FV=0V in 2V 10MA relayon
void ALLPINS_INITIALIZE_0V_2V_10MA_ON()
{
	VRECT.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	V5V.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	INTB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	SINK.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	AC1.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	ENB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	VOUT.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(1000);

}
void ALLPINS_INITIALIZE_0V_1V_1MA_ON()
{
	VRECT.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
	V5V.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
	INTB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
	SINK.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
	AC1.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
	ENB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
	VOUT.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(1000);

}
//5 用于将所有FOVI置为同一状态以使用PIN组, FV=0V in 2V 10MA relayoff
void ALLPINS_INITIALIZE_0V_2V_10MA_OFF()
{
	VRECT.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	V5V.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	INTB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	SINK.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	AC1.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	AC2.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	ENB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	VOUT.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	delay_us(500);

}
//6.I2C,用于所有site写入相同值
void I2CWriteAllSites(int REG_Addr, DWORD i2ccode)
{
	unsigned char sitewritedata[SITE_COUNT] = { 0 };
	sitewritedata[0] = unsigned char(i2ccode);
	dioplus.I2CWriteAll(0XC0, REG_Addr, sitewritedata, 1);
}
//7.I2C,用于各site写入不同值(Trim for ex)
void I2CWritedata(int REG_Addr, unsigned char i2ccode[])
{
	int IC_Addr = 0XC0;
	int i2cbyte = 1;

	unsigned char i2ccode_S1[] = { i2ccode[0] };
	unsigned char i2ccode_S2[] = { i2ccode[1] };
	unsigned char i2ccode_S3[] = { i2ccode[2] };
	unsigned char i2ccode_S4[] = { i2ccode[3] };
	unsigned char i2ccode_S5[] = { i2ccode[4] };
	unsigned char i2ccode_S6[] = { i2ccode[5] };
	unsigned char i2ccode_S7[] = { i2ccode[6] };
	unsigned char i2ccode_S8[] = { i2ccode[7] };

	i2c_site1.address = IC_Addr; // I2C工位1的从机地址 
	i2c_site1.regAddress = REG_Addr; // I2C工位1的寄存器地址 
	i2c_site1.data = i2ccode_S1; // I2C工位1的字节数据缓存
	i2c_site1.dataByteCount = i2cbyte; // I2C工位1的字节数据个数 

	i2c_site2.address = IC_Addr; // I2C工位2的从机地址 
	i2c_site2.regAddress = REG_Addr; // I2C工位2的寄存器地址 i
	i2c_site2.data = i2ccode_S2; // I2C工位2的字节数据缓存 
	i2c_site2.dataByteCount = i2cbyte; // I2C工位2的字节数据个数 

	i2c_site3.address = IC_Addr; // I2C工位3的从机地址 
	i2c_site3.regAddress = REG_Addr; // I2C工位3的寄存器地址 
	i2c_site3.data = i2ccode_S3; // I2C工位3的字节数据缓存
	i2c_site3.dataByteCount = i2cbyte; // I2C工位3的字节数据个数 

	i2c_site4.address = IC_Addr; // I2C工位4的从机地址 
	i2c_site4.regAddress = REG_Addr; // I2C工位4的寄存器地址 i
	i2c_site4.data = i2ccode_S4; // I2C工位4的字节数据缓存 
	i2c_site4.dataByteCount = i2cbyte; // I2C工位4的字节数据个数 

	i2c_site5.address = IC_Addr; // I2C工位5的从机地址 
	i2c_site5.regAddress = REG_Addr; // I2C工位5的寄存器地址 
	i2c_site5.data = i2ccode_S5; // I2C工位5的字节数据缓存
	i2c_site5.dataByteCount = i2cbyte; // I2C工位5的字节数据个数 

	i2c_site6.address = IC_Addr; // I2C工位6的从机地址 
	i2c_site6.regAddress = REG_Addr; // I2C工位6的寄存器地址 i
	i2c_site6.data = i2ccode_S6; // I2C工位6的字节数据缓存 
	i2c_site6.dataByteCount = i2cbyte; // I2C工位6的字节数据个数 

	i2c_site7.address = IC_Addr; // I2C工位7的从机地址 
	i2c_site7.regAddress = REG_Addr; // I2C工位7的寄存器地址 
	i2c_site7.data = i2ccode_S7; // I2C工位7的字节数据缓存
	i2c_site7.dataByteCount = i2cbyte; // I2C工位7的字节数据个数 

	i2c_site8.address = IC_Addr; // I2C工位8的从机地址 
	i2c_site8.regAddress = REG_Addr; // I2C工位8的寄存器地址 i
	i2c_site8.data = i2ccode_S8; // I2C工位8的字节数据缓存 
	i2c_site8.dataByteCount = i2cbyte; // I2C工位8的字节数据个数 

	DIO_PLUS::I2CSite *pI2CSites[] = { &i2c_site1, &i2c_site2, &i2c_site3, &i2c_site4, &i2c_site5, &i2c_site6, &i2c_site7, &i2c_site8 };
	dioplus.I2CWrite(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]));
}
//8.用于kelvin check
void kelvin_measure(FPVI10 &force_source, FOVI &measure_source, double force_value, double *result)
{

	double adresult[SITE_NUM] = { 0.0 };
	double Iadresult_Kelvin[SITE_NUM] = { 0 };

	force_source.Set(FI, 0, FPVI10_2V, FPVI10_1MA, RELAY_ON);
	measure_source.Set(FI, 0, FOVI_2V, FOVI_1MA, RELAY_SENSE_ON);
	delay_us(500);
	force_source.Set(FI, force_value, FPVI10_2V, FPVI10_1MA, RELAY_ON);//±0.0001
	delay_us(2000);
	measure_source.MeasureVI(20, 10);
	SERIAL
	{
		adresult[SITE] = measure_source.GetMeasResult(SITE, MVRET);
		//Iadresult_Kelvin[SITE] = measure_source.GetMeasResult(SITE, MIRET);
		result[SITE] = adresult[SITE]/* / force_value*/;
	}
	force_source.Set(FI, 0, FPVI10_2V, FPVI10_1MA, RELAY_ON);
	delay_us(200);
	force_source.Set(FV, 0, FPVI10_2V, FPVI10_1MA, RELAY_ON);
	delay_us(100);
	force_source.Set(FV, 0, FPVI10_2V, FPVI10_1MA, RELAY_OFF);
	measure_source.Set(FI, 0, FOVI_2V, FOVI_1MA, RELAY_OFF);


}
//9.用于不同频率下IIC各site读值
void I2CFreqRead(double freq, int dev_Addr, int reg_Addr, int read_data[SITE_COUNT], int read_pass[SITE_COUNT])
{
	double period1 = 1 / freq; 
	dioplus.I2CSetClockPeriod(period1);
	dioplus.I2CSetSDADelay(period1 / 6, period1 / 2, period1 * 2 / 3);
	dioplus.I2CSetSCLDelay(0, period1 / 2);

	//dioplus.SetVIH(5.0f);
	//dioplus.SetVIL(0.0f);
	//dioplus.SetVOH(2.2f);
	//dioplus.SetVOL(0.4f);

	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);
	manager.setfields({ { COMM2_DIS, 1 } });//reg0x08='b00000010
	delay_ms(1);

	DIO_PLUS::I2CSite *pI2CSites[] = { &i2c_site1, &i2c_site2, &i2c_site3, &i2c_site4, &i2c_site5, &i2c_site6, &i2c_site7, &i2c_site8 };
	
	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), dev_Addr, reg_Addr, 1);
	SERIAL read_data[SITE] = pI2CSites[SITE]->GetDataByteValue(0);


	SERIAL
	{
		if (read_data[SITE] == 0x02)
		{
			read_pass[SITE] = 1;
		}
		else
		{
			read_pass[SITE] = 0;
		}
	}
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_us(200);
	//TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);
}
//10 计算去掉最大值和最小值后的平均值
double calculateAverageWithoutMinMax(double arr[][SITE_COUNT], int size)
{
	if (size <= 2) {
		return 0; // 如果数组大小小于等于2，无法去掉最大值和最小值，直接返回0
	}

	double min[SITE_COUNT] = { 0 };
	double max[SITE_COUNT] = { 0 };
	double sum[SITE_COUNT] = { 0 };
	double average[SITE_COUNT] = { 0 };
	min[SITE] = arr[0][SITE];
	max[SITE] = arr[0][SITE];
	sum[SITE] = arr[0][SITE];

	// 找出最大值、最小值和求和
	for (int i = 1; i < size; i++) {
		if (arr[i][SITE] < min[SITE]) {
			min[SITE] = arr[i][SITE];
		}
		if (arr[i][SITE] > max[SITE]) {
			max[SITE] = arr[i][SITE];
		}
		sum[SITE] += arr[i][SITE];
	}

	// 减去最大值和最小值
	sum[SITE] = sum[SITE] - min[SITE] - max[SITE];

	// 计算剩余元素的平均值
	average[SITE] = sum[SITE] / (size - 2);

	return average[SITE];
}

void EEPROM_Preview()
{
	for (int reg = 0; reg < BANK_NUM; ++reg) {
		{
			string EE_str;
			EE_str = "EEPROM" + int2str(reg);
			SERIAL ulWriteData[SITE] = dut.assy(EE_str.c_str()).get_working(SITE);
			SERIAL I2CWritedata(I2C_TRIM_BANK + reg, ulWriteData);
		}
		//dut.assy(EE_str.c_str()).copy_read_to_prog(SITE);
	}
}

void EEPROM_VBG_trim()
{
	for (int reg = 0; reg < 2; ++reg) {  //EEPROM1=0x81 bit2~7
		string EE_str;
		EE_str = "EEPROM" + int2str(reg);

		SERIAL ulWriteData[SITE] = dut.assy(EE_str.c_str()).get_working(SITE);
		I2CWritedata(I2C_TRIM_BANK + reg, ulWriteData);
	}
}
 //treg中测试VBG
void measure_VBG_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results)
{


	EEPROM_VBG_trim();
	delay_ms(1);
	if (Global_Tempchar_Program_Flag == 1)
	{
		delay_ms(25);
	}
	Qvm.MeasureLADC(100, 10, QVM_LADC_5V, QVM_LADC_40KHz, MEAS_NORMAL);
	SERIAL	adresult1[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);

	manager.setfields({ { TMOD_CTRL, 0x0f }});
	ENB.Set(FV, 0, FOVI_2V, FOVI_1MA, RELAY_ON);
	delay_ms(1);

	ENB.Set(FV, 1.2, FOVI_2V, FOVI_1MA, RELAY_ON, 0.5);
	delay_ms(1);
	Qvm.MeasureLADC(100, 10, QVM_LADC_5V, QVM_LADC_40KHz, MEAS_NORMAL);
	SERIAL	adresult2[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);

	ENB.Set(FV, 1.24, FOVI_2V, FOVI_1MA, RELAY_ON, 0.5);
	delay_ms(1);
	Qvm.MeasureLADC(100, 10, QVM_LADC_5V, QVM_LADC_40KHz, MEAS_NORMAL);
	SERIAL	
	{ 
		adresult3[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);

		results[SITE] = adresult1[SITE] / (25 * (adresult3[SITE] - adresult2[SITE]) + 1e-32) - (1.24*adresult2[SITE] - 1.2*adresult3[SITE]) / (adresult3[SITE] - adresult2[SITE] + 1e-32);
	}

	ENB.Set(FV, 0, FOVI_2V, FOVI_1MA, RELAY_ON);//debug: ENB fovi没off可能会影响vbg结果
	manager.setfields({ { TMOD_CTRL, 0x00 } });
	delay_ms(1);

	//ENB.Set(FV, 0, FOVI_2V, FOVI_1MA, RELAY_OFF);

}

void EEPROM_ZTC_trim()
{
	for (int reg = 0; reg < 5; ++reg) {  //EEPROM4=0x84 bit3~7
		string EE_str;
		EE_str = "EEPROM" + int2str(reg);
		SERIAL ulWriteData[SITE] = dut.assy(EE_str.c_str()).get_working(SITE);
		I2CWritedata(I2C_TRIM_BANK + reg, ulWriteData);

		//dut.assy(EE_str.c_str()).copy_read_to_prog(SITE);
	}
}
//treg中测试ZTC
void measure_ZTC_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results)
{
	EEPROM_ZTC_trim();
	delay_ms(1);

	if (spec("V5V") == 3.3)
	{
		dioplus.I2CDisconnect();
		//cbit.SetOn(/*K4_IIC_PULLUP,*/ K2_VRECT_V5V_CAP, -1);
		wait_relay();
	}

	INTB.MeasureVI(50, 10);


	SERIAL adresult[SITE] = INTB.GetMeasResult(SITE, MIRET);

	SERIAL results[SITE] = -adresult[SITE] * 1E6;

	if (spec("V5V") == 3.3)
	{
		dioplus.I2CConnect();
		//cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, -1);
		wait_relay();
	}
}

void EEPROM_ADC_VREF_BUFFER_trim()
{
	EEPROM_ZTC_trim();
	for (int reg = 0; reg < 3; ++reg) {  //EEPROM2=0x82 bit2~7
		string EE_str;
		EE_str = "EEPROM" + int2str(reg);
		SERIAL ulWriteData[SITE] = dut.assy(EE_str.c_str()).get_working(SITE);
		I2CWritedata(I2C_TRIM_BANK + reg, ulWriteData);

		//dut.assy(EE_str.c_str()).copy_read_to_prog(SITE);
	}
}
//treg中测试ADC_VREF_BUFFER
void measure_ADC_VREF_BUFFER_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results)
{
	EEPROM_ADC_VREF_BUFFER_trim();
	delay_ms(1);

	if (Global_Tempchar_Program_Flag == 1)
	{
		delay_ms(10);
	}

	Qvm.MeasureLADC(100, 10, QVM_LADC_5V, QVM_LADC_40KHz, MEAS_NORMAL);

	SERIAL results[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);

	if (spec("V5V") == 3.3)
	{
		dioplus.I2CConnect();
		cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, -1);
		wait_relay();
	}
}

void EEPROM_ADC_VIN_BUFFER_trim()
{
	for (int reg = 0; reg < 8; ++reg) {  //EEPROM7=0x87 bit2~7
		string EE_str;
		EE_str = "EEPROM" + int2str(reg);
		SERIAL ulWriteData[SITE] = dut.assy(EE_str.c_str()).get_working(SITE);
		I2CWritedata(I2C_TRIM_BANK + reg, ulWriteData);

		//dut.assy(EE_str.c_str()).copy_read_to_prog(SITE);
	}
}
//treg中测试ADC_VIN_BUFFER
void measure_ADC_VIN_BUFFER_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results)
{
	EEPROM_ADC_VIN_BUFFER_trim();
	delay_ms(1);

	dioplus.I2CDisconnect();
	cbit.SetOn(K2_VRECT_V5V_CAP, K8_OVI4_AC1_SCL, -1);//未使用buffer
	wait_relay();

	SCL.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_us(200);

	SCL.Set(FV, 1, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_ms(1);

	if (Global_Tempchar_Program_Flag == 1)
	{
		delay_ms(10);
	}


	Qvm.MeasureLADC(100, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);

	SCL.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_ms(1);
	SCL.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_OFF);
	dioplus.I2CConnect();
	delay_ms(1);

	SERIAL results[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);
}

void EEPROM_OSC_trim()
{
	EEPROM_ZTC_trim();
	for (int reg = 0; reg < 4; ++reg) {  //EEPROM3=0x83 bit1~7
		string EE_str;
		EE_str = "EEPROM" + int2str(reg);
		SERIAL ulWriteData[SITE] = dut.assy(EE_str.c_str()).get_working(SITE);
		I2CWritedata(I2C_TRIM_BANK + reg, ulWriteData);

		//dut.assy(EE_str.c_str()).copy_read_to_prog(SITE);
	}
}
//treg中测试OSC
void measure_OSC_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results)
{
	EEPROM_OSC_trim();
	delay_ms(1);

	QTMU.MeasFreq(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 20, 1); //cycle number=20,timeout=1ms
	SERIAL 
	{ 
		results[SITE] = QTMU.GetMeasureResult(SITE);
		results[SITE] = results[SITE] * 64 * 12 * 1e-3; //OSC_48M = Freq_int * 64*12
	}

}

void EEPROM_AC1_LS_OFF_trim()
{
	EEPROM_VBG_trim();
	EEPROM_ZTC_trim();
	for (int reg = 0; reg < 1; ++reg) {  //EEPROM0=0x80 bit4~7
		string EE_str;
		EE_str = "EEPROM" + int2str(reg);
		SERIAL ulWriteData[SITE] = dut.assy(EE_str.c_str()).get_working(SITE);
		I2CWritedata(I2C_TRIM_BANK + reg, ulWriteData);

	}
}
//treg中测试AC1_LS_OFF
void measure_AC1_LS_OFF_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results)
{

	EEPROM_AC1_LS_OFF_trim();
	delay_ms(1); 
	AC1.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	SINK.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_us(200);

	AC1.Set(FV, -0.2, FOVI_1V, FOVI_10MA, RELAY_ON);
	delay_ms(1);

	if (Global_Tempchar_Program_Flag == 1)
	{
		AC2.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC2.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
	}
	else
	{
		AC2.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC2.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
	}

	int interval = 10;
	double Trig = 2.5;
	int sam = 400;
	int Trig_Point[SITE_NUM] = { 0 };
	//AC1 sweep from -0.2V to 0.1V
	AC1.AwgSelect("AC1_LS_OFF_TRIM", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_RISING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	AC1.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&AC1);
	STSEnableMeas(&AC1, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &AC1);

	SERIAL
	{
		Trig_Point[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point[SITE]<0 || Trig_Point[SITE]>sam - 1)
		{ 
			Trig_Point[SITE] = 999;
			adresult[SITE] = Trig_Point[SITE];
			results[SITE] = adresult[SITE] * 1e3;//mV

		}
		else
		{
			adresult[SITE] = AC1.GetMeasResult(SITE, MVRET, Trig_Point[SITE]);
			results[SITE] = adresult[SITE] * 1e3;//mV

		}
	}

}

void EEPROM_AC2_LS_OFF_trim()
{
	EEPROM_VBG_trim();
	EEPROM_ZTC_trim();
	for (int reg = 0; reg < 1; ++reg) {  //EEPROM0=0x80 bit0~3
		string EE_str;
		EE_str = "EEPROM" + int2str(reg);
		SERIAL ulWriteData[SITE] = dut.assy(EE_str.c_str()).get_working(SITE);
		I2CWritedata(I2C_TRIM_BANK + reg, ulWriteData);

	}
}
//treg中测试AC2_LS_OFF
void measure_AC2_LS_OFF_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results)
{

	EEPROM_AC2_LS_OFF_trim();
	delay_ms(1);

	AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
	SINK.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_us(200);

	AC2.Set(FV, -0.2, FOVI_1V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	if (Global_Tempchar_Program_Flag == 1)
	{
		AC1.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC1.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
	}
	else
	{
		AC1.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC1.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
	}


	int interval = 10;
	double Trig = 2.5;
	int sam = 400;
	int Trig_Point[SITE_NUM] = { 0 };
	//AC2 sweep from -0.2V to 0.1V
	AC2.AwgSelect("AC2_LS_OFF_TRIM", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_RISING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	AC2.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&AC2);
	STSEnableMeas(&AC2, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &AC2);

	SERIAL
	{
		Trig_Point[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point[SITE]<0 || Trig_Point[SITE]>sam - 1)
		{
			Trig_Point[SITE] = 999;
			adresult[SITE] = Trig_Point[SITE];
			results[SITE] = adresult[SITE] * 1e3;//mV

		}
		else
		{
			adresult[SITE] = AC2.GetMeasResult(SITE, MVRET, Trig_Point[SITE]);
			results[SITE] = adresult[SITE] * 1e3;//mV
		}
	}

}

void EEPROM_ISNS_GAIN_trim()
{
	for (int reg = 0; reg < 6; ++reg) {  //EEPROM5=0x85 bit1~7
		string EE_str;
		EE_str = "EEPROM" + int2str(reg);
		SERIAL ulWriteData[SITE] = dut.assy(EE_str.c_str()).get_working(SITE);
		I2CWritedata(I2C_TRIM_BANK + reg, ulWriteData);

	}
}
//treg中测试ISNS_GAIN
void measure_ISNS_GAIN_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results)
{
	double volt_meas1[SITE_NUM] = { 0.0 };
	double volt_meas2[SITE_NUM] = { 0.0 };
	double volt_meas3[SITE_NUM] = { 0.0 };
	double volt_meas4[SITE_NUM] = { 0.0 };
	//delay_us(3000);

	EEPROM_ISNS_GAIN_trim();
	delay_us(1000);

	FPVI0.Set(FI, 0.3, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	delay_ms(2);

	FPVI0.MeasureVI(50, 10);
	INTB.MeasureVI(50, 10);
	//Qvm.MeasureLADC(100, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);
	SERIAL
	{
		volt_meas1[SITE] = INTB.GetMeasResult(SITE, MVRET);
		//volt_meas1[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);
		volt_meas3[SITE] = FPVI0.GetMeasResult(SITE, MIRET);
	}
	FPVI0.Set(FI, 0.8, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	delay_ms(2);
	FPVI0.MeasureVI(50, 10);
	INTB.MeasureVI(50, 10);
	//Qvm.MeasureLADC(100, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);
	SERIAL
	{
		volt_meas2[SITE] = INTB.GetMeasResult(SITE, MVRET);
		//volt_meas2[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);
		volt_meas4[SITE] = FPVI0.GetMeasResult(SITE, MIRET);
		results[SITE] = (volt_meas2[SITE] - volt_meas1[SITE]) / (volt_meas4[SITE] - volt_meas3[SITE] + 1e-32);/// unit: V/A
	}

	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	delay_ms(10);//wait 10ms

}

void EEPROM_ISNS_OFFSET_trim()
{
	for (int reg = 0; reg < 7; ++reg) {  //EEPROM6=0x86 bit2~7
		string EE_str;
		EE_str = "EEPROM" + int2str(reg);
		SERIAL ulWriteData[SITE] = dut.assy(EE_str.c_str()).get_working(SITE);
		I2CWritedata(I2C_TRIM_BANK + reg, ulWriteData);

	}
}
//treg中测试ISNS_offset
void measure_ISNS_OFFSET_trim(TRIM_NODE *trim_node, TREG_MEASURE_FLAG treg_measure_flag, double *results)
{
	double volt_meas[SITE_NUM] = { 0.0 };
	double volt_meas1[SITE_NUM] = { 0.0 };
	double current_meas[SITE_NUM] = { 0.0 };
	double current_meas1[SITE_NUM] = { 0.0 };
	double calc_out[SITE_NUM] = { 0.0 };

	EEPROM_ISNS_OFFSET_trim();
	delay_ms(2);

	FPVI0.Set(FI, 0.4, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	delay_ms(2);
	//INTB.MeasureVI(50, 10);
	FPVI0.MeasureVI(50, 10);
	Qvm.MeasureLADC(100, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);
	SERIAL
	{
		current_meas[SITE] = FPVI0.GetMeasResult(SITE, MIRET);
		volt_meas[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);
	}

	FPVI0.Set(FI, 0.8, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	delay_ms(2);
	//INTB.MeasureVI(50, 10);
	FPVI0.MeasureVI(50, 10);
	Qvm.MeasureLADC(100, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);
	SERIAL
	{
		current_meas1[SITE] = FPVI0.GetMeasResult(SITE, MIRET);
		volt_meas1[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);
		calc_out[SITE] = (volt_meas1[SITE] - volt_meas[SITE]) / (current_meas1[SITE] - current_meas[SITE] + 1e-32);
		results[SITE] = (volt_meas[SITE] - current_meas[SITE] * calc_out[SITE])*1e3;/// unit: mV
	}

	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	delay_ms(20);//delya for VOUT


}

void convert_dec_to_binary(int code, int bitnum, char* bit)
{
	for (int i = 0; i < bitnum + 1; i++)
	{
		bit[i] = (code % 2) + 48;//转化为0或1对应的ASCII码
		code = code / 2;

		if (i == (bitnum))
		{
			bit[i] = '\0';
		}
	}
}

void measure_ISNS_GAIN_retest(/*TRIM_NODE *trim_node,*/ TREG_MEASURE_FLAG treg_measure_flag, double *results){

	//delay_us(1000);
	EEPROM_ISNS_GAIN_trim();
	delay_us(1000);

	double volt_meas1[SITE_NUM] = { 0.0 };
	double volt_meas2[SITE_NUM] = { 0.0 };
	double volt_meas3[SITE_NUM] = { 0.0 };
	double volt_meas4[SITE_NUM] = { 0.0 };

	int rdata[SITE_NUM];
	SERIAL rdata[SITE] = dut.trim("TRIM_ISNS_GAIN").get_working(SITE);


	FPVI0.Set(FI, 0.3, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	delay_ms(2);

	FPVI0.MeasureVI(50, 10);
	INTB.MeasureVI(50, 10);
	//Qvm.MeasureLADC(100, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);
	SERIAL
	{
		volt_meas1[SITE] = INTB.GetMeasResult(SITE, MVRET);
		//volt_meas1[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);
		volt_meas3[SITE] = FPVI0.GetMeasResult(SITE, MIRET);
	}
	FPVI0.Set(FI, 0.8, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	delay_ms(2);
	FPVI0.MeasureVI(50, 10);
	INTB.MeasureVI(50, 10);
	//Qvm.MeasureLADC(100, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);
	SERIAL
	{
		volt_meas2[SITE] = INTB.GetMeasResult(SITE, MVRET);
		//volt_meas2[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);
		volt_meas4[SITE] = FPVI0.GetMeasResult(SITE, MIRET);
		results[SITE] = (volt_meas2[SITE] - volt_meas1[SITE]) / (volt_meas4[SITE] - volt_meas3[SITE] + 1e-32);/// unit: V/A
	}

	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	delay_ms(10);//wait 10ms


}

void Trim_Retest(void(*measure_func)(/*TRIM_NODE *trim_node, */TREG_MEASURE_FLAG treg_measure_flag, double *results), int step_size, int retest_code_count,
	/*CParam *postTrim, int *retest_flag, */short funcindex, LPCTSTR funclabel, string trimname)
{

	if (retest_code_count < 3 || retest_code_count / 2 == 0)
	{
		return;
	}

	BYTE sitesta_retest[SITE_NUM] = { 0 };

	int retest_flag_EachSite[SITE_NUM] = { 0 };
	int retest_flag = 0;
	string retest_flag_datalog = trimname + "_retestflag";

	double bad_Llimit_postTrim = 0;
	double bad_Hlimit_postTrim = 0;

	double Llimit_postTrim = 0;
	double Hlimit_postTrim = 0;
	string postTrim = trimname + "_post";

	//Llimit_postTrim = postTrim->GetMinLimit();
	//Hlimit_postTrim = postTrim->GetMaxLimit();
	Llimit_postTrim = StsGetParam(funcindex, postTrim.c_str())->GetMinLimit();
	Hlimit_postTrim = StsGetParam(funcindex, postTrim.c_str())->GetMaxLimit();

	double Posttrim_data[SITE_NUM] = { 0.0 };
	const char *trimname_char = trimname.c_str();
	bad_Llimit_postTrim = Llimit_postTrim - (Hlimit_postTrim - Llimit_postTrim) * 10;
	bad_Hlimit_postTrim = Hlimit_postTrim + (Hlimit_postTrim - Llimit_postTrim) * 10;
	SERIAL
	{
		Posttrim_data[SITE] = dut.trim(trimname_char).get_post_reading(SITE);
		//Posttrim_data[SITE] = Posttrim_data[SITE] + (Hlimit_postTrim - Llimit_postTrim);
		if (Posttrim_data[SITE] > Hlimit_postTrim || Posttrim_data[SITE] < Llimit_postTrim)
		{
			if (Posttrim_data[SITE] < bad_Hlimit_postTrim || Posttrim_data[SITE] > bad_Llimit_postTrim)
			{
				retest_flag_EachSite[SITE]++;
				retest_flag++;
				sitesta_retest[SITE] = 1;
			}
		}
		StsGetParam(funcindex, retest_flag_datalog.c_str())->SetTestResult(SITE, 0, retest_flag_EachSite[SITE]);
	}

		if (retest_flag > 0)
		{
			BYTE sitesta[SITE_NUM] = { 0 };
			//BYTE sitesta_retest[SITE_NUM] = { 0 };
			double SiteStatus = StsGetsSiteStatus();//save the active sites status to "SiteStatus"
			int SiteStatus_retest = 0;//save the active sites status to "SiteStatus"
			StsGetSiteStatus(sitesta, SITE_NUM);//get all sites enable info
			//StsGetSiteStatus(sitesta_retest, SITE_NUM);//get all sites enable info
			////StsSetSiteStatus(0xFFFF);//1111 1111 1111 1111  make 16 sites always active

			//for (int n = 0; n < 16; n++)
			//{
			//	if (sitesta_retest[n] & 0x01 == 1)
			//	{
			//		SiteStatus_retest += pow(2, n);//enable site8~15 reuse the QTMUe of site0~7
			//	}
			//}

			StsSetSiteStatus(SiteStatus_retest);//  make reuse sites  active

			double step_data0[SITE_NUM] = { 0.0 };
			double step_data1[SITE_NUM] = { 0.0 };
			double step_data2[SITE_NUM] = { 0.0 };
			double step_data3[SITE_NUM] = { 0.0 };
			double meas_results[SITE_NUM];
			int rdata[SITE_NUM] = { 0.0 };

			SERIAL rdata[SITE] = dut.trim(trimname_char).get_working(SITE);

			SERIAL dut.trim(trimname_char).set_working(0, SITE);
			measure_func(TREG_MEASURE_CHAR, meas_results);
			SERIAL step_data0[SITE] = meas_results[SITE];

			SERIAL dut.trim(trimname_char).set_working(step_size / 2 - 1, SITE);
			measure_func(TREG_MEASURE_CHAR, meas_results);
			SERIAL step_data1[SITE] = meas_results[SITE];

			SERIAL dut.trim(trimname_char).set_working(step_size / 2, SITE);
			measure_func(TREG_MEASURE_CHAR, meas_results);
			SERIAL step_data2[SITE] = meas_results[SITE];

			SERIAL dut.trim(trimname_char).set_working(step_size - 1, SITE);
			measure_func(TREG_MEASURE_CHAR, meas_results);
			SERIAL step_data3[SITE] = meas_results[SITE];

			//SERIAL
			//{
			//	step_data0[SITE] = dut.trim(trimname_char).get_guessed_final(SITE, 0);
			//	step_data1[SITE] = dut.trim(trimname_char).get_guessed_final(SITE, step_size / 2 - 1);
			//	step_data2[SITE] = dut.trim(trimname_char).get_guessed_final(SITE, step_size / 2);
			//	step_data3[SITE] = dut.trim(trimname_char).get_guessed_final(SITE, step_size - 1);
			//}
			//dut.trim(trimname_char).execute(measure_func, spec, funcindex, funclabel, 1, 0, trimname);

			Trim_Retest2(measure_func, step_size, retest_code_count, step_data0, step_data1, step_data2, step_data3, rdata, Llimit_postTrim, Hlimit_postTrim, funcindex, funclabel, trimname);

			//Trim_Retest1(measure_func, step_size, funcindex,  funclabel, trimname);

			StsSetSiteStatus(SiteStatus);//  make reuse sites  active

			//retest_flag = 0;
		}


}
void Trim_Retest2(void(*measure_func)(/*TRIM_NODE *trim_node, */TREG_MEASURE_FLAG treg_measure_flag, double *results), int step_size, int retest_code_count, double data0[SITE_NUM], double data1[SITE_NUM], double data2[SITE_NUM], double data3[SITE_NUM],
	int rdata[SITE_NUM], double Llimit, double Hlimit, /*CParam *postTrim, int *retest_flag, */short funcindex, LPCTSTR funclabel, string trimname){

	const char *trimname_char = trimname.c_str();

	double meas_results[SITE_NUM];
	double meas_results_data[SITE_NUM][255] = { 0 };

	double Target_data[SITE_NUM];
	//int rdata[SITE_NUM];
	//int best_step[SITE_NUM];
	int rdata_working[SITE_NUM][255] = { 0 };

	string trimfullname;
	double diff_data[SITE_NUM][255] = { 0 };

	////SERIAL dut.trim(trimname_char).set_working(30, SITE); //for test
	//dut.trim(trimname_char).set_working(0, 0); //for test
	//dut.trim(trimname_char).set_working(2, 1); //for test
	//dut.trim(trimname_char).set_working(step_size/2 - 1, 2); //for test
	//dut.trim(trimname_char).set_working(step_size/2 - 3, 3); //for test

	SERIAL
	{
		//rdata[SITE] = dut.trim(trimname_char).get_working(SITE);//can not get
		Target_data[SITE] = dut.trim(trimname_char).get_target(SITE);
	}

	int code0_near_code32_flag[SITE_NUM] = { 0 };
	int code0_near_code63_flag[SITE_NUM] = { 0 };
	int code31_near_code32_flag[SITE_NUM] = { 0 };
	int code31_near_code63_flag[SITE_NUM] = { 0 };

	double step_data[SITE_NUM][4] = { 0 };
	double min_data = 0;
	int index_data = 0;

	SERIAL
	{
		if ((abs(data0[SITE] - data2[SITE]) < abs(data0[SITE] - data3[SITE])) /*&& abs(data0[SITE] - data2[SITE]) < 2 * (Hlimit - Llimit))*/) code0_near_code32_flag[SITE] = 1; //code0 near to code32
		if ((abs(data0[SITE] - data3[SITE]) < abs(data0[SITE] - data2[SITE])) /*&& (abs(data0[SITE] - data3[SITE]) < 2 * (Hlimit - Llimit))*/) code0_near_code63_flag[SITE] = 1;

		if ((abs(data1[SITE] - data2[SITE]) < abs(data1[SITE] - data3[SITE])) /*&& (abs(data1[SITE] - data2[SITE]) < 2 * (Hlimit - Llimit))*/) code31_near_code32_flag[SITE] = 1;
		if ((abs(data1[SITE] - data3[SITE]) < abs(data1[SITE] - data2[SITE])) /*&& (abs(data1[SITE] - data3[SITE]) < 2 * (Hlimit - Llimit))*/) code31_near_code63_flag[SITE] = 1;

		step_data[SITE][0] = abs(data0[SITE] - data2[SITE]); //code0_2_code32_diffdata
		step_data[SITE][1] = abs(data0[SITE] - data3[SITE]); //code0_2_code63_diffdata
		step_data[SITE][2] = abs(data1[SITE] - data2[SITE]); //code31_2_code32_diffdata
		step_data[SITE][3] = abs(data1[SITE] - data2[SITE]); //code31_2_code63_diffdata

		min_data = step_data[SITE][0];
		for (int i = 1; i < 4; i++)
		{
			if (step_data[SITE][i] < min_data)
			{
				min_data = step_data[SITE][i];
				index_data = i;
			}
		}
		if (index_data == 0) code0_near_code32_flag[SITE] = 1;
		if (index_data == 1) code0_near_code63_flag[SITE] = 1;
		if (index_data == 2) code31_near_code32_flag[SITE] = 1;
		if (index_data == 3) code31_near_code63_flag[SITE] = 1;


		for (int i = 0; i < retest_code_count; i++)
		{
			//rdata_working[SITE][i] = -1;
			meas_results_data[SITE][i] = 99999;
		}

		//code0_near_code63_flag[SITE] = 1;
	}

		//int i = 0;
		//int retest_code_count = 7;
	int central_code = (retest_code_count - 1) / 2;

	SERIAL
	{
		for (int n = 1; n <= central_code; n++)
		{
			rdata_working[SITE][central_code] = rdata[SITE];
			rdata_working[SITE][central_code + n] = rdata[SITE] + n;
			rdata_working[SITE][central_code - n] = rdata[SITE] - n;
		}

		//rdata_working[SITE][3] = rdata[SITE];
		//rdata_working[SITE][4] = rdata[SITE] + 1;
		//rdata_working[SITE][5] = rdata[SITE] + 2;
		//rdata_working[SITE][6] = rdata[SITE] + 3;

		//rdata_working[SITE][2] = rdata[SITE] - 1;
		//rdata_working[SITE][1] = rdata[SITE] - 2;
		//rdata_working[SITE][0] = rdata[SITE] - 3;

		if (rdata[SITE] < central_code)
		{
			for (int j = central_code - 1; j > -1; j--) //j=2 i=3; j=1 i=2; j=0 i=1
			{
				if (rdata_working[SITE][j] < 0) //rdata[SITE] < 3   
				{
					for (int i = 0; i < j + 1; i++)
					{
						if (code0_near_code32_flag[SITE])
						{
							rdata_working[SITE][j - i] = step_size / 2 + i; // rdata - i
						}
						if (code0_near_code63_flag[SITE])
						{
							rdata_working[SITE][j - i] = step_size - 1 - i; // rdata - 1
						}
						//if (code0_near_code32_flag[SITE] == 0 && code0_near_code63_flag[SITE] == 0 && code31_near_code32_flag[SITE] == 0 && code31_near_code63_flag[SITE] == 0)
						//{
						//	rdata_working[SITE][j] = - 1;
						//}
					}
					j = -1;
				}
			}
		}

		if ((rdata[SITE] >= step_size / 2 && rdata[SITE] < step_size / 2 + central_code))//32 >= rdata[SITE] < 35
		{
			for (int j = central_code - 1; j > -1; j--) //j=2 i=3; j=1 i=2; j=0 i=1
			{
				if (rdata_working[SITE][j] < step_size / 2)
				{
					for (int i = 0; i < j + 1; i++)
					{
						if (code0_near_code32_flag[SITE])
						{
							rdata_working[SITE][j - i] = i; // rdata - i
						}
						if (code31_near_code32_flag[SITE])
						{
						}
						//if (code0_near_code32_flag[SITE] == 0 && code0_near_code63_flag[SITE] == 0 && code31_near_code32_flag[SITE] == 0 && code31_near_code63_flag[SITE] == 0)
						//{
						//	rdata_working[SITE][j] = -1;
						//}
					}
					j = -1;
				}
			}
		}

		if ((rdata[SITE] >= step_size / 2 - central_code && rdata[SITE] < step_size / 2))//29 <= rdata[SITE] < 32
		{
			for (int j = central_code + 1; j < retest_code_count; j++)  //j=4 i=3; j=5 i=2; j=6 i=1
			{
				if (rdata_working[SITE][j] >= step_size / 2)
				{
					for (int i = 0; i < retest_code_count - j; i++)
					{
						if (code31_near_code32_flag[SITE])
						{
						}
						if (code31_near_code63_flag[SITE])
						{
							rdata_working[SITE][j + i] = step_size - 1 - i; // rdata - 1
						}
						//if (code0_near_code32_flag[SITE] == 0 && code0_near_code63_flag[SITE] == 0 && code31_near_code32_flag[SITE] == 0 && code31_near_code63_flag[SITE] == 0)
						//{
						//	rdata_working[SITE][j] = -1;
						//}
					}
					j = retest_code_count;
				}
			}
		}
		if ((rdata[SITE] >= step_size - central_code && rdata[SITE] < step_size))//61 <= rdata[SITE] < 64
		{
			for (int j = central_code + 1; j < retest_code_count; j++)  //j=4 i=3; j=5 i=2; j=6 i=1
			{
				if (rdata_working[SITE][j] >= step_size)
				{
					for (int i = 0; i < retest_code_count - j; i++)
					{
						if (code31_near_code63_flag[SITE])
						{
							rdata_working[SITE][j + i] = step_size / 2 - 1 - i; // rdata - i
						}
						if (code0_near_code63_flag[SITE])
						{
							rdata_working[SITE][j + i] = i; // rdata - 1
						}
						//if (code0_near_code32_flag[SITE] == 0 && code0_near_code63_flag[SITE] == 0 && code31_near_code32_flag[SITE] == 0 && code31_near_code63_flag[SITE] == 0)
						//{
						//	rdata_working[SITE][j] = -1;
						//}
					}
					j = retest_code_count;
				}
			}
		}
	}


		//int index_working[7] = { 3, 2, 4, 1, 5, 0, 6 };
	int index_working[255] = { 0 };
	index_working[0] = central_code;
	index_working[1] = central_code - 1;
	index_working[2] = central_code + 1;
	for (int i = 3; i < retest_code_count; i++)
	{
		if (i % 2 == 0) index_working[i] = index_working[i - 2] + 1;
		if (i % 2 == 1) index_working[i] = index_working[i - 2] - 1;
	}

	double SiteStatus = StsGetsSiteStatus();//save the active sites status to "SiteStatus"
	int allSite_pass_flag = 0;
	int working_saved[SITE_NUM] = { 0 };
	double meas_results_saved[SITE_NUM] = { 0 };
	int EachSite_pass_flag[SITE_NUM] = { 0 };
	for (int i = 0; i < retest_code_count; i++)
	{
		SERIAL
		{
			if (EachSite_pass_flag[SITE] == 0) working_saved[SITE] = rdata_working[SITE][index_working[i]];
			//if (EachSite_pass_flag[SITE] == 1) working_saved[SITE] = working_saved[SITE];
			//if (rdata_working[SITE][index_working[i]] > -1)
			//{

			//dut.trim(trimname_char).set_working(rdata_working[SITE][index_working[i]], SITE);
			dut.trim(trimname_char).set_working(working_saved[SITE], SITE);
			//trimfullname = trimname + "_STEP" + to_string(rdata_working[SITE][index_working[i]]);
			//}
		}
		measure_func(TREG_MEASURE_CHAR, meas_results);

		allSite_pass_flag = 0;
		SERIAL
		{
			if (EachSite_pass_flag[SITE] == 0) meas_results_saved[SITE] = meas_results[SITE];

			meas_results_data[SITE][i] = meas_results_saved[SITE];

			if (meas_results_saved[SITE] > Llimit && meas_results_saved[SITE] < Hlimit)
			{
				allSite_pass_flag += pow(2, SITE);
				EachSite_pass_flag[SITE] = 1;
			}
		}

			//allSite_pass_flag = pow(2, allSite_pass_flag);

		if (allSite_pass_flag != SiteStatus) allSite_pass_flag = -1;
		else break;
	}

	string trimfullname_post;
	string trimfullname_postbit;
	trimfullname_post = trimname + "_post";
	trimfullname_postbit = trimname + "_post_bit";
	SERIAL
	{
		//trimfullname = trimname + "_post";
		StsGetParam(funcindex, trimfullname_post.c_str())->SetTestResult(SITE, 0, meas_results_saved[SITE]);			// log post trimming result
		//trimfullname = trimname + "_post_bit";
		StsGetParam(funcindex, trimfullname_postbit.c_str())->SetTestResult(SITE, 0, working_saved[SITE]);
	}


	double min;
	int index_diff = 0;
	if (allSite_pass_flag == -1)
	{
		SERIAL
		{
			if (EachSite_pass_flag[SITE] == 0)
			{
				for (int i = 0; i < retest_code_count; i++)
				{
					diff_data[SITE][i] = abs(meas_results_data[SITE][i] - Target_data[SITE]);
				}

				min = diff_data[SITE][0];
				for (int i = 1; i < retest_code_count; i++)
				{
					if (diff_data[SITE][i] < min)
					{
						min = diff_data[SITE][i];
						index_diff = i;
					}
				}
				dut.trim(trimname_char).set_working(rdata_working[SITE][index_working[index_diff]], SITE);

				//trimfullname = trimname + "_post";
				StsGetParam(funcindex, trimfullname_post.c_str())->SetTestResult(SITE, 0, meas_results_data[SITE][index_working[index_diff]]);			// log post trimming result
				//trimfullname = trimname + "_post_bit";
				StsGetParam(funcindex, trimfullname_postbit.c_str())->SetTestResult(SITE, 0, rdata_working[SITE][index_working[index_diff]]);
			}
		}
	}


	//int rdata1[SITE_NUM];
	//int rdata2[SITE_NUM];
	//int rdata3[SITE_NUM];
	//int rdata4[SITE_NUM];
	//int rdata5[SITE_NUM];
	//int rdata6[SITE_NUM];
	//int rdata7[SITE_NUM];
	//SERIAL
	//{
	//	rdata1[SITE] = rdata_working[SITE][index_working[0]];
	//	rdata2[SITE] = rdata_working[SITE][index_working[1]];
	//	rdata3[SITE] = rdata_working[SITE][index_working[2]];
	//	rdata4[SITE] = rdata_working[SITE][index_working[3]];
	//	rdata5[SITE] = rdata_working[SITE][index_working[4]];
	//	rdata6[SITE] = rdata_working[SITE][index_working[5]];
	//	rdata7[SITE] = rdata_working[SITE][index_working[6]];
	//}
	////StsSetSiteStatus(SiteStatus);//  make reuse sites  active

	//retest_flag = 0;
}