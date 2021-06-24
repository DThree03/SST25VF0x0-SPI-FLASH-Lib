
#include "FLASH_drivers.h"

#define START_PAGE_ADDRESS      0x010000
#define END_PAGE_ADDRESS        0x3FFFFF
#define FLASH_PAGE_SIZE         8UL

void FLASH2_Initialize()
{
    SST25VF020_CS_High();  //CS high
    SST25VF020_WP_High();  //WP high
    SST25VF020_Hold(1);  //HLD high
}

void FLASH2_Write( unsigned long address, unsigned char buffer)
{
    while( SST25VF020_Busy() );

    SST25VF020_WriteEnable();
    SST25VF020_CS_Low();
    SST25VF020_PageProgram_Cmd();
    
    SST25VF020_WriteAddress( address );
    SST25VF020_SPI_WriteByte( buffer);
    SST25VF020_CS_High();
}

void FLASH2_Read( unsigned long address, unsigned char *buffer, unsigned long data_count )
{
    while( SST25VF020_Busy() );

    SST25VF020_CS_Low();
    SST25VF020_Read_Cmd( );
    SST25VF020_WriteAddress( address );
    SST25VF020_SPI_ReadBuffer( buffer, data_count );
    SST25VF020_CS_High();
}

void FLASH2_ChipErase( void )
{
    SST25VF020_ChipErase();
}


unsigned char FLASH2_ReadByte( unsigned char buffer )
{
    buffer = SST25VF020_SPI_ReadByte( 0 );

    return buffer;

}
