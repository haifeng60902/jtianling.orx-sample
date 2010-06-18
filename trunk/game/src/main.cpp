#include "orx.h"

#include <iostream>

class GameApp
{
public:
  static orxSTATUS orxFASTCALL  EventHandler(const orxEVENT *_pstEvent);
  static orxSTATUS orxFASTCALL  Init();
  static void orxFASTCALL       Exit();
  static orxSTATUS orxFASTCALL  Run();

  GameApp() {};
  ~GameApp() {};

  static GameApp* Instance() {
	  static GameApp instance;
	  return &instance;
  }

private:
  orxSTATUS                     InitGame();
};


orxOBJECT *CreateText(orxSTRING _zTextSection)
{
	orxConfig_PushSection(_zTextSection);
	orxConfig_SetString("Graphic", _zTextSection);
	orxConfig_SetString("Text", _zTextSection);

	orxOBJECT *pstReturn = orxObject_CreateFromConfig(_zTextSection);

	orxConfig_PopSection();

	return pstReturn;
}

// Init game function
orxSTATUS GameApp::InitGame()
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;
  
  // Creates viewport
  if ( orxViewport_CreateFromConfig("Viewport") == NULL ) {
	  eResult = orxSTATUS_FAILURE;
  }

  if ( CreateText("HelloWorld") == NULL) {
	  eResult = orxSTATUS_FAILURE;
  }

  // Done!
  return eResult;
}

// Event handler
orxSTATUS orxFASTCALL GameApp::EventHandler(const orxEVENT *_pstEvent)
{

  // Done!
  return orxSTATUS_SUCCESS;
}

// Init function
orxSTATUS GameApp::Init()
{
  orxSTATUS     eResult;
  orxINPUT_TYPE eType;
  orxENUM       eID;

  /* Gets input binding names */
  orxInput_GetBinding("Quit", 0, &eType, &eID);
  const orxSTRING zInputQuit = orxInput_GetBindingName(eType, eID);

  // Logs
  orxLOG("\n- '%s' will exit from this tutorial"
         "\n* The legend under the logo is always displayed in the current language", zInputQuit );

  orxLOG("Init() called!");

  // Inits our stand alone game
  eResult = GameApp::Instance()->InitGame();

  // Done!
  return eResult;
}

// Exit function
void GameApp::Exit()
{

  // Logs
  orxLOG("Exit() called!");
}

// Run function
orxSTATUS GameApp::Run()
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;


  // Done!
  return eResult;
}


// Main program function
int main(int argc, char **argv)
{
  // Inits and runs orx using our self-defined functions
  orx_Execute(argc, argv, GameApp::Init, GameApp::Run, GameApp::Exit);

  // Done!
  return EXIT_SUCCESS;
}


#ifdef __orxMSVC__

// Here's an example for a console-less program under windows with visual studio
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  // Inits and executes orx
  orx_WinExecute(GameApp::Init, GameApp::Run, GameApp::Exit);

  // Done!
  return EXIT_SUCCESS;
}

#endif // __orxMSVC__
