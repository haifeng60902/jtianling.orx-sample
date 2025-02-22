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
 * @file orxObject.h
 * @date 01/12/2003
 * @author iarwain@orx-project.org
 *
 * @todo
 */

/**
 * @addtogroup orxObject
 *
 * Object module
 * Allows to creates and handle objects
 * Objects are structures containers that can refer to many other structures such as frames, graphics, etc...
 *
 * @{
 */


#ifndef _orxOBJECT_H_
#define _orxOBJECT_H_


#include "orxInclude.h"

#include "object/orxStructure.h"
#include "core/orxClock.h"
#include "memory/orxBank.h"
#include "anim/orxAnimSet.h"
#include "display/orxDisplay.h"
#include "math/orxOBox.h"
#include "sound/orxSound.h"


/** Defines */
#define orxOBJECT_GET_STRUCTURE(OBJECT, TYPE) orx##TYPE(_orxObject_GetStructure(OBJECT, orxSTRUCTURE_ID_##TYPE))


/** Event enum
 */
typedef enum __orxOBJECT_EVENT_t
{
  orxOBJECT_EVENT_CREATE = 0,
  orxOBJECT_EVENT_DELETE,

  orxOBJECT_EVENT_NUMBER,

  orxOBJECT_EVENT_NONE = orxENUM_NONE

} orxOBJECT_EVENT;


/** Internal object structure */
typedef struct __orxOBJECT_t                orxOBJECT;


/** Object module setup
 */
extern orxDLLAPI void orxFASTCALL           orxObject_Setup();

/** Inits the object module
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_Init();

/** Exits from the object module
 */
extern orxDLLAPI void orxFASTCALL           orxObject_Exit();

/** Creates an empty object
 * @return orxOBJECT / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_Create();

/** Creates an object from config
 * @param[in]   _zConfigID    Config ID
 * @ return orxOBJECT / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_CreateFromConfig(const orxSTRING _zConfigID);

/** Deletes an object
 * @param[in] _pstObject        Concerned object
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_Delete(orxOBJECT *_pstObject);

/** Enables/disables an object
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _bEnable      Enable / disable
 */
extern orxDLLAPI void orxFASTCALL           orxObject_Enable(orxOBJECT *_pstObject, orxBOOL _bEnable);

/** Is object enabled?
 * @param[in]   _pstObject    Concerned object
 * @return      orxTRUE if enabled, orxFALSE otherwise
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_IsEnabled(const orxOBJECT *_pstObject);

/** Pauses/unpauses an object
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _bPause       Pause / unpause
 */
extern orxDLLAPI void orxFASTCALL           orxObject_Pause(orxOBJECT *_pstObject, orxBOOL _bPause);

/** Is object paused?
 * @param[in]   _pstObject    Concerned object
 * @return      orxTRUE if paused, orxFALSE otherwise
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_IsPaused(const orxOBJECT *_pstObject);


/** Sets render status of an object
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _bRendered    Rendered or not this frame
 */
extern orxDLLAPI void orxFASTCALL           orxObject_SetRendered(orxOBJECT *_pstObject, orxBOOL _bRendered);

/** Is object rendered this frame?
 * @param[in]   _pstObject    Concerned object
 * @return      orxTRUE if rendered, orxFALSE otherwise
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_IsRendered(const orxOBJECT *_pstObject);


/** Sets user data for an object
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _pUserData    User data to store / orxNULL
 */
extern orxDLLAPI void orxFASTCALL           orxObject_SetUserData(orxOBJECT *_pstObject, void *_pUserData);

/** Gets object's user data
 * @param[in]   _pstObject    Concerned object
 * @return      Stored user data / orxNULL
 */
extern orxDLLAPI void *orxFASTCALL          orxObject_GetUserData(const orxOBJECT *_pstObject);

/** Sets owner for an object
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _pOwner       Owner to set / orxNULL
 */
extern orxDLLAPI void orxFASTCALL           orxObject_SetOwner(orxOBJECT *_pstObject, void *_pOwner);

/** Gets object's owner
 * @param[in]   _pstObject    Concerned object
 * @return      Owner / orxNULL
 */
extern orxDLLAPI orxSTRUCTURE *orxFASTCALL  orxObject_GetOwner(const orxOBJECT *_pstObject);


/** Gets object's first child (only if created with a config ChildList)
 * @param[in]   _pstObject    Concerned object
 * @return      First child object / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_GetChild(const orxOBJECT *_pstObject);

/** Gets object's next sibling (only if created with a config ChildList)
 * @param[in]   _pstObject    Concerned object
 * @return      Next sibling object / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_GetSibling(const orxOBJECT *_pstObject);


/** Sets associated clock for an object
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _pstClock     Clock to associate / orxNULL
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetClock(orxOBJECT *_pstObject, orxCLOCK *_pstClock);

/** Gets object's clock
 * @param[in]   _pstObject    Concerned object
 * @return      Associated clock / orxNULL
 */
extern orxDLLAPI orxCLOCK *orxFASTCALL      orxObject_GetClock(const orxOBJECT *_pstObject);


/** Links a structure to an object
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pstStructure   Structure to link
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_LinkStructure(orxOBJECT *_pstObject, orxSTRUCTURE *_pstStructure);

/** Unlinks structure from an object, given its structure ID
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _eStructureID   ID of structure to unlink
 */
extern orxDLLAPI void orxFASTCALL           orxObject_UnlinkStructure(orxOBJECT *_pstObject, orxSTRUCTURE_ID _eStructureID);


/* *** Object accessors *** */


/** Structure used by an object get accessor, given its structure ID. Structure must then be cast correctly (see helper macro)
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _eStructureID   ID of the structure to get
 * @return orxSTRUCTURE / orxNULL
 */
extern orxDLLAPI orxSTRUCTURE *orxFASTCALL  _orxObject_GetStructure(const orxOBJECT *_pstObject, orxSTRUCTURE_ID _eStructureID);


/** Sets object flipping
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _bFlipX         Flip it on X axis
 * @param[in]   _bFlipY         Flip it on Y axis
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetFlip(orxOBJECT *_pstObject, orxBOOL _bFlipX, orxBOOL _bFlipY);

/** Gets object flipping
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pbFlipX        X axis flipping
 * @param[in]   _pbFlipY        Y axis flipping
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_GetFlip(const orxOBJECT *_pstObject, orxBOOL *_pbFlipX, orxBOOL *_pbFlipY);


/** Sets object pivot
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvPivot        Object pivot
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetPivot(orxOBJECT *_pstObject, const orxVECTOR *_pvPivot);

/** Sets object position
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvPosition     Object position
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetPosition(orxOBJECT *_pstObject, const orxVECTOR *_pvPosition);

/** Sets object rotation
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fRotation      Object rotation (radians)
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetRotation(orxOBJECT *_pstObject, orxFLOAT _fRotation);

/** Sets object scale
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvScale        Object scale vector
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetScale(orxOBJECT *_pstObject, const orxVECTOR *_pvScale);

/** Get object pivot
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvPivot        Object pivot
 * @return      orxVECTOR / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetPivot(const orxOBJECT *_pstObject, orxVECTOR *_pvPivot);

/** Get object origin
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvOrigin       Object origin
 * @return      orxVECTOR / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetOrigin(const orxOBJECT *_pstObject, orxVECTOR *_pvOrigin);

/** Get object position
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvPosition     Object position
 * @return      orxVECTOR / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetPosition(const orxOBJECT *_pstObject, orxVECTOR *_pvPosition);

/** Get object world position
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvPosition     Object world position
 * @return      orxVECTOR / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetWorldPosition(const orxOBJECT *_pstObject, orxVECTOR *_pvPosition);

/** Get object rotation
 * @param[in]   _pstObject      Concerned object
 * @return      orxFLOAT (radians)
 */
extern orxDLLAPI orxFLOAT orxFASTCALL       orxObject_GetRotation(const orxOBJECT *_pstObject);

/** Get object world rotation
 * @param[in]   _pstObject      Concerned object
 * @return      orxFLOAT (radians)
 */
extern orxDLLAPI orxFLOAT orxFASTCALL       orxObject_GetWorldRotation(const orxOBJECT *_pstObject);

/** Get object scale
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvScale        Object scale vector
 * @return      Scale vector
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetScale(const orxOBJECT *_pstObject, orxVECTOR *_pvScale);

/** Gets object world scale
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvScale        Object world scale
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetWorldScale(const orxOBJECT *_pstObject, orxVECTOR *_pvScale);


/** Sets an object parent
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pParent        Parent structure to set (object, spawner, camera or frame) / orxNULL
 * @return      orsSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetParent(orxOBJECT *_pstObject, void *_pParent);


/** Gets object size
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvSize         Object's size
 * @return      orxVECTOR / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetSize(const orxOBJECT *_pstObject, orxVECTOR *_pvSize);


/** Sets an object animset
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pstAnimSet     Animation set to set / orxNULL
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetAnimSet(orxOBJECT *_pstObject, orxANIMSET *_pstAnimSet);


/** Sets an object animation frequency
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fFrequency     Frequency to set
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetAnimFrequency(orxOBJECT *_pstObject, orxFLOAT _fFrequency);

/** Sets current animation for object
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zAnimName      Animation name (config's one) to set / orxNULL
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetCurrentAnim(orxOBJECT *_pstObject, const orxSTRING _zAnimName);

/** Sets target animation for object
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zAnimName      Animation name (config's one) to set / orxNULL
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetTargetAnim(orxOBJECT *_pstObject, const orxSTRING _zAnimName);

/** Is current animation test
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zAnimName      Animation name (config's one) to test
 * @return      orxTRUE / orxFALSE
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_IsCurrentAnim(const orxOBJECT *_pstObject, const orxSTRING _zAnimName);

/** Is target animation test
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zAnimName      Animation name (config's one) to test
 * @return      orxTRUE / orxFALSE
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_IsTargetAnim(const orxOBJECT *_pstObject, const orxSTRING _zAnimName);


/** Gets object's bounding box (OBB)
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pstBoundingBox Bounding box result
 * @return      Bounding box / orxNULL
 */
extern orxDLLAPI orxOBOX *orxFASTCALL       orxObject_GetBoundingBox(const orxOBJECT *_pstObject, orxOBOX *_pstBoundingBox);


/** Sets an object speed
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvSpeed        Speed to set
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetSpeed(orxOBJECT *_pstObject, const orxVECTOR *_pvSpeed);

/** Sets an object speed relative to its rotation/scale
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvRelativeSpeed Relative speed to set
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetRelativeSpeed(orxOBJECT *_pstObject, const orxVECTOR *_pvRelativeSpeed);

/** Sets an object angular velocity
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fVelocity      Angular velocity to set (radians/seconds)
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetAngularVelocity(orxOBJECT *_pstObject, orxFLOAT _fVelocity);

/** Sets an object custom gravity
 * @param[in]   _pstObject        Concerned object
 * @param[in]   _pvCustomGravity  Custom gravity to set / orxNULL to remove it
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetCustomGravity(orxOBJECT *_pstObject, const orxVECTOR *_pvCustomGravity);

/** Gets an object speed
 * @param[in]   _pstObject      Concerned object
 * @param[out]   _pvSpeed       Speed to get
 * @return      Object speed / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetSpeed(const orxOBJECT *_pstObject, orxVECTOR *_pvSpeed);

/** Gets an object relative speed
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvRelativeSpeed Relative speed to get
 * @return      Object relative speed / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetRelativeSpeed(const orxOBJECT *_pstObject, orxVECTOR *_pvRelativeSpeed);

/** Gets an object angular velocity
 * @param[in]   _pstObject      Concerned object
 * @return      Object angular velocity (radians/seconds)
 */
extern orxDLLAPI orxFLOAT orxFASTCALL       orxObject_GetAngularVelocity(const orxOBJECT *_pstObject);

/** Gets an object custom gravity
 * @param[in]   _pstObject        Concerned object
 * @param[out]  _pvCustomGravity  Custom gravity to get
 * @return      Object custom gravity / orxNULL is object doesn't have any
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetCustomGravity(const orxOBJECT *_pstObject, orxVECTOR *_pvCustomGravity);

/** Gets an object center of mass
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvMassCenter   Mass center to get
 * @return      Mass center / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetMassCenter(const orxOBJECT *_pstObject, orxVECTOR *_pvMassCenter);


/** Sets object text string, if object is associated to a text
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zString        String to set
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetTextString(orxOBJECT *_pstObject, const orxSTRING _zString);


/** Applies a torque
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fTorque        Torque to apply
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_ApplyTorque(orxOBJECT *_pstObject, orxFLOAT _fTorque);

/** Applies a force
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvForce        Force to apply
 * @param[in]   _pvPoint        Point (world coordinates) where the force will be applied, if orxNULL, center of mass will be used
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_ApplyForce(orxOBJECT *_pstObject, const orxVECTOR *_pvForce, const orxVECTOR *_pvPoint);

/** Applies an impulse
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvImpulse      Impulse to apply
 * @param[in]   _pvPoint        Point (world coordinates) where the impulse will be applied, if orxNULL, center of mass will be used
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_ApplyImpulse(orxOBJECT *_pstObject, const orxVECTOR *_pvImpulse, const orxVECTOR *_pvPoint);


/** Issues a raycast to test for potential objects in the way
 * @param[in]   _pvStart        Start of raycast
 * @param[in]   _pvEnd          End of raycast
 * @param[in]   _u16SelfFlags   Selfs flags used for filtering (0xFFFF for no filtering)
 * @param[in]   _u16CheckMask   Check mask used for filtering (0xFFFF for no filtering)
 * @param[in]   _pvContact      If non-null and a contact is found it will be stored here
 * @param[in]   _pvNormal       If non-null and a contact is found, its normal will be stored here
 * @return Colliding orxOBJECT / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_Raycast(const orxVECTOR *_pvStart, const orxVECTOR *_pvEnd, orxU16 _u16SelfFlags, orxU16 _u16CheckMask, orxVECTOR *_pvContact, orxVECTOR *_pvNormal);


/** Sets object color
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pstColor       Color to set, orxNULL to remove any specifig color
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetColor(orxOBJECT *_pstObject, const orxCOLOR *_pstColor);

/** Clears object color
 * @param[in]   _pstObject      Concerned object
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_ClearColor(orxOBJECT *_pstObject);

/** Object has color accessor
 * @param[in]   _pstObject      Concerned object
 * @return      orxTRUE / orxFALSE
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_HasColor(const orxOBJECT *_pstObject);

/** Gets object color
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pstColor       Object's color
 * @return      orxCOLOR / orxNULL
 */
extern orxDLLAPI orxCOLOR *orxFASTCALL      orxObject_GetColor(const orxOBJECT *_pstObject, orxCOLOR *_pstColor);


/** Adds an FX using its config ID
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zFXConfigID    Config ID of the FX to add
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddFX(orxOBJECT *_pstObject, const orxSTRING _zFXConfigID);

/** Adds a unique FX using its config ID
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zFXConfigID    Config ID of the FX to add
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddUniqueFX(orxOBJECT *_pstObject, const orxSTRING _zFXConfigID);

/** Adds a delayed FX using its config ID
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zFXConfigID    Config ID of the FX to add
 * @param[in]   _fDelay         Delay time
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddDelayedFX(orxOBJECT *_pstObject, const orxSTRING _zFXConfigID, orxFLOAT _fDelay);

/** Adds a unique delayed FX using its config ID
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zFXConfigID    Config ID of the FX to add
 * @param[in]   _fDelay         Delay time
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddUniqueDelayedFX(orxOBJECT *_pstObject, const orxSTRING _zFXConfigID, orxFLOAT _fDelay);

/** Removes an FX using using its config ID
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zFXConfigID    Config ID of the FX to remove
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_RemoveFX(orxOBJECT *_pstObject, const orxSTRING _zFXConfigID);


/** Adds a sound using its config ID
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zSoundConfigID Config ID of the sound to add
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddSound(orxOBJECT *_pstObject, const orxSTRING _zSoundConfigID);

/** Removes a sound using using its config ID
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zSoundConfigID Config ID of the sound to remove
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_RemoveSound(orxOBJECT *_pstObject, const orxSTRING _zSoundConfigID);

/** Gets last added sound (Do *NOT* destroy it directly before removing it!!!)
 * @param[in]   _pstObject      Concerned object
 * @return      orxSOUND / orxNULL
 */
extern orxDLLAPI orxSOUND *orxFASTCALL      orxObject_GetLastAddedSound(const orxOBJECT *_pstObject);


/** Adds a shader to an object using its config ID
 * @param[in]   _pstObject        Concerned object
 * @param[in]   _zShaderConfigID  Config ID of the shader to add
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddShader(orxOBJECT *_pstObject, const orxSTRING _zShaderConfigID);

/** Removes a shader using using its config ID
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zShaderConfigID Config ID of the shader to remove
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_RemoveShader(orxOBJECT *_pstObject, const orxSTRING _zShaderConfigID);

/** Enables an object's shader
 * @param[in]   _pstObject        Concerned object
 * @param[in]   _bEnable          Enable / disable
 */
extern orxDLLAPI void orxFASTCALL           orxObject_EnableShader(orxOBJECT *_pstObject, orxBOOL _bEnable);

/** Is an object's shader enabled?
 * @param[in]   _pstObject        Concerned object
 * @return      orxTRUE if enabled, orxFALSE otherwise
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_IsShaderEnabled(const orxOBJECT *_pstObject);


/** Gets object config name
 * @param[in]   _pstObject      Concerned object
 * @return      orxSTRING / orxSTRING_EMPTY
 */
extern orxDLLAPI const orxSTRING orxFASTCALL orxObject_GetName(const orxOBJECT *_pstObject);


/** Creates a list of object at neighboring of the given box (ie. whose bounding volume intersects this box)
 * @param[in]   _pstCheckBox    Box to check intersection with
 * @return      orxBANK / orxNULL
 */
extern orxDLLAPI orxBANK *orxFASTCALL       orxObject_CreateNeighborList(const orxOBOX *_pstCheckBox);

/** Deletes an object list created with orxObject_CreateNeighborList
 * @param[in]   _pstObjectList  Concerned object list
 */
extern orxDLLAPI void orxFASTCALL           orxObject_DeleteNeighborList(orxBANK *_pstObjectList);


/** Sets object smoothing
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _eSmoothing     Smoothing type (enabled, default or none)
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetSmoothing(orxOBJECT *_pstObject, orxDISPLAY_SMOOTHING _eSmoothing);

/** Gets object smoothing
 * @param[in]   _pstObject     Concerned object
 * @return Smoothing type (enabled, default or none)
 */
extern orxDLLAPI orxDISPLAY_SMOOTHING orxFASTCALL orxObject_GetSmoothing(const orxOBJECT *_pstObject);


/** Sets object repeat (wrap) values
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fRepeatX       X-axis repeat value
 * @param[in]   _fRepeatY       Y-axis repeat value
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetRepeat(orxOBJECT *_pstObject, orxFLOAT _fRepeatX, orxFLOAT _fRepeatY);

/** Gets object repeat (wrap) values
 * @param[in]   _pstObject     Concerned object
 * @param[out]  _pfRepeatX      X-axis repeat value
 * @param[out]  _pfRepeatY      Y-axis repeat value
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_GetRepeat(const orxOBJECT *_pstObject, orxFLOAT *_pfRepeatX, orxFLOAT *_pfRepeatY);


/** Sets object blend mode
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _eBlendMode     Blend mode (alpha, multiply, add or none)
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetBlendMode(orxOBJECT *_pstObject, orxDISPLAY_BLEND_MODE _eBlendMode);

/** Gets object blend mode
 * @param[in]   _pstObject     Concerned object
 * @return Blend mode (alpha, multiply, add or none)
 */
extern orxDLLAPI orxDISPLAY_BLEND_MODE orxFASTCALL orxObject_GetBlendMode(const orxOBJECT *_pstObject);


/** Sets object lifetime
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fLifeTime      Lifetime to set, negative value to disable it
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetLifeTime(orxOBJECT *_pstObject, orxFLOAT _fLifeTime);

/** Gets object lifetime
 * @param[in]   _pstObject      Concerned object
 * @return      Lifetime / negative value if none
 */
extern orxDLLAPI orxFLOAT orxFASTCALL       orxObject_GetLifeTime(const orxOBJECT *_pstObject);


/** Picks the first active object with graphic "under" the given position
 * @param[in]   _pvPosition     Position to pick from
 * @return      orxOBJECT / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_Pick(const orxVECTOR *_pvPosition);

#endif /* _orxOBJECT_H_ */

/** @} */
