
#ifndef _FLASH2_H
#define _FLASH2_H

//Include system library
#include <stdint.h>
#include <xc.h>

#include "SST25VF020.h"

void FLASH2_Initialize();
void FLASH2_Write( unsigned long address, unsigned char buffer );
void FLASH2_Read( unsigned long address, unsigned char *buffer, unsigned long data_count );
void FLASH2_ChipErase( void );
        
unsigned char FLASH2_ReadByte( unsigned char buffer );

#endif 
