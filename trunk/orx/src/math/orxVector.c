/* Orx - Portable Game Engine
 *
 * Orx is the legal property of its developers, whose names
 * are listed in the COPYRIGHT file distributed 
 * with this source distribution.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
 * @file orxVector.c
 * @date 27/04/2005
 * @author iarwain@orx-project.org
 *
 */


#include "math/orxVector.h"


/* *** Vector constants *** */

const orxVECTOR orxVECTOR_X      = {{orx2F(1.0f)}, {orx2F(0.0f)}, {orx2F(0.0f)}};
const orxVECTOR orxVECTOR_Y      = {{orx2F(0.0f)}, {orx2F(1.0f)}, {orx2F(0.0f)}};
const orxVECTOR orxVECTOR_Z      = {{orx2F(0.0f)}, {orx2F(0.0f)}, {orx2F(1.0f)}};

const orxVECTOR orxVECTOR_0      = {{orx2F(0.0f)}, {orx2F(0.0f)}, {orx2F(0.0f)}};
const orxVECTOR orxVECTOR_1      = {{orx2F(1.0f)}, {orx2F(1.0f)}, {orx2F(1.0f)}};

const orxVECTOR orxVECTOR_RED    = {{orx2F(1.0f)}, {orx2F(0.0f)}, {orx2F(0.0f)}};
const orxVECTOR orxVECTOR_GREEN  = {{orx2F(0.0f)}, {orx2F(1.0f)}, {orx2F(0.0f)}};
const orxVECTOR orxVECTOR_BLUE   = {{orx2F(0.0f)}, {orx2F(0.0f)}, {orx2F(1.0f)}};

const orxVECTOR orxVECTOR_BLACK  = {{orx2F(0.0f)}, {orx2F(0.0f)}, {orx2F(0.0f)}};
const orxVECTOR orxVECTOR_WHITE  = {{orx2F(1.0f)}, {orx2F(1.0f)}, {orx2F(1.0f)}};
