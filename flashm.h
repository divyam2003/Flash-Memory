// flashm.h
#ifndef flash_H_

#define flash_H_
#include "peripherals.h"



//  @brief Initialises the flash memory card
//  FM-flash memory
//  @return uint8_t : returns 0 if successful

uint8_t flashMemoryInit();

//@brief Function to write to the FM
//
//@param addr  : The address to be written to. This must be a multiple of 512
//@param buff  : The data to be written to. This must be 512 bytes
//@return uint8_t : returns 0 if successful

void flashMemoryWrite(uint32_t address, uint8_t *data, uint32_t size);

/**
 * @brief Fuction to read from the FM card
 *
 * @param addr  : The address to be read from. This must be a multiple of 512
 * @param buff  : The buffer to store the read data in
 * @return uint8_t : returns 0 if successful
 */
void flashMemoryRead(uint32_t address, uint8_t *data, uint32_t size);
#endif
