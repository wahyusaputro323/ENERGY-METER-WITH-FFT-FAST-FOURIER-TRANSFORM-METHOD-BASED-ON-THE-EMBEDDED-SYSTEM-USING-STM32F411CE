/*
 * spi_exmples.h
 *
 *  Created on: Jul 3, 2021
 *      Author: wahyu utoro saputro
 */

#ifndef __spi_examples_H
#define __spi_examples_H
#ifdef __cplusplus
 extern "C" {
#endif

void coba ();

#ifdef __cplusplus
}
#endif
#include "main.h"

extern SPI_HandleTypeDef hspi2;

// Function prototypes
HAL_StatusTypeDef spi_write(uint8_t regAddr, uint8_t *pData);
HAL_StatusTypeDef spi_read(uint8_t regAddr, uint8_t *pData);

#endif
