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
 * @file orxMouse.c
 * @date 22/11/2003
 * @author iarwain@orx-project.org
 *
 */


#include "io/orxMouse.h"
#include "plugin/orxPluginCore.h"
#include "debug/orxDebug.h"


/** Misc defines
 */
#define orxMOUSE_KZ_LITERAL_PREFIX            "MOUSE_"


/***************************************************************************
 * Private functions                                                       *
 ***************************************************************************/


/***************************************************************************
 * Public functions                                                        *
 ***************************************************************************/

/** Mouse module setup
 */
void orxFASTCALL orxMouse_Setup()
{
  /* Adds module dependencies */
  orxModule_AddDependency(orxMODULE_ID_MOUSE, orxMODULE_ID_PLUGIN);
  orxModule_AddDependency(orxMODULE_ID_MOUSE, orxMODULE_ID_MEMORY);
  orxModule_AddDependency(orxMODULE_ID_MOUSE, orxMODULE_ID_DISPLAY);
  orxModule_AddDependency(orxMODULE_ID_MOUSE, orxMODULE_ID_CONFIG);

  return;
}

/** Gets button literal name
 * @param[in] _eButton          Concerned button
 * @return Button's name
 */
const orxSTRING orxFASTCALL orxMouse_GetButtonName(orxMOUSE_BUTTON _eButton)
{
  orxSTRING zResult;

#define orxMOUSE_DECLARE_BUTTON_NAME(BUTTON)   case orxMOUSE_BUTTON_##BUTTON: zResult = orxMOUSE_KZ_LITERAL_PREFIX#BUTTON; break

  /* Checks */
  orxASSERT(_eButton < orxMOUSE_BUTTON_NUMBER);

  /* Depending on button */
  switch(_eButton)
  {
    orxMOUSE_DECLARE_BUTTON_NAME(LEFT);
    orxMOUSE_DECLARE_BUTTON_NAME(RIGHT);
    orxMOUSE_DECLARE_BUTTON_NAME(MIDDLE);
    orxMOUSE_DECLARE_BUTTON_NAME(EXTRA_1);
    orxMOUSE_DECLARE_BUTTON_NAME(EXTRA_2);
    orxMOUSE_DECLARE_BUTTON_NAME(WHEEL_UP);
    orxMOUSE_DECLARE_BUTTON_NAME(WHEEL_DOWN);

    default:
    {
      /* Logs message */
      orxDEBUG_PRINT(orxDEBUG_LEVEL_MOUSE, "No name defined for button #%ld.", _eButton);

      /* Updates result */
      zResult = orxSTRING_EMPTY;
    }
  }

  /* Done! */
  return zResult;
}


/***************************************************************************
 * Plugin related                                                          *
 ***************************************************************************/

/* *** Core function definitions *** */

orxPLUGIN_DEFINE_CORE_FUNCTION(orxMouse_Init, orxSTATUS, void);
orxPLUGIN_DEFINE_CORE_FUNCTION(orxMouse_Exit, void, void);
orxPLUGIN_DEFINE_CORE_FUNCTION(orxMouse_SetPosition, orxSTATUS, const orxVECTOR *);
orxPLUGIN_DEFINE_CORE_FUNCTION(orxMouse_GetPosition, orxVECTOR *, orxVECTOR *);
orxPLUGIN_DEFINE_CORE_FUNCTION(orxMouse_IsButtonPressed, orxBOOL, orxMOUSE_BUTTON);
orxPLUGIN_DEFINE_CORE_FUNCTION(orxMouse_GetMoveDelta, orxVECTOR *, orxVECTOR *);
orxPLUGIN_DEFINE_CORE_FUNCTION(orxMouse_GetWheelDelta, orxFLOAT, void);
orxPLUGIN_DEFINE_CORE_FUNCTION(orxMouse_ShowCursor, orxSTATUS, orxBOOL);


/* *** Core function info array *** */

orxPLUGIN_BEGIN_CORE_FUNCTION_ARRAY(MOUSE)

orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(MOUSE, INIT, orxMouse_Init)
orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(MOUSE, EXIT, orxMouse_Exit)
orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(MOUSE, SET_POSITION, orxMouse_SetPosition)
orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(MOUSE, GET_POSITION, orxMouse_GetPosition)
orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(MOUSE, IS_BUTTON_PRESSED, orxMouse_IsButtonPressed)
orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(MOUSE, GET_MOVE_DELTA, orxMouse_GetMoveDelta)
orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(MOUSE, GET_WHEEL_DELTA, orxMouse_GetWheelDelta)
orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(MOUSE, SHOW_CURSOR, orxMouse_ShowCursor)

orxPLUGIN_END_CORE_FUNCTION_ARRAY(MOUSE)


/* *** Core function implementations *** */

/** Inits the mouse module
 * @return Returns the status of the operation
 */
orxSTATUS orxFASTCALL orxMouse_Init()
{
  return orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxMouse_Init)();
}

/** Exits from the mouse module
 */
void orxFASTCALL orxMouse_Exit()
{
  orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxMouse_Exit)();
}

/** Sets mouse position
* @param[in] _pvPosition  Mouse position
* @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
*/
orxSTATUS orxFASTCALL orxMouse_SetPosition(const orxVECTOR *_pvPosition)
{
  return orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxMouse_SetPosition)(_pvPosition);
}

/** Gets mouse on screen position
 * @param[out] _pvPosition  Mouse position
 * @return orxVECTOR / orxNULL
 */
orxVECTOR *orxFASTCALL orxMouse_GetPosition(orxVECTOR *_pvPosition)
{
  return orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxMouse_GetPosition)(_pvPosition);
}

/** Is mouse button pressed?
 * @param[in] _eButton          Mouse button to check
 * @return orxTRUE if presse / orxFALSE otherwise
 */
orxBOOL orxFASTCALL orxMouse_IsButtonPressed(orxMOUSE_BUTTON _eButton)
{
  return orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxMouse_IsButtonPressed)(_eButton);
}

/** Gets mouse move delta (since last call)
 * @param[out] _pvMoveDelta Mouse move delta
 * @return orxVECTOR / orxNULL
 */
orxVECTOR *orxFASTCALL orxMouse_GetMoveDelta(orxVECTOR *_pvMoveDelta)
{
  return orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxMouse_GetMoveDelta)(_pvMoveDelta);
}

/** Gets mouse wheel delta (since last call)
 * @return Mouse wheel delta
 */
orxFLOAT orxFASTCALL orxMouse_GetWheelDelta()
{
  return orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxMouse_GetWheelDelta)();
}

/** Shows mouse cursor
* @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
*/
orxSTATUS orxFASTCALL orxMouse_ShowCursor(orxBOOL _bShow)
{
  return orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxMouse_ShowCursor)(_bShow);
}
