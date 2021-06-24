
#include "SST25VF020.h"

typedef enum
{
    CMD_SE          =       0x20, /**< Erase 4 KBytes of Memory Array */
    CMD_BE          =       0x52, /**< Erase 64, 32 or 8 KBytes of Memory Array */
    CMD_CE          =       0x60, /**< Erase Full Array */
            
    CMD_PP          =       0x02, /**< Page Program */
    CMD_READ        =       0x03, /**< Read Memory */
            
    CMD_AII         =       0xAF, /**< Auto Address Increment */
            
    CMD_WREN        =       0x06, /**< Write Enable */
    CMD_WRDI        =       0x04, /**< Write Disable */
            
    CMD_EWSR        =       0x50, /**< Enable Write Status Register */        
    CMD_RDSR        =       0x05, /**< Read Status Register */
    CMD_WRSR        =       0x01, /**< Write Status Register */
            
    CMD_RID         =       0x90, /**< Read ID */
    
}SST25VF020_cmd_t;            

typedef enum
{
    STATUS_WEL  =   0x02, /**< Write-enable latch status 1 = device is write-enabled
                            0 = device is not write-enabled */
    STATUS_WSE  =   0x04, /**< Write suspend-erase status 1 = erase suspended 0 =
                            erase is not suspended */
    STATUS_WSP  =   0x08, /**< Write suspend-program status 1 = program suspended
                            0 = program is not suspended */
    STATUS_WPLD =   0x10, /**< Write protections lock-down status 1 = write
                            protection lock-down enabled 0 = write protection
                            lock-down disabled */
    STATUS_SEC  =   0x20, /**< Security ID status 1 = security ID space locked
                            0 = security ID space not locked */
    STATUS_RES  =   0x40, /**< Reserved for future use */
    STATUS_BUSY =   0x03, /**< Write operation status 1 = write in progress 0 =
                            no operation in progress */
}SST25VF020_status_t;

/*-------Pin configtion------*/
/*	Replace with your MCU pin setup	*/

void SST25VF020_CS_Low(){
    //LATDbits.LATD7  = 0;
}

void SST25VF020_CS_High(){
    //LATDbits.LATD7  = 1;
}

void SST25VF020_WP_Low() // No WP
{
     //= 0;
}

void SST25VF020_WP_High()
{
     //= 1;
}

void SST25VF020_Hold( bool state ) // no HOLD
{
//    if( state )
//         = 1;
//    else
//         = 0;
}

/*-----SPI Configtion-----*/
/*	Replace with your MCU SPI setup	*/

void SST25VF020_Command( SST25VF020_cmd_t command )   //Send Byte
{
    SPI1_Exchange8bit(command);

    return;
}

unsigned char SST25VF020_SPI_ReadByte(  )   //Read Byte
{
    unsigned char value;
    value = SPI1_Exchange8bit( 0 );

    return value;
}

void SST25VF020_SPI_WriteByte( unsigned char value ) //Send Byte
{
    SPI1_Exchange8bit( value );

    return;
}

void SST25VF020_SPI_ReadBuffer( unsigned char *buffer, unsigned int count )
{
    while( count-- )
    {   
        *( buffer++ ) = SPI1_Exchange8bit( 0x00 );
    }
    
    return;
}

void SST25VF020_SPI_WriteBuffer( unsigned char *buffer, unsigned int count )
{
    while( count-- )
    {
        SPI1_Exchange8bit( *( buffer++ ) );          
    }

    return;
}

void SST25VF020_WriteAddress( unsigned long address )
{    
    unsigned char addr_hi = address >> 16;
    unsigned char addr_mi = ( address & 0x00FF00 ) >> 8;
    unsigned char addr_lo = ( address & 0x0000FF );

    SPI1_Exchange8bit( addr_hi );
    SPI1_Exchange8bit( addr_mi );
    SPI1_Exchange8bit( addr_lo );
    
    return;
}
/* Flash funtion */
unsigned char SST25VF020_ReadSR(){
    unsigned char byte = 0;
    
    SST25VF020_CS_Low();
    SST25VF020_Command( CMD_RDSR );
    byte = SST25VF020_SPI_ReadByte();
    SST25VF020_CS_High();
    return byte;
}
void SST25VF020_EWSR( void )
{
    SST25VF020_CS_Low();
    SST25VF020_Command( CMD_EWSR );
    SST25VF020_CS_High();

    return;
}
void SST25VF020_WRSR(unsigned char byte){
    SST25VF020_CS_Low();
    SST25VF020_Command( CMD_WRSR );
    SST25VF020_SPI_WriteByte(byte);
    SST25VF020_CS_High();
}
/*------------*/
void SST25VF020_WriteEnable( void )
{
    SST25VF020_CS_Low();
    SST25VF020_Command( CMD_WREN );
    SST25VF020_CS_High();

    return;
}

void SST25VF020_WriteDisable( void )
{
    SST25VF020_CS_Low();
    SST25VF020_Command( CMD_WRDI );
    SST25VF020_CS_High();
}
/*------------*/

void SST25VF020_SectorErase( unsigned long address )
{
    while( SST25VF020_Busy() );

    SST25VF020_WriteEnable();
    SST25VF020_CS_Low();
    SST25VF020_Command( CMD_SE );
    SST25VF020_WriteAddress( address );
    SST25VF020_CS_High();

}

void SST25VF020_BlockErase( unsigned long address )
{
    while( SST25VF020_Busy() );

    SST25VF020_WriteEnable();
    SST25VF020_CS_Low();
    SST25VF020_Command( CMD_BE );
    SST25VF020_WriteAddress( address );
    SST25VF020_CS_High();

}

void SST25VF020_ChipErase( void )
{
    while( SST25VF020_Busy() );

    SST25VF020_WriteEnable();
    SST25VF020_CS_Low();
    SST25VF020_Command( CMD_CE );
    SST25VF020_CS_High();
    return;
}

void SST25VF020_PageProgram_Cmd( void )
{
    SST25VF020_Command( CMD_PP );
}

void SST25VF020_Read_Cmd( void )
{
    SST25VF020_Command( CMD_READ );
}

unsigned char SST25VF020_Busy()
{
    unsigned char temp;
    temp = SST25VF020_ReadSR();
    if((temp & STATUS_BUSY) == STATUS_BUSY)
        return 1;
    else 
        return 0;
}




