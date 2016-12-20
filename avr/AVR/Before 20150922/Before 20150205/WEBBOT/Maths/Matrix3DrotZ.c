/*
 * $Id: $
 * Revision History
 * ================
 * $Log: $
 * ================
 *
 * Copyright (C) 2011 Clive Webster (webbot@webbot.org.uk)
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
 *        File: Matrix3DrotZ.c
 *  Created on: 24 Sep 2011
 *      Author: Clive
 */

#include "Matrix3D.h"
#include <math.h>



// Set the matrix to a rotation around the Z axis
void matrix3d_SetRotateZ(MATRIX3D* matrix, double radians){
	double	sinAngle, cosAngle;

	sinAngle = sin(radians);
	cosAngle = cos(radians);

	matrix->m00 = cosAngle;
	matrix->m01 = -sinAngle;
	matrix->m02 = 0.0;

	matrix->m10 = sinAngle;
	matrix->m11 = cosAngle;
	matrix->m12 = 0.0;

	matrix->m20 = 0.0;
	matrix->m21 = 0.0;
	matrix->m22 = 1.0;

}
