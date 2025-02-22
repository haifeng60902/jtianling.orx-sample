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
 * @file orxFrame.h
 * @date 01/12/2003
 * @author iarwain@orx-project.org
 *
 * @todo
 * - Use matrix instead of disjoint position vector/angle float/scale vector
 * - Add 3D support
 */

/**
 * @addtogroup orxFrame
 *
 * Frame (scene node) Module.
 * Allows to handles frame (scene nodes).
 * It consists in a nodes (arranged in a hierarchical tree)
 * having their position given in their parent local coordinate subsystem
 * and caching their global one (in the root coordinate system).
 * They're used to give position, rotation & scale to an object or a group of objects.
 * Frames are structures.
 * They thus can be referenced by Object Module.
 *
 * @{
 */


#ifndef _orxFRAME_H_
#define _orxFRAME_H_

#include "orxInclude.h"

#include "math/orxVector.h"


/** Frame flags
 */
#define orxFRAME_KU32_FLAG_NONE               0x00000000  /**< No flags */

#define orxFRAME_KU32_FLAG_SCROLL_X           0x00000001  /**< X axis differential scrolling flag */
#define orxFRAME_KU32_FLAG_SCROLL_Y           0x00000002  /**< Y axis differential scrolling flag */
#define orxFRAME_KU32_MASK_SCROLL_BOTH        0x00000003  /**< Both axis differential scrolling mask */

#define orxFRAME_KU32_FLAG_DEPTH_SCALE        0x00000004  /**< Relative depth scaling flag */

#define orxFRAME_KU32_FLAG_FLIP_X             0x00000010  /**< X axis flipping flag */
#define orxFRAME_KU32_FLAG_FLIP_Y             0x00000020  /**< Y axis flipping flag */
#define orxFRAME_KU32_MASK_FLIP_BOTH          0x00000030  /**< Both axis flippinf mask */

#define orxFRAME_KU32_MASK_USER_ALL           0x000000FF  /**< User all ID mask */


/** Frame space enum
 */
typedef enum __orxFRAME_SPACE_t
{
  orxFRAME_SPACE_GLOBAL = 0,
  orxFRAME_SPACE_LOCAL,

  orxFRAME_SPACE_NUMBER,

  orxFRAME_SPACE_NONE = orxENUM_NONE

} orxFRAME_SPACE;


/** Internal Frame structure
 */
typedef struct __orxFRAME_t                   orxFRAME;


/** Setups the frame module
 */
extern orxDLLAPI void orxFASTCALL             orxFrame_Setup();

/** Inits the frame module
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL        orxFrame_Init();

/** Exits from the frame module
 */
extern orxDLLAPI void orxFASTCALL             orxFrame_Exit();


/** Creates a frame
 * @param[in]   _u32Flags     flags for created animation
 * @return      Created orxFRAME / orxNULL
 */
extern orxDLLAPI orxFRAME *orxFASTCALL        orxFrame_Create(orxU32 _u32Flags);

/** Deletes a frame
 * @param[in]   _pstFrame       Frame to delete
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL        orxFrame_Delete(orxFRAME *_pstFrame);


/** Sets a frame parent
 * @param[in]   _pstFrame       Concerned frame
 * @param[in]   _pstParent      Parent frame to set
 */
extern orxDLLAPI void orxFASTCALL             orxFrame_SetParent(orxFRAME *_pstFrame, orxFRAME * _pstParent);

/** Is a root child?
 * @param[in]   _pstFrame       Concerned frame
 * @return orxTRUE if its parent is root, orxFALSE otherwise
 */
extern orxDLLAPI orxBOOL orxFASTCALL          orxFrame_IsRootChild(const orxFRAME *_pstFrame);


/** Is dirty?
 * @param[in]   _pstFrame       Concerned frame
 * @return orxTRUE if dirty, orxFALSE otherwise
 */
extern orxDLLAPI orxBOOL orxFASTCALL          orxFrame_IsDirty(const orxFRAME *_pstFrame);


/** Sets a frame position
 * @param[in]   _pstFrame       Concerned frame
 * @param[in]   _eSpace         Coordinate space system to use
 * @param[in]   _pvPos          Position to set
 */
extern orxDLLAPI void orxFASTCALL             orxFrame_SetPosition(orxFRAME *_pstFrame, orxFRAME_SPACE _eSpace, const orxVECTOR *_pvPos);

/** Sets a frame rotation
 * @param[in]   _pstFrame       Concerned frame
 * @param[in]   _eSpace         Coordinate space system to use
 * @param[in]   _fAngle         Angle to set (radians)
 */
extern orxDLLAPI void orxFASTCALL             orxFrame_SetRotation(orxFRAME *_pstFrame, orxFRAME_SPACE _eSpace, orxFLOAT _fAngle);

/** Sets a frame scale
 * @param[in]   _pstFrame       Concerned frame
 * @param[in]   _eSpace         Coordinate space system to use
 * @param[in]   _pvScale        Scale to set
 */
extern orxDLLAPI void orxFASTCALL             orxFrame_SetScale(orxFRAME *_pstFrame, orxFRAME_SPACE _eSpace, const orxVECTOR *_pvScale);


/** Gets a frame position
 * @param[in]   _pstFrame       Concerned frame
 * @param[in]   _eSpace         Coordinate space system to use
 * @param[out]  _pvPos          Position of the given frame
 * @return orxVECTOR / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL       orxFrame_GetPosition(orxFRAME *_pstFrame, orxFRAME_SPACE _eSpace, orxVECTOR *_pvPos);

/** Gets a frame rotation
 * @param[in]   _pstFrame       Concerned frame
 * @param[in]   _eSpace         Coordinate space system to use
 * @return Rotation of the given frame (radians)
 */
extern orxDLLAPI orxFLOAT orxFASTCALL         orxFrame_GetRotation(orxFRAME *_pstFrame, orxFRAME_SPACE _eSpace);

/** Gets a frame scale
 * @param[in]   _pstFrame       Concerned frame
 * @param[in]   _eSpace         Coordinate space system to use
 * @param[out]  _pvScale        Scale
 * @return      orxVECTOR / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL       orxFrame_GetScale(orxFRAME *_pstFrame, orxFRAME_SPACE _eSpace, orxVECTOR *_pvScale);

#endif /* _orxFRAME_H_ */

/** @} */
