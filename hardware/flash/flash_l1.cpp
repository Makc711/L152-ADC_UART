/**
  ******************************************************************************
  * @file           : flash_l1.cpp
  * @author         : Rusanov M.N.
  ******************************************************************************
  */

#include "flash_l1.h"

flash_l1::flash_l1() = default;

/**
  * @brief  Get the structure for sector erase.
  * @address_start[in]  sector start address
  * @address_end[in]    sector end address
  * 
  * @erase_init_struct[out]  A reference to the structure to erase, which will
  *                          be initialized here.
  */
void flash_l1::init_erase_struct(
  FLASH_EraseInitTypeDef &erase_init_struct, 
  const uint32_t address_start, 
  const uint32_t address_end)
{
  erase_init_struct.TypeErase   = FLASH_TYPEERASE_PAGES;
  erase_init_struct.PageAddress = address_start;
  erase_init_struct.NbPages     = (address_end - address_start) / FLASH_PAGE_SIZE
    + ((((address_end - address_start) % FLASH_PAGE_SIZE) > 0) ? 1 : 0);
}