
#ifndef _FIRMWARE_RW_H_
#define _FIRMWARE_RW_H_

#include "stm32f1xx_hal.h"
#ifdef WIN32
#include "win_type.h"
#else
#endif

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;



#define FLASH_END               FLASH_BANK1_END
#define APP_CONFIG_START_ADDRESS ((8*FLASH_PAGE_SIZE) + 0x08000000)
#define CONFIG_START_ADDRESS     ((9*FLASH_PAGE_SIZE) + 0x08000000)
#define APP_START_ADDRESS        ((1*FLASH_PAGE_SIZE) + CONFIG_START_ADDRESS)


void JumpToApp(void);
void AppInit(void);


#endif
