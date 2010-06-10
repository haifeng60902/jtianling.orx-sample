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
 * @file orxKeyboard.c
 * @date 22/11/2003
 * @author iarwain@orx-project.org
 *
 */


#include "io/orxKeyboard.h"
#include "plugin/orxPluginCore.h"
#include "debug/orxDebug.h"


/** Misc defines
 */
#define orxKEYBOARD_KZ_LITERAL_PREFIX           "KEY_"


/***************************************************************************
 * Private functions                                                       *
 ***************************************************************************/


/***************************************************************************
 * Public functions                                                        *
 ***************************************************************************/

/** Keyboard module setup
 */
void orxFASTCALL orxKeyboard_Setup()
{
  /* Adds module dependencies */
  orxModule_AddDependency(orxMODULE_ID_KEYBOARD, orxMODULE_ID_PLUGIN);
  orxModule_AddDependency(orxMODULE_ID_KEYBOARD, orxMODULE_ID_MEMORY);
  orxModule_AddDependency(orxMODULE_ID_KEYBOARD, orxMODULE_ID_BANK);
  orxModule_AddDependency(orxMODULE_ID_KEYBOARD, orxMODULE_ID_DISPLAY);

  return;
}

/** Gets key literal name
 * @param[in] _eKey       Concerned key
 * @return Key's name
 */
const orxSTRING orxFASTCALL orxKeyboard_GetKeyName(orxKEYBOARD_KEY _eKey)
{
  orxSTRING zResult;

#define orxKEYBOARD_DECLARE_KEY_NAME(KEY)   case orxKEYBOARD_KEY_##KEY: zResult = orxKEYBOARD_KZ_LITERAL_PREFIX#KEY; break

  /* Checks */
  orxASSERT(_eKey < orxKEYBOARD_KEY_NUMBER);

  /* Depending on key */
  switch(_eKey)
  {
    orxKEYBOARD_DECLARE_KEY_NAME(A);
    orxKEYBOARD_DECLARE_KEY_NAME(B);
    orxKEYBOARD_DECLARE_KEY_NAME(C);
    orxKEYBOARD_DECLARE_KEY_NAME(D);
    orxKEYBOARD_DECLARE_KEY_NAME(E);
    orxKEYBOARD_DECLARE_KEY_NAME(F);
    orxKEYBOARD_DECLARE_KEY_NAME(G);
    orxKEYBOARD_DECLARE_KEY_NAME(H);
    orxKEYBOARD_DECLARE_KEY_NAME(I);
    orxKEYBOARD_DECLARE_KEY_NAME(J);
    orxKEYBOARD_DECLARE_KEY_NAME(K);
    orxKEYBOARD_DECLARE_KEY_NAME(L);
    orxKEYBOARD_DECLARE_KEY_NAME(M);
    orxKEYBOARD_DECLARE_KEY_NAME(N);
    orxKEYBOARD_DECLARE_KEY_NAME(O);
    orxKEYBOARD_DECLARE_KEY_NAME(P);
    orxKEYBOARD_DECLARE_KEY_NAME(Q);
    orxKEYBOARD_DECLARE_KEY_NAME(R);
    orxKEYBOARD_DECLARE_KEY_NAME(S);
    orxKEYBOARD_DECLARE_KEY_NAME(T);
    orxKEYBOARD_DECLARE_KEY_NAME(U);
    orxKEYBOARD_DECLARE_KEY_NAME(V);
    orxKEYBOARD_DECLARE_KEY_NAME(W);
    orxKEYBOARD_DECLARE_KEY_NAME(X);
    orxKEYBOARD_DECLARE_KEY_NAME(Y);
    orxKEYBOARD_DECLARE_KEY_NAME(Z);
    orxKEYBOARD_DECLARE_KEY_NAME(0);
    orxKEYBOARD_DECLARE_KEY_NAME(1);
    orxKEYBOARD_DECLARE_KEY_NAME(2);
    orxKEYBOARD_DECLARE_KEY_NAME(3);
    orxKEYBOARD_DECLARE_KEY_NAME(4);
    orxKEYBOARD_DECLARE_KEY_NAME(5);
    orxKEYBOARD_DECLARE_KEY_NAME(6);
    orxKEYBOARD_DECLARE_KEY_NAME(7);
    orxKEYBOARD_DECLARE_KEY_NAME(8);
    orxKEYBOARD_DECLARE_KEY_NAME(9);
    orxKEYBOARD_DECLARE_KEY_NAME(NUMPAD0);
    orxKEYBOARD_DECLARE_KEY_NAME(NUMPAD1);
    orxKEYBOARD_DECLARE_KEY_NAME(NUMPAD2);
    orxKEYBOARD_DECLARE_KEY_NAME(NUMPAD3);
    orxKEYBOARD_DECLARE_KEY_NAME(NUMPAD4);
    orxKEYBOARD_DECLARE_KEY_NAME(NUMPAD5);
    orxKEYBOARD_DECLARE_KEY_NAME(NUMPAD6);
    orxKEYBOARD_DECLARE_KEY_NAME(NUMPAD7);
    orxKEYBOARD_DECLARE_KEY_NAME(NUMPAD8);
    orxKEYBOARD_DECLARE_KEY_NAME(NUMPAD9);
    orxKEYBOARD_DECLARE_KEY_NAME(F1);
    orxKEYBOARD_DECLARE_KEY_NAME(F2);
    orxKEYBOARD_DECLARE_KEY_NAME(F3);
    orxKEYBOARD_DECLARE_KEY_NAME(F4);
    orxKEYBOARD_DECLARE_KEY_NAME(F5);
    orxKEYBOARD_DECLARE_KEY_NAME(F6);
    orxKEYBOARD_DECLARE_KEY_NAME(F7);
    orxKEYBOARD_DECLARE_KEY_NAME(F8);
    orxKEYBOARD_DECLARE_KEY_NAME(F9);
    orxKEYBOARD_DECLARE_KEY_NAME(F10);
    orxKEYBOARD_DECLARE_KEY_NAME(F11);
    orxKEYBOARD_DECLARE_KEY_NAME(F12);
    orxKEYBOARD_DECLARE_KEY_NAME(F13);
    orxKEYBOARD_DECLARE_KEY_NAME(F14);
    orxKEYBOARD_DECLARE_KEY_NAME(F15);
    orxKEYBOARD_DECLARE_KEY_NAME(UP);
    orxKEYBOARD_DECLARE_KEY_NAME(RIGHT);
    orxKEYBOARD_DECLARE_KEY_NAME(DOWN);
    orxKEYBOARD_DECLARE_KEY_NAME(LEFT);
    orxKEYBOARD_DECLARE_KEY_NAME(ESCAPE);
    orxKEYBOARD_DECLARE_KEY_NAME(SPACE);
    orxKEYBOARD_DECLARE_KEY_NAME(RETURN);
    orxKEYBOARD_DECLARE_KEY_NAME(BACKSPACE);
    orxKEYBOARD_DECLARE_KEY_NAME(TAB);
    orxKEYBOARD_DECLARE_KEY_NAME(PAGEUP);
    orxKEYBOARD_DECLARE_KEY_NAME(PAGEDOWN);
    orxKEYBOARD_DECLARE_KEY_NAME(END);
    orxKEYBOARD_DECLARE_KEY_NAME(HOME);
    orxKEYBOARD_DECLARE_KEY_NAME(INSERT);
    orxKEYBOARD_DECLARE_KEY_NAME(DELETE);
    orxKEYBOARD_DECLARE_KEY_NAME(ADD);
    orxKEYBOARD_DECLARE_KEY_NAME(SUBTRACT);
    orxKEYBOARD_DECLARE_KEY_NAME(MULTIPLY);
    orxKEYBOARD_DECLARE_KEY_NAME(DIVIDE);
    orxKEYBOARD_DECLARE_KEY_NAME(PAUSE);
    orxKEYBOARD_DECLARE_KEY_NAME(RALT);
    orxKEYBOARD_DECLARE_KEY_NAME(RCTRL);
    orxKEYBOARD_DECLARE_KEY_NAME(RSHIFT);
    orxKEYBOARD_DECLARE_KEY_NAME(RSYSTEM);
    orxKEYBOARD_DECLARE_KEY_NAME(LALT);
    orxKEYBOARD_DECLARE_KEY_NAME(LCTRL);
    orxKEYBOARD_DECLARE_KEY_NAME(LSHIFT);
    orxKEYBOARD_DECLARE_KEY_NAME(LSYSTEM);
    orxKEYBOARD_DECLARE_KEY_NAME(MENU);
    orxKEYBOARD_DECLARE_KEY_NAME(LBRACKET);
    orxKEYBOARD_DECLARE_KEY_NAME(RBRACKET);
    orxKEYBOARD_DECLARE_KEY_NAME(SEMICOLON);
    orxKEYBOARD_DECLARE_KEY_NAME(COMMA);
    orxKEYBOARD_DECLARE_KEY_NAME(PERIOD);
    orxKEYBOARD_DECLARE_KEY_NAME(QUOTE);
    orxKEYBOARD_DECLARE_KEY_NAME(SLASH);
    orxKEYBOARD_DECLARE_KEY_NAME(BACKSLASH);
    orxKEYBOARD_DECLARE_KEY_NAME(TILDE);
    orxKEYBOARD_DECLARE_KEY_NAME(EQUAL);
    orxKEYBOARD_DECLARE_KEY_NAME(DASH);

    default:
    {
      /* Logs message */
      orxDEBUG_PRINT(orxDEBUG_LEVEL_KEYBOARD, "No name defined for key #%ld.", _eKey);

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

orxPLUGIN_DEFINE_CORE_FUNCTION(orxKeyboard_Init, orxSTATUS, void);
orxPLUGIN_DEFINE_CORE_FUNCTION(orxKeyboard_Exit, void, void);
orxPLUGIN_DEFINE_CORE_FUNCTION(orxKeyboard_IsKeyPressed, orxBOOL, orxKEYBOARD_KEY);
orxPLUGIN_DEFINE_CORE_FUNCTION(orxKeyboard_Hit, orxBOOL, void);
orxPLUGIN_DEFINE_CORE_FUNCTION(orxKeyboard_Read, orxKEYBOARD_KEY, void);
orxPLUGIN_DEFINE_CORE_FUNCTION(orxKeyboard_ClearBuffer, void, void);


/* *** Core function info array *** */

orxPLUGIN_BEGIN_CORE_FUNCTION_ARRAY(KEYBOARD)

orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(KEYBOARD, INIT, orxKeyboard_Init)
orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(KEYBOARD, EXIT, orxKeyboard_Exit)
orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(KEYBOARD, IS_KEY_PRESSED, orxKeyboard_IsKeyPressed)
orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(KEYBOARD, HIT, orxKeyboard_Hit)
orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(KEYBOARD, READ, orxKeyboard_Read)
orxPLUGIN_ADD_CORE_FUNCTION_ARRAY(KEYBOARD, CLEAR_BUFFER, orxKeyboard_ClearBuffer)

orxPLUGIN_END_CORE_FUNCTION_ARRAY(KEYBOARD)


/* *** Core function implementations *** */

/** Inits the keyboard module
 */
orxSTATUS orxFASTCALL orxKeyboard_Init()
{
  return orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxKeyboard_Init)();
}

/** Exits from the keyboard module
 */
void orxFASTCALL orxKeyboard_Exit()
{
  orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxKeyboard_Exit)();
}

/** Is key pressed?
 * @param[in] _eKey       Key to check
 * @return orxTRUE if presse / orxFALSE otherwise
 */
orxBOOL orxFASTCALL orxKeyboard_IsKeyPressed(orxKEYBOARD_KEY _eKey)
{
  return orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxKeyboard_IsKeyPressed)(_eKey);
}

/** Returns orxTRUE if there are keypresses waiting in the input buffer.
 * @return orxTRUE if keys have been pressed, else orxFALSE
 */
orxBOOL orxFASTCALL orxKeyboard_Hit()
{
  return orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxKeyboard_Hit)();
}

/** Returns the next character from the keyboard buffer, in ASCII format.
 * If the buffer is empty, it waits until a key is pressed.
 * The low byte of the return value contains the ASCII code of the key,
 * and the high byte the scancode.
 * @return Ascii and scancode value
 */
orxKEYBOARD_KEY orxFASTCALL orxKeyboard_Read()
{
  return orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxKeyboard_Read)();
}

/**  Empties the keyboard buffer.
 */
void orxFASTCALL orxKeyboard_ClearBuffer()
{
  orxPLUGIN_CORE_FUNCTION_POINTER_NAME(orxKeyboard_ClearBuffer)();
}
