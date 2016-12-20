/*
 * $Id: $
 * Revision History
 * ================
 * $Log: $
 * ================
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
 *        File: uartFlushReceiveBuffer.c
 *  Created on: 28 Dec 2010
 *      Author: Clive Webster
 */

#include "../_uart_common.h"

void __uartFlushReceiveBuffer(UART* uart){
	if(__uartGetRxBuffer(uart)){
		// flush all data from receive buffer
		bufferFlush(__uartGetRxBuffer(uart));
	}else{
		CRITICAL_SECTION{
			uart->rxChar = -1;
		}
	}
}



