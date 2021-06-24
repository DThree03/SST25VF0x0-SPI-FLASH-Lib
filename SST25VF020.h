
#ifndef _SST25VF020_H
#define _SST25VF020_H

/* Include system library */
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

/* Include your MCU spi lib here */
//#include "../spi1.h"
/* Include your MCU GPIO lib here */
//#include "../pin_manager.h"

unsigned char SST25VF020_SPI_ReadByte(  );
void SST25VF020_SPI_WriteByte( unsigned char value );
void SST25VF020_SPI_ReadBuffer( unsigned char *buffer, unsigned int count );
void SST25VF020_SPI_WriteBuffer( unsigned char *buffer, unsigned int count );
void SST25VF020_WriteAddress( unsigned long address );

void SST25VF020_CS_Low();
void SST25VF020_CS_High();
void SST25VF020_WP_Low();
void SST25VF020_WP_High();
void SST25VF020_Hold( bool state );

unsigned char SST25VF020_ReadSR();
void SST25VF020_EWSR(); //Enable Write Status Register
void SST25VF020_WRSR(unsigned char byte); //Write Status Register

void SST25VF020_WriteEnable( void );
void SST25VF020_WriteDisable( void );

void SST25VF020_PageProgram_Cmd( void );
void SST25VF020_Read_Cmd( void );

void SST25VF020_SectorErase( unsigned long address );
void SST25VF020_BlockErase( unsigned long address );
void SST25VF020_ChipErase( void );

unsigned char SST25VF020_Busy();

#endif // _SST25VF020_H

