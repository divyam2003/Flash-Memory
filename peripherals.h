// peripherals.h

#include<drivers/mss_spi/mss_spi.h>
#include <drivers/mss_gpio/mss_gpio.h>

#define WriteEnable 0x06
#define WriteDisable 0x04
#define DummyBite 0xA5

#define Flash_CE PB0
#define Flash_CE_pin_low spi_port &= ~(1<<SS)
#define Flash_CE_pin_high spi_port |= (1<<SS)

#define ReadSR1 0x05
#define WriteSR1 0x01
#define ReadSR2 0x35

#define Write_Enab_for_Vol_status_regist 0x50

#define ReadData 0x03
#define WriteData 0x02
#define ReadDataFast 0x0B

#define JEDECID 0x9F
#define UniqueID 0x4B

#define SectErase4KB 0x20
#define SectErase32KB 0x52
#define SectErase64KB 0xD8
#define ChipErase 0xC7

#define EReset 0x66
#define Reset 0x99

#define FM_CS_GPIO				MSS_GPIO_10 // pin & CS chip select
