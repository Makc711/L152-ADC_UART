/**
  ******************************************************************************
  * @file           : eeprom_rw.cpp
  * @author         : Rusanov M.N.
  ******************************************************************************
  */

#include "eeprom_rw.h"

eeprom_rw::eeprom_rw() = default;

void eeprom_rw::write_word(const uint32_t address, const uint32_t word)
{
  if (const HAL_StatusTypeDef status = HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAM_WORD, address, word);
      status != HAL_OK)
  {
    /* Error occurred while writing data in Eeprom memory.
       User can add here some code to deal with this error */
    Error_Handler();
  }
}

void eeprom_rw::write_only_one_word(uint32_t address, uint32_t word)
{
  HAL_FLASHEx_DATAEEPROM_Unlock();
  write_word(address, word);
  HAL_FLASHEx_DATAEEPROM_Lock();
}

uint32_t eeprom_rw::read_word(const uint32_t address)
{
  return *reinterpret_cast<__IO uint32_t*>(address);  // NOLINT(performance-no-int-to-ptr)
}

void eeprom_rw::check_word(const uint32_t address, const uint32_t word)
{
  if (read_word(address) != word)
  {
    Error_Handler();
  }
}

void eeprom_rw::write_arr_to_flash(const uint32_t address, const uint32_t* arr, const size_t size_bytes)
{
  if (const uint32_t end_addr = address + size_bytes - 1;
      end_addr > static_cast<uint32_t>(addr::MAX_END_ADDR))
  {
    Error_Handler();
  }

  HAL_FLASHEx_DATAEEPROM_Unlock();

  const size_t whole_words = size_bytes / sizeof(uint32_t);
  for (size_t i = 0; i < whole_words; ++i)
  {
    const size_t addr = address + i * sizeof(uint32_t);
    write_word(addr, arr[i]);
    check_word(addr, arr[i]);
  }

  if (const size_t remaining_bytes = size_bytes % sizeof(uint32_t);
    remaining_bytes > 0)
  {
    const uint32_t mask = (remaining_bytes == 1)
                                 ? 0x000000FF
                                 : (remaining_bytes == 2)
                                     ? 0x0000FFFF
                                     : 0x00FFFFFF;
    const uint32_t last_word = arr[whole_words] & mask;
    const size_t addr = address + size_bytes - remaining_bytes;
    write_word(addr, last_word);
    check_word(addr, last_word);
  }

  HAL_FLASHEx_DATAEEPROM_Lock();
}

void eeprom_rw::read_arr_from_flash(const uint32_t address, uint32_t* arr, const size_t size_bytes)
{
  if (const uint32_t end_addr = address + size_bytes - 1;
      end_addr > static_cast<uint32_t>(addr::MAX_END_ADDR))
  {
    Error_Handler();
  }

  const size_t whole_words = size_bytes / sizeof(uint32_t);
  for (size_t i = 0; i < whole_words; ++i)
  {
    arr[i] = read_word(address + i * sizeof(uint32_t));
  }

  if (const size_t remaining_bytes = size_bytes % sizeof(uint32_t);
    remaining_bytes > 0)
  {
    const size_t addr = address + size_bytes - remaining_bytes;
    const uint32_t mask = (remaining_bytes == 1)
                                 ? 0x000000FF
                                 : (remaining_bytes == 2)
                                     ? 0x0000FFFF
                                     : 0x00FFFFFF;
    arr[whole_words] = (arr[whole_words] & ~mask) | (read_word(addr) & mask);
  }
}
