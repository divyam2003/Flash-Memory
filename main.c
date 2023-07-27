// main.c

#include "peripherals.h"

spi intisialisation
void SPI_Init(){
	MSS_SPI_init(&g_mss_spi1);
	MSS_SPI_configure_master_mode(&g_mss_spi1,MSS_SPI_SLAVE_0,MSS_SPI_MODE0,512,8);
}

int main() {
    // Initialize the SPI interface and flash memory
    // Configure the SPI settings such as clock frequency, data mode, etc.


    flashMemoryInit();

    // Data to be written to the flash memory
    uint8_t writeData[] = {0x11, 0x22, 0x33, 0x44, 0x55};
    uint32_t dataSize = sizeof(writeData);

    // Address to write the data to in the flash memory
    uint32_t writeAddress = 0x00000000;

    // Write data to the flash memory
    flashMemoryWrite(writeAddress, writeData, dataSize);

    // Data buffer to store the read data from the flash memory
    uint8_t readData[dataSize];

    // Address to read the data from in the flash memory
    uint32_t readAddress = 0x00000000;

    // Read data from the flash memory
    flashMemoryRead(readAddress, readData, dataSize);

    // Verify the written and read data, handle any errors if necessary

    return 0;
}
