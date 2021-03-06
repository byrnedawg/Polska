/*
 * $Id: _humidity_common.h,v 1.4 2010/06/14 19:09:07 clivewebster Exp $
 *
 * Revision History
 * ================
 * $Log: _humidity_common.h,v $
 * Revision 1.4  2010/06/14 19:09:07  clivewebster
 * Add copyright license info
 *
 * Revision 1.3  2009/11/02 18:40:29  clivewebster
 * Added revision log
 *
 * ===========
 *
 * Copyright (C) 2010 Clive Webster (webbot@webbot.org.uk)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Created on: 19-Sep-2009
 *      Author: Clive Webster
 *
 *  Defines the common interface for all humidity sensors
 *
 */

#ifndef HUMIDITY_H_
#define HUMIDITY_H_
#include "../_sensor_common.h"

// Define the data type used by all compasses
// Changing this will mean changing humidityDump
#define HUMIDITY_TYPE uint16_t

// Define forward references
struct s_humidity;

// Define the api for the class
typedef struct PROGMEM c_humidity{
	SENSOR_CLASS sensor;						// include parent class
} HUMIDITY_CLASS;

#define MAKE_HUMIDITY_CLASS(init,read,startup,delay) {MAKE_SENSOR_CLASS(init,read,startup,delay)}

// Define the data for each sensor
typedef struct s_humidity{
	SENSOR			sensor;						// Include fields from parent type
	HUMIDITY_TYPE	percent;						// Last read value
} HUMIDITY;

#define MAKE_HUMIDITY_SENSOR(class) {MAKE_SENSOR(&(class.sensor)),(HUMIDITY_TYPE)0}

// Create macros to make the virtual methods easier to call
#define humidityRead(device) _sensorRead_(&device.humidity.sensor)
#define humidityInit(device) _sensorInit_(&device.humidity.sensor)

// Dump the value of a sensor to the rprintf destination
void _humidityDump(const HUMIDITY* device);
#define humidityDump(device) _humidityDump(&device.humidity);


#endif /* HUMIDITY_H_ */

