/*
  Sim900_EEPROM is an Arduino library for storing the
  Sim900 (https://github.com/nigelb/Sim900) connection
  (CONN) struct in the Arduino's EEPROM
  Copyright (C) 2013  NigelB

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef __SIM_900_EEPROM_H__
#define __SIM_900_EEPROM_H__

#define SIM900_EEPROM_MAGIC_NUMBER 0xDEAD

#define SIM900_EEPROM_OK 1
#define SIM900_EEPROM_ERROR_INVALID_MAGIC_NUMBER -1

#include "Sim900.h"

struct CONN_EEPROM
{
	uint16_t magic_number;
	uint16_t cid;
	uint16_t contype;
	uint16_t apn;
	uint16_t user;
	uint16_t pwd;
	uint16_t phone;
	uint16_t rate;

	CONN_EEPROM() :
		magic_number(SIM900_EEPROM_MAGIC_NUMBER),
		cid(0),
		contype(0),
		apn(0),
		user(0),
		pwd(0),
		phone(0),
		rate(0){}
};

namespace SIM900_EEPROM
{
	uint16_t store_connection(uint16_t position, CONN &connection);
	uint16_t restore_connection(uint16_t position, CONN &connection);
	uint16_t eeprom_write_field(uint16_t position, char* value);
	uint16_t eeprom_write_field(uint16_t position, uint16_t value);
	uint16_t eeprom_read_field(uint16_t position, uint16_t &value);
	uint16_t eeprom_read_field(uint16_t position, char* &value);
}


#endif
