/*
 * eep.h
 *
 *  Created on: Aug 28, 2018
 *      Author: sam
 */


#ifndef __EEPROM_H
#define __EEPROM_H

#include <stdbool.h>
#include "stm32f1xx_hal.h"
/*
 * usr files*/
#include "effect.h"

//################################################################################################################
bool	EE_Format(void);
bool 	EE_Read(uint16_t VirtualAddress, uint32_t* Data);
bool 	EE_Write(uint16_t VirtualAddress, uint32_t Data);
bool	EE_Reads(uint16_t StartVirtualAddress,uint16_t HowMuchToRead,uint32_t* Data);
bool 	EE_Writes(uint16_t StartVirtualAddress,uint16_t HowMuchToWrite,uint32_t* Data);
//################################################################################################################

bool EE_Reads_Efx(uint16_t start, uint16_t size,  efx_node_t** data);
bool EE_Writes_Efx(uint16_t start, uint16_t size, efx_node_t** data);
#endif
