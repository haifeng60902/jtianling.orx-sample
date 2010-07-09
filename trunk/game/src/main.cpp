#include "orx.h"

#include <iostream>
#include <string>
using namespace std;
orxOBJECT* gPaddle;
class GameApp
{
public:
  static orxSTATUS orxFASTCALL  EventHandler(const orxEVENT *_pstEvent);
  static orxSTATUS orxFASTCALL  Init();
  static void orxFASTCALL       Exit();
  static orxSTATUS orxFASTCALL  Run();
  static void orxFASTCALL	Update(const orxCLOCK_INFO *_clock_info, void *_context);

  GameApp() {};
  ~GameApp() {};

  static GameApp* Instance() {
	  static GameApp instance;
	  return &instance;
  }

private:
  orxSTATUS                     InitGame();
};

#define BLOCK_TYPE 1

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
  orxSTATUS result = orxSTATUS_SUCCESS;
  orxCLOCK *pstClock = orxClock_Create(orx2F(0.05f), orxCLOCK_TYPE_USER);
  orxClock_Register(pstClock, GameApp::Update, NULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);


  // Creates viewport
  if ( orxViewport_CreateFromConfig("Viewport") == NULL ) {
	  result = orxSTATUS_FAILURE;
  }

  if (orxObject_CreateFromConfig("Ball") == NULL) {
	  result = orxSTATUS_FAILURE;
  }


  if ( (gPaddle = orxObject_CreateFromConfig("Paddle")) == NULL) {
	  result = orxSTATUS_FAILURE;
  }

  if (orxObject_CreateFromConfig("Blocks") == NULL) {
	  result = orxSTATUS_FAILURE;
  }

  if (orxObject_CreateFromConfig("Walls") == NULL) {
	  result = orxSTATUS_FAILURE;
  }

  orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, GameApp::EventHandler);
  // Done!
  return result;
}

// Event handler
orxSTATUS orxFASTCALL GameApp::EventHandler(const orxEVENT *_pstEvent)
{
	orxSTATUS eResult = orxSTATUS_SUCCESS;
	if(_pstEvent->eType == orxEVENT_TYPE_PHYSICS) {
		if( _pstEvent->eID == orxPHYSICS_EVENT_CONTACT_REMOVE ) {
			/* Gets colliding objects */
			orxOBJECT *object_recipient = orxOBJECT(_pstEvent->hRecipient);
			orxOBJECT *object_sender = orxOBJECT(_pstEvent->hSender);

			string recipient_name(orxObject_GetName(object_recipient));
			string sender_name(orxObject_GetName(object_sender));
			if(sender_name.substr(0, sender_name.length()-1) == "Block") {
				// 这样比直接删除要安全
				orxObject_SetLifeTime(object_sender, orxFLOAT_0);
			}
		}
	}
  // Done!
  return orxSTATUS_SUCCESS;
}

void GameApp::Update(const orxCLOCK_INFO *_clock_info, void *_context) 
{
#define MOVE_SPEED 10
	if( orxInput_IsActive("GoLeft") ) {
	orxVECTOR pos;
	orxObject_GetPosition(gPaddle, &pos);
	pos.fX -= MOVE_SPEED;
	orxObject_SetPosition(gPaddle, &pos);

	} if (orxInput_IsActive("GoRight")) {
	orxVECTOR pos;
	orxObject_GetPosition(gPaddle, &pos);
	pos.fX += MOVE_SPEED;
	orxObject_SetPosition(gPaddle, &pos);
	}
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
