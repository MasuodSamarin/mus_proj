/*
 * eep.c
 *
 *  Created on: Aug 28, 2018
 *      Author: sam
 */

#include "eeprom.h"
#include "eepromConfig.h"



#ifdef  _EEPROM_F1_LOW_DESTINY
#define		_EEPROM_FLASH_PAGE_SIZE								1024
/* Base address of the Flash sectors */
#define ADDR_FLASH_PAGE_0     ((uint32_t)0x08000000) /* Base @ of Page 0, 1 Kbytes */
#define _EEPROM_FLASH_PAGE_ADDRESS    (ADDR_FLASH_PAGE_0|(_EEPROM_FLASH_PAGE_SIZE*_EEPROM_USE_FLASH_PAGE))
#if (_EEPROM_USE_FLASH_PAGE>31)
#error  "Please Enter correct value _EEPROM_USE_FLASH_PAGE  (0 to 31)"
#endif
#endif


#ifdef  _EEPROM_F1_MEDIUM_DESTINY
#define		_EEPROM_FLASH_PAGE_SIZE								1024
/* Base address of the Flash sectors */
#define ADDR_FLASH_PAGE_0     ((uint32_t)0x08000000) /* Base @ of Page 0, 1 Kbytes */
#define _EEPROM_FLASH_PAGE_ADDRESS    (ADDR_FLASH_PAGE_0|(_EEPROM_FLASH_PAGE_SIZE*_EEPROM_USE_FLASH_PAGE))
#if (_EEPROM_USE_FLASH_PAGE>127)
#error  "Please Enter currect value _EEPROM_USE_FLASH_PAGE  (0 to 127)"
#endif
#endif


#ifdef  _EEPROM_F1_HIGH_DESTINY
#define		_EEPROM_FLASH_PAGE_SIZE								2048
/* Base address of the Flash sectors */
#define ADDR_FLASH_PAGE_0     ((uint32_t)0x08000000) /* Base @ of Page 0, 2 Kbytes */
#define _EEPROM_FLASH_PAGE_ADDRESS    (ADDR_FLASH_PAGE_0|(_EEPROM_FLASH_PAGE_SIZE*_EEPROM_USE_FLASH_PAGE))
#if (_EEPROM_USE_FLASH_PAGE>255)
#error  "Please Enter currect value _EEPROM_USE_FLASH_PAGE  (0 to 255)"
#endif
#endif

uint32_t	EEPROMPageBackup[_EEPROM_FLASH_PAGE_SIZE/4] = {0};
efx_node_t	EEPROMPageBackupEfx[_EEPROM_FLASH_PAGE_SIZE/4] = {0};

//##########################################################################################################
//##########################################################################################################
//##########################################################################################################
bool	EE_Format(void)
{
	uint32_t	error;
	FLASH_EraseInitTypeDef	flashErase;
	flashErase.NbPages=128-_EEPROM_USE_FLASH_PAGE;
	flashErase.Banks = FLASH_BANK_1;
	flashErase.PageAddress = _EEPROM_FLASH_PAGE_ADDRESS;
	flashErase.TypeErase = FLASH_TYPEERASE_PAGES;

	HAL_FLASH_Unlock();
	if(HAL_FLASHEx_Erase(&flashErase,&error)==HAL_OK)
	{
		HAL_FLASH_Lock();
		if(error != 0xFFFFFFFF)
			return false;
		else
			return true;
	}
	HAL_FLASH_Lock();

	return false;
}
//##########################################################################################################
bool EE_Read(uint16_t VirtualAddress, uint32_t* Data)
{
	if(VirtualAddress >=	(_EEPROM_FLASH_PAGE_SIZE/4))
		return false;
	*Data =  (*(__IO uint32_t*)((VirtualAddress*4)+_EEPROM_FLASH_PAGE_ADDRESS));
	return true;
}

//##########################################################################################################
bool EE_Write(uint16_t VirtualAddress, uint32_t Data)
{
	if(VirtualAddress >=	(_EEPROM_FLASH_PAGE_SIZE/4))
		return false;

	if((*(__IO uint32_t*)((VirtualAddress*4)+_EEPROM_FLASH_PAGE_ADDRESS)) != 0xFFFFFFFF)
	{

		if( EE_Reads(0,(_EEPROM_FLASH_PAGE_SIZE/4),EEPROMPageBackup)==false)
		{
			HAL_FLASH_Lock();
			return false;
		}
		EEPROMPageBackup[VirtualAddress]=Data;
		EE_Format();

		HAL_FLASH_Unlock();
		for(uint16_t	i=0 ; i<_EEPROM_FLASH_PAGE_SIZE/4 ; i++)
		{
			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(i*4)+_EEPROM_FLASH_PAGE_ADDRESS,(uint64_t)EEPROMPageBackup[i])!=HAL_OK)
				{
					HAL_FLASH_Lock();
					return false;
				}
		}
	}
	HAL_FLASH_Unlock();
	if(Data!=0xFFFFFFFF)
	{
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(VirtualAddress*4)+_EEPROM_FLASH_PAGE_ADDRESS,(uint64_t)Data)==HAL_OK)
		{
			HAL_FLASH_Lock();
			return true;
		}
		else
		{
			HAL_FLASH_Lock();
			return false;
		}
	}
	HAL_FLASH_Lock();
	return true;

}
//##########################################################################################################
bool EE_Reads(uint16_t StartVirtualAddress,uint16_t HowMuchToRead,uint32_t* Data)
{
	if((StartVirtualAddress+HowMuchToRead) >	(_EEPROM_FLASH_PAGE_SIZE/4))
		return false;
	for(uint16_t i=StartVirtualAddress; i<HowMuchToRead+StartVirtualAddress; i++)
	{
		*Data =  (*(__IO uint32_t*)((i*4)+_EEPROM_FLASH_PAGE_ADDRESS));
		Data++;
	}
	return true;
}
//##########################################################################################################
bool 	EE_Writes(uint16_t start,uint16_t size,uint32_t* data)
{
	if((start+size) >	(_EEPROM_FLASH_PAGE_SIZE/4))
		return false;
	if( EE_Reads(0,(_EEPROM_FLASH_PAGE_SIZE/4),EEPROMPageBackup)==false)
		return false;
	for(uint16_t	i=start ; i<size+start ; i++)
	{
		EEPROMPageBackup[i]=*data;
		data++;
	}
	if(EE_Format()==false)
		return false;
	HAL_FLASH_Unlock();
	for(uint16_t	i=0 ; i<(_EEPROM_FLASH_PAGE_SIZE/4); i++)
	{
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(i*4)+_EEPROM_FLASH_PAGE_ADDRESS,(uint64_t)EEPROMPageBackup[i])!=HAL_OK)
		{
			HAL_FLASH_Lock();
			return false;
		}
	}
	HAL_FLASH_Lock();
	return true;
}
//##########################################################################################################

#include <stdio.h>
#include <string.h>
//#define size_of_node sizeof(efx_node_t)/sizeof(uint32_t)
/*
 * TODO: d is fucking shit*/
#define SIZE_NODE_BYTE 24
#define SIZE_NODE_INT 3

bool EE_Reads_Efx(uint16_t start, uint16_t size, efx_node_t* data[])
{
	if((start + (size * SIZE_NODE_BYTE)) >	(_EEPROM_FLASH_PAGE_SIZE))
		return false;
	//uint8_t var = 0;
	for (int var = 0; var < size; ++var) {
		uint32_t addr = _EEPROM_FLASH_PAGE_ADDRESS + start + (var*SIZE_NODE_BYTE);
		__IO efx_node_t *efx =  (__IO efx_node_t*)(addr);
		data[var] = (efx_node_t*)efx;

	}
	/*
	for(uint16_t i=start; i<=start + (size * SIZE_NODE_BYTE); (i+=SIZE_NODE_BYTE))
	{
		//efx_node_t *efx = malloc(sizeof(efx_node_t));
		efx_node_t *efx =  &(*( efx_node_t*)((i)+_EEPROM_FLASH_PAGE_ADDRESS));
		data[var++] = (efx_node_t*)efx;
	}
	*/
	return true;
}

bool EE_Writes_Efx(uint16_t start, uint16_t size, efx_node_t* data[])
{
	if((start + (size * SIZE_NODE_BYTE)) >	(_EEPROM_FLASH_PAGE_SIZE))
		return false;
	//if( EE_Reads_Efx(0,(_EEPROM_FLASH_PAGE_SIZE/sizeof(efx_node_t)),EEPROMPageBackupEfx)==false)
		//return false;
	//for(uint16_t i=start ; i<size+start ; i++)
	//{
		//EEPROMPageBackupEfx[i]=*data[i];
		//(*data)++;
	//}
	uint64_t node[SIZE_NODE_INT*size];
	for (int var = 0; var < size; ++var) {
		memmove((void*)&node[SIZE_NODE_INT*var], (void*)(data[var]), SIZE_NODE_BYTE);

	}
	//memcpy((void*)node, (void*)*data, SIZE_NODE_BYTE*size);
	if(EE_Format()==false)
		return false;
	uint8_t var = 0;
	HAL_FLASH_Unlock();
	for (int var = 0; var < SIZE_NODE_INT*size; ++var) {
		uint32_t addr = _EEPROM_FLASH_PAGE_ADDRESS + start + (var*8);

		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addr, node[var]) != HAL_OK){
			HAL_FLASH_Lock();
			return false;
		}
	}
	/*
	for(uint16_t i=start; i<=start + (size * SIZE_NODE_BYTE); (i+=SIZE_NODE_BYTE))
	{
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,
				(i) + _EEPROM_FLASH_PAGE_ADDRESS, node[var++]) != HAL_OK)
		{
			HAL_FLASH_Lock();
			return false;
		}
	}
	*/
	HAL_FLASH_Lock();
	return true;
}


