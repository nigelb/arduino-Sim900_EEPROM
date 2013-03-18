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

#include "Sim900_EEPROM.h"
#include <EEPROM.h>

#define SIM900_EEPROM_write_field(connection, store, field, message)\
	if(connection.field != 0)\
	{\
		len = strlen(connection.field);\
		if(len > 0)\
		{\
			/*Serial.println(message);*/\
			store.field = pos;\
			pos += eeprom_write_field(pos, connection.field);\
		}\
	}\

#define SIM900_EEPROM_read_field(connection, store, field)\
		if(store.field != 0)\
		{\
			char *tmp;\
			eeprom_read_field(store.field, tmp);\
			connection.field = tmp;\
		}

uint16_t SIM900_EEPROM::store_connection(uint16_t position, CONN &connection)
{
	CONN_EEPROM store;
	byte* d = (byte*)&store;
	int header_size = sizeof(CONN_EEPROM);
	int pos = position + header_size;
	int len;
	store.cid = connection.cid;
	SIM900_EEPROM_write_field(connection, store, contype, "Writing Contype to EEPROM");
	SIM900_EEPROM_write_field(connection, store, apn, "Writing APN to EEPROM");
	SIM900_EEPROM_write_field(connection, store, user, "Writing User to EEPROM");
	SIM900_EEPROM_write_field(connection, store, pwd, "Writing PWD to EEPROM");
	SIM900_EEPROM_write_field(connection, store, phone, "Writing Phone to EEPROM");
	SIM900_EEPROM_write_field(connection, store, rate, "Writing Rate to EEPROM");
	for (int i = 0; i < header_size; i++)
	{
		EEPROM.write(i + position, d[i]);
	}
	return pos - position;
}

uint16_t SIM900_EEPROM::restore_connection(uint16_t position, CONN &connection)
{
	CONN_EEPROM store;
	store.magic_number = 0;
	byte* d = (byte*)&store;
	int header_size = sizeof(CONN_EEPROM);
	for(int i = 0; i < header_size; i++)
	{
		d[i] = EEPROM.read(position + i);
	}
	if(store.magic_number == SIM900_EEPROM_MAGIC_NUMBER)
	{
		SIM900_EEPROM_read_field(connection, store, contype);
		SIM900_EEPROM_read_field(connection, store, apn);
		SIM900_EEPROM_read_field(connection, store, user);
		SIM900_EEPROM_read_field(connection, store, pwd);
		SIM900_EEPROM_read_field(connection, store, phone);
		SIM900_EEPROM_read_field(connection, store, rate);
		connection.cid = store.cid;
		return SIM900_EEPROM_OK;

	}
	return SIM900_EEPROM_ERROR_INVALID_MAGIC_NUMBER;
}

uint16_t SIM900_EEPROM::eeprom_write_field(uint16_t position, char* value)
{
	uint16_t count = 0;
	uint16_t len = strlen(value);
	if(len > 0)
	{
		count = eeprom_write_field(position, len);
		for(uint16_t i = 0; i < len; i++, count++)
		{
			EEPROM.write(count + position, value[i]);
		}
	}
	return count;
}

uint16_t SIM900_EEPROM::eeprom_write_field(uint16_t position, uint16_t value)
{

	byte* ptr = (byte*)&value;
	for(uint16_t i = 0; i < sizeof(uint16_t); i++)
	{
		EEPROM.write(position + i, ptr[i]);
	}
	//Serial.print("Wrote: ");
	//Serial.println(value);
	return sizeof(uint16_t);

}
uint16_t SIM900_EEPROM::eeprom_read_field(uint16_t position, uint16_t &value)
{
	byte* ptr = (byte*)&value;
	for(uint16_t i = 0; i < sizeof(uint16_t); i++)
	{
		ptr[i] = EEPROM.read(position + i);
	}
	return sizeof(uint16_t);
}

uint16_t SIM900_EEPROM::eeprom_read_field(uint16_t position, char* &value)
{
	uint16_t size;
	uint16_t count = eeprom_read_field(position, size);
	value = (char*)malloc(size+1);
	for(uint16_t i = 0; i < size; i++, count++)
	{
		value[i] = EEPROM.read(position + count);
	}
	value[size] = 0;
	return count;

}


