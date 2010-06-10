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
 * @file orxScreenshot.c
 * @date 07/12/2003
 * @author iarwain@orx-project.org
 *
 */


#include "utils/orxScreenshot.h"

#include "debug/orxDebug.h"
#include "core/orxConfig.h"
#include "display/orxDisplay.h"
#include "io/orxFile.h"
#include "io/orxFileSystem.h"
#include "utils/orxString.h"
#include "memory/orxMemory.h"


/** Module flags
 */
#define orxSCREENSHOT_KU32_STATIC_FLAG_NONE                     0x00000000

#define orxSCREENSHOT_KU32_STATIC_FLAG_READY                    0x00000001

#define orxSCREENSHOT_KU32_STATIC_MASK_ALL                      0xFFFFFFFF


/** Misc defines
 */
#define orxSCREENSHOT_KU32_BUFFER_SIZE                          256

#define orxSCREENSHOT_KZ_CONFIG_SECTION                         "Screenshot"
#define orxSCREENSHOT_KZ_CONFIG_DIRECTORY                       "Directory"
#define orxSCREENSHOT_KZ_CONFIG_BASE_NAME                       "BaseName"
#define orxSCREENSHOT_KZ_CONFIG_EXTENSION                       "Extension"
#define orxSCREENSHOT_KZ_CONFIG_DIGITS                          "Digits"


/***************************************************************************
 * Structure declaration                                                   *
 ***************************************************************************/

/** Static structure
 */
typedef struct __orxSCREENSHOT_STATIC_t
{
  orxU32    u32ScreenshotIndex;                                 /**< Screenshot index */
  orxU32    u32Flags;                                           /**< Control flags */
  orxCHAR   acScreenshotBuffer[orxSCREENSHOT_KU32_BUFFER_SIZE]; /**< Screenshot file name buffer */

} orxSCREENSHOT_STATIC;


/***************************************************************************
 * Static variables                                                        *
 ***************************************************************************/

/** Static data
 */
static orxSCREENSHOT_STATIC sstScreenshot;


/***************************************************************************
 * Private functions                                                       *
 ***************************************************************************/

/** Computes next screenshot index
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
static orxINLINE orxSTATUS orxScreenshot_ComputeIndex()
{
  orxSTRING zDirectory, zBaseName, zExtension;
  orxU32    u32Digits;
  orxSTATUS eResult = orxSTATUS_SUCCESS;

  /* Checks */
  orxASSERT(sstScreenshot.u32Flags & orxSCREENSHOT_KU32_STATIC_FLAG_READY)

  /* Uses default directory, base name, extension & digits */
  zDirectory  = orxSCREENSHOT_KZ_DEFAULT_DIRECTORY_NAME;
  zBaseName   = orxSCREENSHOT_KZ_DEFAULT_BASE_NAME;
  zExtension  = orxSCREENSHOT_KZ_DEFAULT_EXTENSION;
  u32Digits   = orxSCREENSHOT_KU32_DEFAULT_DIGITS;

  /* Pushes section */
  if((orxConfig_HasSection(orxSCREENSHOT_KZ_CONFIG_SECTION) != orxFALSE)
  && (orxConfig_PushSection(orxSCREENSHOT_KZ_CONFIG_SECTION) != orxSTATUS_FAILURE))
  {
    orxSTRING zValue;
    orxU32    u32Value;

    /* Gets directory name */
    zValue = orxConfig_GetString(orxSCREENSHOT_KZ_CONFIG_DIRECTORY);

    /* Valid? */
    if((zValue != orxNULL) && (zValue != orxSTRING_EMPTY))
    {
      /* Stores it */
      zDirectory = zValue;
    }

    /* Gets screenshot base name */
    zValue = orxConfig_GetString(orxSCREENSHOT_KZ_CONFIG_BASE_NAME);

    /* Valid? */
    if((zValue != orxNULL) && (zValue != orxSTRING_EMPTY))
    {
      /* Stores it */
      zBaseName = zValue;
    }

    /* Gets screenshot extension */
    zValue = orxConfig_GetString(orxSCREENSHOT_KZ_CONFIG_EXTENSION);

    /* Valid? */
    if((zValue != orxNULL) && (zValue != orxSTRING_EMPTY))
    {
      /* Stores it */
      zExtension = zValue;
    }

    /* Gets digit number */
    if((u32Value = orxConfig_GetU32(orxSCREENSHOT_KZ_CONFIG_DIGITS)) > 0)
    {
      /* Stores it */
      u32Digits = u32Value;
    }

    /* Pops previous section */
    orxConfig_PopSection();
  }

  /* Valid? */
  if(orxFileSystem_Exists(zDirectory) != orxFALSE)
  {
    do
    {
      /* Gets file to find name */
      orxString_NPrint(sstScreenshot.acScreenshotBuffer, orxSCREENSHOT_KU32_BUFFER_SIZE, "%s/%s%0*ld.%s", zDirectory, zBaseName, u32Digits, sstScreenshot.u32ScreenshotIndex + 1, zExtension);

      /* Updates screenshot index */
      sstScreenshot.u32ScreenshotIndex++;
    }
    /* Till not found */
    while(orxFileSystem_Exists(sstScreenshot.acScreenshotBuffer) != orxFALSE);
  }
  else
  {
    /* Logs message */
    orxDEBUG_PRINT(orxDEBUG_LEVEL_SCREENSHOT, "Invalid directory [%s]. Please create it to enable screenshots.", zDirectory);

    /* Can't find folder */
    eResult = orxSTATUS_FAILURE;
  }

  /* Done! */
  return eResult;
}

/***************************************************************************
 * Public functions                                                        *
 ***************************************************************************/

/** Screenshot module setup
 */
void orxFASTCALL orxScreenshot_Setup()
{
  /* Adds module dependencies */
  orxModule_AddDependency(orxMODULE_ID_SCREENSHOT, orxMODULE_ID_MEMORY);
  orxModule_AddDependency(orxMODULE_ID_SCREENSHOT, orxMODULE_ID_CONFIG);
  orxModule_AddDependency(orxMODULE_ID_SCREENSHOT, orxMODULE_ID_FILESYSTEM);
  orxModule_AddDependency(orxMODULE_ID_SCREENSHOT, orxMODULE_ID_DISPLAY);

  return;
}

/** Inits the screenshot module
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
orxSTATUS orxFASTCALL orxScreenshot_Init()
{
  orxSTATUS eResult = orxSTATUS_FAILURE;

  /* Not already Initialized? */
  if(!(sstScreenshot.u32Flags & orxSCREENSHOT_KU32_STATIC_FLAG_READY))
  {
    /* Cleans control structure */
    orxMemory_Zero(&sstScreenshot, sizeof(orxSCREENSHOT_STATIC));

    /* Inits flags */
    sstScreenshot.u32Flags = orxSCREENSHOT_KU32_STATIC_FLAG_READY;
  }
  else
  {
    /* Logs message */
    orxDEBUG_PRINT(orxDEBUG_LEVEL_SCREENSHOT, "Tried to initalize Screenshot module when it was already initialized.");

    /* Already initialized */
    eResult = orxSTATUS_SUCCESS;
  }

  /* Done! */
  return eResult;
}

/** Exits from the screenshot module
 */
void orxFASTCALL orxScreenshot_Exit()
{
  /* Initialized? */
  if(sstScreenshot.u32Flags & orxSCREENSHOT_KU32_STATIC_FLAG_READY)
  {
    /* Updates flags */
    sstScreenshot.u32Flags &= ~orxSCREENSHOT_KU32_STATIC_FLAG_READY;
  }
  else
  {
    /* Logs message */
    orxDEBUG_PRINT(orxDEBUG_LEVEL_SCREENSHOT, "Tried to exit from Screenshot module when it wasn't initialized.");
  }

  return;
}

/** Captures a screenshot
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
orxSTATUS orxFASTCALL orxScreenshot_Capture()
{
  orxSTATUS eResult;

  /* Checks */
  orxASSERT(sstScreenshot.u32Flags & orxSCREENSHOT_KU32_STATIC_FLAG_READY);

  /* Computes screenshot index */
  eResult = orxScreenshot_ComputeIndex();

  /* Valid? */
  if(eResult != orxSTATUS_FAILURE)
  {
    /* Saves it */
    eResult = orxDisplay_SaveBitmap(orxDisplay_GetScreenBitmap(), sstScreenshot.acScreenshotBuffer);

    /* Success? */
    if(eResult != orxSTATUS_FAILURE)
    {
      /* Logs */
      orxDEBUG_PRINT(orxDEBUG_LEVEL_SCREENSHOT, "Screenshot captured to [%s].", sstScreenshot.acScreenshotBuffer);
    }
  }

  /* Done! */
  return eResult;
}
