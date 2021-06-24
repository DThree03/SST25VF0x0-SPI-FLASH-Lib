Before use, modify library follow:
1. SST25VF0x0.h:  Include your MCU SPI and GPIO setup SPI pin
2. SST25VF0x0.c:
- Add your MCU GPIO funtion to set or reset CS pin in "Pin configtion" zone
- Replace your MCU SPI funtion in "SPI Configtion" zone to READ and WRITE byte via SPI
