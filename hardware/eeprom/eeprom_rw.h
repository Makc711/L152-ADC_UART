/**
  ******************************************************************************
  * @file           : eeprom_rw.h
  * @author         : Rusanov M.N.
  * @version        : V1.0.0
  * @date           : 17-May-2024
  * @brief          : Header for eeprom_rw.cpp file.
  *                   This file contains functions for working with internal
  *                   STM32 EEPROM memory
  *
  ******************************************************************************
  */

#pragma once

#include "main.h"

class eeprom_rw
{
public:
  enum class addr
  {
    START_ADDR    = static_cast<uint32_t>(0x08080000), /* 8 kbytes */
    MAX_END_ADDR  = START_ADDR + 8 * 1024 - 1
  };

protected:
  eeprom_rw();
  static void write_only_one_word(uint32_t address, uint32_t word);
  [[nodiscard]] static uint32_t read_word(uint32_t address);
  static void write_arr_to_flash(uint32_t address, const uint32_t* arr, size_t size_bytes);
  static void read_arr_from_flash(uint32_t address, uint32_t* arr, size_t size_bytes);

private:
  static void write_word(uint32_t address, uint32_t word);
  static void check_word(uint32_t address, uint32_t word);
};
