
/*
 * $Id: GP2Y0A700K0F.c,v 1.3 2010/07/15 14:38:19 clivewebster Exp $
 *
 * Revision History
 * ================
 * $Log: GP2Y0A700K0F.c,v $
 * Revision 1.3  2010/07/15 14:38:19  clivewebster
 * Allow variable ADC reference voltage
 *
 * Revision 1.2  2010/06/14 19:03:07  clivewebster
 * Add copyright license info
 *
 * Revision 1.1  2010/01/30 21:21:49  clivewebster
 * Added new sensors
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
 *
 *
 * GP2Y0A700K0F.c
 *
 *  Created on: 29-Jan-2010
 *      Author: Clive Webster
 */

#include "GP2.h"
// Requires the floating point library
#include <math.h>

#include "../../../a2d.h"

// Read all the values and store into the device
static void __GP2Y0A700K0F_read(SENSOR* sensor){
	Sharp_GP2Y0A700K0F* device = (Sharp_GP2Y0A700K0F*)sensor;

//	uint16_t adc = a2dConvert10bit(device->adcPin);
//	device->distance.cm = 94407.0 * pow(adc,-1.0891);

	uint16_t adc = a2dReadMv(device->adcPin);
	device->distance.cm = 531492.0 * pow(adc,-1.0891);
}

DISTANCE_CLASS c_Sharp_GP2Y0A700K0F = MAKE_DISTANCE_CLASS(null,&__GP2Y0A700K0F_read,0,0);

