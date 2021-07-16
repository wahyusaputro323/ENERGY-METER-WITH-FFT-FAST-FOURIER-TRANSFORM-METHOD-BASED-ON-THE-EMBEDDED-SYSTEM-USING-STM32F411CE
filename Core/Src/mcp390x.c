/*
 * mcp390x.c
 *
 *  Created on: Jul 14, 2021
 *      Author: wahyu utoro saputro
 */

#define MCP390x_H
#include "global.h"
#include "spi_examples.h"
#include "mcp390x.h"
#undef MCP390x_H

extern long Multiply16x16 (int, int);
extern SPI_HandleTypeDef hspi2;
#define MCP390x_SPI &hspi2;

unsigned int pointer = 0;
unsigned int pointer1 = 10;

#define MCP390x_CS_PORT GPIOB
#define MCP390x_CS_PIN GPIO_PIN12

// Reference Voltage Signal from MCP3909 Arrow.com
int voltage_signal[128] =
{
		/*
		13000,12984,12937,12859,12750,12610,12440,12240,12010,11752,11465,11150,10809,10442,10049,
		9632,9192,8730,8247,7744,7222,6683,6128,5558,4975,4380,3774,3159,2536,1907,1274,638,0,-638,
		-1274,-1907,-2536,-3159,-3774,-4380,-4975,-5558,-6128,-6683,-7222,-7744,-8247,-8730,-9192,
		-9632,-10049,-10442,-10809,-11150,-11465,-11752,-12010,-12240,-12440,-12610,-12750,-12859,
		-12937,-12984,-13000,-12984,-12937,-12859,-12750,-12610,-12440,-12240,-12010,-11752,-11465,
		-11150,-10809,-10442,-10049,-9632,-9192,-8730,-8247,-7744,-7222,-6683,-6128,-5558,-4975,
		-4380,-3774,-3159,-2536,-1907,-1274,-638,0,638,1274,1907,2536,3159,3774,4380,4975,5558,
		6128,6683,7222,7744,8247,8730,9192,9632,10049,10442,10809,11150,11465,11752,12010,12240,
		12440,12610,12750,12859,12937,12984

		14133, 13261, 12281, 11198, 10019, 8755, 7417, 6017, 4571, 3091, 1594, 94, -1394, -2858, -4284,
		-5660, -6979, -8230, -9408, -10508, -11527, -12463, -13316, -14087, -14778, -15392, -15934, -16408,
		-16818, -17171, -17472, -17726, -17939, -18114, -18258, -18373, -18463, -18531, -18578, -18606,
		-18614, -18603, -18571, -18517, -18437, -18330, -18193, -18022, -17815, -17569, -17281, -16950,
		-16575, -16154, -15689, -15179, -14626, -14032, -13400, -12731, -12029, -11298, -10538, -9755,
		-8949, -8123, -7279, -6418, -5542, -4651, -3747, -2829, -1900, -961, -13, 941, 1900, 2859, 3815, 4763,
		5699, 6617, 7512, 8379, 9212, 10006, 10756, 11457, 12108, 12704, 13243, 13726, 14151, 14520, 14835,
		15099, 15315, 15487, 15621, 15722, 15796, 15849, 15888, 15917, 15944, 15974, 16011, 16059, 16122,
		16201, 16297, 16409, 16535, 16671, 16812, 16951, 17080, 17190, 17269, 17309, 17296, 17220, 17070,
		16835, 16507, 16077, 15540, 14893


		10011, 9175, 8300, 7390, 6450, 5483, 4497, 3498, 2490, 1481, 476, -521, -1503, -2469, -3414, -4338, -5239,
		-6117, -6972, -7805, -8617, -9409, -10181, -10935, -11669, -12383, -13076, -13746, -14391, -15007, -15592,
		-16142, -16652, -17121, -17544, -17919, -18243, -18516, -18736, -18903, -19017, -19081, -19095, -19062,
		-18985, -18864, -18705, -18507, -18275, -18009, -17710, -17380, -17019, -16626, -16201, -15744, -15252,
		-14724, -14160, -13558, -12917, -12237, -11517, -10758, -9960, -9126, -8258, -7358, -6430, -5478, -4507,
		-3522, -2526, -1526, -526, 470, 1456, 2429, 3386, 4323, 5239, 6132, 7001, 7845, 8665, 9460, 10232, 10980,
		11705, 12407, 13086, 13741, 14371, 14975, 15549, 16093, 16601, 17072, 17501, 17886, 18224, 18511, 18746,
		18927, 19054, 19126, 19145, 19113, 19032, 18904, 18733, 18522, 18275, 17994, 17682, 17340, 16971, 16575,
		16151, 15698, 15216, 14700, 14150, 13563, 12937, 12270, 11560, 10807
		*/

		12226, 11260, 10060, 8656, 7095, 5438, 3750, 2099, 549, -847, -2050, -3040, -3815, -4393, -4809, -5112,
		-5360, -5614, -5933, -6369, -6961, -7731, -8683, -9801, -11052, -12388, -13752, -15078, -16304, -17373,
		-18237, -18867, -19248, -19387, -19308, -19050, -18667, -18217, -17762, -17358, -17055, -16887, -16871,
		-17007, -17276, -17645, -18064, -18477, -18824, -19048, -19098, -18938, -18545, -17915, -17062, -16018,
		-14827, -13546, -12233, -10949, -9747, -8670, -7746, -6986, -6383, -5914, -5539, -5211, -4873, -4469,
		-3948, -3270, -2407, -1348, -102, 1307, 2837, 4434, 6038, 7587, 9020, 10287, 11350, 12188, 12800, 13200,
		13422, 13511, 13525, 13522, 13562, 13696, 13963, 14387, 14974, 15710, 16566, 17495, 18440, 19340, 20132,
		20758, 21172, 21344, 21259, 20924, 20363, 19618, 18742, 17798, 16851, 15961, 15181, 14550, 14088, 13798,
		13663, 13648, 13705, 13773, 13789, 13691, 13424, 12944, 12226, 11260, 10060, 8656
};

int current_signal [128] =
{
		/*
		104, 104, 103, 103, 102, 101, 100, 98, 96, 94, 92, 89, 86, 84, 80, 77, 74, 70, 66, 62, 58,
		53, 49, 44, 40, 35, 30, 25, 20, 15, 10, 5, 0, -5, -10, -15, -20, -25, -30, -35, -40, -44,
		-49, -53, -58, -62, -66, -70, -74, -77, -80, -84, -86, -89, -92, -94, -96, -98, -100, -101,
		-102, -103, -103, -104, -104, -104, -103, -103, -102, -101, -100, -98, -96, -94, -92, -89,
		-86, -84, -80, -77, -74, -70, -66, -62, -58, -53, -49, -44, -40, -35, -30, -25, -20, -15,
		-10, -5, 0, 5, 10, 15, 20, 25, 30, 35, 40, 44, 49, 53, 58, 62, 66, 70, 74, 77, 80, 84, 86,
		89, 92, 94, 96, 98, 100, 101, 102, 103, 103, 104
		*/

		10752, 10732, 10672, 10573, 10437, 10267, 10063, 9831, 9572, 9291, 8989, 8672, 8341, 7998,
		7646, 7287, 6921, 6549, 6171, 5787, 5397, 4998, 4592, 4177, 3752, 3316, 2870, 2414, 1947,
		1471, 987, 496, 0, -499, -998, -1497, -1991, -2480, -2962, -3435, -3896, -4347, -4784, -5209,
		-5620, -6017, -6400, -6770, -7126, -7468, -7796, -8109, -8407, -8689, -8954, -9201, -9427,
		-9633, -9815, -9972, -10103, -10207, -10282, -10327, -10342, -10327, -10282, -10207, -10103,
		-9972, -9815, -9633, -9427, -9201, -8954, -8689, -8407, -8109, -7796, -7468, -7126, -6770,
		-6400, -6017, -5620, -5209, -4784, -4347, -3896, -3435, -2962, -2480, -1991, -1497, -998,
		-499, 0, 496, 987, 1471, 1947, 2414, 2870, 3316, 3752, 4177, 4592, 4998, 5397, 5787, 6171,
		6549, 6921, 7287, 7646, 7998, 8341, 8672, 8989, 9291, 9572, 9831, 10063, 10267, 10437, 10573,
		10672, 10732
};

void CS_Enable(void)
{
	HAL_GPIO_WritePin(MCP390x_CS_PORT, MCP390x_CS_PIN, GPIO_PIN_SET);
}

void CS_Disable(void)
{
	HAL_GPIO_WritePin(MCP390x_CS_PORT, MCP390x_CS_PIN, GPIO_PIN_RESET);
}

void InitSPI(void)
{
	uint8_t BUF = 0;
	uint16_t SPIEN = 0;
	CS_Enable();
	HAL_SPI_Transmit(&hspi2, &BUF, 2, 1000);
	CS_Disable();
}

//void WritingSPI (uint16_t Reg, uint16_t data)
//{
//	uint16_t BUF = 0;
//	if (BUF)
//	{
//		BUF = data;
//	}
//	else
//	{
//		BUF = data & 0xff;
//	}
//	while (SPI2STATbits.SPITBF == 1)
//		{
//		}
//}
//
//void InitMCP390x(void)
//{
//	unsigned int k;
//
//	//Reset MCP3909
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
//
//	ZeroValueCh[0] = 0;
//	ZeroValueCh[1] = 0;
//
//	HAL_Delay(10000);
//	//Select MCLR
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
//	HAL_Delay(18);
//	spi_write(0xac, k);
//}
//
//void Read390x(void)
//{
//	long temp_energy;
//	int temp01;
//
//	CS_Enable();
//	spi_temp = BUF;
//	SPI2STATbits.SPIROV = 0;
//	BUF = 0;
//
//	/*
//		temp01 = voltage_signal[pointer++];
//		temp02 = current_signal[pointer1++];
//
//		if(pointer>=124)
//		 pointer = 0;
//
//		if(pointer1>=124)
//		 pointer1 = 0;
//	*/
//
//	if(!flag.bits.temp_flag)
//		{
//		flag.bits.temp_flag = 1;
//		while(!SPI2STATbits.SPIRBF)
//			{}
//		temp01 = BUF;								// voltage channel
//		SPI2STATbits.SPIROV = 0;						// clear receive flag
//		BUF = 0;
//		while(!SPI2STATbits.SPIRBF)
//			{}
//		temp01 = BUF;
//		SPI2STATbits.SPIROV = 0;
//		BUF = 0;
//		cycle_energy_buf[0] = cycle_energy_buf[0] + temp_energy;
//		while(!SPI2STATbits.SPIRBF)
//			{}
//		temp01 = BUF;
//		SPI2STATbits.SPIROV = 0;
//		BUF = 0;
//		cycle_energy_buf[0] = cycle_energy_buf[0] + temp_energy;
//		}
//	else
//	{
//		flag.bits.temp_flag = 0;
//		while(!SPI2STATbits.SPIRBF)
//			{}
//		//voltage_sample[0][DataNum] = temp01;
//		//temp01 = SPI2BUF;
//		voltage_sample[0][DataNum] = BUF; //temp01;	// voltage channel
//		//	voltage_sample[0][DataNum] -= ZeroValueCh[0]; // not needed in mode 0xac
//		SPI2STATbits.SPIROV = 0; // clear receive flag
//		SPI2BUF = 0; // send data/produce clock
//		while(!SPI2STATbits.SPIRBF)
//			{}
//		//current_sample[0][DataNum] = temp02; //temp02;
//		//temp02 = SPI2BUF;			// current channel
//		current_sample[0][DataNum] = BUF; //temp02;
//		//	current_sample[0][DataNum] -= ZeroValueCh[1];
//		SPI2STATbits.SPIROV = 0; // Clear flag
//		temp_energy = Multiply16x16(current_sample[0][DataNum], voltage_sample[0][DataNum]);
//				cycle_energy_buf[0] = cycle_energy_buf[0] + temp_energy;
//
//				DataNum++;							// wait for the next data
//				if(DataNum >= BUF_SIZE)				// loop back to the begin of cycle buffer
//				 DataNum = 0;
//
//				LeftDataNum++;
//				if((LeftDataNum >= DataNum_Cycle3)&&(!flag.bits.DataReady2Cal))			// complete sampling
//				{
//					 flag.bits.DataReady2Cal = 1;
//					 cycle_energy[0] = cycle_energy_buf[0];
//					 cycle_energy_buf[0]=0;
//				}
//			}
//
//			SPI2STATbits.SPIROV = 0;
//			CS_Enable();
//}


//MASIH BINGUNG STATEMENTNYA


void gain_control(int phase, int gain)
{
	phase == PHASE_A;
	if(gain==0)
	{
		G0A = 0;
		G1A = 0;
	}
	else if(gain==1)
	{
		G0A = 1;
		G1A = 0;
	}
	else if(gain==3)
	{
		G0A = 0;
		G1A = 1;
	}
	else if(gain==4)
	{
		G0A = 1;
		G1A = 1;
	}
		ZeroValueCh[0] = 0;
		ZeroValueCh[1] = 0;
}
