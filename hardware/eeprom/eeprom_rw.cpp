/**
  ******************************************************************************
  * @file           : eeprom_rw.cpp
  * @author         : Rusanov M.N.
  ******************************************************************************
  */

#include "eeprom_rw.h"

uint32_t eeprom_rw::erase_sector(uint32_t address_start, uint32_t address_end)
{
  return 0;
}

void eeprom_rw::write_byte(uint32_t address, uint8_t byte)
{
  
}

uint8_t eeprom_rw::read_byte(uint32_t address)
{
  return 0;
}

void eeprom_rw::check_byte(uint32_t address, uint8_t byte)
{
  
}

void eeprom_rw::write_arr_to_flash(uint32_t address, const uint8_t* arr, size_t size)
{
  
}

void eeprom_rw::read_arr_from_flash(uint32_t address, uint8_t* arr, size_t size)
{
  
}

uint32_t eeprom_rw::get_sector(uint32_t address)
{
  return 0;
}
