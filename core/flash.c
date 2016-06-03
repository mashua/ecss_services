#include "flash.h"
#include "stm32f4xx_hal.h"

#define SECTOR_3_ADD_START 
#define SECTOR_3_ADD_FIN   0x0800FFFF
#define SECTOR_3_SIZE	   0xFFF

#define TRANSMIT_VAR_ADD   0x0800C000

#pragma location = 0x0800C000 
const uint32_t occupy_sector[SECTOR_3_SIZE] = { 0xa94249da, 0x0A };

uint32_t flash_INIT() {
    return occupy_sector[0];
}

uint32_t flash_read_trasmit() {

    uint32_t *val = (uint32_t*)TRANSMIT_VAR_ADD;

    return *val;
}

void flash_write_trasmit(uint32_t data) {

    HAL_FLASH_Unlock();

    //HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError);
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

    FLASH_Erase_Sector(FLASH_SECTOR_3, VOLTAGE_RANGE_3);

    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, TRANSMIT_VAR_ADD, data);

    HAL_FLASH_Lock();
}
