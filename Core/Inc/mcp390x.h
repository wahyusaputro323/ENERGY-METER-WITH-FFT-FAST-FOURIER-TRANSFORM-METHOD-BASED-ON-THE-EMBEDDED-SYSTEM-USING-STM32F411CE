/*
 * mcp390x.h
 *
 *  Created on: Jun 30, 2021
 *      Author: wahyu utoro saputro
 */

#define MCP390X_H_
#include "stm32f4xx_hal.h"

//unsigned int tempValue
 unsigned int spi_temp;

#define G0A_PORT GPIOA
#define G0A_PIN GPIO_PIN9
#define G1A_PORT GPIOA
#define G1A_PIN GPIO_PIN10
#define MCP390x_CS_PORT GPIOB
#define MCP390x_CS_PIN GPIO_PIN12
#define PHASE_A 1

extern SPI_HandleTypeDef hspi2;
// Function prototypes
HAL_StatusTypeDef spi_write(uint8_t regAddr, uint8_t *pData);
HAL_StatusTypeDef spi_read(uint8_t regAddr, uint8_t *pData);

extern void InitSPI(void);
extern void InitMCP390x(void);
extern void ReadMCP390x(void);
extern int ZeroValueCh[2];
extern int Phase_Gain[1];
extern void Delay (int cnt);

