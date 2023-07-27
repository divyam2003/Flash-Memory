// flashm.c

#include"flashm.h"
//#include "SPI.h"  // Include the SPI driver library or header file


// Commands for W25Q64FV Flash Memory
uint8_t CMD0[] = {0x06};        //
uint8_t CMD1[] = {0x99};        //
//Write Enable
//uint8_t CMD1[] = {0x04};        // Write Disable
//uint8_t CMD2[] = {0x01, 0x00};  // Read (1-1-4)
//uint8_t CMD3[] = {0x03, 0x00, 0x00, 0x00};  // Read (1-1-4)
//uint8_t CMD4[] = {0x0B, 0x00, 0x00, 0x00};  // Fast Read (1-1-4)
//uint8_t CMD5[] = {0x0C, 0x00, 0x00, 0x00};  // Fast Read (1-1-1)
//uint8_t CMD6[] = {0x02, 0x00, 0x00, 0x00};  // Page Program (1-1-4)
//uint8_t CMD7[] = {0x20, 0x00, 0x00, 0x00};  // Subsector Erase (4KB) (1-1-4)
//uint8_t CMD8[] = {0x52, 0x00, 0x00, 0x00};  // Sector Erase (32KB) (1-1-4)
//uint8_t CMD9[] = {0xD8, 0x00, 0x00, 0x00};  // Block Erase (64KB) (1-1-4)
//uint8_t CMD10[] = {0x60};       // Chip Erase (1-1-4)
//uint8_t CMD11[] = {0x9F};       // Read JEDEC ID
//uint8_t CMD12[] = {0x01};       // Read Electronic ID
//uint8_t CMD13[] = {0x05};       // Read Unique ID
//uint8_t CMD14[] = {0x81, 0x00}; // Read SFDP Register
//uint8_t CMD15[] = {0x50};       // Clear SR Fail Flags

// ... Add more commands as needed for your specific application.

// Function to send a single command to the flash memory and receive the response
void sendCommand(uint8_t *cmd, uint8_t size, uint8_t *rx_buffer) {
    for (uint8_t i = 0; i < size; i++) {
        rx_buffer[i] = MSS_SPI_transfer_frame(&g_mss_spi1, cmd[i]);
    }
}

// Function to check if the flash memory is busy (write operation in progress)
uint8_t fmbusy() {
	uint8_t rx_buffer[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    // Set the slave select for the flash memory
    MSS_SPI_set_slave_select(&g_mss_spi1, MSS_SPI_SLAVE_0);

    // Send the Read Status Register command (RDSR: 0x05)
    uint8_t readStatusCmd[] = {0x05};
    sendCommand(readStatusCmd, sizeof(readStatusCmd),rx_buffer);

    // Receive the status register value
    uint8_t status = MSS_SPI_transfer_frame(&g_mss_spi1, 0x00); // Send dummy byte to receive data

    // Deselect the flash memory as the SPI slave
    MSS_SPI_clear_slave_select(&g_mss_spi1, MSS_SPI_SLAVE_0);

    // Check if the Write In Progress (WIP) bit is set (bit 0 of status register)
    return (status & 0x01) != 0;
}



// Function to initialize the W25Q64FV flash memory
uint8_t flashMemoryInit() {
    uint8_t rx_buffer[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    uint32_t i = 0;

//    making CS low
    MSS_GPIO_set_output(FM_CS_GPIO,0);

    // Make sure the write enable latch is set
    sendCommand(CMD0, sizeof(CMD0), rx_buffer);

    // Dummy SPI clock cycles (10 cycles)
    for (i = 0; i < 10; i++) {
        MSS_SPI_transfer_frame(&g_mss_spi1, 0xff);
    }

    // Set the slave select for the flash memory
    MSS_SPI_set_slave_select(&g_mss_spi1, MSS_SPI_SLAVE_0);

    // Send (RESET) and wait for the response (response should be 0x01)
    do {
//    	enable reset 0x66
        sendCommand(CMD1, sizeof(CMD0), rx_buffer);
        i++;
    } while (rx_buffer[0] != 1 && i < 127);

    // If the response is not 0x01, there might be an issue with the flash memory
    if (i >= 127) {
        MSS_SPI_clear_slave_select(&g_mss_spi1, MSS_SPI_SLAVE_0);
        // Handle the error or return an error code
        return 1;
    }

    // ... Continue with the rest of the initialization code as needed.

    // After initialization, clear the slave select for the flash memory
    MSS_SPI_clear_slave_select(&g_mss_spi1, MSS_SPI_SLAVE_0);

    //    making CS high after operation
     MSS_GPIO_set_output( FM_CS_GPIO,1);
    return 0;


}

// Function to write data to the flash memory
void flashMemoryWrite(uint32_t address, uint8_t *data, uint32_t size) {
	uint8_t rx_buffer[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

	//    making CS low
	    MSS_GPIO_set_output( FM_CS_GPIO,0);

    // Enable the flash memory for writing
    uint8_t enableWriteCmd[] = {0x06};
    sendCommand(enableWriteCmd, sizeof(enableWriteCmd),rx_buffer);

    // Set the slave select for the flash memory
    MSS_SPI_set_slave_select(&g_mss_spi1, MSS_SPI_SLAVE_0);

    // Send the write command (Page Program) followed by the address to write to
    uint8_t writeCmd[] = {0x02, (address >> 16) & 0xFF, (address >> 8) & 0xFF, address & 0xFF};
    sendCommand(writeCmd, sizeof(writeCmd),rx_buffer);

    // Send the data to be written
    for (uint32_t i = 0; i < size; i++) {
        MSS_SPI_transfer_frame(&g_mss_spi1, data[i]);
    }

    // Deselect the flash memory as the SPI slave
    MSS_SPI_clear_slave_select(&g_mss_spi1, MSS_SPI_SLAVE_0);

    // Wait for the write operation to complete
    while (fmbusy()) {
        // Add a delay or other logic to wait for the write operation to complete
    }

    //    making CS high after operation
         MSS_GPIO_set_output( FM_CS_GPIO,1);
}

// Function to read data from the flash memory
void flashMemoryRead(uint32_t address, uint8_t *data, uint32_t size) {
	uint8_t rx_buffer[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

	//    making CS low
		    MSS_GPIO_set_output( FM_CS_GPIO,0);

    // Set the slave select for the flash memory
    MSS_SPI_set_slave_select(&g_mss_spi1, MSS_SPI_SLAVE_0);

    // Send the read command (Read Data) followed by the address to read from
    uint8_t readCmd[] = {0x03, (address >> 16) & 0xFF, (address >> 8) & 0xFF, address & 0xFF};
    sendCommand(readCmd, sizeof(readCmd),rx_buffer);

    // Receive the data from the flash memory
    for (uint32_t i = 0; i < size; i++) {
        data[i] = MSS_SPI_transfer_frame(&g_mss_spi1, 0x00); // Send dummy byte to receive data
    }

    // Deselect the flash memory as the SPI slave
    MSS_SPI_clear_slave_select(&g_mss_spi1, MSS_SPI_SLAVE_0);

    //    making CS high after operation
         MSS_GPIO_set_output( FM_CS_GPIO,1);
}



//uint8_t SD_Init(){
//
//}
