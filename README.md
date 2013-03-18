arduino-Sim900_EEPROM
=====================

arduino-Sim900_EEPROM is an Arduino library for storing the [Sim900](https://github.com/nigelb/Sim900) connection (CONN) struct in the Arduino's EEPROM 

Example usage:
```cxx
/*
  arduino-Sim900_EEPROM is an Arduino library for storing the
  Sim900 (https://github.com/nigelb/Sim900) connection
  (CONN) struct in the Arduino's EEPROM
  Copyright (C) 2012  NigelB

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

#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "Sim900.h"
#include "Sim900_EEPROM.h"

CONN store_settings, retrieve_settings;

void setup()
{
  Serial.begin(115200);
  store_settings.cid = 1;
  store_settings.contype = "GPRS";
  store_settings.apn = "internet";

  Serial.println("Storing connection:");
  Serial.print("\tCID: ");
  Serial.println(store_settings.cid);
  Serial.print("\tAPN: ");
  Serial.println(store_settings.apn);
  Serial.print("\tContype: ");
  Serial.println(store_settings.contype);
  Serial.println();
  SIM900_EEPROM::store_connection(0, store_settings);  

  Serial.println();
  Serial.println("Restoring connection:");
  if(SIM900_EEPROM::restore_connection(0, retrieve_settings))
  {
    Serial.print("\tCID: ");
    Serial.println(retrieve_settings.cid);
    Serial.print("\tAPN: ");
    Serial.println(retrieve_settings.apn);
    Serial.print("\tContype: ");
    Serial.println(retrieve_settings.contype);
  }
}

void loop()
{
  
}
```
